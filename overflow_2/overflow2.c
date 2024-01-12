#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void setup(){

    setvbuf(stdout, 0LL, 2, 0LL);
    setvbuf(stdin, 0LL, 1, 0LL);


}


int useful(){
    __asm__("pop %rdi");

}

int vuln(){

    char leaker[64];
    char buff[32];

    printf("Dame algo para imprimir : ");
    read(0, leaker, sizeof(leaker));
    printf(leaker);

    printf("\nBien! Ahora overflow aca : ");
    read(0, buff, 0x100);

}




int main(){
    setup();
    vuln();

    }