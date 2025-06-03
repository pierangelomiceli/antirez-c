#include <stdio.h>

int main(void){
    char c  = 128; // questo stampa -128 (ricomincia da -128 dopo 127)   
    printf("%d\n ", c); // stampa -128 perché è come se rifacesse il giro da capo
    return 0;
}

