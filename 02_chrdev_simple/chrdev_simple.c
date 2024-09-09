#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/module.h>
#include <linux/types.h>

#define PRE_PRINT "chrdev_simple: "
#define PRINT(s, ...) printk(KERN_ALERT PRE_PRINT s, ##__VA_ARGS__)

static void* data; /* Указатель на буфер псевдоустройства */
static unsigned long size = 1; /* размер буфера псевдоустройства */

static dev_t dev = 0;          /* номер устройства */
static size_t scull_major = 0; /* старший номер устройства */
static size_t scull_minor = 0; /* младший номер устройства */
static const unsigned int count = 1; /* количество устройств */
struct cdev cdev; /* структура символьного устройства */
static bool cdev_success = false; /* Признак инициализации cdev*/

int scull_open(struct inode* inode, struct file* filp);
int scull_release(struct inode* inode, struct file* filp);
ssize_t scull_read(struct file* filp, char __user* buf, size_t count,
                   loff_t* f_pos);
ssize_t scull_write(struct file* filp, const char __user* buf, size_t count,
                    loff_t* f_pos);
loff_t scull_llseek(struct file* filp, loff_t off, int whence);

/* структура операций с символьным устройством */
struct file_operations scull_fops = {
    .owner = THIS_MODULE,
    .llseek = scull_llseek,
    .read = scull_read,
    .write = scull_write,
    // .ioctl = NULL,
    .open = scull_open,
    .release = scull_release,
};

static void clean(void);

static int __init hello_init(void)
{
	int result = 0;

	PRINT("Start init chrdev_simple\n");

	dev = 0;
	scull_major = 0;
	scull_minor = 0;
	memset(&cdev, 0, sizeof(cdev));

	result = alloc_chrdev_region(&dev, scull_minor, count, "chrdev_simple");
	if (result < 0) {
		PRINT("scull: can't get major %u\n", dev);
		goto end;
	}

	scull_major = MAJOR(dev);
	scull_minor = MINOR(dev);

	data = kmalloc(size * sizeof(char*), GFP_KERNEL);
	if (!data) {
		PRINT("error kmallocl(%ld)\n", size * sizeof(char*));
		result = -ENOMEM;
		goto end;
	}

	cdev_init(&cdev, &scull_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &scull_fops;
	result = cdev_add(&cdev, dev, 1);
	/* Терпите неудачу изящно, если это необходимо */
	if (result) {
		PRINT("Error %d adding scull\n", result);
		goto end;
	};
	cdev_success = true;

	PRINT("scull_major=%ld\n", scull_major);
	PRINT("scull_minor=%ld\n", scull_minor);

end:

	if (result != 0)
		clean();

	PRINT("Stop init chrdev_simple\n");

	return result;
}

static void __exit hello_exit(void)
{
	PRINT("Start exit chrdev_simple\n");

	clean();

	PRINT("Stop exit chrdev_simple\n");
}

static void clean(void)
{

	if (dev) {
		PRINT("unregister_chrdev_region\n");
		unregister_chrdev_region(dev, count);
		dev = 0;
	}

	if (cdev_success) {
		PRINT("cdev_del\n");
		cdev_del(&cdev);
		memset(&cdev, 0, sizeof(cdev));
		cdev_success = false;
	}

	scull_major = 0;
	scull_minor = 0;

	if (data) {
		PRINT("kfree\n");
		kfree(data);
		data = NULL;
	}
}

int scull_open(struct inode* inode, struct file* filp)
{
	return 0; /* успешно */
}

int scull_release(struct inode* inode, struct file* filp)
{
	return 0; /* успешно */
}

ssize_t scull_read(struct file* filp, char __user* buf, size_t count,
                   loff_t* f_pos)
{
	ssize_t retval = 0;

	if (*f_pos >= size)
		goto end;

	if (*f_pos + count > size)
		count = size - *f_pos;

	if (copy_to_user(buf, data + *f_pos, count)) {
		retval = -EFAULT;
		goto end;
	}

	*f_pos += count;
	retval = count;

end:
	return retval;
}

ssize_t scull_write(struct file* filp, const char __user* buf, size_t count,
                    loff_t* f_pos)
{
	ssize_t retval = -ENOMEM;

	if (*f_pos >= size)
		goto end;

	if (*f_pos + count > size)
		count = size - *f_pos;

	memset(data, 0, size);

	if (copy_from_user(data + *f_pos, buf, count)) {
		retval = -EFAULT;
		goto end;
	}

	*f_pos += count;
	retval = count;

end:
	return retval;
}

loff_t scull_llseek(struct file* filp, loff_t off, int whence)
{
	loff_t newpos;

	switch (whence) {
		case 0: /* SEEK_SET */
			newpos = off;
			break;
		case 1: /* SEEK_CUR */
			newpos = filp->f_pos + off;
			break;
		case 2: /* SEEK_END */
			newpos = size + off;
			break;
		default: /* не может произойти */
			return -EINVAL;
	}
	if (newpos < 0)
		return -EINVAL;

	filp->f_pos = newpos;
	return newpos;
}

module_init(hello_init);
module_exit(hello_exit);

/* Set desired capacity with insmod */
module_param(size, ulong, S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Simple chrdev driver");
