#include <stdio.h>


// questa funzione non prende parametri e non torna niente
// ed ha soltanto un side effect (stampa una variabile senza processare alcun dato)
void incr(void){
    int x = 1; // dichiarazione della variabile con assegnazione
    x = x + 1; // assegniamo a x (a sinistra) il valore di x + 1;
    printf("%d\n", x); // stampo speficiando il tipo di dato con %d (interi)
}

int main(void){
    incr(); // viene chiamata senza argomenti 
    incr(); // viene chiamata senza argomenti 
    incr(); // viene chiamata senza argomenti 
    incr(); // viene chiamata senza argomenti 
    return 0;
}