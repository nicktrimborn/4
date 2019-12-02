/**
 * @file   irqgen_cdev.c
 * @author Nicola Tuveri
 * @date   15 November 2018
 * @version 0.7
 * @target_device Xilinx PYNQ-Z1
 * @brief   A stub module to support the IRQ Generator IP block for the
 *          Real-Time System course (character device support).
 */

# include <linux/kernel.h>           // Contains types, macros, functions for the kernel
# include <linux/device.h>
# include <linux/string.h>
#include <linux/semaphore.h>
# include <linux/cdev.h>             // Header for character devices support
# include <linux/fs.h>               // Header for Linux file system support
# include <linux/uaccess.h>          // Header for userspace access support

# include "irqgen.h"                 // Shared module specific declarations

#define IRQGEN_CDEV_CLASS "irqgen-class"

struct irqgen_chardev {
    // struct semaphore sem;
    struct cdev cdev;
    dev_t devt;
    struct device *dev;
    struct class *class;

    // TODO: do we need a sync mechanism for any cdev operation?
};

static struct irqgen_chardev irqgen_chardev;


// The prototype functions for the character driver -- must come before the struct definition
static int     irqgen_cdev_open(struct inode *, struct file *);
static int     irqgen_cdev_release(struct inode *, struct file *);
static ssize_t irqgen_cdev_read(struct file *, char *, size_t, loff_t *);

static struct file_operations fops = {
    .open = irqgen_cdev_open,
    .release = irqgen_cdev_release,
    .read = irqgen_cdev_read,
};

// Initialize the char device driver
int irqgen_cdev_setup(struct platform_device *pdev)
{
    int retval;
    cdev_init(&irqgen_chardev.cdev, &fops);
    irqgen_chardev.cdev.owner = THIS_MODULE;
    irqgen_chardev.cdev.kobj.parent = &pdev->dev.kobj;

    // DONE: dinamically allocate a major and a minor for this chrdev
    retval = alloc_chrdev_region(&irqgen_chardev.devt, 0, 1, DRIVER_NAME);
    if (retval < 0) {
        printk(KERN_INFO KMSG_PFX "Major number allocation failed\n");
        goto err; 
    }
    printk(KERN_INFO KMSG_PFX "Device allocated, major: %d, minor %d\n", 
        MAJOR(irqgen_chardev.devt), MINOR(irqgen_chardev.devt));

    // DONE: add to the system the cdev for the allocated (major,minor)
    //don't forget error handling
    retval = cdev_add(&irqgen_chardev.cdev, irqgen_chardev.devt, 1);
    if(retval < 0) {
        printk(KERN_INFO KMSG_PFX "Unable to add cdev\n");
        goto err_cdev_add;
    }

    // Add an "irqgen" node in the /dev/ filesystem (hint: device_create())
    // don't forget error handling
    // Create device classes
    irqgen_chardev.class = class_create(THIS_MODULE, IRQGEN_CDEV_CLASS);
    if(irqgen_chardev.class == NULL) {
        printk(KERN_INFO KMSG_PFX "Unable to create class %s\n", IRQGEN_CDEV_CLASS );
        goto  err_cdev_add;
    } 

    irqgen_chardev.dev = device_create(irqgen_chardev.class, NULL, irqgen_chardev.devt, NULL, DRIVER_NAME);
    if(irqgen_chardev.dev == NULL) {
        printk(KERN_INFO KMSG_PFX "Unable to create device\n");
        goto err_device_create;
    }
    // TODO: do we need a sync mechanism for any cdev operation?
    // sema_init(&irqgen_chardev.sem, 1);
    return 0;
    // DONE: use labels to handle errors and undo any resource allocation
err_device_create:
    class_destroy(irqgen_chardev.class);
err_cdev_add:
    cdev_del(&irqgen_chardev.cdev);
    // kfree(&irqgen_chardev.cdev);
err_alloc_chrdev:
    unregister_chrdev_region(irqgen_chardev.devt, 1);
err:
    printk(KERN_ERR KMSG_PFX "irqgen_cdev_setup() failed\n");
    return retval;
}

void irqgen_cdev_cleanup(struct platform_device *pdev)
{
    // destroy, unregister and free, in the right order, all resources
    // allocated in irqgen_cdev_setup()
    cdev_del(&irqgen_chardev.cdev);
    device_destroy(irqgen_chardev.class, irqgen_chardev.devt);
    class_destroy(irqgen_chardev.class);
    unregister_chrdev_region(irqgen_chardev.devt, 1);
    // kfree(&irqgen_chardev.cdev);

}

static u8 already_opened = 0;

static int irqgen_cdev_open(struct inode *inode, struct file *f)
{
# ifdef DEBUG
    printk(KERN_DEBUG KMSG_PFX "irqgen_cdev_open() called.\n");
# endif
    // down(&irqgen_chardev.sem);
    if (already_opened) {
        return -EBUSY;
    }
    already_opened = 1;
    // up(&irqgen_chardev.sem);
    return 0;
}

static int irqgen_cdev_release(struct inode *inode, struct file *f)
{
# ifdef DEBUG
    printk(KERN_DEBUG KMSG_PFX "irqgen_cdev_release() called.\n");
# endif

    if (!already_opened) {
        return -ECANCELED;
    }
    already_opened = 0;
    return 0;
}

// This will write in the userspace buffer one line at a time, the
// client (or the std library) will retry automatically.
//
// NOTE: We require the userland buffer to be at least 60 bytes (count>=60)
static ssize_t irqgen_cdev_read(struct file *fp, char *ubuf, size_t count, loff_t *f_pos)
{
    // We cannot write to user space directly: we need to use a buffer
    // in kernel space and then use specialized functions to copy the
    // data to provided the userland buffer.
#define KBUF_SIZE 100
    static char kbuf[KBUF_SIZE];
    ssize_t ret = 0;

    struct latency_data v;

    if (count < 60) {
        printk(KERN_ERR KMSG_PFX "read() buffer too small (<=60).\n");
        return -ENOBUFS;
    }

    // TODO: how to protect access to shared r/w members of irqgen_data?
    spin_lock_irqsave(&irqgen_data->s_lock, irqgen_data->flags);
        if (irqgen_data->rp == irqgen_data->wp) {
            // Nothing to read
            spin_unlock_irqrestore(&irqgen_data->s_lock, irqgen_data->flags);
            return 0;
        }
    

    v = irqgen_data->latencies[irqgen_data->rp];
    irqgen_data->rp = (irqgen_data->rp + 1)%MAX_LATENCIES;
    spin_unlock_irqrestore(&irqgen_data->s_lock, irqgen_data->flags);
    ret = scnprintf(kbuf, KBUF_SIZE, "%u,%lu,%llu\n", v.line, v.latency, v.timestamp);
    if (ret < 0) {
        goto end;
    } else if (ret == 0) {
        ret = -ENOMEM;
        goto end;
    }

    // TODO: how to transfer from kernel space to usrooter space?
    *f_pos += ret+1;
    // copy_to_user( ubuf, kbuf, ret+1);
    copy_to_user( ubuf, kbuf, ret+1);

end:
    // spin_unlock_irqrestore(&irqgen_data->s_lock, irqgen_data->flags);
    return ret;
#undef KBUF_SIZE
}

