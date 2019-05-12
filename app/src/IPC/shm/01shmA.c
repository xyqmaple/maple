/*
 * @brief: IPC by using shared memory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <errno.h>

#include "print.h"

static int shmid;

void fa(int signum)
{
	INFO("deleting shared memory, please wait ...\n");
	sleep(1);

	if (shmctl(shmid, IPC_RMID, NULL) < 0) {
		ERR("shmctl err: %s\n", strerror(errno));
		exit(-1);
	}
	INFO("delete shared memory successful!\n");
	exit(0);
}

int main(int argc, char *argv[])
{
	key_t key;
	int ret;
	void *pv = NULL;

	key = ftok(".", 100);
	if (key < 0) {
		ERR("ftok err: %s\n", strerror(errno));
		return key;
	}
	INFO("key = %#x\n", key);

	/* create shared memory */
	shmid = shmget(key, 4, IPC_CREAT | IPC_EXCL | 0664);
	if (shmid < 0) {
		ERR("shmget err: %s\n", strerror(errno));
		return shmid;
	}
	INFO("shmid = %d\n", shmid);

	/* attach shared memory */
	pv = shmat(shmid, NULL, 0);
	if ((void *)-1 == pv) {
		ERR("shmat err: %s\n", strerror(errno));
		return -EPERM;
	}
	INFO("attach shared memory successful!\n");

	/* access shared memory */
	*(int *)pv = 100;

	/* detach shared memory */
	ret = shmdt(pv);
	if (ret < 0) {
		ERR("shmdt err: %s\n", strerror(errno));
		return ret;
	}

	/* delete shared memory if not use */
	NOTICE("delete shared memory, please enter \"Ctrl+c\"...\n");

	if (SIG_ERR == signal(SIGINT, fa)) {
		ERR("signal err: %s\n", strerror(errno));
	}
	while (1);

	return 0;
}

