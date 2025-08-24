#include <stdio.h>
#include <stdlib.h>
int main(){
    int a,i,m;
    char n[100];
    FILE *ftr;
    printf("Enter No of Entries: ");
    scanf("%d",&a);
    ftr=(fopen("C:\\Users\\arsha\\Downloads\\Embedded-SelfStudy\\Phase1_C\\Example\\txtorbin\\Student.txt","w"));
    if (ftr==NULL){
        printf("\nError !");
        exit(1);
    }
    
    for(i=0;i<a;i++){
        printf("\nEnter the name of Student %d :",i+1);
        scanf("%s",&n);
        printf("\nEnter Marks");
        scanf("%d",&m);
        fprintf(ftr,"Name:%s\nMarks:%d\n\n",n,m);
    }
    fclose(ftr);
    return 0;
}