//使用消息队列实现进程间的通信
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

//定义消息的数据类型
typedef struct
{
	long mtype;		// 消息的类型
	char buf[20];		// 消息的内容
}Msg;

int main(void)
{
	//1.获取key值，使用ftok()
	key_t key = ftok(".", 150);
	if(-1 == key)
	{
		perror("ftok"),exit(-1);
	}
	printf("key = %#x\n", key);

	//2.获取消息队列，使用msgget()
	int msqid = msgget(key, 0);
	if(-1 == msqid)
	{
		perror("msgget"),exit(-1);
	}
	printf("msqid = %d\n", msqid);

	//3.接收消息到消息队列中，使用msgsnd()
	Msg msg = {};
	// 始终接收消息队列中第一个消息
	//int res = msgrcv(msqid, &msg, sizeof(msg.buf), 0, 0);
	// 始终接收消息队列中第一个类型为2的消息
	//int res = msgrcv(msqid, &msg, sizeof(msg.buf), 2, 0);
	// 始终接收类型小于等于-2绝对值的消息
	int res = msgrcv(msqid, &msg, sizeof(msg.buf), -2, 0);
	if(-1 == res)
	{
		perror("msgsnd"),exit(-1);
	}
	printf("接收到的消息类型是：%ld,消息内容是：%s\n", msg.mtype, msg.buf);

	return 0;
}

