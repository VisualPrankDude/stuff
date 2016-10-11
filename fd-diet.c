#include <stdio.h>
#include <stdlib.h>

int main() {
int i;
for (i=2;i<256;i++)
{ 
   close(i);
}
 chdir("/tmp");
 system("/bin/bash");
 //system("/bin/bash -c \"PS1=,; pwd\"");
 //system("/bin/bash -c \"PS1=, \"");
 return 1;
}
