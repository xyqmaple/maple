#include <stdio.h>

int main(int argc, char *argv[])
{
	unsigned int val = 0x12345678;
	unsigned char *pc = (unsigned char *)&val;

	if (0x12 == pc[0]) {
		printf("big endian\n");
	} else if (0x78 == pc[0]) {
		printf("little endian\n");
	} else {
		printf("endian type unknown!\n");
	}

	return 0;
}

