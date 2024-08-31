#include <linux/init.h>
#include <linux/module.h>

static unsigned long init_number = 1;
static char* whom = "world";

static int __init hello_init(void)
{
	for (size_t i = 0; i < init_number; i++)
		printk(KERN_ALERT "Hello, %s\n", whom);

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
module_param(whom, charp, S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Simple hello driver");
