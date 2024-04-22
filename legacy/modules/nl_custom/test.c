#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/netlink.h>

#include "nl_custom.h"

static void *zalloc(size_t size)
{
	return calloc(1, size);
}

static void usage(void)
{
	printf("Usage: ./a.out <msg>\n");
	exit(1);
}

int main(int argc, char *argv[])
{
	int sockfd = -1, ret = 0, len = 0;
	struct nlmsghdr *nlh = NULL;
	struct sockaddr_nl src_addr = {}, dst_addr = {};

	if (argc < 2) {
		usage();
	}

	sockfd = socket(AF_NETLINK, SOCK_RAW, NETLINK_TEST);
	if (sockfd < 0) {
		printf("%s: socket failed!\n", __func__);
		return -1;
	}

	/* Init sender's address information. */
	src_addr.nl_family = AF_NETLINK;
	src_addr.nl_pid = getpid(); // port number
	src_addr.nl_groups = 0;

	ret = bind(sockfd, (struct sockaddr *)&src_addr, sizeof(struct sockaddr_nl));
	if (ret < 0) {
		printf("%s: bind failed!\n", __func__);
		goto out;
	}

	/* Init receiver's address information. */
	dst_addr.nl_family = AF_NETLINK;
	dst_addr.nl_pid = 0; // port number (0 - sendto kernel)
	dst_addr.nl_groups = 0;

	nlh = zalloc(NLMSG_SPACE(CUSTOM_MAX_PAYLOAD));
	if (!nlh) {
		printf("%s: zmalloc failed!\n", __func__);
		goto out;
	}
	nlh->nlmsg_flags = 0;
	nlh->nlmsg_len = NLMSG_SPACE(CUSTOM_MAX_PAYLOAD);
	nlh->nlmsg_pid = src_addr.nl_pid;
	nlh->nlmsg_seq = 0;
	nlh->nlmsg_type = NLMSG_TYPE_STRING;

	/* Fill in messages that need to be sent. */
	strncpy(((struct custom_nlmsg_info *)NLMSG_DATA(nlh))->str, argv[1], 
		sizeof(((struct custom_nlmsg_info *)0)->str) - 1);

	ret = sendto(sockfd, nlh, nlh->nlmsg_len, 0, (struct sockaddr *)&dst_addr,
		sizeof(struct sockaddr_nl));
	if (ret < 0) {
		printf("%s: sendto failed!\n", __func__);
		goto out;
	}
	printf("%s: sendto kernel: %s\n", __func__, argv[1]);
	
	len = sizeof(struct sockaddr_nl);
	memset(nlh, 0, NLMSG_SPACE(CUSTOM_MAX_PAYLOAD));

	ret = recvfrom(sockfd, nlh, NLMSG_SPACE(CUSTOM_MAX_PAYLOAD), 0, 
		(struct sockaddr *)&dst_addr, &len);
	if (ret < 0) {
		printf("%s: recvfrom failed!\n", __func__);
		goto out;
	}

	printf("Received message payload: %s\n", (char *)NLMSG_DATA(nlh));

out:
	close(sockfd);

	return 0;
}

