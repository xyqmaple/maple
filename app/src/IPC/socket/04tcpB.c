// 实现基于tcp协议的通信模型
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
	//1.创建socket，使用socket()
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");
	//2.准备通信地址，使用服务器的地址
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("192.168.43.22");
	//3.连接socket和通信地址，使用connect()
	int res = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(-1 == res)
	{
		perror("connect"),exit(-1);
	}
	printf("连接成功\n");
	//4.进行通信，使用send()/recv()
	while(1)
	{
		char msg[200] = {0};
		printf("请输入要发送的内容:\n");
		scanf("%s", msg);
		res = send(sockfd, msg, strlen(msg), 0);
		if(-1 == res)
		{
			perror("send"),exit(-1);
		}
		printf("成功发送数据到服务器，发送的数据大小是:%d\n", res);
		//判断当客户端发送"bye"时，则下线
		if(!strcmp(msg, "bye"))
		{
			break;  //结束通信
		}
		char buf[100] = {0};
		res = recv(sockfd, buf, sizeof(buf), 0);
		if(-1 == res)
		{
			perror("recv"),exit(-1);
		}
		printf("服务器发来的数据是:%s,数据大小是:%d\n", buf, res);
	}
	//5.关闭socket,使用close()
	res = close(sockfd);
	if(-1 == res)
	{
		perror("close"),exit(-1);
	}
	printf("成功关闭socket\n");
	return 0;
}
