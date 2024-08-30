#include <linux/init.h>
#include <linux/module.h>

static unsigned long    init_number = 100;

static int __init hello_init(void)
{
printk(KERN_ALERT "Hello, world\n");
return 0;
}

static void __exit hello_exit(void)
{
printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

/* Set desired capacity with insmod */
module_param_named(number, init_number, ulong, S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Simple hello driver");
