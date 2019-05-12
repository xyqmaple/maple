/*
 * @brief: read numbers from the file named "a.pipe" which is a named pipe file.
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
	int num, fd = -1;
	ssize_t size;

	fd = open(PIPE_PATH, O_RDONLY);
	if (fd < 0) {
		ERR("open %s err: %s\n", PIPE_PATH, strerror(errno));
		return fd;
	}

	do {
		size = read(fd, &num, sizeof(num));
		if (size < 0) {
			ERR("read err: %s\n", strerror(errno));
			goto out;

		} else if (size > 0) {
			INFO("%d\n", num);
		}
	} while(size > 0);

	INFO("read successful!\n");

out:
	close(fd);
	return size;
}
