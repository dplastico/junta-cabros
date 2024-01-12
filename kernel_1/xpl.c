#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/cdev.h>

#include "dplamod.h"

int main(){

    int answer;

    struct mystruct test = {0, "test"};



    int dev = open("/dev/dplamod", O_WRONLY);
	
	
	printf("DEBUG : %ld\n", WR_VALUE);
    
	
	if(dev == -1){
        printf("Error opening the device %s \n", DEVICE_PATH);
        return -1;
    }

	printf("Opening was successfull!\n");

	ioctl(dev, RD_VALUE, &answer);
	printf("The answer is %d\n", answer);

	answer = 123;

	ioctl(dev, WR_VALUE, &answer);
	ioctl(dev, RD_VALUE, &answer);
	printf("The answer is  now %d\n", answer);

	ioctl(dev, GREETER, &test);

	
	close(dev);

}
