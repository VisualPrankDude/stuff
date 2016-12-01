/* update by VisualPrankDude  */
/*
 * 0x4553 - ElectronicSouls - 0x4553 
 * search in a binary or core dump for a user supplied string and get the exact location in memory.
 * idea is based on sectorx's segment.c which is much better, but this was made for fun and works well so wtf :)
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <elf.h>


void Header(int fd) 
{
     Elf64_Ehdr ehdr;
     if (lseek(fd,0,SEEK_SET)==-1)
         fprintf(stderr,"friday: won't lseek\n");
         return 1;
     
     if (read(fd,&ehdr,sizeof(Elf64_Ehdr)==-1))
         fprintf(stderr,"friday: won't read\n");
         return 1;

     fprintf(stderr,"ELF Binary Header:\n");
     fprintf(stderr,"ident..:  %s\n",ehdr.e_ident);
     fprintf(stderr,"type...: ");

     switch (ehdr.e_type){
      case 2:
      printf("Executable\n");
      break;
      case 4:
      printf("Core\n");
      break;
      default:
      printf("Invalid File!\n");
      exit(1);
      break; 
     }
     puts(".");
}

int main(int argc, char *argv[])
{	
	struct stat st_str;

	Elf64_Ehdr *elf_hdr;
	Elf64_Phdr *p_hdr;

	char *file_buf = NULL;
	
	int fd = 0,
	     i = 0,
	     e = 0,
	     s;

	if(argc<3) {
	   puts("coregrep [core] [string]");
	   return 1;
	}

	if((fd=open(argv[1],O_RDONLY))<0) {
	    fprintf(stderr, "Unable to open file!\n");
	    return 1;
	}

       fprintf(stderr,"%s has a valid format!\n",argv[1]);
       fprintf(stderr,"trying to locate string: %.255s\n\n",argv[2]); 

        if (fstat(fd,&st_str)==-1) {
         fprintf(stderr,"friday: won't read\n");
         return 1;
        }

        file_buf=(char *)malloc(st_str.st_size);
        if (!file_buf)
            return 1;
	memset(file_buf,0,st_str.st_size);
        if (file_buf<=0)
            return 1;

	if (read(fd,file_buf,st_str.st_size)<0) {
            fprintf(stderr, "error! read() failed..\n");
	    if(file_buf)
            free(file_buf);
            if(fd)
	    close(fd);

	    return 1;
	}

	elf_hdr = (Elf64_Ehdr *)file_buf;
        Header(fd);

	for (i=0; i < elf_hdr->e_phnum; i++) 
        {
		p_hdr = (Elf64_Phdr *)
                        (file_buf+elf_hdr->e_phoff+(i*elf_hdr->e_phentsize));

                for (e = p_hdr->p_offset; 
                     e < p_hdr->p_offset+p_hdr->p_filesz; 
                     e++)

	        if(!strncmp(file_buf+e,argv[2],strlen(argv[2]))){

                fprintf(stderr, "[String %.255s found at: 0x%08x]\n", 
                         argv[2] , ((p_hdr->p_vaddr+e) - p_hdr->p_offset));
                }
	}

        puts("done.");

	if (file_buf) free(file_buf);
	if (fd) close(fd);

exit(0);
}
