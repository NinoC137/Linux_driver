#include <linux/module.h>

#include <linux/kernel.h>

#include <linux/init.h>

static int __init hello_init(void) {

      printk(KERN_INFO "Hello Driver!\n");

      return 0;
}

static void __exit hello_exit(void) {

     printk(KERN_INFO "Goodbye Driver!\n");

}

module_init(hello_init);

module_exit(hello_exit);

MODULE_LICENSE("GPL");

MODULE_AUTHOR("NinoC137");

MODULE_DESCRIPTION("Hello World Linux Device Driver");
