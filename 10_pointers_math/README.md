# 09: Introduction to pointers 

Questo è un estratto della [decima](https://www.youtube.com/watch?v=lc7hL9Wt-ho) lezione del corso **Let's learn C** creato da [Salvatore Sanfilippo (antirez)](https://github.com/antirez)


## Matematica dei puntatori

L'ultima volta abbiamo visto:

```c

#include <stdio.h>

void incr(int *p){
    p[0] = p[0] + 1;
}


int main(void){
    int x = 5;

    printf("x was %d\n", x);

    incr(&x);

    printf("x now is %d\n", x);
    return 0;
}

```

Abbiamo visto che, anche se `x` è locale nella main, la funzione `incr` tramite uso del puntatore può accedere al valore della variabile ed incrementarla.

Abbiamo accennato al fatto come, sia la sintassi con `*p` che quella con `p[0]` siano equivalenti e leggano il valore della variabile memorizzata dentro `p`.

Queste operazioni si chiamano `deferenziazione` di `p`. 

```
    Deferenziare significa accedere ad un valore attraverso il suo indirizzo di memoria
```

Questa operazione si può fare sia in lettura che in scrittura.

Ad esempio possiamo leggere il valore:

```c

#include <stdio.h>

void incr(int *p){
    printf("Before incr: %d\n", *p);

    p[0] = p[0] + 1;
}


int main(void){
    int x = 5;
    
    printf("x was %d\n", x);

    incr(&x);

    printf("x now is %d\n", x);
    return 0;
}

```

Otteniamo la lettura del valore usando *p nella printf


```sh
gcc ptr1.c && ./a.out
# x was 5
# Before incr 5
# x now is 6
```


# Puntatori di puntatori

```c
#include <stdio.h>

int main(void){
    int x = 5;
    int *y = &x;
    int **z = &y;
    printf("x is stored in %d and y is stored in  %d\n", y, z );

    return 0;
}

```
In questo caso `z` cosa è? 

Si tratta di un puntatore ad un puntatore di tipo int, che è l'indirizzo di memoria dove è registrato `y` che a sua volta è un indirizzo di memoria che punta all'indirizzo di memoria di `x`.

La variabile `y` sarà anch'essa regitrata da qualche parte, tuttavia non possiamo usare un puntatore ad un interno ma devo usare un puntatore ad un putnatore di un intero per sapere l'indirizzo.

Entrambe le variabili sono di tipo intero, sono due numeri, ma tutti i puntatori sono numeri, numero del valore del bus di indirizzi del processore.

Per conoscere questa grandezza possiamo usare `sizeof`:


```c
#include <stdio.h>

int main(void){
    int x = 5;
    int *y = &x;
    int **z = &y;
    printf("x is stored in %p and y is stored in  %p\n", y, z );
    printf("%d, %d, %d\n", (int)sizeof(x), (int)sizeof(y), (int)sizeof(z) );

    return 0;
}
```

L'espressione `(int)` dice al `C` di convertire il valore in tipo intero (casting), è una cosa che vedremo più aavanti ma almomento serve per evitare warning del compilatore.


```sh
gcc ptr1.c && ./a.out

# x is stored in 0x7ffe1ac01f94 and y is stored in  0x7ffe1ac01f98
# 4, 8, 8
```

Il valore di `x` che è un intero, è di `4 byte`, cioè 32 bit, invece i puntatori sono larghi `8 byte` quindi 64 bit

Questo esempio è valido per comprendere che normalmente tutti i puntatori hanno la stessa dimensione, cioè sono sono larghi uguale.

Lo standard del C potrebbe non garantire questo concetto ma non è importante ai fini della comprensione del concetto.


# Esperimenti con stringhe

Avendo:

```c
#include <stdio.h>

int main(void){
    char mystr[] = "Hello World";

    printf("%s\n", mystr );

    return 0;
}
```

Abbiamo detto che le stringhe sono array di caratteri, array di tipi char, e sapendo questo potremmo ragionare in questi termini:

C'è una parte della memoria dove saranno registarti questi caratteri, possiamo quindi dichiarare un puntatore `p` di tipo `char` che può contenere un solo byte.

    In C il nome di un array è anche un puntatore.

In c tutte le varaibili dichiarate come array possono essere usate direttamente come indirizzi di memoria, come puntatori di quel tipo.

In questo caso per assegnare il puntatore non serve scrivere `char *p = &mystr;` anzi, sarebbe un errore, perché il nome stesso dell'array è già esso stesso il nostro puntatore.


```c
#include <stdio.h>

int main(void){
    char mystr[] = "Hello World";

    char *p = mystr; // non serve &mystr, il nome mystr è già un puntatore

    printf("At %p I can see: %s\n", mystr, mystr );

    return 0;
}
```
Stampiamo con la printf sia come puntatore che come stringa il valore di `mystr`.

Otteniamo:

```sh
gcc ptr1.c && ./a.out
# At 0x7ffd7dc0fb6c I can see: Hello World
```

## Accediamo agli elementi del puntatore 

Potremmo provare a scrivere:

```c

#include <stdio.h>

int main(void){
    char mystr[] = "Hello World";

    char *p = mystr; 

    printf("%c%c\n", p[0], p[1]);


    return 0;
}

```
otteniamo:

```sh
gcc ptr1.c && ./a.out
# He
```

Usando la notazione p[] possiamo accedere a tutti gli elementi successivi della memoria del puntatore.

Usando *p, io accediamo solo al primo elemento, tuttavia possiamo accedere agli altri valori usando la stessa notazione.

```c

#include <stdio.h>

int main(void){
    char mystr[] = "Hello World";

    char *p = mystr; 

    printf("%c%c\n", *p, *(p+1));


    return 0;
}
```
otteniamo ugualmente:

```sh
gcc ptr1.c && ./a.out
# He
```

Ciò significa che prima di fare la deferenziazione, (accesso alla variabile tramite il suo indirizzo di memoria) accediamo all'indirizzo successivo della memoria, perché ricordamo sempre che i puntatori essendo che sono numeri, li possiamo incrementare e decrementare e questo ci permette di puntare al byte successivo, prima di accedere al suo valore:


## altro spunto sull'incremento dei puntatori

Poniamo di dichiarare un puntatore short (interi a 16 bit, 2 byte) e farci stampare quello che c'è nella posizione del puntatore: 

```c

#include <stdio.h>

int main(void){
    char mystr[] = "AABBCCDDEEFF";
    
    short *p = mystr;

    printf("%d\n", *p);

    return 0;
}

```

Qui stiamo assegnando un puntatore short (2 byte) all'indirizzo di memoria del nostro array di char (1 byte)


otteniamo:

```sh
gcc ptr1.c && ./a.out
# 16705
```

otteniamo quel numero che rappresenta i primi 2 byte della stringa 65+(65*256) (65 è il carattere 'A') 


## Proviamo ad incrementare questo puntatore

Poniamo di incrementare il puntatore prima di stampare.

```c

#include <stdio.h>

int main(void){
    char mystr[] = "AABBCCDDEEFF";
    
    short *p = (short*)mystr;

    p += 1;
    
    printf("%d\n", *p);

    return 0;
}
```
otteniamo:

```sh
gcc ptr1.c && ./a.out
# 16962
```

Istintivamente ci saremmo aspettati il valore `AB` convertito.
Invece abbiamo ottenuto `BB` cioè 66 + 66 * 256.


Il motivo è che la matematica dei puntatori segue una regola particolare ed utile.

    Quando incrementiamo un puntatore di una unità, in realtà il puntatore viene prima moltiplicato per la grandezza base del tipo base del puntatore.

Se `short` vale 2 byte, quando lo incremento di 1, il puntatore si sposta di 2 byte, quindi seguendo la stringa, in cui ogni carattere pesa un byte, si sposta di due caratteri.

Quindi abbiamo ottenuto il valore 16962

se avessimo incrementato di 4 saremmo arrivati alla coppia `EE` ottenendo 17733.

```c

#include <stdio.h>

int main(void){
    char mystr[] = "AABBCCDDEEFF";
    
    short *p = (short*)mystr;

    // stampo la posizione del quarto short 0 1 2 3 4
    printf("%d\n", p[4]); 

    return 0;
}

```

Ricordiamo che il C si disinteressa del tutto se scriviamo p[40] cioè di una posizione che non esiste nella nostra stringa, ma stamperà qualcosa che è nella memoria indipendentemente dal fatto che sia un valore corretto per il nostro programma, oppure andrà in segmentation fault.



## creazione della printf

Possiamo creare una printf custom, usando la funzione `putchar` della libreria standard del C.

```c

#include <stdio.h>

int main(void){
    char mystr[] = "AABBCCDDEEFF";
    
    char *p = mystr;
    printf("At the beginning p is %p\n", p);
    printf("At the beginning p is %lu\n", (unsigned long)p);

    while(*p != 0){
        putchar(*p);
        p++;        
    }
    printf("\n");
    printf("At the end p is %p\n", p);

    return 0;
}

```

otteniamo

```sh
gcc ptr1.c && ./a.out

# At the beginning p is 0x7ffec7dc413b
# At the beginning p is 140732251521339
# AABBCCDDEEFF
# At the end p is 0x7ffec7dc4147
```

## Estrazione dei valori di puntatori di puntatori


Quando accediamo ad un valore del puntatore con *, otteniamo il tipo tipo base, nel nostro caso un `char`.


Se avessimo avuto un puntatore di puntatore a p `**p` e avessimo fatto estrazione a *p avremmo ottenuto il puntatore a p `*p` che è un puntatore a sua volta.

Quindi, ogni volta che deferenzaino il puntatore è come se togliessio un asterisco.


Esempio esplicativo non del'autore:

```c
#include <stdio.h>

int main(void){
    char mystr[] = "AABBCCDDEEFF";
    
    char *p = mystr;

    char **p2 = &p;

    // prima estrazione 
    printf("Address of **p is %p\n", p2);
    printf("Address of **p is %p\n", p2);

    // seconda estrazione
    printf("Address of *p is %p\n", p2[0]);
    printf("Address of *p is %p\n", *p2);

    // valore del carattere
    printf("Value of char is %c\n", p2[0][0]);
    printf("Value of char is %c\n", **p2);
    
    return 0;
}


```

otteniamo

```sh
gcc ptr1.c && ./a.out
Address of **p is 0x7ffda5e00d38
Address of **p is 0x7ffda5e00d38
Address of *p is 0x7ffda5e00d4b
Address of *p is 0x7ffda5e00d4b
Value of char is A
Value of char is A
```

