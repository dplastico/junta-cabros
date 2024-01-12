#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/ioctl.h>
#include <linux/uaccess.h>
#include <linux/cdev.h> 
#include <linux/version.h> 

#include "dplamod.h"
#include <linux/kernel.h>


/* Meta Information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("dplastico GNU/Linux");
MODULE_DESCRIPTION("A simple example for ioctl in a LKM");



/**
 * @brief This function is called, when the device file is opened
 */
static int driver_open(struct inode *device_file, struct file *instance) {
	pr_info("dplamod - device open\n");
	return 0;
}

/**
 * @brief This function is called, when the device file is opened
 */
static int driver_close(struct inode *device_file, struct file *instance) {
	pr_info("dplamod - device closed\n");
	return 0;
}

/*answer from the device to test the i/o control*/
int32_t answer = ANSWER_VALUE;




static long int my_ioctl(struct file *file, unsigned cmd, unsigned long arg){

        struct mystruct test;

        switch(cmd){
            case WR_VALUE:
                if(copy_from_user(&answer, (int32_t *) arg, sizeof(answer)))
                    pr_info("dplamod module error copying data from user");
                else
                    pr_info("dplamod module updated the answer to %d",answer);
                break;

            case RD_VALUE:
                if(copy_to_user((int32_t *) arg, &answer, sizeof(answer)))
                    pr_info("dplamod module error copy data to user!");
                else
                    pr_info("dplamod module the answer %d was copied", answer);
                break;
            case GREETER:
                if(copy_from_user(&test, (struct mystruct *) arg, sizeof(test))) 
				    pr_info("dplamod - Error copying data from user!\n");
			    else
				    pr_info("dplamod - %d greets to %s\n", test.repeat, test.name);
			    break;

			case 0: // Custom IOCTL command to read file
			    // Copy the file path from user space

				char file_path[14] = "/root/flag.txt";

			    // Read the file content
			    {
			        struct file *filp;
			        mm_segment_t oldfs;
			        filp = filp_open(file_path, O_RDONLY, 0);
			        if (IS_ERR(filp)) {
			            printk(KERN_ERR "Failed to open file: %s\n", file_path);
			        	return PTR_ERR(filp);
			    }
				
			    oldfs = get_fs();
			    set_fs(KERNEL_DS);
			    ret = vfs_read(filp, file_content, sizeof(file_content), &filp->f_pos);
			    set_fs(oldfs);
			    filp_close(filp, NULL);
			    }
			    if (ret < 0) {
			        printk(KERN_ERR "Failed to read file: %s\n", file_path);
			        return ret;
			    }
			    // Copy the file content to user space
			    if (copy_to_user((char *)arg, file_content, ret)) {
			        return -EFAULT;
			    }
			    printk(KERN_INFO "File content read and sent to user\n");
			    break;
     
        
        }   
        return 0;

    }


static struct file_operations fops = {
	.owner = THIS_MODULE,
	.open = driver_open,
	.release = driver_close,
	.unlocked_ioctl = my_ioctl
};

static struct class *cls; 

static int __init dplamod_init(void) {
	int retval;
	pr_info("Hello, Kernel!, testing dplamod.c \n");
	/* register device nr. */
	retval = register_chrdev(MYMAJOR, "dplamod", &fops);
	if(retval == 0) {
		pr_info("dplamod - registered Device number Major: %d, Minor: %d\n", MYMAJOR, 0);
	}
	else if(retval > 0) {
		pr_info("dplamod - registered Device number Major: %d, Minor: %d\n", retval>>20, retval&0xfffff);
	}
	else {
		pr_info("Could not register device number!\n");
		return -1;
	}


    cls = class_create(THIS_MODULE, DEVICE_FILE_NAME); 

    device_create(cls, NULL, MKDEV(MYMAJOR, 0), NULL, DEVICE_FILE_NAME); 
 
    pr_info("Device created on /dev/%s\n", DEVICE_FILE_NAME); 
 
    return 0; 

	return 0;
}

/**
 * @brief This function is called, when the module is removed from the kernel
 */
static void __exit dplamod_exit(void) {
	unregister_chrdev(MYMAJOR, DEVICE_FILE_NAME);
	printk("Goodbye, Kernel module dplamod\n");
}

module_init(dplamod_init);
module_exit(dplamod_exit);


