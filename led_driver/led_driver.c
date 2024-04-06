#include "linux/module.h"
#include "linux/kernel.h"
#include "linux/init.h"

#include "linux/fs.h"
#include "linux/errno.h"
#include <linux/miscdevice.h>
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

static int major;   //确定主设备号
static struct class *led_class; //创建led设备
struct led_operations *p_led_opr;

#define MIN(a, b) (a < b ? a : b)

static ssize_t led_drv_read(struct file *file, char __user *buf, size_t size, loff_t *offset){
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

static ssize_t led_drv_write(struct file *file, const char __user *buf, size_t size, loff_t *offset){
    int err;
    char status;
    struct inode *inode = file_inode(file);
    int minor = iminor(inode);

	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    err = copy_from_user(&status, buf, 1);

    p_led_opr->ctl(minor, status);

	return 1;
}

static int led_drv_open(struct inode *node, struct file *file){
    int minor = iminor(node);
    printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
    p_led_opr->init(minor);

    return 0;
}

static int led_drv_close (struct inode *node, struct file *file)
{
	printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
	return 0;
}

struct file_operations led_drv = {
    .owner = THIS_MODULE,
    .open = led_drv_open,
    .release = led_drv_close,
    .read = led_drv_read,
    .write = led_drv_write,
};

static int __init led_init(void){
    int err;
    
    printk("my led driver loading");
    major = register_chrdev(0, "my_led", &led_drv);

    led_class = class_create(THIS_MODULE, "my_led_class");
    err = PTR_ERR(led_class);
    if(IS_ERR(led_class)){
        printk("%s %s line %d\n", __FILE__, __FUNCTION__, __LINE__);
        printk("led class create failure\n");
        unregister_chrdev(major, "my_led");
        return -1;
    }

    p_led_opr = get_board_led_opr();

    device_create(led_class, NULL, MKDEV(major, 0), NULL, "my_led0");

    return 0;
}

static void __exit led_exit(void){
    printk("my led driver removing\n");

    device_destroy(led_class, MKDEV(major, 0));
    class_destroy(led_class);
    unregister_chrdev(major, "my_led");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("NinoC137");
MODULE_DESCRIPTION("My led driver!");
MODULE_INFO(intree, "Y");