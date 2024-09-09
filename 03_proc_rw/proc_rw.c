#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

#define PRE_PRINT "proc_rw: "
#define PRINT(s, ...) printk(KERN_ALERT PRE_PRINT s, ##__VA_ARGS__)

static char* msg;              /* Указатель на буфер proc */
static unsigned long size = 1; /* размер буфера proc */
static struct proc_dir_entry* proc_file;

ssize_t my_proc_read(struct file* filp, char __user* buffer, size_t len,
                     loff_t* offset)
{
	return simple_read_from_buffer(buffer, len, offset, msg, strlen(msg));
}

ssize_t my_proc_write(struct file* filp, const char __user* buffer, size_t len,
                      loff_t* offset)
{
	if (len > size - 1)
		return -EINVAL;

	if (copy_from_user(msg, buffer, len))
		return -EFAULT;

	msg[len] = '\0';
	return len;
}

static const struct proc_ops proc_fops = {
    .proc_read = my_proc_read,
    .proc_write = my_proc_write,
};

static int __init proc_read_init(void)
{
	msg = kmalloc(size, GFP_KERNEL);
	if (!msg) {
		PRINT("error kmallocl(%ld)\n", size);
		goto end;
	}
	memset(msg, 0, size);

	proc_file = proc_create("proc_rw", 0666, NULL, &proc_fops);
	if (!proc_file)
		return -ENOMEM;

end:
	return 0;
}

static void __exit proc_read_exit(void)
{
	if (msg) {
		PRINT("kfree\n");
		kfree(msg);
		msg = NULL;
	}
	remove_proc_entry("proc_rw", NULL /* родительская директория */);
}

module_init(proc_read_init);
module_exit(proc_read_exit);

module_param(size, ulong, S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Proc read/write file");
