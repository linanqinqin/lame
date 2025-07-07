// lame-int.c
#include <stdio.h>
extern int __vdso_lame_add(int x, int y);  // declare the vDSO function

int main() {
    int result = __vdso_lame_add(0, 0);
    printf("lame_add = %x\n", result);

    printf("About to invoke LAME interrupt (INT 0xF1)\n");

    // Inline assembly to execute INT 0xF1
    asm volatile ("int $0xF1");

    printf("Returned from LAME interrupt (INT 0xF1)\n");

    return 0;
}
