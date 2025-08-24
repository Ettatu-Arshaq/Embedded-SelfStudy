#include <stdio.h>
#include <stdlib.h>
int main() {
    int *data,n;
    printf("Enter No of elements: ");
    scanf("%d",&n);
    data=(int*)calloc(n,sizeof(int));
    if (data == NULL) {
        printf("Error!!! memory not allocated.");
        exit(0);
    }
    for (int i = 0; i < n; ++i){
        printf("Enter element %d: ",i+1);
        scanf("%d", data + i);
    }
    for (int i = 0; i < n; ++i){
        printf("Element %d:%d\n",i+1, *(data + i));
    }
    free(data);
    return 0;
}



