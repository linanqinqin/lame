// lame-int.c
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>

#define INIT_VAL 99

extern volatile int lame_handler_count;
extern int __vdso_lame_add(int x, int y);  // declare the vDSO function

static inline void trigger_lame(void)
{
    asm volatile("int $0xf1");
}

int main() {
    int result = __vdso_lame_add(0, 0);
    printf("lame_add = %x\n", result);

    uint64_t counter = INIT_VAL;
    
    printf("=== LAME Handler Test (Register-based) ===\n");
    
    /* Set initial value in r13 */
    asm volatile("movq %0, %%r13" : : "r"(counter) : "r13");
    printf("Set counter in r13 to: %lu\n", counter);
    
    /* Trigger the LAME interrupt */
    printf("Triggering LAME interrupt (INT $0xF1)...\n");
    trigger_lame();
    
    /* Read the value back from r13 */
    asm volatile("movq %%r13, %0" : "=r"(counter) : : "r13");
    printf("After interrupt, counter in r13: %lu\n", counter);
    
    /* Verify the result */
    if (counter == INIT_VAL + 1) {
        printf("✓ SUCCESS: Counter was incremented by 1!\n");
        printf("✓ LAME handler is working correctly!\n");
        return 0;
    } else {
        printf("✗ FAILURE: Expected %lu, got %lu\n", INIT_VAL+1, counter);
        printf("✗ LAME handler may not be working\n");
        return 1;
    }

    return 0;
}
