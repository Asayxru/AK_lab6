#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/seq_file.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Seq file API demo module");

static void *seq_start(struct seq_file *m, loff_t *pos)
{
    if (*pos == 0)
        return pos;
    return NULL;
}

static void *seq_next(struct seq_file *m, void *v, loff_t *pos)
{
    return NULL; // only one line
}

static void seq_stop(struct seq_file *m, void *v)
{
}

static int seq_show(struct seq_file *m, void *v)
{
    seq_printf(m, "Hello from seq_file API!\n");
    return 0;
}

static struct seq_operations seq_ops = {
    .start = seq_start,
    .next  = seq_next,
    .stop  = seq_stop,
    .show  = seq_show,
};

static int hello_seq_open(struct inode *inode, struct file *file)
{
    return seq_open(file, &seq_ops);
}

static const struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = hello_seq_open,
    .read    = seq_read,
    .llseek  = seq_lseek,
    .release = seq_release,
};

static int __init hello_seq_init(void)
{
    proc_create("hello_seq", 0, NULL, &fops);
    printk(KERN_INFO "hello_seq: /proc/hello_seq created\n");
    return 0;
}

static void __exit hello_seq_exit(void)
{
    remove_proc_entry("hello_seq", NULL);
    printk(KERN_INFO "hello_seq: removed\n");
}

module_init(hello_seq_init);
module_exit(hello_seq_exit);
