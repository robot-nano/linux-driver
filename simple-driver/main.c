//
// Created by wserver on 2022/12/9.
//

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kern_levels.h>

#include "device_file.h"

MODULE_DESCRIPTION("Simple Linux driver");
MODULE_LICENSE("APACHE");
MODULE_AUTHOR("Wserver");

static int simple_driver_init(void) {
    int result = 0;
    printk(KERN_NOTICE "Simple-driver: Initialization started\n");


    return result;
}

static void simple_driver_exit(void) {

}

module_init(simple_driver_init);
module_exit(simple_driver_exit);
