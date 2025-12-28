# 09: Introduction to pointers 

Questo è un estratto della [nona](https://www.youtube.com/watch?v=BBgZs-jd_QY) lezione del corso **Let's learn C** creato da [Salvatore Sanfilippo (antirez)](https://github.com/antirez)


## I puntatori 
I puntatori sono semplici ma vanno presi a piccole dosi per comprendere appieno i pochi concetti che ci stanno attorno.


```c
#include <stdio.h>

int main(void){

    // variabile locale
    int x = 5;

    printf("%d\n", x);
    return 0;
}
```

```sh
gcc -W -O0 -Wall recursion.c && ./a.out
# output
# 5
```


## Dichiariamo un puntatore:

Per dichiarare un puntatore scriviamo il simbolo `*` (asterisco) prima del nome della variabile:

```c
#include <stdio.h>

int main(void){

    // variabile locale
    int x = 5;

    // puntatore
    int *y;

    printf("%d\n", x);
    return 0;
}
```

La variabile dichiarata come `*y` si chiama ugualmente `y` non "asterisco y", il simbolo `*` serve solo ad modifcare il tipo della variabile.

Alcuni preferiscono inserire il `*` subito dopo il tipo.

Secondo l'autore è un errore, perchè possono nascere delle ambiguità, cioè scrivendo:

```c
    int* y, z;
```

in questo caso, la `y` sarà un puntatore di tipo intero, mentre `z` sarà un intero e per specificare che è un puntatore in entrambi i casi dovrei scrivere:

```c
 int* y, *z
```
il che risulta poco coerente con la grammatica del `c`.


Invece, se si vuole dichiarare un puntatore è preferibile scrivere:

```c

int *y, *z;

```
chiaro e leggibile.


##  stampare il valore del puntatore
Esattamente come si stampa il valore di un intero, si può stampare il valore del puntatore, usando `p`

```c

#include <stdio.h>

int main(void){

    // variabile locale
    int x = 5;

    // puntatore
    int *y = 0;

    printf("%d\n", x);
    printf("%p\n", y);
    return 0;
}


```

Nell'esempio andiamo a inizializzare il puntatore a 0, che non è altro che un puntatore nullo (null pointer)


```sh
    gcc -W -O0 -Wall ptr1.c && ./a.out
# output
# (nil)


# oppure
# 0x0

```

Per indicare un puntatore come zero o nullo, `C` ha una sua keyword che è `NULL` qundi possiamo scrivere anche


```c

#include <stdio.h>

int main(void){

    // variabile locale
    int x = 5;

    // puntatore forme equivalenti
    int *y = 0; 
    int *y2 = NULL;
    

    printf("%d\n", x);
    printf("%p\n", y);
    return 0;
}

```


## Assegnare al puntatore l'indirizzo di una variabile


Dopo avere creato il puntatore a NULL possiamo scrivere:

```c

#include <stdio.h>

int main(void){

    // variabile locale
    int x = 5;

    // puntatore
    int *y = 0; 
    printf("%d\n", x);

    // punta all'indirizzo di x
    y = &x;

    printf("x is stored at the address: %p\n", y);
    return 0;
}

```

l'operatore `&` posto prima del nome di una variabile, NON significa che vogliamo assegnare alla variabile il suo valore, ma l'indirizzo in memoria alla quale la variabile è registrata, l'indirizzo al quale punta.

In questo caso vogliamo il puntatore alla variabile perché in puntatori sono `indirizzi di memoria`.


## I

Così come `*` serviva alla definzione di puntatore, cioè ad avere un indirizzo e non una variabile, ed essendo che i puntatori sono tutti indistintamente degli indirizzi di memoria, potremmo pensare che l'atto di specificare il tipo di un puntatore (cioè che un puntatore possa essere un puntatore a intero o un puntatore a stringa) sia inutile.

Cioè potremmo chiederci: 
    
    Perché, essendo tutti uguali, andiamo a specificare di voler usare un puntatore a intero o un puntatore a stringa, essendo tutti indirizzi?

In effetti è vero, ma è utile farlo, perché se noi scriviamo:


```c

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
    
    // qui assegno 10 all'indirizzo dove punta y (cioè l'indirizzo di x) 
    *y = 10;
    
    return 0;
}

```

Scrivendo `*y = 10;`, NON sto dicendo a y di puntare all'indirizzo 10, ma sto dicendo al compilatore che all'indirizzo di memoria al quale sta puntando y (e y punta all'inrizzo di x), assegno il valore di 10 che è un intero.

E come fa il compilatore a sapere che quell'indirizzo di memoria è un intero?

Appunto dalla dichiarazione del tipo del puntatore!

Stampando il valore di x: 

```c

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
    
    // assegna il valore 10 alla variabile al quale punta y (cioè l'indirizzo di x) 
    *y = 10;
    
    printf("x now is %d\n", x);

    return 0;
}
```
avremo:

```sh

gcc ptr1.c && ./a.out
# x was 5
# x is stored at the address: 0x7ffd08f57c0c
# x now is 1

```


Ricapitolando le operazioni del programma scritto:

x è una variable intera

y è una variabile intera ma che contiene l'indirizzo di memoria di un intero

y non è grande quanto un intero, ma è largo quaantp un `intptr_t` (facilmente la grandezza di x sarà 4 byte, mentre quello di y sarà 8 byte)

Ad y si assegna l'indirizzo a cui x è registrato, usando l'operatore `&`

con `*` e `=` (assegnamento) indichiamo di scrivere  il valore `10` nell'intero nella memoria dove è momorizzato y

Equivalentemente, usando altra notazione, avremmo potuto scrivere anche:

```c

#include <stdio.h>

int main(void){

    int x = 5;

    int *y = 0; 
    printf("x was %d\n", x);

    y = &x;

    printf("x is stored at the address: %p\n", y);
    
    // altra notazione: qui assegno 10 all'indirizzo dove punta y usando la notazione array 
    y[0] = 10;
    
    printf("x now is %d\n", x);

    return 0;
}
```

Possiamo scrivere anche così, perché in `C` c'è una strana equivalenza tra i puntatori e gli array, come se `y` contenesse l'indirizzo base di un array, solo che siccome punta ad un singolo intero, potremo usare solamente l'indice 0.

Questa notazione è utile perché ci fa capire meglio il modo in cui internamente avviene questa operazione.

Usando un indice diverso da 0, ad esempio y[1], avremmo ottenuto dei risultati inattesi o addirittura crash del programma.


## A che serve?

Perchè io registro su y l'indirizzo di x? Non avrei potuto asseganre direattametne 10 a y?

In questo caso sì, ma vedremo che non sempre è possibile, ed è per questo che useramo i puntatori.


## Altro esempio: incrementiamo il valore di una variabile


```c

#include <stdio.h>

void incr(int *p){
    *p = *p +1;
}


int main(void){
    int x = 5;
    int *y = NULL; 

    printf("x was %d\n", x);
    y = &x;
    incr(y);
    printf("x now is %d\n", x);
    return 0;
}

```
otteniamo

```sh

gcc ptr1.c && ./a.out

# output
# x was 5
# x now is 6

```

Alla fuznione `incr` passiamo l'indirizzo di memoria a cui punta x, 

Non è necessario, come fatto sopra, inizializzare uuna variabile puntatore intero da passare alla funzione `incr`.

Avremo potuto indifferntemente scrivere anche:

```c

#include <stdio.h>

void incr(int *p){
    *p = *p +1;
    // equivalente
    //p[0] = p[0] + 1;
}


int main(void){
    int x = 5;

    printf("x was %d\n", x);
    incr(&x);

    printf("x now is %d\n", x);
    return 0;
}

```
otteniamo lo stesso risultato
```sh

gcc ptr1.c && ./a.out

# output
# x was 5
# x now is 6

```

Operativamente la funzione `incr` fa: 

Prendi l'intero che è registrato all'inrizzo `p`, ci aggiungi 1 e poi assegna in qulla locazione di memoria a cui punta `p` il risultato della espressione.

