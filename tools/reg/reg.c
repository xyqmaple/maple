#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEV_MEM_PATH                                    "/dev/mem"

#define REG_MMAP_ALIGN                                  0x1000
#define REG_MMAP_SIZE                                   0x1000

#define REG_ADDR_ALIGN                                  0x4

#define ERR(fmt, ...) printf("[E][%s,%d]" fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#define WARN(fmt, ...) printf("[W][%s,%d]" fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#define NOTICE(fmt, ...) printf("[N][%s,%d]" fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#define INFO(fmt, ...) printf("[I]" fmt "\n", ##__VA_ARGS__)
#ifdef DEBUG
#define DBG(fmt, ...) printf("[D][%s,%d]" fmt "\n", __func__, __LINE__, ##__VA_ARGS__)
#else
#define DBG(fmt, ...)
#endif

#define ALIGN_DOWN(_val, _align)                ((_val) & ~((_align) - 1))
#define ALIGN_UP(_val, _align)                  (((_val) + (_align) - 1) & ~((_align) - 1))

#define IS_ALIGN(_val, _align)                  (!((_val) & ((_align) - 1)))

enum usr_option {
        USR_OPT_REG_READ,
        USR_OPT_REG_WRITE,
};

struct reg_cfg {
        /* The register address to be mapped. */
        unsigned int mmap_phy_addr;

        unsigned int mmap_phy_size;
        /* The virtual address after @mmap_phy_addr mapped. */
        volatile unsigned int *mmap_virt_addr;

        unsigned int usr_option;
        /* The register address need to be accessed. */
        unsigned int usr_addr;
        /* The register value need to be assigned to @usr_addr */
        unsigned int usr_value;
        /* The register range need to be accessed. */
        unsigned int usr_range;
};

static struct reg_cfg g_reginfo = {};

static void usage(void)
{
        printf( "Usage:\n"
                        "\treg r <addr> [length]\n"
                        "\treg w <addr> <value>\n");
}

static int parse_param(int argc, char *argv[])
{
        char *option = argv[1];

        if (!strncmp(option, "r", 1))
                g_reginfo.usr_option = USR_OPT_REG_READ;
        else if (!strncmp(option, "w", 1))
                g_reginfo.usr_option = USR_OPT_REG_WRITE;
        else
                return -EINVAL;

        switch (argc) {
        case 4:
                if (g_reginfo.usr_option == USR_OPT_REG_READ) {
                        g_reginfo.usr_range = ALIGN_UP(strtol(argv[3], NULL, 0), REG_ADDR_ALIGN);
                } else if (g_reginfo.usr_option == USR_OPT_REG_WRITE) {
                        g_reginfo.usr_value = strtol(argv[3], NULL, 0);
                        g_reginfo.usr_range = 0x4;
                }
                break;
        case 3:
                if (g_reginfo.usr_option == USR_OPT_REG_READ)
                        g_reginfo.usr_range = 0x4;
                break;
        }

        g_reginfo.usr_addr = strtol(argv[2], NULL, 0);
        if (!IS_ALIGN(g_reginfo.usr_addr, REG_ADDR_ALIGN)) {
                ERR("usr_addr(0x%08x) not align to 0x%xByte!", 
                        g_reginfo.usr_addr, REG_ADDR_ALIGN);
                return -EINVAL;
        }

        g_reginfo.mmap_phy_addr = ALIGN_DOWN(g_reginfo.usr_addr, REG_MMAP_ALIGN);
        g_reginfo.mmap_phy_size = ALIGN_UP(g_reginfo.usr_addr + g_reginfo.usr_range, 
                REG_MMAP_ALIGN) - g_reginfo.mmap_phy_addr;

        return 0;
}

static int do_reg_read(void)
{
        int i;
        unsigned int offset = 0;
        volatile unsigned int *virt_addr = NULL;

        offset = (g_reginfo.usr_addr - g_reginfo.mmap_phy_addr) / REG_ADDR_ALIGN;
        virt_addr = g_reginfo.mmap_virt_addr + offset;

        printf("\nreg_range:0x%08x + 0x%x\n", g_reginfo.usr_addr, g_reginfo.usr_range);

        for (i = 0; (4 * i) < g_reginfo.usr_range; i++) {
                if (!(i % 4)) {
                        printf("\n0x%08x: ", g_reginfo.usr_addr + 4 * i);
                }
                printf("%08x  ", *(virt_addr + i));
        }
        printf("\n");

        return 0;
}

static int do_reg_write(void)
{
        unsigned int offset = 0;
        volatile unsigned int *virt_addr = NULL;

        offset = (g_reginfo.usr_addr - g_reginfo.mmap_phy_addr) / REG_ADDR_ALIGN;
        virt_addr = g_reginfo.mmap_virt_addr + offset;

        *virt_addr = g_reginfo.usr_value;
        return 0;
}

static int do_opt(void)
{
        int ret;

        switch (g_reginfo.usr_option)
        {
                case USR_OPT_REG_READ:
                        ret = do_reg_read();
                        break;

                case USR_OPT_REG_WRITE:
                        ret = do_reg_write();
                        break;

                default:
                        return -EINVAL;
        }

        return ret;
}

int main(int argc, char *argv[])
{
        int fd = -1;

        if (argc < 2 || parse_param(argc, argv)) {
                usage();
                return -EINVAL;
        }

        DBG("open %s...", DEV_MEM_PATH);
        fd = open(DEV_MEM_PATH, O_RDWR | O_NDELAY);
        if (fd < 0) {
                ERR("open %s err!(%d,%s)", DEV_MEM_PATH, fd, strerror(errno));
                return fd;
        }
        DBG("mmap phy addr:0x%x size:0x%x", 
                g_reginfo.mmap_phy_addr, g_reginfo.mmap_phy_size);

        g_reginfo.mmap_virt_addr = (volatile unsigned int *)mmap(NULL, g_reginfo.mmap_phy_size, 
                PROT_READ | PROT_WRITE, MAP_SHARED, fd, g_reginfo.mmap_phy_addr);
        if (MAP_FAILED == g_reginfo.mmap_virt_addr) {
                ERR("mmap err!(%s)", strerror(errno));
                goto out;
        }
        do_opt();

        munmap((void *)g_reginfo.mmap_virt_addr, g_reginfo.mmap_phy_size);
        g_reginfo.mmap_virt_addr = NULL;
out:
        close(fd);
        return 0;
}