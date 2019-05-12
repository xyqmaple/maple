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
	//2.准备通信地址，使用结构体类型
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("172.30.3.105");
	//3.绑定socket和通信地址，使用bind()
	int res = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(-1 == res)
	{
		perror("bind"),exit(-1);
	}
	printf("绑定成功\n");
	//4.进行通信，send()/sendto()/recv/recvfrom
	char buf[100] = {0};
	//准备结构体变量和大小的变量
	struct sockaddr_in recv_addr;
	socklen_t len = sizeof(recv_addr);
	//res = recv(socket, buf, sizeof(buf), 0);
	res = recvfrom(socket, buf, sizeof(buf), 0, (struct sockaddr*)&recv_addr, &len);
	if(-1 == res)
	{
		perror("recvfrom"),exit(-1);
	}
	printf("客户端发来的数据是：%s,数据大小是:%d\n", buf, res);
	//如何实现向客户端回发消息呢???
	res = sendto(sockfd, "I received!", 11, 0, (struct sockaddr*)&recv_addr, len);
	if(-1 == res)
	{
		perror("sendto"),exit(-1);
	}
	printf("成功发送数据到客户端，发送的数据大小是：%d\n", res);
	//5.关闭socket,使用close()
	res = close(sockfd);
	if(-1 == res)
	{
		perror("close"),exit(-1);
	}
	printf("成功关闭socket\n");
	return 0;
}









