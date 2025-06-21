#include <stdio.h>

int main(void){
   
    char str[6] = {'h','e','l','l','o', 0};
    
    int i = 0;
    while(str[i] != 0){
        printf("%c", str[i]);
        i++;
    }
    printf("\n");

    return 0;
}