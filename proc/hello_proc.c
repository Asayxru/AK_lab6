#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#define PROC_NAME "hello_proc"

MODULE_LICENSE("GPL");

static ssize_t proc_read(struct file *file, char __user *buf, size_t count, loff_t *off)
{
    char msg[] = "Hello from /proc!\n";
    return simple_read_from_buffer(buf, count, off, msg, sizeof(msg));
}

static const struct file_operations proc_fops = {
    .owner = THIS_MODULE,
    .read = proc_read,
};

static int __init hello_proc_init(void)
{
    proc_create(PROC_NAME, 0, NULL, &proc_fops);
    printk(KERN_INFO "/proc/hello_proc created\n");
    return 0;
}

static void __exit hello_proc_exit(void)
{
    remove_proc_entry(PROC_NAME, NULL);
    printk(KERN_INFO "/proc/hello_proc removed\n");
}

module_init(hello_proc_init);
module_exit(hello_proc_exit);
