#include <linux/init.h>
#include <linux/module.h>

static unsigned long size = 1;

static int __init hello_init(void)
{
	printk(KERN_ALERT "Start init chdev_simple\n");
	printk(KERN_ALERT "Stop init chdev_simple\n");

	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Start exit chdev_simple\n");
	printk(KERN_ALERT "Stop exit chdev_simple\n");
}

module_init(hello_init);
module_exit(hello_exit);

/* Set desired capacity with insmod */
module_param(size, ulong, S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Simple chdev driver");
