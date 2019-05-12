//使用信号量集实现进程间的通信
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(void)
{
	//1.获取key值，使用ftok()
	key_t key = ftok(".", 200);
	if(-1 == key)
	{
		perror("ftok"),exit(-1);
	}
	printf("key = %#x\n", key);
	//2.获取信号量集，使用semget()
	int semid = semget(key, 0, 0);
	if(-1 == semid)
	{
		perror("semget"),exit(-1);
	}
	printf("semid = %d\n", semid);
	//3.操作信号量集，使用semop()
	int i = 0;
	for(i = 0;i < 10;i++)
	{
		pid_t pid = fork();
		if(-1 == pid)
		{
			perror("fork"),exit(-1);
		}
		// 子进程模拟抢占共享资源的过程
		if(0 == pid)
		{
			// 准备结构体变量，并初始化
			struct sembuf buf;
			buf.sem_num = 0;		// 下标
			buf.sem_op = -1;		// 信号量减1
			buf.sem_flg = 0;		// 操作标志
			// 调用semop()操作信号量集
			int res = semop(semid, &buf, 1);
			if(-1 == res)
			{
				perror("semop"),exit(-1);
			}
			printf("进程%d申请共享资源成功\n", getpid());
			// 模拟占用共享资源的过程
			sleep(20);
			// 模拟释放共享资源的过程
			buf.sem_op = 1;
			res = semop(semid, &buf, 1);
			if(-1 == res)
			{
				perror("semop"),exit(-1);
			}
			printf("进程%d释放共享资源\n", getpid());
			// 终止子进程
			exit(0);
		}
	}
	return 0;
}

