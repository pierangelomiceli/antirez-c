
#include <stdio.h>

int main(void){

    // il ciclo for si compne di 3 parti
    int i = 0;
    for (
        i = 0;  // PARTE 1, inizializzazione
        i < 10;     // PARTE 2, controllo
        i++         // PARTE 3, incremento
         ) {
        printf("%d\n", i); // solo questo nel body della funzione
    }

    // volendo trasformare il for in un while possiamo fare:
    
    // estrapoliamo la PARTE 1 scrivendola prima del while
    i = 0;
    // scriviamo il while inserendo come condizione la PARTE 2 estrapolata
    while(i<10){
        // scriviamo qualsiasi cosa fosse contenuta nel body del for
        printf("%d\n", i); // solo questo nel body della funzione
        // scrivo la parte estrapolata della PARTE 3
        i++;
    }

    return 0;
}
