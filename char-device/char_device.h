#include <linux/cdev.h>
#include <linux/ioctl.h>

#undef PDEBUG
#ifdef SIMPLE_DEBUG
#ifdef __KERNEL__
#define PDEBUG(fmt, args...) printk(KERN_DEBUG "DEMO: " fmt, ##args)
#else
#define PDEBUG(fmt, args...) fprint(stderr, fmt, ##args)
#endif
#else
#define PDEBUG(fmt, args...) /* not debugging: nothing */
#endif

#undef PDEBUG
#define PDEBUG(fmt, args...)

#define SIMPLE_MAJOR 224
#define SIMPLE_MINOR 0
#define COMMAND_LEDON 1
#define COMMAND_LEDOFF 2

#define MAX_SIZE 256

struct simple_dev {
  struct cdev cdev;
};

ssize_t simple_read(struct file* filp, char __user* buf, size_t count, loff_t* f_pos);

ssize_t simple_write(struct file* filp, const char __user* buf, size_t count, loff_t* f_pos);

loff_t simple_llseek(struct file* filp, loff_t off, int whence);

int simple_ioctl(struct inode* inode, struct file* filp, unsigned int cmd, unsigned long arg);