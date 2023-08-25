
volatile unsigned int * const GPIO_VAL = (unsigned int *)0x80;

const int ITER_COUNT = 2;
const int BLINK_MODE_0 = 0x10101010;
const int BLINK_MODE_1 = 0x01010101;

int iter_counter = 0;

int main();
// static void sleep();

__attribute__((naked)) void _start() {
    // set stack pointer to 0xe0
    asm(
        "li sp, 0xe0\n"
        "jal main\n"
        "li a0, 44\n"
        "ecall\n"
    );
}

void sleep() {
    asm("nop");
    asm("nop");
    asm("nop");
    iter_counter += 1;
}

int main() {
    //  void (*sleep_ptr)() = &sleep;

    for (int j = 0; j < ITER_COUNT; j++) {
        *GPIO_VAL = BLINK_MODE_0;
        // asm("jal sleep");
        sleep();
        *GPIO_VAL = BLINK_MODE_1;
        // asm("jal sleep");
        sleep();
    }
    *GPIO_VAL = iter_counter;
    return 0;
}

