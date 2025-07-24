# 07: Approfondimenti sulla risorsione

Questo è un estratto della [settima lezione](https://www.youtube.com/watch?v=HCRthhjbfAg) del corso **Let's learn C** creato da [Salvatore Sanfilippo (antirez)](https://github.com/antirez)



## Prologo

Nell'ultima lezione ci eravamo lasciati con questo codice:

```c
#include <stdio.h>

void conta(int start, int end){
    
    if(start> end) return;

    printf("%d\n", start);

    conta(start+1, end);

}


int main(void){  
   
    conta(0,9);

    return 0;
} 
```
questa funzione stampa il valore di `start` e poi richiama sè stessa, risolvendo ogni volta un pezzetto di computazione fino da arrivare alla fine.

Questo modo di pensare alla ricorsione è molto comune e si può appliciare a tante casistiche.

Per una funzione che trova il massimo elemento di un array, potremmo dire che se l'array è costituito da un solo elemento, il massimo dell'array è l'elemento stesso.
Se invece l'array è costuito dal massimo tra un elemnto e il massimo tra tutti gli altri elementi,  anche in questo caso potrei eimplemntare la funzione in termini ricorsivi.

la scrsa volta abbiamo anche parlato di una interessante funzione che è quella della `tail call optimization`:


Considerando il codice sopra, il compilatore potrebbe operare delle ottiimizzazioni per non creare nuovi stackframe ad ogni iterazione (diversamente da quanto visto nella precedente lezione, in cui ogni chiamata annidata creava uno stackframe, utilizzando nuova memoria).

Se vogliamo fare una ottimizzazione manuale, senza fidarci del lavoro del compilatore possiamo farlo usando il `goto`:

```c
#include <stdio.h>

// versione precedente rinominata
void conta_vanilla(int start, int end){
    if(start> end) return;
    printf("%d\n", start);
    conta(start+1, end);
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
```

la versione conta del codice in questo caso usa il `goto`, ma è assolutamente equivalente a quella della lezione precedente.

Questa cosa è possibile solo se `conta` è una chiamata di coda, ec in questo caso lo è, essendo ultima chiamata della funzione.

A volte, in C è fondamentale trasformare una ricorsione in una iterazione e questo è un modo per farlo.

Inoltre, la funzione che usa `goto`, impegna solamente uno stack di memora con un risparmio notevole della stessa.

Andnado a compilare:

```sh
    gcc -W -O0 -Wall hello_world.c && ./a.out
```

otteniamo:
```sh
gcc -W -O0 -Wall hello_world.c && ./a.out
# output
# 0 0x7ffde0397ddc
# 1 0x7ffde0397ddc
# 2 0x7ffde0397ddc
# 3 0x7ffde0397ddc
# 4 0x7ffde0397ddc
# 5 0x7ffde0397ddc
# 6 0x7ffde0397ddc
# 7 0x7ffde0397ddc
# 8 0x7ffde0397ddc
# 9 0x7ffde0397ddc

```
Come possiamo notare il puntatore è sempre lo stesso, (sarebbe diverso se stampassimo il pntatore nella funzione `conta_vanilla`)

Quindi, il `goto` serve a questo e ad altre cose, tuttavia tendiamo ad evitare il `goto` ed al suo posto usiamo i costrutti di loop a più alto livello.

**Nota personale**

Un altro modo per risparmiare il stack è questo senza l'uso del goto:


```c
// anche questa funzione mantiene sempre lo stesso stack, ed anche questa qui è una iterazione

#include <stdio.h>

void conta_while(int start, int end){

    if(start> end) return;

    while(start < end){
        printf("%d %p\n", start, &start);
        start++;
    } 
}
int main(void){ 

    conta_while(0,9);   
    return 0;
}


```
compilando ed eseguendo:

```sh
gcc hello_world.c && ./a.out
# output

# 0 0x7ffe2682234c
# 1 0x7ffe2682234c
# 2 0x7ffe2682234c
# 3 0x7ffe2682234c
# 4 0x7ffe2682234c
# 5 0x7ffe2682234c
# 6 0x7ffe2682234c
# 7 0x7ffe2682234c
# 8 0x7ffe2682234c
```


## while

Il while è un loop che è usato anche in altri linguaggi con sintassi c-like (come JavaScript, C#, etc)

```c

#include <stdio.h>


int main(void){  

    int i = 0;
    // finchè i è minore di 10 eseguo il blocco dentro il while
    while(i < 10){
        i++; // incremento la variabile di loop
        printf("%d\n", i); 
    }
    return 0;
}

```



## for
La stessa cosa la possiamo scrivere usando il costrutto `for` (anche qui sintassi identica per i linguaggi C-like)

```c
#include <stdio.h>

int main(void){  
    for (int i = 0; i < 10; i++) {
        printf("%d\n", i); // scrivo solo questo nel body della funzione
    }
    return 0;
}
```

Questo programma ha lo stesso output dei precedenti.

### Il for è un while mascherato

la cosa interessante da notare è che il for è un while mascherato.

Possiamo infatti passare da un for ad un while seguendo questi passaggi:


```c

#include <stdio.h>

int main(void){

    // il ciclo for si compne di 3 parti
    int i = 0;
    for (
        i = 0;      // PARTE 1, inizializzazione
        i < 10;     // PARTE 2, controllo
        i++         // PARTE 3, incremento
         ) {
        printf("%d\n", i); // solo questo nel body della funzione
    }

    // volendo trasformare il for in un while possiamo questi sono i passaggi:
    
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

```

Questi due cicli sono identici e produrranno lo stesso output:
```sh
gcc -W -O0 -Wall hello_world.c && ./a.out
# output
# 0
# 1
# 2
# 3
# 4
# 5
# 6
# 7
# 8
# 9
# 0
# 1
# 2
# 3
# 4
# 5
# 6
# 7
# 8
# 9
```


Il for non è altro che zucchero sintattico ([syntactic sugar](https://en.wikipedia.org/wiki/Syntactic_sugar)) per il `while`, che ha un momento di inizializzazione, e un momento di incremento.

Tra l'altro, si può notare che nel codice precedente la variabile `i` era già inizializzata prima del ciclo, ed a questo punto possiamo anche omettere l'inizializzazione, inserendo solo un punto e virgola, ottenendo lo stesso identico output:


```c

#include <stdio.h>

int main(void){

    int i = 0;
    // non è necessario inizializzare i dentro il for
    for (; i < 10; i++) {
        printf("%d\n", i); 
    }
}

```

Inoltre ossiamo omettere anche la condizione di test, inserendo il controllo specifico ed un `break` (il `break` si può usare nel `for`, nel `while` ma anche nello `switch`, in quest'ultimo caso, con finalità differenti) per rompere il ciclo dentro il body:


```c
#include <stdio.h>

int main(void){

    int i = 0;
    // non è necessario inizializzare 'i' dentro il for
    // togliamo la condizione di test e la gestiamo dentro il body
    for (; ; i++) {
        if(i >= 10) break; // inseriamo break; per rompere il ciclo
        printf("%d\n", i); 
    }
}



```

Possiamo anche rimuovere l'incremento, gestendo anch'esso dentro il body del ciclo.

```c

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

```

A questo punto il `for` è diventato come un ciclo `while` sprovvisto di inizializzazione, controllo, ed incremento.

Di fatto, è un ciclo infinito dove mettiamo la condizione di stop dentro il body usando `break` e l'incremento alla fine del body.

Un altro modo per fare il ciclo infinito è usando il `while(1)`.

Questa è una condzione sempre vera (per il C la verità può essere 0 o 1, cioè un numero uguale a 0 è **falso**, mentre un numero diverso da 0 è **vero**) :


```c
#include <stdio.h>

int main(void){

    int i = 0;
    // stessi concetti ma con il while
    while (1)
    {
        if(i >= 10) break; // inseriamo break; per rompere il ciclo
        printf("%d\n", i); 
        i++;
    }
}


```

Tutte queste funzioni producono lo stesso identico output.

Da una certa versione del C, è consentito inizializzare la variabile all'interno il ciclo for, nella parte di inizializzazione, quindi possiamo scrivere_

```c
#include <stdio.h>

int main(void){ 
    // tutto in una riga perché ho una sola istruzione
    // in una sola riga ho espresso una computazione complicata 
    for (int i = 0; i < 10; i++) printf("%d\n", i); 
    
    return 0;
}

```

Tuttavia, bisogna notare che in questo caso, subito dopo il for, la variabile `i` non esiste più.
Questo può essere una scomodità in certe condizioni.

Ad esempio, se facessimo:

```c

// Attenzione: Questo codice non compila volutamente
#include <stdio.h>

int main(void){ 
    // tutto in una riga perché ho una sola istruzione
    // in una sola riga ho espresso una computazione complicata 
    for (int i = 0; i < 10; i++) printf("%d\n", i); 

    printf("%d", i); // qui i non esiste
    
    return 0;
}

```
otterremmo un errore di compilazione del tipo:

```sh
hello_world.c: In function ‘main’:
hello_world.c:8:18: error: ‘i’ undeclared (first use in this function)
    8 |     printf("%d", i);
      |                  ^
hello_world.c:8:18: note: each undeclared identifier is reported only once for each function it appears in
```
 
problema che non avremmo dicharando `i` fuori dal ciclo:

```c
#include <stdio.h>

int main(void){ 

    // dichiarando fuori possiamo riutiizzare i dopo il ciclo while
    int i=0;
    for (i = 0; i < 10; i++) printf("%d\n", i); 

    printf(">>%d", i); // comodo
    
    return 0;
}

```
Detto ciò a volte può essere comodo sapere che valore ha la variaible di ciclo dopo il ciclo stesso, ad esempio:


```c
#include <stdio.h>

int main(void){ 

    // dichiarando `i` fuori dal ciclo possiamo riutilizzarla dopo il ciclo while

    int a[] = {1, 5, 8, 4, 9, 0};
    int i;

    for (i = 0; a[i] != 0; i++) {
        // potremmo stampare il valore degli array
        // printf("%d\n", a[i]); 

        // oppure poniamo il caso che invece di volere stampare il valore dell'array
        // volessimo sapere se l'array contiene il valore 8
        if(a[i] == 8) break; // rompiamo il ciclo appena lo incontriamo
    }

    // fuori dal ciclo possiamo chiedere alla variabile i la posizione in cui si trovava nell'array quando ha incotrato 8 
    if(a[i] == 0){
        // arrivato all'ultimo elemento senza risucire a trovarlo
        printf("Non trovato\n");
    }
    else{
        // se non è riuscito ad arrivare all'ultimo elemento è proprio perché lo ha trovato!
        printf("Trovato\n");
    }

    return 0;
}



```

Questo tipo di strategia è possibile solamente inizializzando la variabile di ciclo fuori dal ciclo, e per questo a volte può essere utile usarla.


## do while

Il while ha una alternatia che è quella del `do while` 

```c

#include <stdio.h>

int main(void){ 

    // la prima viene fatta la prima iterazione ed eseguita l'operazione dentro il body del do
    do {

    } while(1); // e poi viene valutata la condizione 

    return 0;
}

```

Il `do-while` non è un costrutto sempre utilizzato e ci sono alternative come ad esempio usare il `while`, andando a valutare la variabile di ciclo alla fine del body.


## switch

Lo `switch` è un costrutto anch'esso presente in linguaggi c-like e rappresenta una serie di casi che vengono valutati in ordine di scrittura.
quando la condizione di uno dei casi è verificata, entra dentro quella sezione.

In ogni `case` si inserisce un break che fa terminare lo switch.

Alla fine si può inserire un caso `case default` per tutti gli altri casi che non rientrano nei precedenti (è opzionale)

Dentro on sezione del `case` posso inserire più istruzioni, ma non posso dichiarare delle variabili (più avanti si vede come questo si possa fare)

```c

#include <stdio.h>

int main(void){ 

    int i = 5;
    switch(i){

        case 5: 
            // posso inserire più istruzioni
            printf("è un cinque\n");
            printf("Sì, proprio un bel cinque\n");
            break;
        case 6: 
            printf("è un sei\n"); 
            break;
        case 7: 
            printf("è un sette\n"); 
            break;
        
        default: printf("qualche altro numero\n"); 
            break;
    }
    return 0;
}

```
compilando abbiamo:


```sh
gcc -W -O0 -Wall hello_world.c && ./a.out
# output
#
# è un cinque
# Sì, proprio un bel cinque
```


### A cosa serve il break? quindi?

Se omettessimo un `break` e scrivessimo:

```c
#include <stdio.h>

int main(void){ 

    int i = 5;
    switch(i){
        case 3: 
            // quin non entrerebbe perché il valore 5 non corrisponde a 3
            printf("è un tre\n");
            // break; 
        case 5: 
            // i == 5, entrerebbe qui
            printf("è un cinque\n");
            printf("Sì, proprio un bel cinque\n");
            // break;  // commentato il break
        case 6: 
            // prosegue anche qui perchè nel blocco case precedente 
            // non c'è il break 
            printf("è un sei\n"); 
            break;
        case 7: 
            // qui non entra perché prima c'è sopra c'è il break
            printf("è un sette\n"); 
            break;
        
        default: printf("qualche altro numero\n"); 
            break;
    }
    return 0;
}
```

Se non ci fosse il `break` e dato che la varaibile `i` == `5`, entrerebbe nel case del 5 e dato che questo blocco non ha il `break`, proseguirebbe entrando anche in tutti i successivi (senza nemmeno più valutare la condizione) fino a quand non ne incontra uno con il `break`; 

Se `i` fosse `8` entrerebbe solo nel caso default (nel caso vi fosse un caso default)

compilando ed eseguendo abbiamo:


```sh
gcc hello_world.c && ./a.out
# output

# è un cinque
# Sì, proprio un bel cinque
# è un sei
```

**Nota personale:** 
Il fatto di entrare anche nei successivi, succederebbe solo ed esclusivamente se entrasse almeno in uno dei case:

In questo caso pur non esendoci alcun break andrebbe solo al default, perché la discriminante è se riesce ad entrare in uno.

**Se entra in uno si fa tutti quelli successivi senza il break.**

```c
#include <stdio.h>

int main(void){ 

    int i = 12;
    switch(i){
        case 3: 
            // non entrerebbe perché il valore non corrisponde
            printf("è un tre\n");
            // break; 
        case 5: 
            // entrerebbe qui
            printf("è un cinque\n");
            printf("Sì, proprio un bel cinque\n");
            // break; 
        case 6: 
            // entrerebbe anche qui perchè nel blocco case precedente in cui è entrato
            // non c'è il break 
            printf("è un sei\n"); 
            // break;
        case 7: 
            // qui non entra perché prima c'è sopra c'è il break
            printf("è un sette\n"); 
            // break;
        
        default: printf("qualche altro numero\n"); 
            break;
    }
    return 0;
}

```
questo darebbe:

```sh

gcc hello_world.c && ./a.out
# ouput
#
# qualche altro numero
```

Alla luce di ciò, a meno di specifiche esigenze, è buona norma usare il break;



## Variabili nei blocchi case

Come potremmo fare se volessimo dichiarare una variabile dentro il blocco del case?

Usando solito blocco delle paretesi graffe:

```c

#include <stdio.h>

int main(void){ 

    int i = 5;
    switch(i){

        case 5: 
            {
                // ora dentro il blocco posso dichairare delle variabili
                int j = 10;

                // posso inserire più istruzioni
                printf("è un cinque (%d)\n", j);
                printf("Sì, proprio un bel cinque\n");
            }
            
            break;
        case 6: 
            printf("è un sei\n"); 
            break;
        case 7: 
            printf("è un sette\n"); 
            break;
        
        default: printf("qualche altro numero\n"); 
            break;
    }
    return 0;
}

```
risultato:

```sh

gcc hello_world.c && ./a.out
# ouput

gcc hello_world.c && ./a.out
è un cinque (10)
Sì, proprio un bel cinque

```



## altre risorse

Tail call optimization TCO:
https://eklitzke.org/how-tail-call-optimization-works


