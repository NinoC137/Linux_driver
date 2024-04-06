#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include <linux/errno.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/major.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/stat.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/kmod.h>
#include <linux/gfp.h>
#include "led_opr.h"

#define LED_FILE "/sys/class/leds/led0/brightness"

static int board_demo_led_init(int which){
    printk("%s %s line %d, led %d\n", __FILE__, __FUNCTION__, __LINE__, which);
	return 0;
}

static int board_demo_led_ctl(int which, char status){
    struct file *filp;
    char value;

    filp = filp_open(LED_FILE, O_WRONLY, 0);
    if(IS_ERR(filp)){
        printk("falied to open led0\n");
        return PTR_ERR(filp);
    }

    value = status;
    kernel_write(filp, &value, 1, 0);

    printk("%s %s line %d, led %d, %c\n", __FILE__, __FUNCTION__, __LINE__, which, status);
    filp_close(filp, NULL);
	return 0;
}

static struct led_operations board_demo_led_opr = {
	.init = board_demo_led_init,
	.ctl  = board_demo_led_ctl,
};

struct led_operations *get_board_led_opr(void)
{
	return &board_demo_led_opr;
}