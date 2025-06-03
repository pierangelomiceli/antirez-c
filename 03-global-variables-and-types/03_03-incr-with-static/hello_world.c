
#include <stdio.h>

void incr(void){
    static int x = 0; // questa è una variabile globale ma che è visibile solo dentro la funzione incr
    x = x + 1;
    printf("%d\n", x); 
}

int main(void){
    incr(); // 1
    incr(); // 2
    incr(); // 3
    incr(); // 4
    // questo darebbe errore di compilazione
    // printf("%d\n", x); 

    return 0;
}
