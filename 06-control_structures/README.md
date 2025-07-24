# 06: Strutture di controllo

Questo è un estratto della [sesta lezione](https://www.youtube.com/watch?v=lc7aYXNl1T8) del corso **Let's learn C** creato da [Salvatore Sanfilippo (antirez)](https://github.com/antirez)


Sarebbe il momento di passare ai puntatori.


Tuttavia non possiamo affrontarli direttamente senza affontare prima le strutture di controllo in C, ovvero le scelte condizionali e le struttre di di ciclo (lo switch, il for, il while, il do...while e la ricorsione, quest'ultima può essere considerato a tutti gli effetti un modo che permette di creare cicli)

Senza questi concetti non si potrebbero affrontare i puntatori perché i cicli e gli if vengono usati pesantemente durante l'interazione con i puntatori

Inoltre violerebbe la propedeuticità preposta, cioè prima introdurre i concetti da utilizzare nelle puntate successive e poi effettivamnet eutilizzarle



## If statement

La scelta condizionale ovvero la keyword `if`:

```c
#include <stdio.h>

int main(void){

    int i = 5;

    // valuta questa condizione
    if(i > 3){
        printf("i > 3\n");        
    }
    // l'else è opzionale
    // si usa se serve
    else{ 
        printf("i <= 3\n");
    }
    
    return 0;
}
```

Eseguendo abbiamo:

```sh

gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# i > 3
```


Notiamo che:
- la parola chiave if() è una condizione
- il contenuto tra parentesi dell'if valuta una condizione: se la condizione è vera entra dentro il blocco. 
- il blocco è tutto ciò che è contenuto tra le parentesi graffe `{}`.
- il blocco successivo ad else è opzionale e viene eseguito solo se la condizione dentro l'if precedente non si verifica
- il blocco dentro else è opzionale e può essere rimosso nel caso non dobbiamo eseguire nessuna operazione

Ad esempio potremmo scrivere:

```c
#include <stdio.h>

int main(void){

    int i = 5;

    // valuta questa condizione
    if(i > 3){
        printf("i > 3\n");        
    }
    
    return 0;
}
```

Eseguendo abbiamo lo stesso output:

```sh

gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# i > 3
```


Questo sembra semplice, ma potrebbe essere ancora più semplice.


Ad esempio  possiamo vedere che il blocco potrebbe anche non essere necessario:

```c
#include <stdio.h>

int main(void){

    int i = 5;

    if(i > 3) printf("i > 3\n"); // non usiamo il blocco

    else printf("i <= 3\n");        
    
    return 0;
}
```

In questo caso abbiamo solo la necessità di eseguire una sola operazione dopo l'`if` e non abbiamo nessuna necessità di usare il [blocco di delimitazione](#guardclause):

Metrelo tutto su una riga, ad esmepio rende il codice molto chiaro, anche semanticamente.

Inoltre riduciamo la linghezza del codice in verticale.

Altri stili accetabili sono:

```c
    // manca del codice per semplicita'

    // questo e' ok
    if(i > 3) 
        printf("i > 3\n"); 
    
    return 0;
    
    // anche questo e' ok
    if(i > 3){ 
        printf("i > 3\n"); 
    }
    return 0;
```
l'importante è che ci sia una certa coerenza nella scrittura o ogni stile va bene.

### Questo non è ok

Questo modo invece fa abbastanza schifo, in quanto particolarmente illeggibile. Va evitato.

```c
    if(i > 3) 
    printf("i > 3\n"); 
    return 0;
```
Ricordiamo che l'indentazione in C non è semantica, e non ha alcun significato per la compilazione, ed il codice completo compilerbbe comunque.


## Cosa è un blocco

Scriviamo:

```c
#include <stdio.h>

int main(void){
    // posso mettere un blocco 
    // ovunque voglia nel codice
    {
        printf("i > 3\n"); 
    }
    return 0;
}
```
Nel codice abbiamo inserito un blocco che non serve a nulla, tranne che a spiegare che è perfettamente legittimo.



## lo scopo del blocco
Proseguendo possiamo fare:


```c
// non compila
#include <stdio.h>

int main(void){   
    {
        int i = 5;
        printf("i is %d\n", i); 
    }
    printf("i is %d\n", i); 

    return 0;
}
```

Se tentassimo di compilare questo codice avremmo un errore del tipo:

```sh
# output
# hello_world.c: In function ‘main’:
# hello_world.c:8:25: error: ‘i’ undeclared (first use in this function)
#     8 |     printf("i is %d\n", i);
#       |                         ^

```
Questo perché fuori dal blocco non possiamo fare riferimento alla variabile `i` che è valida soltando all'interno del blocco in cui è dichiarato (ed in quelli al suo interno), e si dice che sia `locale` in quel blocco.
Quindi lo scopo lessicale, della i è solo dentro al blocc in cui è dichairato.


## variabile i in blocchi differneti: altro esempio dello scopo

Scriviamo:

```c
#include <stdio.h>

int main(void){  
    
    int i = 8;
    {
        int i = 5;
        printf("i is %d\n", i); // qui utilizzo quella del suo blocco (5)
    }
    printf("i is %d\n", i);  // qui utilizzo i =8

    return 0;
}
```

in output abbiamo:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# i is 5
# i is 8
```

Viene stampato 5 e poi 8, perché pur avendo lo stesso identico nome, sono a tutti gli effetti due variabili diverse, con indirizzo diverso e valore diverso, ognuna nel suo scopo lessicale.

### Digressione sui puntatori

Violando per un attimo la progressione del corso, usiamo per un attimo i puntatori, per dimostrare la veridicità di quanto affermato, e cioè che le variabili siano effettivmaente differenti, andando a vedere il modo con cui si può stampare l'indirizzo di memoria di un puntatore.


Scriviamo:


```c
#include <stdio.h>

int main(void){  
    
    int i = 8;
    {
        int i = 5;
        printf("i a is stored at %p\n", &i);  // qui utilizzo lo specificatore di tipo %p per i puntatori
    }
    printf("i is a stored at %p\n", &i);      // stessa cosa

    return 0;
}
```


```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# i is stored at 0x7ffc4adc6cc4
# i is stored at 0x7ffc4adc6cc0
```

La i è registrata da qualche parte (registro, stack, etc), se vogliamo ottenere l'indirizzo di memoria, forzeremo il compilatore ad usare lo stack e non può metterlo dentro il registro, (non può ottimizzare più di tanto e deve essere in memoria necessariamente).

Dall'ouput possiamo vedere che i due indirizzi sono molto vicini e che distano esattamente 4 byte.


**Nota**
gli indirizzi di memoria in questo esempio, crescono verso il basso (Descending stack) mentre negli esempi dell'autore è al contrario (Ascending stack)
Questo dipende dalla configurazione dell'OS.


Infatti se andiamo a verificare la grandezza della variabile abbiamo:

```c
#include <stdio.h>

int main(void){  
    
    int i = 8;
    {
        int i = 5;
        printf("i (%zu bytes) is stored at %p\n",sizeof(i), &i);  // qui utilizzo lo specificatore di tipo %p per i puntatori
                                                            // e %zu per la dimensione long unsigned
    }
    printf("i (%zu bytes) is stored at %p\n", sizeof(i), &i);      // stessa cosa

    return 0;
} 
```

in questo caso abibamo usato lo spcificatore %zu per la sizeof (prima avevamo usato %lu) perché è abbastanza grande da garantire di contenere qualsiasi dimensione data dall'architettura usata.

Avremo:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# i (4 bytes) is stored at 0x7ffc94fd9334
# i (4 bytes) is stored at 0x7ffc94fd9330
```

Esattamente i nostri 4 byte previsti.

Quello che abbiamo crato ci permette di non farci problemi quando notiamo l'apertura e chiusra di blocchi nell istruzioni consizionali o di loop.
Quindi vediamo che stiamo aprendo delle parentesi graffe dentro degli if, while, etc sappiamo che stiamo creando un nuovo blocco in C che permette di avere varaibili con scopo locale.


Le variabili risiedono nello stack della funzione, ed esiste solo dentro il blocco anche come tempo di vita. Ovviamente il compilatore avrà il compito secondo le ottimizzazioni di gestire lo stack secondo la sua struttura di decidere come crearle, se istanziarle via via o se tutte insieme.

Quello che a noi interessa è che la variabile vive solo nel suo blocco, nel suo scope.


## Vediamo come avviene effettivamente


Teoricamente possiamo vedere da come viene visualizzato l'indirizzo, se avviene o meno una ottimizzazione:

facendo:

```c

#include <stdio.h>

int main(void){  
    
    int i = 8;
    {
        int i = 5;
        printf("i (%zu bytes) is stored at %p\n",sizeof(i), &i);  // qui utilizzo lo specificatore di tipo %p per i puntatori
                                                            // e %zu per la dimensione long unsigned
    }
    {
        int i = 5;
        printf("i (%zu bytes) is stored at %p\n",sizeof(i), &i);  // qui utilizzo lo specificatore di tipo %p per i puntatori
                                                            // e %zu per la dimensione long unsigned
    }
    printf("i (%zu bytes) is stored at %p\n", sizeof(i), &i);      // stessa cosa

    return 0;
} 

```

cioè ripetendo lo stesso blocco, potrebbe avvenire che il compilatore ricrea la variabile in un nuovo indirizzo per ogni scope, oppure riutilizzare la stesso.

Nell'output dell'autore abbiamo una cosa del genere:

```sh

gcc -W -O0 -Wall hello_world.c && ./a.out 

# output
i (4 bytes) is stored at 0x16f88ee18 # nuovo indirizzo
i (4 bytes) is stored at 0x16f88ee14 # nuovo indirizzo
i (4 bytes) is stored at 0x16f88ee1c # nuovo indirizzo
```

Nel mio esempio avviene proprio una ottimizzazione:

```sh
gcc -W -O0 -Wall hello_world.c && ./a.out 

# output
i (4 bytes) is stored at 0x7ffe1e0578b4 # nuovo indirizzo
i (4 bytes) is stored at 0x7ffe1e0578b4 # stesso indirizzo
i (4 bytes) is stored at 0x7ffe1e0578b0 # nuovo indirizzo

```
Infatti nel secondo scope la variabile viene riutilizzata.


## GOTO

Vediamo la funzionalità del GOTO in C.
Poniamo il caso di voler creare una funzione che stampa i numeri da 0 fino a 9

```c
#include <stdio.h>

int main(void){  
   
    int i = 0;

again:    // questa è una etichetta
    printf("%d\n", i);
    i++;
    if(i < 10) goto again; // va alla etichetta
    return 0;
} 
```
Abbiamo creato una etichetta `again` (il nome è a discrezione del programmatore).

L'etichetta serve solo al compilatore per capire a quale indirizzo di memoria il programma deve saltare quando incontra il `goto`

Il programma stamperà il valore, poi verrà inccremantato e fino a quando `i` sarà minore di `10`, il programma usando il `goto` andrà all'etichetta, ricominciano da quel punto.

```sh

gcc -W -O0 -Wall hello_world.c && ./a.out

# output
# ciao
# ciao
# ciao
# ciao
# ciao
# ...fino alla chiusura del programma
```

Questa sintassi è molto simile a quella del BASIC deli anni '80, in cui c'erano i listati fatti in questa maniera:

```basic
10 print "ciao"
20 goto 10
```

per fare un ciclo infinito di "ciao".

Questa cosa si può riprodurre anche in c in maniera molto simile

```c
#include <stdio.h>

int main(void){  
    l10:  printf("ciao\n");
    l20: goto l10;
} 
```

Quindi il basic non fa altro che dare ad ogni riga una etichetta e C è abbastanza flessibile da permetterci di imitarlo.
Le etichette devono iniziare con una lettera.


## usare if con il goto


```c
#include <stdio.h>

int main(void){  
   
    int i = 0;

    while(i<10){
        printf("%d\n", i);
        i++;
    }

    return 0;
} 
```


L'istruzione `while(i<10)` significa che entrerà nel blocco solamente se la condizione sarà vera, cioè se `i` è minore di `10`.


Quindi essendo che all'inizio ì è 0 entreràò nel blocco, stamperà la variabile, incrementerà e si andrà a riposzionare nella posizione di entrata del `while`, riverificherà la condizione e rieseguirà le stesse operazioni fino a quando incremento dopo incremenot arriverà a non essere più verificata la condizione di entrata.

Il funzionamento è quindi molto simile al `goto` e possiamo tradurlo in questa maniera.



```c
#include <stdio.h>

int main(void){  
   
    int i = 0;

    loop:
    if (!(i<10)) goto next;
        printf("%d\n", i);
        i++;
        goto loop;
    next:

    return 0;
} 
```
qui sto usando una negazione, se la negazione di (i < 0) vado su next, cioè esco dal ciclo.
in C la negazione di qualsiasi numero è 0 e la negazione di 0 sarà 1 (ricordiamo che il c tratta solo numeri)


Se invece volessi manteerner a condzione senza una negazione possiamo fare:
```c
#include <stdio.h>

int main(void){  
   
    int i = 0;

    loop:
    if (i<10) goto enter_loop; // 
    goto next;

    enter_loop:
        printf("%d\n", i);
        i++;
        goto loop;
    next:

    return 0;
} 
```
è un po' più complicato, ma il succo è cheè importante fare vedere come if e goto insieme, possono creare tutto quello che si vuole.


Possiamo anche fare:
```c
#include <stdio.h>

int main(void){  
   
    int i = 0;

loop_start:
    if(i<10){
        printf("%d\n", i);
        i++;
        goto loop_start;
    }

    return 0;
} 
```


## Ricorsione: un modo per evitare il goto


Se volessimo evitare il goto potremmo usare la ricorsione:


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

La funzione conta valida start ed end e stampa il valore, dopodichè richiama un'altra funzione, che stavolta è se stessa passando come argomento il valore di start+1.

abbiamo eliminato del tutto il goto che non esiste più nel nostro programma.

La prossima volta vedremo la recursion tail optimization, ma adesso è importante notare che nel nostro programma viene chiamanta una nuova funzione di continuo, anche se è sè stessa, creando ogni volta uno stackframe e consumando della memoria.

Possiamo vederlo stampando l'indirizzo di memoria ad ogni iterazione:


```c

#include <stdio.h>

void conta(int start, int end){

    printf("%p %p\n", &start, &end);

    if(start> end) return;

    printf("%d\n", start);

    conta(start+1, end);

}

int main(void){  
   
    conta(0,9);

    return 0;
} 
```

avremo:

```sh
# output
# 0x7ffc91b5243c 0x7ffc91b52438
# 0
# 0x7ffc91b5241c 0x7ffc91b52418
# 1
# 0x7ffc91b523fc 0x7ffc91b523f8
# 2
# 0x7ffc91b523dc 0x7ffc91b523d8
# 3
# 0x7ffc91b523bc 0x7ffc91b523b8
# 4
# 0x7ffc91b5239c 0x7ffc91b52398
# 5
# 0x7ffc91b5237c 0x7ffc91b52378
# 6
# 0x7ffc91b5235c 0x7ffc91b52358
# 7
# 0x7ffc91b5233c 0x7ffc91b52338
# 8
# 0x7ffc91b5231c 0x7ffc91b52318
# 9
# 0x7ffc91b522fc 0x7ffc91b522f8
```


Con bc, impostando esadecimale ibase=16, possiamo calcolare quanta memoria viene usata per questa operazione sottraendo il valore di indirizzo finale da quello iniziale

52438-522F8 = 320

Ciò significa che ha usato 320 byte per gestire una 4 byte.


Questo modo di scrivere i programmi è tipica della programmazione funzionale ed è molto elegante, tuttavia utilizza tanta memoria per fare delle operazioni semplici.




# Pensiero laterale: a cosa mi ha fatto pensare

Come nella lezione precendente mi sono venute in mente alcuni concetti, man mano che la lezione proseguiva.

<a id="guardclause"></a> 

### guard clauses
- le guard clause sono spesso inserite in una una riga, dato che sono molto semplici e generalmente permettono di fare dei controlli preliminari prima di decidere se proseguire con la funzione o uscire anticipatamente. L'autore stesso ne fa uso quando scrive la parte relativa alla ricorsione.

