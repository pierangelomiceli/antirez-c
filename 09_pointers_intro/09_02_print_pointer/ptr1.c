#include <stdio.h>

int main(void){

    // variabile locale
    int x = 5;

    // puntatore
    int *y = 0; 
    printf("%d\n", x);

    // punto all'indirizzo di x
    y = &x;

    printf("x is stored at the address: %p\n", y);
    return 0;
}