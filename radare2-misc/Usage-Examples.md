# save destroyed file

- [Search strings](#search-strings)
- [Search executable sections](#search-executable-sections)
- [Search a specific instruction](#search-a-specific-instruction)
- [Search for relative addressing](#search-for-relative-addressing)
- [Search xrefs](#search-xrefs)
- [Search string in functions](#Search-string-in-functions)
- [Debugging session](#debugging-session)
- [Modifying files](#modifying-files)
- [Using the visual mode](#using-the-visual-mode)
- [Get the description of an opcode](#get-the-description-of-an-opcode)
- [Quoting Commands](#quoting-commands)
- [Disassemble @ Entrypoint](#disassemble-entrypoint)
- [Rename Function](#rename-function)
- [List Functions](#list-functions)
- [Equivalent of hitting "x" in Hopper or IDA?](#equivalent-of-hitting-x-in-hopper-or-ida)
- [I get a "random" exitcode when exiting r2](#i-get-a-random-exitcode-when-exiting-r2)
- [shift the code to the right and avoid misprint of jmp info](#shift-the-code-to-the-right-and-avoid-misprint-of-jmp-info)

###Search strings

```
$ r2 /bin/ls
[0x0040488f]> /i Stallman
Searching 8 bytes from 0x00400238 to 0x0040488f: 53 74 61 6c 6c 6d 61 6e 
[# ]hits: 004138 < 0x0040488f  hits = 0   
```

Synopsis

```
|Usage: /[amx/] [arg]
```

###Search executable sections
```
[0x004004a0]> pd~rwx
;      [12] va=0x004004a0 pa=0x000004a0 sz=434 vsz=434 rwx=-r-x .text
|   ;  [13] va=0x00400654 pa=0x00000654 sz=9 vsz=9 rwx=-r-x .fini
|  ;  [15] va=0x004006a4 pa=0x000006a4 sz=60 vsz=60 rwx=-r-- .eh_frame_hdr
   ;  [16] va=0x004006e0 pa=0x000006e0 sz=276 vsz=276 rwx=-r-- .eh_frame
```

###Search a specific instruction
```
/c xor r  # match rdx,rdi
f hit_0 @ 0x00400088   # 3: xor rdx, rbx
f hit_1 @ 0x004000a2   # 3: xor rdi, rdi
/c cpuid 
f hit_0 @ 0x00400082   # 2: cpuid
```

To see the full listing pdf is your friend.

###Search for relative addressing

```
echo 'pid~rip' | r2 -qn ./nn 
0x00000099 488d35daffffff lea rsi, [rip-0x26]
```

###Searching xrefs

```
$ r2 /bin/ls
[0x0040488f]> aa
[0x0040488f]> ax
d 0x00411d20 -> 0x0040489e
d 0x00411cb0 -> 0x004048a5
d 0x004028c0 -> 0x004048ac
C 0x004048b3 -> 0x00402500
d 0x0061a5ff -> 0x004048c0
d 0x0061a5f8 -> 0x004048e2

[0x0040488f]> pdf ~XREF
|          ; DATA XREF from 0x00411d20 (unk)
|          ; DATA XREF from 0x00411cb0 (fcn.00411ca5)
|          ; DATA XREF from 0x004028c0 (fcn.004028c0)
           ; CODE (CALL) XREF from 0x0040493d (fcn.00404929)
           ; DATA XREF from 0x0061a5ff (unk)
|          ; DATA XREF from 0x0061a5f8 (unk)
```

###Searching string in functions

```
pd 1@str.Hello~fcn
```

###Search filesystem with arguments

workaround: 
```
[0x0040488f]> ls -l ~foo
crw-r--r--  1    0:0    0               foo4
brw-r--r--  1    0:0    0               foo3
drwxr-xr-x  1 1011:1011 40              foo2/
-rw-r--r--  1 1011:1011 0               foo1
```

###Debugging session

a short example zlul grummel session 
(note: add your sessions here, or see examples in issues/radare.org examples)

```
r2 -e asm.middle=true -e scr.color=0 blah/a.out
[0x0040488f]> af
[0x0040488f]> / __stack_chk_fail
Searching 16 bytes from 0x00400238 to 0x0040488f: 5f 5f 73 74 61 63 6b 5f 63 68 6b 5f 66 61 69 6c 
[# ]hits: 104877 < 0x0040488f  hits = 1   
0x004010ec hit0_0 "__stack_chk_fail"
[0x0040488f]> db 0x0040488f
[0x0040488f]> db
0x0040488f - 0x00404890 1 --- sw break enabled cmd=""
[0x0040488f]> !!
History saved to .config/radare2/history

TBD!1
```


###Modifying files

This is important to always enable write mode ('-w') while opening file to be able to modify it:
```
$ r2 -w morrn
[0x0040488f]> w FOOBAR
[0x0040488f]> q
$ grep FOO morrn 
Binary file morrn matches
```
or for scripts:

```
$ echo wx cc| r2 -qnw morrn
```


####Using the visual mode

- enter with V
- run radare command with ':' eg.
```
:> af 
```
- exit with q

####Get the description of an opcode

```
[0x00000000]> ?d mov
moves data from src to dst
```

####Graph!

First you need to analyze the code with `af` or `aa`
Then:

    ag $$ > a.dot
    !dot -Tpng a.dot > a.png

or just `agv`

####Quoting Commands

Currently radare does not support quoting of arguments.  If there is a command that requires a reserved radare character like `;`, then the command needs to be quoted like this:

    [0x000002af]> "java i_mref blah append (ILjava/lang/String;)V"

For commands that have quotes in the command, perform quoting like:

    [0x000002af]> "command \"arg0\" arg1"

###Disassemble @ Entrypoint

     [0x000002af]> aa
     [0x000002af]> pdf @ entry0

###Rename Function

    [0x000002af]> fr fcn.004024f6 lol

To modify the name of the functions shown in calls you can use:

    [0x000002af]> afn lol 0x004024f6

###List Functions

    [0x00400440]> afl
    0x00400440  42  1  sym._start
    0x00400420  6  1  sym.imp.__libc_start_main
    0x00400426  16  1  fcn.00400426
    0x0040040c  10  2  fcn.0040040c

###Equivalent of hitting "x" in Hopper or IDA?

    axt @str.StringFlag will display the xrefs,

###I get a "random" exitcode when exiting r2

You can choose an exit code with `q num` for example `q 10` then `echo $?` will display 10
Otherwise the return value is if not 0 or 1 is the last value computed in RNum

###shift the code to the right and avoid misprint of jmp info

You can use "asm.lineswidth: Number of columns for program flow arrows" to assign a new value just "e asm.lineswidth=new_value"
