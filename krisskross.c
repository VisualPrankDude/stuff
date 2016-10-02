/*

gdb stepi

/build/gdb-HnfxP_/gdb-7.10/gdb/elfread.c:977: internal-error: elf_gnu_ifunc_resolver_return_stop: Assertion `b->loc->next == NULL' failed.
A problem internal to GDB has been detected,


,rasm2 -b 64 'jmp 0x601020'
e91b106000

objdump -R argv0
0000000000601030 R_X86_64_JUMP_SLOT  memcpy

*/

#include <stdio.h>
#include <string.h>

#define SC "\xe9\x1b\x10\x60\x00"

int main() {
    printf("0x%x\n",0x61018); /* 0x61018 is printf */
    memcpy(0x601018,SC,2);    /* try overwrt printf@got, jmp to memcpy */
    return 0;
}

/* 
(gdb) stepi
_dl_new_object (realname=realname@entry=0x7ffff7df655c "", libname=libname@entry=0x7ffff7df655c "", type=type@entry=0, 
    loader=loader@entry=0x0, mode=mode@entry=536870912, nsid=nsid@entry=0) at dl-object.c:97
97      dl-object.c: No such file or directory.
(gdb) stepi
*/
