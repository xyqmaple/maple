#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

//定义消息的数据类型
typedef struct
{
	long mtype;
	char buf[20];
} Msg;

int main(void)
{
	size_t size = 0;

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

	//3.接收消息，使用msgrcv()
	Msg msg1;
	do{
		size = msgrcv(msqid, &msg1, sizeof(msg1.buf), 0, 0);
		if(-1 == size)
		{
			perror("msgrcv"),exit(-1);
		}
		else if(size > 0)
		{
			printf("%s\n", msg1.buf);
		}
	}while(size != 0);

	return 0;
}

