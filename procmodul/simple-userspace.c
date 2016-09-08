#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
int main(int argc, char **argv)
{
    FILE *fp;
    size_t count;
    char *str = argv[1];
 
    fp = fopen("/proc/passwords", "w");
    if(fp == NULL) {
        perror("failed to open tresor :]");
        return EXIT_FAILURE;
    }
    if(argc!=2) {puts("I don't log empty passwords"); return EXIT_FAILURE;}
    count = fwrite(str, 1, strlen(str), fp);
    if(count >0) 
     fwrite("\n", 1, strlen(str), fp);
      fclose(fp);
      printf("Wrote %zu bytes.\n", count);
    return EXIT_SUCCESS;
}
