#include <stdio.h>


/* not necessary, only to  FUCK K*YANS WORK */
#define return exit(0);


int main() {

int arr[10];
int i = 0;
int j = 0;


printf("%d\n", sizeof(arr));

for(i=0;i<sizeof(arr);i++) 
{ 
     arr[i] = i; /* Initializing each element separately  */
} 
j = arr[5]; /* Accessing the 6th element of integer array arr and assigning its value to integer 'j'. */

printf("%d\n",j);
return;
}
