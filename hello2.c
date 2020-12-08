#include <linux/init.h>
#include <linux/module.h>

#include <hello1.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("HelloWorld");
MODULE_AUTHOR("Peter Polovinkin <>");

static uint count = 1;
module_param(count, uint, 0);

static int hello_init(void)
{
    return print_hello(count);
}

static void hello_exit(void)
{
    printk(KERN_ALERT "Ending...\n");
}

module_init(hello_init);
module_exit(hello_exit);
