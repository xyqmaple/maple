/**
 * @file core.c
 * @author yeqiang_xu <yeqiang_xu@maxio-tech.com>
 * @brief 
 * @version 0.1
 * @date 2024-04-23
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/random.h>
#include <linux/fs.h>
#include "mod_cfg.h"

#ifdef CONFIG_PRIV_FILE_PATH
#define FILE_PATH	CONFIG_PRIV_FILE_PATH
#else
#define FILE_PATH	"/tmp/data.bin"
#endif
#define DATA_LENTH	512

static int file_write(struct file *fp, const void *buf, size_t size)
{
	ssize_t ret;

	ret = kernel_write(fp, buf, size, NULL);
	if (ret != size) {
		pr_err("Total:%lu, Written:%ld\n", size, ret);
		return -EIO;
	}
	return 0;
}

static int file_random_write(struct file *fp, size_t size)
{
	int ret;
	void *buf;

	buf = kmalloc(size, GFP_KERNEL);
	if (!buf) {
		pr_err("No memory!\n");
		return -ENOMEM;
	}
	get_random_bytes(buf, size);

	ret = file_write(fp, buf, size);

	kfree(buf);
	return ret;
}

static struct file *file_open(const char *path)
{
	struct file *fp;

	fp = filp_open(path, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (IS_ERR(fp))
		pr_err("ERR-%ld: open '%s'!\n", PTR_ERR(fp), path);

	return fp;
}

static int file_close(struct file *fp)
{
	int ret;

	ret = filp_close(fp, NULL);
	if (ret)
		pr_err("ERR-%d: close!\n", ret);

	return ret;
}

static int __init rwfile_init(void)
{
	struct file *fp;

	fp = file_open(FILE_PATH);
	if (IS_ERR(fp))
		return PTR_ERR(fp);
	
	file_random_write(fp, DATA_LENTH);

	file_close(fp);
	return 0;
}
module_init(rwfile_init);

static void __exit rwfile_exit(void)
{

}
module_exit(rwfile_exit);

MODULE_LICENSE("GPL");
