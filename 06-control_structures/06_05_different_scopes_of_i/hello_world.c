#include <stdio.h>

int main(void){  
    
    int i = 8;
    {
        int i = 5;
        printf("i is %d\n", i); // qui utilizzo quella del suo blocco (5)
    }
    printf("i is %d\n", i);  // qui utilizzo i =8

    return 0;
}