/*
 * @brief: communicate with each other by using unnamed pipe.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "print.h"

int main(int argc, char *argv[])
{
	int i, pipefd[2], ret;
	pid_t pid;

	/* pipefd[0] - read port, pipefd[1] - write port. */
	ret = pipe(pipefd);
	if (ret < 0) {
		ERR("pipe err: %s\n", strerror(errno));
		return ret;
	}

	pid = fork();
	if (pid < 0) {
		ERR("fork err: %s\n", strerror(errno));
		goto out;
	}

	/* child process */
	if (0 == pid) {
		int tmp;

		close(pipefd[1]);
		do {
			ret = read(pipefd[0], &tmp, sizeof(tmp));
			if (ret < 0) {
				ERR("read err: %s\n", strerror(errno));
				close(pipefd[0]);
				exit(-1);
			}
			INFO("%d\n", tmp);

		} while(ret > 0);
		INFO("read successful\n");
		
		close(pipefd[0]);
		exit(0);
	}
	/* parent process */
	close(pipefd[0]);

	for (i = 1; i <= 100; i++) {
		ret = write(pipefd[1], &i, sizeof(i));
		if (ret < 0) {
			ERR("write err: %s\n", strerror(errno));
			goto out1;
		}
	}
	INFO("write successful\n");
out1:
	close(pipefd[1]);
	return ret;
out:
	close(pipefd[0]);
	close(pipefd[1]);
	return pid;
}
