obj-m := hello_driverPlus.o

all: hello_driverPlus.c
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o hello_driverTest hello_driverTest.c
clean:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
