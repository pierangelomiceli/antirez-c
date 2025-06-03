#include <stdio.h>

int main(void){
    unsigned char c = 254;
    c++; // 0 restituisce 0 perché va in overflow
    c++; // 1
    
    printf("%d\n ", c); // stampa 1
    return 0;
}