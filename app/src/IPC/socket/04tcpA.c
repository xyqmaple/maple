
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

//定义全局变量记录socket的描述符
int sockfd;

void fa(int signum)
{
	printf("正在关闭服务器，请稍后...\n");
	sleep(3);
	//7.关闭socket,使用close()
	int res = close(sockfd);
	if(-1 == res)
	{
		perror("close"),exit(-1);
	}
	printf("成功关闭服务器\n");
	exit(0);
}

int main(void)
{
	//1.创建socket,使用socket()
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sockfd)
	{
		perror("socket"),exit(-1);
	}
	printf("创建socket成功\n");
	//2.准备通信地址，使用结构体类型
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8888);
	addr.sin_addr.s_addr= inet_addr("192.168.43.22");
	//3.绑定socket和通信地址，使用bind()
	int res = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
	if(-1 == res)
	{
		perror("bind"),exit(-1);
	}
	printf("绑定成功\n");
	//4.监听，使用listen()
	res = listen(sockfd, 100);
	if(-1 == res)
	{
		perror("listen"),exit(-1);
	}
	printf("监听成功\n");
	//通过自定义信号处理方式来关闭服务器
	printf("关闭服务器，请按ctrl+c...\n");
	if(SIG_ERR == signal(SIGINT, fa))
	{
		perror("signal"),exit(-1);
	}
	//5.不断地响应客户端的连接请求，使用accept()
	while(1)
	{
		struct sockaddr_in recv_addr;
		socklen_t len = sizeof(recv_addr);
		int fd = accept(sockfd, (struct sockaddr*)&recv_addr, &len);
		if(-1 == fd)
		{
			perror("accept"),exit(-1);
		}
		char* ip = inet_ntoa(recv_addr.sin_addr);
		printf("客户端%s连接成功...\n", ip);
		// 创建子进程和客户端进行通信，fork()
		pid_t pid = fork();
		if(-1 == pid)
		{
			perror("fork"),exit(-1);
		}
		// 子进程
		if(0 == pid)
		{
			//设置对信号SIGINT进行默认处理
			if(SIG_ERR == signal(SIGINT, SIG_DFL))
			{
				perror("signal"),exit(-1);
			}
			//关闭用于监听的socket描述符
			res = close(sockfd);
			if(-1 == res)
			{
				perror("close"),exit(-1);
			}
			//6.针对每个客户端不断通信，使用send()/recv()
			while(1)
			{
				char buf[100] = {};
				res = recv(fd, buf, sizeof(buf), 0);
				if(-1 == res)
				{
					perror("recv"),exit(-1);
				}
				printf("客户端%s发来的数据是：%s\n", ip, buf);
				//判断客户端发来的是否"bye"
				if(!strcmp(buf, "bye"))
				{
					printf("客户端%s已下线\n", ip);
					break;  //跳出无限循环
				}
				//向客户端回发消息
				res = send(fd, "I received!", 11, 0);
				if(-1 == res)
				{
					perror("send"),exit(-1);
				}
			}
			//break执行后跳到了这里
			//关闭用于通信的socket描述符
			res = close(fd);
			if(-1 == res)
			{
				perror("close"),exit(-1);
			}
			//终止子进程
			exit(0);
		}
		//父进程执行的代码
		//关闭用于通信的描述符
		res = close(fd);
		if(-1 == res)
		{
			perror("close"),exit(-1);
		}
	}
	return 0;
}
