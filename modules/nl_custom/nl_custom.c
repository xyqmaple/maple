#include <linux/kernel.h>
#include <linux/module.h>
#include <net/netlink.h>
#include <net/net_namespace.h>

#include "nl_custom.h"

static struct sock *sk = NULL;

static void nl_custom_recv_msg(struct sk_buff *skb)
{
	struct sk_buff *send_skb = NULL;
	struct nlmsghdr *nlh = NULL, *send_nlh = NULL;
	struct custom_nlmsg_info *nlmsg = NULL;

	nlh = nlmsg_hdr(skb);
	nlmsg = nlmsg_data(nlh);

	switch (nlh->nlmsg_type) {

	case NLMSG_TYPE_STRING:
		pr_info("%s: Recieve: %s, From: %d, payload: %d\n", __func__,
			nlmsg->str, nlh->nlmsg_pid, nlmsg_len(nlh));

		send_skb = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
		if (!send_skb) {
			pr_err("%s: nlmsg_new failed!\n", __func__);
			return;
		}
		send_nlh = nlmsg_put(send_skb, 0, 0, NLMSG_TYPE_STRING, nlmsg_len(nlh), 0);
		if (!send_nlh) {
			pr_err("%s: nlmsg_put failed!\n", __func__);
			return;
		}

		strcpy(nlmsg_data(send_nlh), "[from kernel]: I have received!");

		nlmsg_unicast(sk, send_skb, nlh->nlmsg_pid);

		break;

	default:
		pr_err("%s: msg_type %u is not support", __func__, nlh->nlmsg_type);
	}
}

static struct netlink_kernel_cfg nlcfg = {
	.input = nl_custom_recv_msg,
};

static int __init nl_custom_init(void)
{
	sk = netlink_kernel_create(&init_net, NETLINK_TEST, &nlcfg);
	if (!sk) {
		pr_err("%s: netlink_kernel_create failed!\n", __func__);
		return -EFAULT;
	}

	pr_info("%s: insmod successful!\n", __func__);
	return 0;
}
module_init(nl_custom_init);

static void __exit nl_custom_exit(void)
{
	netlink_kernel_release(sk);
	pr_info("%s: rmmod successful!\n", __func__);
}
module_exit(nl_custom_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("yeqiang_xu");
MODULE_DESCRIPTION("Custom netlink driver");
MODULE_VERSION("1.8.6");

