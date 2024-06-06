all: test_cdev_mutex_4wr test_open_read

test_cdev_mutex_4wr:
	gcc -Wall -g -o test_cdev_mutex_4wr test_cdev_mutex_4wr.c -lpthread
	@echo Usage arg: cdev file name

test_open_read:
	gcc -Wall -g -o test_open_read test_open_read.c
	@echo Usage arg: cdev file name and count of read bytes


clean:
	@rm test_cdev_mutex_4wr test_open_read
