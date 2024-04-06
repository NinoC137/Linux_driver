my_led_driver-y := led_driver.o board_demo.o
obj-m := my_led_driver.o

all:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o led_test led_test.c
clean:
	sudo make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean