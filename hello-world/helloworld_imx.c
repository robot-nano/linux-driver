//
// Created by wserver on 2022/12/11.
//

#include <linux/init.h>
#include <linux/module.h>
#include <linux/time.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Inc");
MODULE_DESCRIPTION("hello world!");

static int num = 10;
static struct timespec64 start_time;

module_param(num, int, S_IRUGO);

static void say_hello(void) {
  int i ;
  for (i = 0; i <= num; ++i) {
    printk(KERN_NOTICE "[%d%d] Hello!\n", i, num);
  }
}

static int __init hello_init(void) {
  ktime_get_raw_ts64(&start_time);
  printk(KERN_NOTICE "Loading first!\n");
  say_hello();
  return 0;
}

static void __exit hello_exit(void) {
  struct timespec64 end_time;
  ktime_get_raw_ts64(&end_time);
  printk(KERN_NOTICE "Unloading module first %lld seconds\n",
         end_time.tv_sec - start_time.tv_sec);
  say_hello();
}

module_init(hello_init);
module_exit(hello_exit);