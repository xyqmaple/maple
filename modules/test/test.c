#include <linux/kernel.h>
#include <linux/module.h>

static int __init test_init(void)
{
	printk("%s\n", __func__);
	return 0;
}
module_init(test_init);

static void __exit test_exit(void)
{
	printk("%s\n", __func__);
}
module_exit(test_exit);

MODULE_LICENSE("Proprietary");

