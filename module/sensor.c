#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "dummy_sensor"
static int major_num;

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
    char msg[] = "Temperature: 45C\n";
    int msg_len = sizeof(msg);
    
    if (*offset >= msg_len) return 0; // EOF
    if (len > msg_len - *offset) len = msg_len - *offset;
    
    if (copy_to_user(buffer, msg + *offset, len) != 0) return -EFAULT;
    *offset += len;
    return len;
}

static struct file_operations fops = { .read = dev_read };

static int __init sensor_init(void) {
    major_num = register_chrdev(0, DEVICE_NAME, &fops);
    printk(KERN_INFO "DummySensor: Loaded with major number %d\n", major_num);
    return 0;
}

static void __exit sensor_exit(void) {
    unregister_chrdev(major_num, DEVICE_NAME);
    printk(KERN_INFO "DummySensor: Unloaded\n");
}

module_init(sensor_init);
module_exit(sensor_exit);
MODULE_LICENSE("GPL");

