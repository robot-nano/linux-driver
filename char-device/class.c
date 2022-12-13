#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Inc");
MODULE_DESCRIPTION("char-device");

#define DEVICE_NAME "mydev"
#define CLASS_NAME "hello_class"

static struct class* helloClass;
static struct cdev my_dev;
dev_t dev;

static int my_dev_open(struct inode* inode, struct file* file) {
  printk(KERN_NOTICE "my_dev_open() is called\n");
  return 0;
}

static int my_dev_close(struct inode* inode, struct file* file) {
  printk(KERN_NOTICE "my_dev_close() is called\n");
  return 0;
}

static long my_dev_ioctl(struct file* file, unsigned int cmd, unsigned long arg) {
  printk(KERN_NOTICE "my_dev_ioctl() is called. cmd = %d, arg = %ld\n", cmd, arg);
  return 0;
}

/* declare a file_operations structure */
static const struct file_operations my_dev_fops = {
    .owner = THIS_MODULE,
    .open = my_dev_open,
    .release = my_dev_close,
    .unlocked_ioctl = my_dev_ioctl,
};

static int __init hello_init(void) {
  int ret;
  dev_t dev_no;
  int Major;
  struct device* helloDevice;
  printk(KERN_NOTICE "Hello world init\n");

  /* Allocate dynamically device numbers */
  ret = alloc_chrdev_region(&dev_no, 0, 1, DEVICE_NAME);
  if (ret < 0) {
    printk(KERN_ERR "Unable to allocate Major number\n");
    return ret;
  }

  /* Get the device identifiers */
  Major = MAJOR(dev_no);
  dev = MKDEV(Major, 0);

  printk("Allocated correctly with major number %d\n", Major);

  /* Initialize the cdev structure and add it to kernel space */
  cdev_init(&my_dev, &my_dev_fops);
  ret = cdev_add(&my_dev, dev, 1);
  if (ret < 0) {
    unregister_chrdev_region(dev, 1);
    printk(KERN_ERR "Unable to add cdev\n");
    return ret;
  }

  /* Register the device class */
  helloClass = class_create(THIS_MODULE, CLASS_NAME);
  if (IS_ERR(helloClass)) {
    unregister_chrdev_region(dev, 1);
    cdev_del(&my_dev);
    printk(KERN_ERR "Failed to register device class\n");
    return PTR_ERR(helloClass);
  }
  printk(KERN_NOTICE "device class registered correctly\n");

  /* Create a device node named DEVICE_NAME associated to dev */
  helloDevice = device_create(helloClass, NULL, dev, NULL, DEVICE_NAME);
  if (IS_ERR(helloDevice)) {
    class_destroy(helloClass);
    cdev_del(&my_dev);
    unregister_chrdev_region(dev, 1);
    printk(KERN_ERR "Failed to create the device");
    return PTR_ERR(helloDevice);
  }
  printk(KERN_NOTICE "The device is created correctly\n");

  return 0;
}

static void __exit hello_exit(void) {
  device_destroy(helloClass, dev);
  class_destroy(helloClass);
  cdev_del(&my_dev);
  unregister_chrdev_region(dev, 1);
  printk(KERN_NOTICE "Hello world with parameter exit\n");
}

module_init(hello_init);
module_exit(hello_exit);
