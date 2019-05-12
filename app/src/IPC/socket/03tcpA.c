// 实现基于tcp协议的通信模型
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	//1.创建socket,使用socket()
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");
	//2.准备通信地址，使用结构体类型
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("192.168.43.22");
	//3.绑定socket和通信地址，使用bind()
	int res = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(-1 == res)
	{
		perror("bind"),exit(-1);
	}
	printf("绑定成功\n");
	//4.监听,使用listen()
	res = listen(sockfd, 100);
	if(-1 == res)
	{
		perror("listen"),exit(-1);
	}
	printf("监听成功\n");
	//5.响应客户端的连接请求，使用accept()
	struct sockaddr_in recv_addr;
	socklen_t len = sizeof(recv_addr);
	int fd = accept(sockfd, (struct sockaddr*)&recv_addr, &len);
	if(-1 == fd)
	{
		perror("accept"),exit(-1);
	}
	char* ip = inet_ntoa(recv_addr.sin_addr);
	printf("客户端%s连接成功...\n", ip);
	//6.进行通信，使用send()/recv()
	char buf[100] = {0};
	res = recv(fd, buf, sizeof(buf), 0);
	if(-1 == res)
	{
		perror("recv"),exit(-1);
	}
	printf("客户端发来的数据是:%s,数据大小是:%d\n", buf, res);
	res = send(fd, "I received!", 11, 0);
	if(-1 == res)
	{
		perror("send"),exit(-1);
	}
	printf("成功发送数据到客户端，发送的数据大小是：%d\n", res);
	//7.关闭socket,使用close()
	res = close(fd);
	if(-1 == res)
	{
		perror("close"),exit(-1);
	}
	res = close(sockfd);
	if(-1 == res)
	{
		perror("close"),exit(-1);
	}
	printf("成功关闭socket\n");
	return 0;
}
