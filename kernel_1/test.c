#include <stdio.h>
#include <stdlib.h>

#define WR_VALUE _IOW('a', 'a', int32_t *)


int main(){

    printf("DEBUG : %d\n", WR_VALUE);
}