#include <linux/module.h>
#include <linux/fs.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/mod_devicetable.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Inc");
MODULE_DESCRIPTION("platform_driver");

static int my_dev_open(struct inode* inode, struct file* file) {
  printk(KERN_NOTICE "my_dev_open() is called.\n");
  return 0;
}

static int my_dev_close(struct inode* inode, struct file* file) {
  printk(KERN_NOTICE "my_dev_close() is called.\n");
  return 0;
}

static long my_dev_ioctl(struct file* file, unsigned int cmd, unsigned long arg) {
  printk("my_dev_ioctl() is called. cmd = %d, arg = %ld\n", cmd, arg);
  return 0;
}

static const struct file_operations my_dev_fops = {
    .owner = THIS_MODULE,
    .open = my_dev_open,
    .release = my_dev_close,
    .unlocked_ioctl = my_dev_ioctl,
};

static struct miscdevice helloworld_miscdevice = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "mydev",
    .fops = &my_dev_fops,
};

static int __init my_prob(struct platform_device* pdev) {
  int ret_val;
  printk("my_prob() function is called.\n");
  ret_val = misc_register(&helloworld_miscdevice);

  if (ret_val != 0) {
    printk("could not register the misc device mydev");
    return ret_val;
  }
  printk("mydev: got minor %i\n", helloworld_miscdevice.minor);
  return 0;
}

static int __exit my_remove(struct platform_device* pdev) {
  printk(KERN_NOTICE "my_remove() function is called\n");
  misc_deregister(&helloworld_miscdevice);
  return 0;
}

static const struct of_device_id my_of_ids[] = {
    {.compatible = "arrow,hellokeys"},
    {},
};

MODULE_DEVICE_TABLE(of, my_of_ids);

static struct platform_driver my_platform_driver = {
    .probe = my_prob,
    .remove = my_remove,
    .driver = {
        .name = "hellokeys",
        .of_match_table = my_of_ids,
        .owner = THIS_MODULE,
    }
};

module_platform_driver(my_platform_driver);