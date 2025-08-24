#include <stdio.h>
#include <ctype.h>
void main(){
    int i,j;
    char a[]={'A','2','C','4','5','#','@','a','2','2','2','d','d','e','u','2','2','2','2','2','\0'};
    for (i=0;a[i]!='\0';i++){
        if(!isalpha(a[i])){
            for(j=i;a[j]!='\0';j++){
                    a[j]=a[j+1];
            }
            i--;
        }
    }
    printf("Output String : ");
    puts(a);

}