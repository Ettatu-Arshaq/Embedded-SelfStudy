#include <stdio.h>
int main() {
    int i=0,n=0;
    double arr[100],l=0;

    while (1) {
        printf("Enter No of Elements [1-100]");
        scanf("%d",&n);
        if (n<100){
            break;
        }
        else{
            printf("Error");
            
        }
    }

    for (i=0;i<n;i++){
        printf("Enter %d Element",i+1);
        scanf("%lf",&arr[i]); 
    }

    for (i=0;i<n;i++){
        if (l<arr[i]){
        l=arr[i]; 
        }
    }
    printf("Largest Element in array : %.2f",l);
}