// 实现基于socket的网络通信
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
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");
	//2.准备通信地址,使用结构体类型
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr = inet_addr("192.168.43.153");
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
	printf("读取数据成功，读取到的数据是:%s,数据的大小是:%d\n", buf, res);
	//5.关闭socket,使用close()
	res = close(sockfd);
	if(-1 == res)
	{
		perror("close"),exit(-1);
	}
	printf("成功关闭socket\n");
	return 0;
}
