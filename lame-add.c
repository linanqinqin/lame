// lame-add.c
#include <stdio.h>
extern int __vdso_lame_add(int x, int y);  // declare the vDSO function

int main() {
    int result = __vdso_lame_add(1, 3);
    printf("lame_add(1,3) = %d\n", result);
    return 0;
}
