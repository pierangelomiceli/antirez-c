
#include <stdio.h>

int main(void){

    int i = 0;
    // non è necessario inizializzare i dentro il for
    // togliamo la condizione di test e la gestiamo dentro il body
    // togliamo l'incremento e lo gestiamo dentro il body
    for (;;) {
        if(i >= 10) break; // inseriamo break; per rompere il ciclo
        printf("%d\n", i); 
        i++;
    }
}
