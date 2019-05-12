/*
 * @brief: write numbers to the file named "a.pipe" which is a named pipe file.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#include "print.h"

#define PIPE_PATH			"a.pipe"

int main(int argc, char *argv[])
{
	int i, ret, fd = -1;

	fd = open(PIPE_PATH, O_WRONLY);
	if (fd < 0) {
		ERR("open %s err: %s\n", PIPE_PATH, strerror(errno));
		return fd;
	}

	for (i = 0; i <= 100; i++) {
		ret = write(fd, &i, sizeof(i));
		if (ret < 0) {
			ERR("write: %s\n", strerror(errno));
			goto out;
		}
	}
	INFO("write successful!\n");

out:
	close(fd);
	return ret;
}
