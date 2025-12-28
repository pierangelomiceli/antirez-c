

#include <stdio.h>

int main(void){

    // variabile locale
    int x = 5;

    // puntatore
    int *y = 0; 
    printf("x was %d\n", x);

    // punto all'indirizzo di x
    y = &x;

    printf("x is stored at the address: %p\n", y);
    
    // qui assegno 10 all'indirizzo dove punta y usando la notazione array 
    y[0] = 10;
    
    printf("x now is %d\n", x);

    return 0;
}