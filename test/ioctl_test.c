//
// Created by wserver on 2022/12/12.
//
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    int my_dev = open("/dev/mydev", 0);

    if (my_dev < 0) {
        perror("Failed to open device file: /dev/mydev.");
    } else {
        ioctl(my_dev, 100, 110);
        close(my_dev);
    }
    return 0;
}