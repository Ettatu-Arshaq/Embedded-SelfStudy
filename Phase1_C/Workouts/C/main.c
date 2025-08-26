#include <stdio.h>
#include <stdlib.h>

// Global variable
int g_var = 10;

// Extern variable (declared here, defined in another file)
extern int ext_var;

void demo_auto();
void demo_static();
void demo_register();
void demo_heap();
void demo_volatile();

int main() {
    printf("===== Memory Demo Project =====\n");

    demo_auto();
    demo_static();
    demo_static(); // call twice to see persistence
    demo_register();
    demo_heap();
    demo_volatile();

    return 0;
}

void demo_auto() {
    int local = 5;  // auto variable
    printf("Auto (local) variable address: %p value: %d\n", (void*)&local, local);
}

void demo_static() {
    static int counter = 0;
    counter++;
    printf("Static variable persists, counter = %d at %p\n", counter, (void*)&counter);
}

void demo_register() {
    register int r = 42;
    printf("Register variable (cannot print address) value = %d\n", r);
}

void demo_heap() {
    int *ptr = (int*)malloc(sizeof(int));
    *ptr = 99;
    printf("Heap allocated variable at %p value: %d\n", (void*)ptr, *ptr);
    free(ptr);
}

void demo_volatile() {
    volatile int flag = 1;
    printf("Volatile variable (simulated hardware flag) value = %d\n", flag);
}
