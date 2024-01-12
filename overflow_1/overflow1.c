#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



int win(){

    system("/bin/sh");
}



void setup(){

    setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stdin, 0LL, 1, 0LL);

}

void leakme(){

    printf("Toma unas addresses\n");
    printf("Win function : 0x%llx \n", &win);
    


}


void vuln(){

    char buffer[16];
    printf("Haz el overflow aca : ");
    read(0, buffer, 0x100);
}

int main(){
    setup();
    leakme();
    vuln(); 

}