/*

update code from others
dropuid

./dropuid
uid=0(root) gid=0(root) groups=0(root),4(adm),5(tty),24(cdrom),29(audio),30(dip),42(shadow),46(plugdev),1000(sk)
$ id
uid=1004(user) gid=0(root) groups=0(root),4(adm),5(tty),24(cdrom),29(audio),30(dip),42(shadow),46(plugdev),1000(sk)


*/


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main() {

 int s(uid_t uid) {
 setuid(0); system("/usr/bin/id"); 
 if(uid>0) {
            setuid(uid);
   }
 }

#undef setuid
#define setuid s

s(1004);

return system ("/bin/sh");
}
