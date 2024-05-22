#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <pthread.h>
#include "test_cdev_mutex_4wr.h"

#define CDEV (char*)argv[1]

struct fds {
	int w0,r0,w1,r1,w2,r2,w3,r3;
	int ready;
	pthread_mutex_t *m;
};

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Need arg (cdev file path)\n");
		return 1;
	}

	printf("Char device file: '%s'\n", CDEV);

	pthread_t t0, t1, t2, t3;
	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
	struct fds fds;
	fds.ready = 0;
	fds.m = &m;

	fds.w0 = open(CDEV, O_WRONLY | O_CREAT, 0666);
	fds.r0 = open(CDEV, O_RDONLY);
	fds.w1 = open(CDEV, O_WRONLY);
	fds.r1 = open(CDEV, O_RDONLY);
	fds.w2 = open(CDEV, O_WRONLY);
	fds.r2 = open(CDEV, O_RDONLY);
	fds.w3 = open(CDEV, O_WRONLY);
	fds.r3 = open(CDEV, O_RDONLY);

	pthread_create(&t0, NULL, t0main, &fds);
	pthread_create(&t1, NULL, t1main, &fds);
	pthread_create(&t2, NULL, t2main, &fds);
	pthread_create(&t3, NULL, t3main, &fds);

	void *tr;

	pthread_join(t0, &tr);
	pthread_join(t1, &tr);
	pthread_join(t2, &tr);
	pthread_join(t3, &tr);

	return 0;
}

void* t0main(void *arg)
{
	struct fds *fds = (struct fds*)arg;
	pthread_mutex_lock(fds->m);
	fds->ready++;
	pthread_mutex_unlock(fds->m);
	int i = 0;
	char buf[2048];
	while(fds->ready != 4);
	printf("thread 0 start loop\n");
	while (i++ < 35) {
		write(fds->w0, "0", 1);
		read(fds->r0, buf, sizeof buf);
		printf("%s\n", buf);
	}
	return 0;
}

void* t1main(void *arg)
{
	struct fds *fds = (struct fds*)arg;
	pthread_mutex_lock(fds->m);
	fds->ready++;
	pthread_mutex_unlock(fds->m);
	int i = 0;
	char buf[2048];
	while(fds->ready != 4);
	printf("thread 1 start loop\n");
	while (i++ < 35) {
		write(fds->w1, "1", 1);
		read(fds->r1, buf, sizeof buf);
		printf("%s\n", buf);
	}
	return 0;
}

void* t2main(void *arg)
{
	struct fds *fds = (struct fds*)arg;
	pthread_mutex_lock(fds->m);
	fds->ready++;
	pthread_mutex_unlock(fds->m);
	int i = 0;
	char buf[2048];
	while(fds->ready != 4);
	printf("thread 2 start loop\n");
	while (i++ < 35) {
		write(fds->w2, "2", 1);
		read(fds->r2, buf, sizeof buf);
		printf("%s\n", buf);
	}
	return 0;
}

void* t3main(void *arg)
{
	struct fds *fds = (struct fds*)arg;
	pthread_mutex_lock(fds->m);
	fds->ready++;
	pthread_mutex_unlock(fds->m);
	int i = 0;
	char buf[2048];
	while(fds->ready != 4);
	printf("thread 3 start loop\n");
	while (i++ < 35) {
		write(fds->w3, "3", 1);
		read(fds->r3, buf, sizeof buf);
		printf("%s\n", buf);
	}
	return 0;
}
