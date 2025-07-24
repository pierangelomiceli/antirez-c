#include <stdio.h>

int main(void){  
    
    int i = 8;
    {
        int i = 5;
        printf("i (%zu bytes) is stored at %p\n",sizeof(i), &i);  // qui utilizzo lo specificatore di tipo %p per i puntatori
                                                            // e %zu per la dimensione long unsigned
    }
    {
        int i = 5;
        printf("i (%zu bytes) is stored at %p\n",sizeof(i), &i);  // qui utilizzo lo specificatore di tipo %p per i puntatori
                                                            // e %zu per la dimensione long unsigned
    }
    printf("i (%zu bytes) is stored at %p\n", sizeof(i), &i);      // stessa cosa

    return 0;
} 