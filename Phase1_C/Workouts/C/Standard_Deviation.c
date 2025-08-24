#include <stdio.h>
#include <math.h> 
float SD(float data[],int n);
int main(){
    int i,n;
    float data[100];
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
    for (i=0;i<n;++i){
        printf("Enter %d Element",i+1);
        scanf("%f",&data[i]); 
    }
    printf("SD of Array is : %.2f",SD(data,n));
    }

float SD(float data[],int n){
    int i;
    float sum=0,mean=0,sd=0;
    for (i=0;i<n;i++){
        sum+=data[i];
    }
    mean=sum/n;
    for (i=0;i<n;i++){
        sd+=pow(data[i]-mean,2);
    } 
    return(sqrt(sd/n));
}
