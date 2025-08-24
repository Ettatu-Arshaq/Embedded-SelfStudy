#include <stdio.h>
#include <ctype.h>
#include <string.h>


int vowel(char a[]){
    int i=0;
    int vow=0;
    for (i=0;a[i]!='\0';i++){
        if (strchr("aeiou",tolower(a[i]))){
            vow++;
        }
    }
    return(vow);
}
int consonent(char a[]){
    int i=0;
    int cons=0;
    for (i=0;a[i]!='\0';i++){
        if (isalpha(a[i]) && !strchr("aeiou",tolower(a[i]))){
            cons++;
        }
    }
    return(cons);
}
int digit(char a[]){
    int dig=0,i=0;
    for (i=0;a[i]!='\0';i++){
        if (isdigit(a[i])){
            dig++;
        }
    }
    return(dig);
}
int space(char a[]){
    int spc=0,i=0;
    for (i=0;a[i]!='\0';i++){
        if (strchr(" ",a[i])){
            spc++;
        }
    }
    return(spc);
}
void main(){
    char a[1000];
    printf("Enter the string : ");
    fgets(a,sizeof(a),stdin);

    printf("Vowels :%d \n",vowel(a));
    printf("Consonents :%d \n",consonent(a));
    printf("digits :%d\n",digit(a));
    printf("Space :%d",space(a));
}

