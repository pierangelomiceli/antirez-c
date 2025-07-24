#include <stdio.h>

// versione precedente rinominata
void conta_vanilla(int start, int end){
    if(start> end) return;
    printf("%d\n", start);
    conta_vanilla(start+1, end);
}

// nuova versione con il goto
void conta(int start, int end){
iterate:            // creiamo una etichetta
    if(start> end) return;
    printf("%d %p\n", start, &start); // stampiamo sia il valore che i puntatore a start
    start = start + 1;
    goto iterate;
}

int main(void){  
    conta(0,9);
    return 0;
}