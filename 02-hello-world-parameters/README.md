# 02: HelloWorld 02

Questo è un estratto della [seconda lezione](https://www.youtube.com/watch?v=Z84vlG1RRtg) del corso **Let's learn C** creato da [Salvatore Sanfilippo (antirez)](https://github.com/antirez)


## La definizione della funzione main: la firma 


Questa è la struttura della nostra funzione `main`:
```c
/// definizione
int main(void){}

// int è il valore di ritorno: viene inserita prima del nome ed indica che la funzione ritorna una valore intero.

// (void): dentro le parentesi ci sono i parametri di input che la funzione accetta, in questa caso specifico non accetta nessun argomento.
``` 

Generaltmente è sempre meglio specificare main(void) anziché scrivere main() senza parametri: alcuni compilatori non compilano, oppure darebbe dei warning.
I warningsi possono abilitare esplicitamente usando l'opzione -W
```sh
gcc -O2 -W -Wall hello_world.c
```
Tuttavia nel C moderno é possibile definire la funzione senza il void come parametro, e potrebbe non essere restituito né un errore né un warning.

In ogni caso si preferisce scrivere esplicitamente main(void) per sicurezza e maggiore compatibilità.


## Funzione sum: una funzione con parametri

Creiamo una funzione che somma due numeri interi (int).

**Nota: Dare un nome inglese alle nostre funzioni è una consolidata e buona pratica di programmazione.**

```c
// questa funzione 
// - ritorna un intero 
// - riceve in input due interi, ognuno dei quali separati da virgola
int sum(int a, int b){
    // il valore di ritorno è la somma di due interi che a sua volta è un intero.
    // vi è dunque coerenza con il tipo di ritorno atteso.
    return a+b; // questa statement è una espressione e return accetta delle espressioni.
}
```

Dopo averla dichiarata possiamo usarla nella nostra funzione **main**.

## Analisi delle parti del programma

```c
#include <stdio.h>

int sum(int a, int b){
    return a+b;
}

int main(void){
    printf("Hello world %d\n", sum(10, 20));
    return 0;
}
```
Quando la compiliamo e la eseguiamo: 

```sh
gcc hello_world.c

# e poi 
./a.out

# oppure concateniamo le due operazioni in un'unica riga:
gcc hello_world.c && ./a.out

# output
# Hello world 30
```

## Analisi di print: la stampa a video formattata

La main fa uso della funzione **printf** (print formatted, abbreviato).

Si tratta di una funzione che stampa valori in maniera formattata. 

Il primo [argomento](#paramvsarg) è il formato che contiene i caratteri `hello world` seguiti da un segnaposto `%d` che ci dice che verrà fornito un intero.

**Nota:** la funzione *printf* è una [funzione variadica](https://www.gnu.org/software/libc/manual/html_node/Variadic-Functions.html): una funzione che accetta un numero variabile di argomenti, il numero di argomenti da dare a printf non è mai predeterminato.

Se nella **printf** inseriamo `%d`, non appena la sua implemntazione si accorge della presenza di quello specifico argomento, ne richiederà il valore per sostituirlo al segnaposto.
Il modo con cui viene cercato il parametro non è come nei linguaggi di alto livello in cui viene fornito un array di argomeniti: essendo il C un linguaggio compilato, avverrà una manipolazione a livello della memoria, aspetto che verrà affrontato più avanti.

Dato che la **printf** è una funzione più complessa delle altre, e dato che la usiamo intensamente, al momento ci accontentiamo di sapere che:


    Funzione variadica -> accetta un numero variabile di argomenti


### Numero errato di parametri alla printf

Cosa succederebbe se dessimo un numero inferiore di argomenti alla **printf** rispetto a quelli che andiamo ad indicare nella stringa formattata?

Ad esempio:

```c
    // printf si aspetta 2 argomenti nella stringa formattata
    // ma ne forniamo solamente 1
    printf("Hello world %d %d %d a", sum(10, 20));
```

In questo caso ci restituirebbe un warning del tipo:

```bash 
cc -W -Wall hello_world.c 


hello_world.c:8:29: warning: format ‘%d’ expects a matching ‘int’ argument [-Wformat=]
    8 |     printf("Hello world %d %d\n", sum(10, 20));
      |                            ~^
      |                             |
      |                             int
# 1: in certe piattaforme il warning non viene restituito se non si esplicita l'opzione -W -Wall

# 2: l'errore cambia a seconda della piattaforma

# 3: attenzione a lasciare del codice che presenta dei warning: quando eseguiamo questo tipo di codice, 
#    il risultato può cambiare a seconda della piattaforma 
#    e stiamo fornendo un programma con un comportamento indefinito nel modo in cui risponderà
#    perchè c'è un errore: potrebbe addirittura andare in crash.

# alcune piattaforme danno:
Hello world 30 0 # su mac
Hello world 30 30 # su linux
```

Bisogna evitare i [warning](#coincidence)


## Analisi di main

La funzione **main** è una funzione speciale in quanto non serve che qualcuno la chiami in maniera esplicita, come invece fatto con la sum, e rappresenta il punto di partenza di ogni programma C.

### Non può compilare senza la main

Un programma C senza la **main** non verrebbe mai compilato:

```c
// this code does not compile
#include <stdio.h>

printf("Ciao\n");
return 0;
```
e nemmeno:

```c
// this code does not compile
#include <stdio.h>

int pippo(void){
    printf("Ciao\n");
    return 0;
}

```
la funzione main è **SEMPRE** necessaria.


## Altro esempio con gli int

Proviamo a vedere come funzionano gli int.

```c
#include <stdio.h>

// questo int indica il ritorno della funzione (un intero, come visto in precedenza)
int main(void){

    // invece questo int indica che sto definendo delle variabili.
    int a = 10; 
    
    // in C bisogna necessariamente scrivere il tipo di ogni variabile.
    // C è sprovvisto di inferenza e
    // la seguente riga non farebbe compilera il codice perché non stiamo indicando il tipo
    // a = 10;

    int b = 20;
    int c = a+b;

    printf("Ciao: %d\n", c);
    return 0;
}
```

Inoltre vediamo che:

```c
int a = 10;     // questa è una dichiarazione con inizializzazione al valore 10
int c = a+b;    // questa è una dichiarazione con espressione
```

quindi notiamo che le espressioni si possono avere:

- sia come ritorno di una funzione (la nostra `return a+b` vista prima). 
- sia durante le inizializzazioni delle variabili.

```c
// potremmo fare anche così

#include <stdio.h>

int main(void){
    int a, b, c; // qui creiamo tre variabili


    a=10; //    questa non è più una inizializzazione.
    //          nell'inizializzazione, l'assegnazione del valore avviene durante la definzione della variabile
    a=11; //    queste invece sono assegnazioni successive perfettamente lecite
    a=5+7; //   e ancora
    b=20;
    c=a+b;

    printf("Ciao: %d\n", c);
    return 0;
}
```
Le variabili a, b e c sono delle variabili locali.

## Le variabili locali

Avendo:

```c
#include <stdio.h>

int sum(int a, int b){
    int c;
    c = a+b;
    return c;
}

int main(void){
    printf("Ciao: %d\n", sum(10, 20));
    return 0;
}

```

La variabile `int c` è una variabile locale: significa che viene creata quando la funzione **sum** viene chiamata e ogni singola volta viene creata da zero.

Inoltre, smette di esistere non appena il controllo passa di nuovo al suo chiamante, `printf` nel caso specifico, ed il suo valore verrà distrutto o riutilizzato, ma come vedremo più avanti con i puntatori, nemmeno in quel caso potremo fare affidamento al suo valore, dopo l'uscita dalla funzione sum.

Al momento è solo di fondamentale importanza capire qual è il tempo di vita della variabile c.

Inoltre, i due parametri della funzione `int a` e `int b` della **sum** non sono altro che variabili anch'esse.

La differenza è che i primi due sono argomenti, ma la funzione crea 3 variabili.

Ad `a` e `b` assegna i valori `10` e `20`, perché questi sono gli argomenti con cui viene chiamata la `sum`.

In definitiva, quando la funzione **sum** ritorna il suo valore,  in realtà vengono distrutte 3 variabili, a, b e c: `a` e `b` due sono argomenti e l'altro è `c` che è una varibile d'appoggio creata al suo interno. 


**Nota: A livello di esecuzione del programmma, la funzione `sum` che è utilizzata da printf deve essere risolta prima della printf. (si può notare andando vedre l'assembly tramite `cc -S hello_word.c`)
perchè il compilatore non conoscendo a priori il valore restituito da `sum`, deve necessariamente eseguirla prima di poter usare la `printf`**


## La funzione di ritorno della main

Dal seguente codice notiamo che la funzione main ha un `return 0`.

```c
#include <stdio.h>

int main(void){
    printf("Hello world\n");
    return 0;
}
```

A prima vista può sembrare strano: noi non la usiamo, nessuno la chiama.

In realtà, la funzione di ritorno di **main** serve a segnalare al sistema operativo, se il programma ha avuto un buon esito o meno.

Se il programma ritorna `0` ha avuto successo. Altirmenti un codice diverso da `0` indica una uscita dal programma con un errore.

il fatto che il programma ritorni `0` si può testare tramite

```sh
./a.out; echo $?
# possiamo vedere che ritorna 0 oppure un numero 
```

### Perchè è utile?

la cosa è particolarmente utile in quanto il valore di ritorno può essere usato per concatenare delle operazioni con l'operatore bash `&&`

Ad esempio:

```
./a.out && ls
```

Se **main**
- ritornasse `0`, dopo la sua esecuzione avrei l'esecuzione successiva del comando `ls`
- ritornasse qualunque altro valore diverso da `0` si fermerebbe.

questo perchè per bash l'uscita valid, senza errori è 0 e indica un programma che ha un codice errore 0 (Significa TUTTO OK e non rappresenta un booleano).

Mnemonicamente si può usare 0 come (ZERO ERRORI)



# Pensiero laterale: a cosa mi ha fatto pensare

Come nella lezione precendente mi sono venute in mente alcuni concetti, man mano che la lezione proseguiva.

<a id="coincidence"></a> 
### Programming by coincidence: dal libro The pragmatic programmer (Dave Thomas and Andy Hunt)

Comportamenti indefiniti ed effetti indesiderati sono da evitare, la programmazione per coincidenza ha come effetto maggiore l'imprevedibilità del codice.

Il caso limite è che un programma scritto per coincidenza funzioni non si sa per quale motivo.

<a id="paramvsarg"></a>
### Parametro e argomento 

La distinzione tra argomento e parametro è nota in tutti i linguaggi. 
Il parametro è quello presente nella dichiarazione della funzione, ed invece l'argomento è il valore "reale" passato quando viene eseguita la funzione.

















<br />