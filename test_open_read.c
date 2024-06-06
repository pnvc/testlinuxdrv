#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc < 3) {
		printf("Need args: cdev file path, count of reading\n");
		return 1;
	}
	int count = atoi(argv[2]);
	int fd = 0;
	fd = open(argv[1], O_RDONLY);
	printf("filename: %s, file fd: %d, count: %d\n", argv[1], fd, count);
	char buf[5000] = {0};

	if (count > 5000)
		count = 5000;

	pread(fd, (void*)buf, count, 0);

	printf("%s\n", buf);

	return 0;
}
