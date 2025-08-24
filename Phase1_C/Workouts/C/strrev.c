#include <stdio.h>
void revstr();
void main(){
    
    printf("Enter a String :");
    revstr();
}

void revstr(){
    char c ;
    scanf("%c",&c);
    if (c!='\n'){
        revstr();
        printf("%c",c);
    }
}