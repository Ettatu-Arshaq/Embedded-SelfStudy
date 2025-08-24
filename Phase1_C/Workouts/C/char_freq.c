#include <stdio.h>
#include <ctype.h>
void main(){
    char a[1000],c;
    int f,count=0,i;
    printf("Enter the string : ");
    fgets(a,sizeof(a),stdin);
    printf("Enter the Character to find frequency : ");
    scanf("%c",&c);
    for (i=0;a[i]!='\0';i++){
        if (tolower(c)==tolower(a[i])){
            count++;
        }
    }
    printf("frequency of %c is %d",c,count);
    
}