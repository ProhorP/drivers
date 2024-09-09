#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

static char msg[100];
static struct proc_dir_entry *proc_file;

ssize_t my_proc_read(struct file *filp, char __user *buffer, size_t len, loff_t *offset) {
    return simple_read_from_buffer(buffer, len, offset, msg, strlen(msg));
}

ssize_t my_proc_write(struct file *filp, const char __user *buffer, size_t len, loff_t *offset) {
    if (len > sizeof(msg) - 1)
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

static int __init proc_read_init(void) {
	memset(msg, 0, sizeof(msg));
    proc_file = proc_create("proc_read", 0666, NULL, &proc_fops);
    if (!proc_file) {
        return -ENOMEM;
    }
    return 0;
}

static void __exit proc_read_exit(void)
{
	remove_proc_entry("proc_read", NULL /* родительская директория */);
}

module_init(proc_read_init);
module_exit(proc_read_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Proc read file");
