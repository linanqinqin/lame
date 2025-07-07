#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include <link.h>      // for AT_SYSINFO_EHDR
#include <sys/auxv.h>

int main(void) {
    // Method A: via dlsym
    void *h = dlopen("linux-vdso.so.1", RTLD_NOW);
    void *sym = dlsym(h, "__vdso_lame_entry");
    printf("via dlsym:    __vdso_lame_entry = %p\n", sym);

    // Method B: via getauxval + symbol offset
    Elf64_Ehdr *vdso_base = (Elf64_Ehdr *)getauxval(AT_SYSINFO_EHDR);
    printf("vDSO base via auxv: %p\n", vdso_base);

    return 0;
}
