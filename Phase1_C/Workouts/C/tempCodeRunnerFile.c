#include <stdio.h>
#include <string.h>

int main() {
   char str[5][50], temp[50];
   printf("Enter 5 words: ");

   // Getting strings input
   for (int i = 0; i < 5; ++i) {
      fgets(str[i], sizeof(str[i]), stdin);
      str[i][strcspn(str[i], "\n")] = '\0';
   }
   for (int i=0;i<5;i++){
      for (int j=0;j<4-i;j++){
         if(strcmp(strlwr(str[j]),strlwr(str[j+1]))>0){
            strcpy(temp,str[j]);
            strcpy(str[j],str[j+1]);
            strcpy(str[j+1],temp);
         }
      }
      
   }
   printf("Sorted Array is : ");
   for (int i = 0; i < 5; ++i){
        puts(str[i]);
    }
}