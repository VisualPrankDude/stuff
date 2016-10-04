/* 

 update code from others, more e

*/


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define PAM \
"password	[success=1 default=ignore]	pam_unix.so obscure md5\n\
password	requisite			pam_deny.so\n\
password	required			pam_permit.so\n"
int main() {
  int fd = open("/etc/pam.d/common-password",O_TRUNC|O_CREAT|O_WRONLY,0600);
  write(fd,PAM,sizeof(PAM));
  close(fd);
  exit(0);
}
