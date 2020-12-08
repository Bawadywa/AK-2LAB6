#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <hello1.h>
#include <linux/slab.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("HelloWorld");
MODULE_AUTHOR("Peter Polovinkin <>");

EXPORT_SYMBOL(print_hello);
static struct my_list_head *head;

int print_hello(uint count)
{
    int i;
    struct my_list_head *temp_head_1;
    struct my_list_head *temp_head_2;

    head = kmalloc(sizeof(struct my_list_head*), GFP_KERNEL);

    temp_head_1 = head;

    if (count == 0)
    {
        pr_warn("WARNING\ncount = 0\n");
        return 0;
    }
    else if (count >= 5 && count <= 10)
    {
        pr_warn("WARNING\ncount is between 5 and 10\n");
    }
    else if (count > 10)
    {
        pr_err("ERROR\n count > 10");
        return -EINVAL;
    }
    
    for (i = 0; i < count; i++)
    {
        temp_head_1->next = kmalloc(sizeof(struct my_list_head*), GFP_KERNEL);
        temp_head_1->time = ktime_get();
        pr_info("Hello, world\n");
        temp_head_1->post_time = ktime_get();
        temp_head_2 = temp_head_1;
        temp_head_1 = temp_head_1->next;
    }
    kfree(temp_head_2->next);
    temp_head_2->next = NULL;

    return 0;
}

static int __init hello1_init(void)
{
    pr_info("hello1 init");
    return 0;
}

static void __exit hello1_exit(void)
{
    struct my_list_head* temp_1 = head;
    struct my_list_head* temp_2 = temp_1;
    while(temp_1 != NULL)
    {
        pr_info("Time spent is %lld", temp_1->post_time - temp_1->time);
        temp_2 = temp_1;
        temp_1=temp_2->next;
        kfree(temp_2);
    }
    
    pr_info("hello1 exit");
}

module_init(hello1_init);
module_exit(hello1_exit);
