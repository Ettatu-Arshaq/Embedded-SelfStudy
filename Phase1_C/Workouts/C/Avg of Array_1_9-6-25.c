// Avg of nos
#include <stdio.h>
int main(){
int n,i;
float a[100],s=0,avg;
printf("Enter the no of Elements ");
scanf("%d",&n);
while (n>100||n<1)
 {    
      printf("No of elemets Exceeded the limit \n");
      printf("Enter again");
      scanf("%d",&n);
   }
for (i=0;i<n;i++){
   printf("Enter the %d element",i+1);
   scanf("%f",&a[i]);
   s=s+a[i] ;
}
avg=s/n ;
printf("Average of Array : %2f",avg);
   
 }
