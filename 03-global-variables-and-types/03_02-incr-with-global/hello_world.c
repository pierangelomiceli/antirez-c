#include <stdio.h>

int x = 0;

void incr(void){
    x = x + 1; 
    printf("%d\n", x); 
}

int main(void){
    incr(); // stampa 1
    incr(); // stampa 2
    incr(); // stampa 3
    incr(); // stampa 4
    return 0;
}
