#ifndef DPLAMOD_H 
#define DPLAMOD_H 



/*define major number*/

#define MYMAJOR 100
#define ANSWER_VALUE 420


struct mystruct{
    int repeat;
    char name[16]
}

#define WR_VALUE _IOW('a', 'a', int32_t *)
#define RD_VALUE _IOR('a', 'b', int32_t *)
#define GREETER  _IOW('a', 'c', struct mystruct *)
#define FLAG 0x1337

#define DEVICE_FILE_NAME "dplamod" 
#define DEVICE_PATH "/dev/dplamod" 


#endif