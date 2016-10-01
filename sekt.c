/*

   ripped from hicks

 */


#include <sys/stat.h>
#include <sys/utsname.h>
#include <sys/mman.h>
#include <elf.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


#define GNU   ".gnu.version"

int print_shdr(const char *const f, size_t s) {

	int fd  = open(f, O_RDONLY);
	char *p = mmap(0, s, PROT_READ, MAP_PRIVATE, fd, 0);

	if(p==NULL) {
		printf("mmap() failed\n");
		exit(22);
	}


	Elf64_Ehdr *ehdr = (Elf64_Ehdr*)p; /* checked in main */
	Elf64_Shdr *shdr = (Elf64_Shdr *)(p + ehdr->e_shoff);
	Elf64_Phdr *phdr = (Elf64_Phdr *)p;

	if(phdr->p_type==6) { // XXX
		printf("[+] Found PT_PHDR magic\n");
	}

	if(ehdr->e_machine != EM_X86_64) {
		printf("[-] Not 64bit\n");
		exit(1);
	}
	if (ehdr->e_type == ET_CORE) {
		printf ("[i] This is a core file\n");
		exit (1);
	} else if
		(ehdr->e_type == ET_DYN) {
			printf ("[+] Shared object\n");
		} else if
			(ehdr->e_type == ET_REL) {
				printf ("[+] Relocatable object\n");
			}  else { 
				if (ehdr->e_type != ET_EXEC)  {
					printf ("[-] fake\n");
					exit (1);
				}
			}

		if (ehdr->e_ident ==  3)  {  /* ELFOSABI_LINUX) */
			printf("[o] Linux (ELFOSABI_LINUX) \n");
			//exit(1);
		}


		printf("Dumping all sections\n\
				segment\tindex\toffset\tsize\tsection name\n");

		if ( ehdr->e_shnum == 0 ||\
				ehdr->e_shoff == 0 ||\
				ehdr->e_shstrndx == 0 ) {
			printf("[-] e_shnum/eshoff/e_shstrndx missing\n");
			exit(1);
		}

		int shnum = ehdr->e_shnum;
		Elf64_Shdr *sh_strtab = &shdr[ehdr->e_shstrndx];
		const char *const sh_strtab_p = p + sh_strtab->sh_offset;
		printf("shnum: %d\n", shnum);
		char *LOAD1;

		/* owned machine */
		if(strstr(0x0021cd10,LOAD1)) {
			/* printf("[+] Found PT_LOAD0 at 0x%u\n", 0x0021cd10 - 0x1c7f4);  /bin/ls XXX */ 
			printf("[+] Found PT_LOAD0 at 0x%u\n", 0x0021cd10 - ehdr->e_ehsize); // XXX
			printf("[+] Found PT_LOAD1 at 0x%u\n");
		}


		for (int i = 0; i < shnum; i++) {

			printf("%d\n ", phdr->p_flags & ( PF_R | PF_W | PF_X )); /* XXX */

			if (strcmp(GNU, sh_strtab_p + shdr[i].sh_name) == 0 ) {
				printf("Binary is from\033[91m");
				printf(" GNU Project\n");
				printf("\x1B[0;39m");
			}

			if (strcmp(".got", sh_strtab_p + shdr[i].sh_name) == 0 ) {
				printf("Binary is \033[92mdynamically linked\n");
				printf("\x1B[0;39m");
			}

			if (strcmp(".text", sh_strtab_p + shdr[i].sh_name) < 0 ) {
				printf("Binary has \033[94mno .text section\n");
				printf("\x1B[0;39m");
				exit (1);
			}

			if (getenv("DUMPSECT")) { 
				printf("%2d: %4d\t0x%lu,\t0x%lu\t'%s'\n", i, shdr[i].sh_name,
						shdr[i].sh_offset,  shdr[i].sh_size,  sh_strtab_p + shdr[i].sh_name);  
			}
		}
		printf("[+] Done.\n");

		return 0;
}

int check_uname() {  /* check for running arch */
	struct utsname n; 
	uname (&n);
	printf("[+] Found a %.10s system\n", n.sysname);
	return 0;
}



int main(int ac, char *av[]) {
	struct stat st;
	const char *f = "/bin/sh";

	if (1==ac)
		printf("Look for ELF sections by VisualPrankDude\n"); 

	if (ac>1) {
		char buf[4] = {0,0,0,0};
		int testfd = open(av[1],O_RDONLY);
		read(testfd,buf,4);

		if(strstr(buf,"\177ELF")) {
			puts("[+] valid ELF mag so far");
		} else {
			puts("[-] No ELF mag found");
			exit(1);
		}
		buf[0] = '\0';
		close(testfd);
	}
	check_uname(); 
	f = av[1];

	if (stat(f, &st) != 0) {
		puts("[--] System Error");
		return 1;
	}

	return print_shdr(f, st.st_size);

}
