/*

 call /bin/sh

*/

#include <stdio.h>
#include <string.h>

#define SC "\xe8\x68\x73\x2f\x6e\x69\x62\x2f"

int main() {
    printf("0x%x\n",0x61018); /* 0x61018 is printf */
    memcpy(0x601018,SC,strlen(SC));    /* try overwrt printf@, jmp to memcpy */
    printf("AAAAAhrr\t\v\n");
    return 0;
}
