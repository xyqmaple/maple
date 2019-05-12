//使用信号量集实现进程间的通信
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <signal.h>

//定义全局变量记录信号量集的ID
int semid;

void fa(int signum)
{
	printf("正在删除信号量集，请稍后...\n");
	sleep(3);
	int res = semctl(semid, 0, IPC_RMID);
	if(-1 == res)
	{
		perror("semctl"),exit(-1);
	}
	printf("删除信号量集成功\n");
	exit(0);
}

int main(void)
{
	//1.获取key值,使用ftok()
	key_t key = ftok(".", 200);			//　200只取低8位
	if(-1 == key)
	{
		perror("ftok"),exit(-1);
	}
	printf("key = %#x\n", key);

	//2.创建信号量集，使用semget()
	semid = semget(key,1/*信号量集的大小*/, IPC_CREAT|IPC_EXCL|0664);
	if(-1 == semid)
	{
		perror("semget"),exit(-1);
	}
	printf("semid = %d\n", semid);

	//3.初始化信号量集,使用semctl()
	// int arr[1]; arr[0] = 5;
	int res = semctl(semid, 0/*信号量集的下标*/, SETVAL, 5/*信号量的初始值为5*/);
	if(-1 == res)
	{
		perror("semctl"),exit(-1);
	}
	printf("初始化信号量集成功\n");

	//4.若不再使用，则删除信号量集，semctl()
	printf("删除信号量集请按ctrl+c...\n");
	if(SIG_ERR == signal(SIGINT, fa))
	{
		perror("signal"),exit(-1);
	}
	while(1);
	return 0;
}

