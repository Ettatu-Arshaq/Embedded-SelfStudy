// Online C compiler to run C program online
#include <stdio.h>

int main() {
int x = 100;
int *p = &x;

printf("x = %d\n", x);
printf("*p = %d\n", *p);
 *p=200;
printf("x = %d\n", x);
printf("*p = %d\n", *p);

    return 0;
}