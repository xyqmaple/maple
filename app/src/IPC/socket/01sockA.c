// 实现基于socket的本地通信
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(void)
{
	//1.创建socket,使用socket()
	int sockfd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");
	//2.准备通信地址，使用结构体类型
	struct sockaddr_un addr;
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, "a.sock");
	//3.绑定socket和通信地址，使用bind()
	int res = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(-1 == res)
	{
		perror("bind"),exit(-1);
	}
	printf("绑定socket和通信地址成功\n");
	//4.进行通信，使用read()/write()
	char buf[100] = {0};
	res = read(sockfd, buf, sizeof(buf));
	if(-1 == res)
	{
		perror("read"),exit(-1);
	}
	printf("读取到的消息内容是：%s,消息大小是：%d\n", buf, res);
	//5.关闭socket,使用close()
	res = close(sockfd);
	if(-1 == res)
	{
		perror("close"),exit(-1);
	}
	printf("成功关闭socket\n");
	return 0;
}
