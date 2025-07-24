
#include <stdio.h>

int main(void){  
   
    int i = 0;

again:    // questa è una etichetta
    printf("%d\n", i);
    i++;
    if(i < 10) goto again; // va alla etichetta
    return 0;
} 
