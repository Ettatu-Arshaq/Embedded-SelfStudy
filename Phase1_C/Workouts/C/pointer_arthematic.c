// Online C compiler to run C program online
#include <stdio.h>

int main() {
int arr[3] = {10, 20, 30};
int *p = arr;

printf("%d\n", *p);       // prints 10
printf("%d\n", *(p+1));   // prints 20
printf("%d\n", *(p+2));   // prints 30


    return 0;
}