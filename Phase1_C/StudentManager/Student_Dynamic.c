#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int roll;
    char name[50];
    float marks;
}std;
void addstd();
void display();
void search();
void delete();
int main(){
    int ext=0,ch;

    do{
        printf("=========== STUDENT RECORD MANAGER ===========\n1. Add New Student\n2. View All Students\n3. Search Student by Roll Number\n4. Delete Student Record\n5. Exit\n==============================================\nEnter your choice: _");
        scanf("%d",&ch);
        if(ch==1){addstd(); }
        else if (ch==2){display();}
        else if(ch==3){search();}
        else if(ch==4){delete();}
        else if (ch==5){exit(0);}
        else{printf("\nWrOng Entry !!!\n");}
    }
    while(ext==0);
}

void addstd() {
    int nr;
    FILE *ftr;

    printf("\nEnter No of Entries : ");
    scanf("%d", &nr);

    // Allocate memory dynamically AFTER knowing nr
    std *st = (std*) malloc(nr * sizeof(std));
    if (st == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    ftr = fopen("studentdata.bin", "ab");
    if (ftr == NULL) {
        printf("\nERROR! Couldn\'t Open File\n");
        free(st);
        exit(0);
    }

    for (int i = 0; i < nr; i++) {
        printf("\nEnter Entry No %d\n", i + 1);
        printf("RollNo: ");
        scanf("%d", &st[i].roll);
        printf("Name: ");
        scanf("%s", st[i].name);
        printf("Marks : ");
        scanf("%f", &st[i].marks);

        fwrite(&st[i], sizeof(std), 1, ftr);
    }

    printf(" Successfully Saved Entries\n");
    fclose(ftr);
    free(st); // Free allocated memory
}


void display(){
    std st;
    FILE *ftr;
    ftr=(fopen("studentdata.bin","rb"));
    if (ftr==NULL){
        printf("\nERrOR!Couldnt Open File\n");
        exit(0);
    }    
    int i=0;
    while ((fread(&st,sizeof(std),1,ftr))==1){
        printf("Rollno:%d\tName:%s\tMarks:%.2f\n",st.roll,st.name,st.marks);
        i++;
    }
    fclose(ftr);
}
void search(){
    int n;
    std st;
    FILE *ftr;
    ftr=(fopen("studentdata.bin","rb"));
    if (ftr==NULL){
        printf("\nERrOR!Couldnt Open File\n");
        exit(0);
    }
    printf("Enter the RollNo to search :");
    scanf("%d",&n);   
    while ((fread(&st,sizeof(std),1,ftr))==1){
        if(st.roll==n){
            printf("Record Found!\n");
            printf("Rollno:%d\tName:%s\tMarks:%.2f\n",st.roll,st.name,st.marks);
            break;
        }
    }
    fclose(ftr);
}
void delete(){
    char cnf;
    int f=0,rn;
    std st;
    FILE *ftr;
    FILE *tmp;
    tmp=(fopen("Temp.bin","wb"));
    ftr=(fopen("studentdata.bin","rb"));
    if (ftr==NULL||tmp==NULL){
        printf("\nERrOR!Couldnt Open File\n");
        exit(1);
    }
    printf("Enter the RollNo to Delete :");
    scanf("%d",&rn);   
    while ((fread(&st,sizeof(std),1,ftr))==1){
        if(st.roll!=rn){
                fwrite(&st,sizeof(std),1,tmp);
            }
        if(st.roll==rn){
            Confirm:
            printf("Confirm[y\\n] !Do you really wanted to delete: ");
            printf("Rollno:%d\tName:%s\tMarks:%.2f\n",st.roll,st.name,st.marks);
            scanf(" %c",&cnf);
            if (cnf=='Y'||cnf=='y'){
                f=1;
            }    
            else if(cnf=='N'||cnf=='n'){
                break;
            }
            else{
                printf("!!!!!!1Wrong Choice!!!!!!!\n ");
                goto Confirm;
            }
        }
    }   
    fclose(ftr);
    fclose(tmp);
    if(f==1){
        remove("studentdata.bin");
        rename("Temp.bin","studentdata.bin");
        printf("\nRecord removed Sucessfully\n");
    }   
    else{
        remove("Temp.bin");
    }

}
