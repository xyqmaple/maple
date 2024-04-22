#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/stddef.h>

#define WORK_QUEUE_NAME "wq_custom"

#ifndef CONFIG_CUSTOM_DELAY_WORK
static struct work_struct ws_custom = {};
#else
#define WORK_QUEUE_DELAY_TIME 1000
static struct delayed_work dw_custom = {};
#endif /* CONFIG_CUSTOM_DELAY_WORK */

static struct workqueue_struct *wq_custom = NULL;

#ifndef CONFIG_CUSTOM_DELAY_WORK
static void work_func(struct work_struct *work)
{
	pr_info("%s: Succeed in executing work!\n", __func__);
}
#else
static void delay_work_func(struct work_struct *work)
{
	pr_info("%s: Succeed in executing delay work!\n", __func__);
}
#endif /* CONFIG_CUSTOM_DELAY_WORK */

static int __init wq_custom_init(void)
{
	wq_custom = create_workqueue(WORK_QUEUE_NAME);
	if (!wq_custom) {
		pr_err("%s: Failed to create workqueue which named %s!\n", 
			__func__, WORK_QUEUE_NAME);
		return -EFAULT;
	}
	pr_info("%s: Succeed in creating workqueue which named %s!\n",
		__func__, WORK_QUEUE_NAME);

#ifndef CONFIG_CUSTOM_DELAY_WORK
	INIT_WORK(&ws_custom, work_func);
#else
	INIT_DELAYED_WORK(&dw_custom, delay_work_func);

	if (false == queue_delayed_work(wq_custom, &dw_custom, WORK_QUEUE_DELAY_TIME)) {
		pr_err("%s: Failed to set workqueue delay time!\n", __func__);
		return -EPERM;
	}
#endif /* CONFIG_CUSTOM_DELAY_WORK */

	pr_info("%s: Insmod successful!\n", __func__);
	return 0;
}
module_init(wq_custom_init);

static void __exit wq_custom_exit(void)
{
#ifndef CONFIG_CUSTOM_DELAY_WORK
	if (false == cancel_work(&ws_custom)) {
#else
	if (false == cancel_delayed_work(&dw_custom)) {
#endif /* CONFIG_CUSTOM_DELAY_WORK */
		pr_err("%s: Failed to cancel work!\n", __func__);
	}
	flush_workqueue(wq_custom);
	destroy_workqueue(wq_custom);

	pr_info("%s: Rmmod successful!\n", __func__);
}
module_exit(wq_custom_exit);

MODULE_LICENSE("GPL");

