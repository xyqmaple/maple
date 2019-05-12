//按照模型打印共享内存中的数据100即可
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>

int main(void)
{
	//1.获得key值，使用ftok()
	key_t key = ftok(".", 100);
	if(-1 == key)
	{
		perror("ftok"),exit(-1);
	}
	printf("key = %#x\n", key);
	//2.获取共享内存，使用shmget()
	int shmid = shmget(key, 0, 0);
	if(-1 == shmid)
	{
		perror("shmget"),exit(-1);
	}
	printf("shmid = %d\n", shmid);
	//3.挂接共享内存，使用shmat()
	void* pv = shmat(shmid, NULL, 0);
	if((void*)-1 == pv)
	{
		perror("shmat"),exit(-1);
	}
	printf("挂接共享内存成功\n");
	//4.访问共享内存
	printf("*(int*)pv = %d\n", *(int*)pv);
	//5.脱接共享内存，使用shmdt()
	int res = shmdt(pv);
	if(-1 == res)
	{
		perror("shmdt"),exit(-1);
	}
	printf("脱接成功\n");

	return 0;
}

