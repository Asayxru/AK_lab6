#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Debug module that causes kernel OOPS");

static int __init hello_debug_init(void)
{
    printk(KERN_INFO "hello_debug: module loaded\n");

    // Явна помилка: запис за NULL → kernel OOPS
    printk(KERN_ERR "hello_debug: triggering NULL dereference!\n");

    *(int *)0 = 123;   // OOPS тут

    return 0;
}

static void __exit hello_debug_exit(void)
{
    printk(KERN_INFO "hello_debug: module unloaded\n");
}

module_init(hello_debug_init);
module_exit(hello_debug_exit);
