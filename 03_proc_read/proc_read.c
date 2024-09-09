#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>

static char* str = "Non";

int proc_read(char* buf, char** start, off_t offset, int count, int* eof,
              void* data)
{
	int len = 0;
	len = sprintf(buf + len, "%s\n", str);
	*eof = 1;
	return len;
}

static int __init proc_read_init(void)
{
	create_proc_read_entry("proc_read", 0 /* режим по умолчанию */,
	                       NULL /* родительская директория */,
	                       proc_read /* функция для вызова*/,
	                       NULL /* клиентские данные */);

	return 0;
}

static void __exit proc_read_exit(void)
{

	remove_proc_entry("proc_read", NULL /* родительская директория */);
}

module_init(proc_read_init);
module_exit(proc_read_exit);

/* Set desired capacity with insmod */
module_param(str, charp, S_IRUGO);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Proc read file");
