#ifndef __CUSTOM_NETLINK_H__
#define __CUSTOM_NETLINK_H__

/* Custom netlink protocol. */
#define NETLINK_TEST			(31)

/* Custom netlink msg type. */
#define NLMSG_TYPE_STRING		(0x11)

#define NLMSG_STRING_SIZE		(64)

struct custom_nlmsg_info {
	union {
		char str[NLMSG_STRING_SIZE];
	};
};
#define CUSTOM_MAX_PAYLOAD		(sizeof(struct custom_nlmsg_info))

#endif /* __CUSTOM_NETLINK_H__ */

