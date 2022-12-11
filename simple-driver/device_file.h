//
// Created by wserver on 2022/12/9.
//

#ifndef LINUX_DRIVER_DEVICE_FILE_H
#define LINUX_DRIVER_DEVICE_FILE_H

#include <linux/compiler.h>

__must_check int register_device(void);
void unregister_device(void);

#endif //LINUX_DRIVER_DEVICE_FILE_H
