#include <stdio.h>
void main(){
    int a[100][100],b[100][100],i,j,s[100][100],r,c;
    printf("Enter no of rows and columns of matrices[1-100]:");
    scanf("%d%d",&r,&c);
    for(i=0;i<r;i++){
        for (j=0;j<c;j++){
            printf("Array 1:Enter %dth row %dth column Element:",i+1,j+1);
            scanf("%d\n",&a[i][j]);
        }
    }
    for(i=0;i<r;i++){
        for (j=0;j<c;j++){
            printf("Array 2:Enter %dth row %dth column Element:",i+1,j+1);
            scanf("%d\n",&b[i][j]);
        }
    }
    for(i=0;i<r;i++){
        for (j=0;j<c;j++){
            s[i][j]=a[i][j]+b[i][j] ;
        }
    }
    printf("Array 1 + Array 2 ");
    for(i=0;i<r;i++){
        for (j=0;j<c;j++){
            printf ("%d\t",s[i][j]);
        }
        printf("\n");
    }
                

             
        }