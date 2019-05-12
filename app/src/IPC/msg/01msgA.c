#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

//定义全局变量记录消息队列的ID
int msqid;

//定义消息的数据类型
typedef struct
{
	long mtype;		// 消息的类型
	char buf[20];		// 消息的内容
} Msg;

void fa(int signum)
{
	printf("正在删除消息队列，请稍后...\n");
	sleep(3);
	//调用msgctl()实现删除
	int res = msgctl(msqid, IPC_RMID, NULL);
	if(-1 == res)
	{
		perror("msgctl"),exit(-1);
	}
	printf("删除消息队列成功\n");
	exit(0);
}


int main(void)
{
	//1.获取key值，使用ftok()
	key_t key = ftok(".", 150);
	if(-1 == key)
	{
		perror("ftok"),exit(-1);
	}
	printf("key = %#x\n", key);

	//2.创建消息队列，使用msgget()
	msqid = msgget(key, IPC_CREAT|IPC_EXCL|0664);
	if(-1 == msqid)
	{
		perror("msgget"),exit(-1);
	}
	printf("msqid = %d\n", msqid);

	//3.发送消息到消息队列中，使用msgsnd()
	Msg msg1 = {1, "hello"};
	Msg msg2 = {2, "world"};
	int res = msgsnd(msqid, &msg2, sizeof(msg2.buf), 0);
	if(-1 == res)
	{
		perror("msgsnd"),exit(-1);
	}
	printf("发送消息2到消息队列成功\n");

	res = msgsnd(msqid, &msg1, sizeof(msg1.buf), 0);
	if(-1 == res)
	{
		perror("msgsnd"),exit(-1);
	}
	printf("发送消息1到消息队列成功\n");

	//4.如果不再使用，删除消息队列，msgctl()
	printf("删除队列请按ctrl+c...\n");
	if(SIG_ERR == signal(SIGINT, fa))
	{
		perror("signal"),exit(-1);
	}
	while(1);
	return 0;
}

