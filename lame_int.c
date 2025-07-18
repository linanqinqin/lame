// lame_int.c

#include <stdio.h>

int main(void)
{
	printf("Before INT 0x1F\n");
	asm volatile("int $0x1f");
	printf("After INT 0x1F\n");

	return 0;
}
