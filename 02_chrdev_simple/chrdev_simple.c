#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/module.h>
#include <linux/types.h>

static unsigned long size = 1;
static dev_t dev = 0;
static size_t scull_major = 0;
static size_t scull_minor = 0;
static const unsigned int count = 1;

static void clean(void);

static int __init hello_init(void)
{
	int result = 0;

	printk(KERN_ALERT "Start init chrdev_simple\n");

	dev = 0;
	scull_major = 0;
	scull_minor = 0;

	result = alloc_chrdev_region(&dev, scull_minor, count, "chrdev_simple");
	if (result < 0) {
		printk(KERN_WARNING "scull: can't get major %u\n", dev);
		goto end;
	}

	scull_major = MAJOR(dev);

end:

	if (result < 0)
		clean();

	printk(KERN_ALERT "Stop init chrdev_simple\n");

	return result;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "Start exit chrdev_simple\n");

	clean();

	printk(KERN_ALERT "Stop exit chrdev_simple\n");
}

static void clean(void)
{

	if (dev) {
		unregister_chrdev_region(dev, count);
		dev = 0;
	}
	scull_major = 0;
	scull_minor = 0;
}

module_init(hello_init);
module_exit(hello_exit);

/* Set desired capacity with insmod */
module_param(size, ulong, S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Simple chrdev driver");
