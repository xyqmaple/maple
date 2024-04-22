#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>

static struct tasklet_struct c_tasklet;

static void c_tasklet_handler(unsigned long data)
{
	pr_info("%s: Succeed in executing tasklet!\n", __func__);
}

static int __init c_tasklet_init(void)
{
	tasklet_init(&c_tasklet, c_tasklet_handler, 0);
	tasklet_schedule(&c_tasklet);

	pr_info("%s: Insmod successful!\n", __func__);
	return 0;
}
module_init(c_tasklet_init);

static void __exit c_tasklet_exit(void)
{
	tasklet_kill(&c_tasklet);
	pr_info("%s: Rmmod successful!\n", __func__);
}
module_exit(c_tasklet_exit);

MODULE_LICENSE("GPL");

