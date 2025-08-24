#include <stdio.h>
int c,r,i,j;
void enterData(int q[][100],int k[][100]);
void sumData(int q[][100],int k[][100],int sum[][100]);
void Display(int s[][100]);
void main(){
    int a[100][100],b[100][100],s[100][100];
    printf("Enter no of rows and columns of matrices[1-100]:");
    scanf("%d%d",&r,&c);
    enterData(a,b);
    sumData(a,b,s);
    Display(s);
        }
void enterData(int q[][100],int k[][100]){
    for(i=0;i<r;i++){
        for (j=0;j<c;j++){
            printf("Array 1:Enter %dth row %dth column Element:",i+1,j+1);
            scanf("%d",&q[i][j]);
        }
    }
    for(i=0;i<r;i++){
        for (j=0;j<c;j++){
            printf("Array 2:Enter %dth row %dth column Element:",i+1,j+1);
            scanf("%d",&k[i][j]);
        }
    }
}
void sumData(int q[][100],int k[][100],int sum[][100]){
    for(i=0;i<r;i++){
        for (j=0;j<c;j++){
            sum[i][j]=q[i][j]+k[i][j] ;
        }
    }
}
void Display(int sum[][100]){
    printf("Array 1 + Array 2 \n");
    for(i=0;i<r;i++){
        for (j=0;j<c;j++){
            printf ("%d\t",sum[i][j]);
        }
        printf("\n");
    }
}