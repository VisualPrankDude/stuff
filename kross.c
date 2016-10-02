#include <stdio.h>
#include <string.h>

#define E "\xe8\x68\x73\x2f\x6e\x69\x62\x2f"

int main() {
    printf("0x%x\n",0x61018); /* 0x61018 is printf */
    memcpy(0x601018,E,strlen(E));
    return 0;
}
