
/* ripped from getdtors.c */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <dirent.h>

unsigned long get_sect_addr(unsigned long tmp4)
{
  char exec_buf[1024];
  char *objdump = "/usr/bin/objdump";
  char file[128];
  char buf[1024], sect[1024];
  FILE *f;
  unsigned long ret = 0, tmp1, tmp2, tmp3;

  sprintf(file, "/var/tmp/tmprand%i", rand());
   sprintf(exec_buf, "%s -h /usr/bin/crontab > %s", objdump, file);

  system(exec_buf);

  f = fopen(file, "r");
  if (!f) {
    perror("fopen()");
    exit(0);
  }

  while (!feof(f)) {
    fgets(buf, 1024, f);
    sscanf(buf, "  %i .%s %x %x \n", &tmp1, sect, &tmp2, &tmp3);
    if (strcmp(sect, tmp4)) continue;
    ret = tmp3;
    break;
  }

  if (file)
     unlink(file);

  if (!ret) {
    printf("can't read %s addr\n", tmp4);
    exit(0);
  }

  return ret;
}

int main(int argc, char **argv) {

 unsigned long sect_addr = 0xAABBCCDD;
 int verbose = 0;

 if (argc < 2) {
    printf ("usage: %s init_array | fini_array\n", argv[0]);
    exit(1);
  }
    sect_addr = get_sect_addr(argv[1]);

 if (verbose) {
    printf("\n%s addr is at 0x%08x\n", argv[1],sect_addr);
 }
     printf("0x%08x\n", sect_addr);
     fflush(stdout);

return 0;

}
