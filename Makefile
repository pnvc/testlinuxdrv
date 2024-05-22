test_cdev_mutex_4wr:
	gcc -Wall -g -o test_cdev_mutex_4wr test_cdev_mutex_4wr.c -lpthread

clean:
	@rm test_cdev_mutex_4wr
