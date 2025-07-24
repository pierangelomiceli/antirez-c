#include <stdio.h>

int main(void){  
    
    int i = 8;
    {
        int i = 5;
        printf("i is stored at %p\n", &i);  // qui utilizzo lo specificatore di tipo %p per i puntatori
    }
    printf("i is stored at %p\n", &i);      // stessa cosa

    return 0;
} 