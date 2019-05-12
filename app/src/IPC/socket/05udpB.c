//实现基于udp协议的网络通信模型
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	//1.创建socket，使用socket()
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");
	//2.准备通信地址，使用服务器的地址
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("172.30.3.105");
	//3.进行通信，send()/sendto()/recv/recvfrom
	//int res = send(socket, "hello", 5, 0);
	int res = sendto(socket, "hello", 5, 0, (struct sockaddr*)&addr, sizeof(addr));
	if(-1 == res)
	{
		perror("sendto"),exit(-1);
	}
	printf("成功发送数据到服务器，发送的数据大小是:%d\n", res);
	//接受服务器回发的消息
	char buf[100] = {0};
	res = recv(sockfd, buf, sizeof(buf), 0);
	if(-1 == res)
	{
		perror("recv"),exit(-1);
	}
	printf("服务器发来的消息是：%s，大小是：%d\n", buf, res);
	//4.关闭socket,使用close()
	res = close(sockfd);
	if(-1 == res)
	{
		perror("close"),exit(-1);
	}
	printf("成功关闭socket\n");
	return 0;
}









