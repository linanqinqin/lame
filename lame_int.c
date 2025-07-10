// lame-int.c
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#define INIT_VAL = 99

extern volatile int lame_handler_count;
extern int __vdso_lame_add(int x, int y);  // declare the vDSO function

static inline void trigger_lame(void)
{
    asm volatile("int $0xf1");
}

int main() {
    int result = __vdso_lame_add(0, 0);
    printf("lame_add = %x\n", result);

    /* Print initial counter value */
    printf("Initial lame_handler_count: %d\n", lame_handler_count);
    
    /* Set initial value to a known number for easier verification */
    lame_handler_count = INIT_VAL;
    printf("Set lame_handler_count to: %d\n", lame_handler_count);
    
    /* Trigger the LAME interrupt */
    printf("Triggering LAME interrupt (INT $0xF1)...\n");
    trigger_lame();
    
    /* Print the counter value after the interrupt */
    printf("After interrupt, lame_handler_count: %d\n", lame_handler_count);
    
    /* Verify the result */
    if (lame_handler_count == INIT_VAL + 1) {
        printf("✓ SUCCESS: Counter was incremented by 1!\n");
        printf("✓ LAME handler is working correctly!\n");
        return 0;
    } else {
        printf("✗ FAILURE: Expected 43, got %d\n", lame_handler_count);
        printf("✗ LAME handler may not be working\n");
        return 1;
    }

    return 0;
}
