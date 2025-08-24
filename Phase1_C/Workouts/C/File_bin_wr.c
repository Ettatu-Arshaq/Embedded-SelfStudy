#include <stdio.h>
#include <stdlib.h>
typedef struct{
    char name[20];
    int height;
}std;
int main(){
    std stud1[5],stud2[5];
    int i,n;
    FILE *fptr;
    fptr=(fopen("C:\\Users\\arsha\\Downloads\\Embedded-SelfStudy\\Phase1_C\\Example\\txtorbin\\Entry.txt","wb"));
    if (fptr==NULL){
        printf("ERrOR!");
        exit(0);
    }
    printf("Enter no of entries");
    scanf("%d",&n);
    for (i=0;i<n;i++){
        printf("Entry %d::Enter Name:",i+1);
        scanf("%s",stud1[i].name);
        printf("Enter Height:");
        scanf("%d",&stud1[i].height);
    }
    fwrite(stud1,sizeof(std),n,fptr);
    fclose(fptr);
    fptr=(fopen("C:\\Users\\arsha\\Downloads\\Embedded-SelfStudy\\Phase1_C\\Example\\txtorbin\\Entry.txt","rb"));
    fread(stud2,sizeof(std),n,fptr);
    for (i=0;i<n;i++){
        printf("\nNAme:%s",stud2[i].name);
        printf("\nHeight%d",stud2[i].height);
    }
    fclose(fptr);

} 