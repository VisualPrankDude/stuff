/* move stdout to fd5 */

#include <stdio.h>
#include <stdlib.h>


#define MAX_FD 1024

int main() {
int i;
for (i=0;i<MAX_FD;i++)
        { 
	if (i==1||i==5) { i++; } 
	if (i) { close(i); }
	}

if ( chdir("/tmp")==-1)  {
	exit(1);
}
system("/bin/bash");
return 1;
}


#!/bin/sh
# tldp/bash scripting guide 
#exec 5<>  /dev/fd/1 # Open stdout and assign fd 5 to it
#./f
#read <&5         # Read the first line
#exec 5>&-        # Close fd 5
#echo $REPLY
