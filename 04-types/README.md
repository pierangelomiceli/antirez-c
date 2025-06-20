# 04: Variabili locali, globali, static e tipi di dati

Questo è un estratto della [quarta lezione](https://www.youtube.com/watch?v=YNsXyasn4R4) del corso **Let's learn C** creato da [Salvatore Sanfilippo (antirez)](https://github.com/antirez)


Una volta affrontati i tipi interi, poi facciamo un salto indietro.

In altri tipi di linguaggi, per gli interi, c'è una certa consistenza nel come vengono trattati a prescindere dal sistema, ed è così negli altri linguaggi anche moderni, con principi differenti o anche di basso livello.

Il C è un linguaggio degli anni '60 la cui ambizione era la compatibilità con tutti i sistemi, ognuno dei quali poteva avere la propria implementazione.

Per tali motivi, dei tipi non è specificato quanto debba essere grande.

Ad esempio un `int` e varia da piattaforma a piattaforma: può essere a 32, 16, 64 bit etc

Una cosa che però vale per tutte le implementazioni è che se un `int` dichiarato non viene preceduta dalla parola chiave `unsigned`, allora l'intero può rappresentare sia numeri negativi che numeri positivi.

Non possiamo sapere però quanto sia grande.


## Funzione sizeof()

Tuttavia, possiamo ricorrere alla funzione `sizeof()` che ci permette di sapere, nella specifica piattaforma, di sapere quanto occupa una variabile.
```c
#include <stdio.h>

int main(void){
    int x = 5;
    printf("Hello world: int is %d bytes\n", sizeof(x));
    return 0;
}
```

Compilando, possiamo ricevere un `warning` (in alcuni sistemi per ottenere il warning si devono usare le opzioni `-W`, o `-Wall`)

```sh

gcc -Wall hello_world.c && ./a.out 

# output
#    hello_world.c: In function ‘main’:
#    hello_world.c:6:34: warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long unsigned int’ [-Wformat=]
#     6 |     printf("Hello world: int is %d bytes\n", sizeof(x));
#     |                                 ~^           ~~~~~~~~~
#     |                                  |           |
#     |                                  int         long unsigned int
#     |                                 %ld
# Hello world: int is 4 bytes

```

Significa che il compilatore si aspettava di ricevere un intero (con `%d`), ma il tipo ritornato da `sizeof` è un intero lungo senza il segno (`unsigned long`).

Questo warning si può affrotnare in due modi differenti:

### Modo 1: casting della variabile

Per utilizzare la tenica del `casting` si antepone alla variabile, tra parentesi il tipo di destinazione.

Letteralmente: 

***converti quello che è a destra del casting, nel tipo tra parentesi***

```c

#include <stdio.h>

int main(void){
    int x = 5;
    // con il casting si converte il risultato di sizeof(x) in un (int)
    printf("Hello world: int is %d bytes\n", (int)sizeof(x));
    return 0;
}

```

Compilando ed eseguendo il warning scompare.

```sh
gcc hello_world.c && ./a.out 

# output
# Hello world: int is 4 bytes
```

### Modo 2: utilizzando lo specificatore di tipo `lu`

Un altro modo per eliminare il warning, è quello di usare `lo specificatore di tipo` corretto sulla `printf` che in questo caso per il `long unsigned` è `lu` 

```c

#include <stdio.h>

int main(void){
    int x = 5;
    // lu è lo specificatore di tipo corretto per rappresentare l'output di sizeof
    printf("Hello world: int is %lu bytes\n", sizeof(x));
    return 0;
}

```

```sh
gcc hello_world.c && ./a.out 

# output
# Hello world: int is 4 bytes
```


## Analisi dell'output di sizeof per l'intero

L'output di `sizeof` ci dice che un intero, nel nostro sistema è composto da 4 byte. 

`2^32` contiene `4294967296` simboli

In altre parole, dovendo rappresentare:

- un intero senza segno (2^32): da 0 a 4294967295 simboli (4294967296-1 perché lo zero è uno dei simboli da rappresentare) 
- un intero con segno (2^31): da -2147483648 a +2147483647 (2147483648-1)


## limits.h

Tornando al nostro programma, ci potremmo chiedere se ci fosse la possibilità di sapere il numero minimo e massimo di simboli, senza doverlo calcolare come abbiamo appena fatto.

Sì, usando la limits.h possiamo usare `INT_MIN` e `INT_MAX`:

```c
#include <stdio.h>
#include <limits.h>

int main(void){
    int x = 5;
    printf("Hello world: int min: %d, int max %d\n", 
        INT_MIN, iNT_MAX
    );
    return 0;
}
```

Una volta inclusto `limits.h` il preprocessore trasforma queste due costanti nei valori corrispondenti, rappresentaibli su quella piattaforma.

```sh
gcc hello_world.c && ./a.out 

# output
# Hello world: int min: -2147483648, int max 2147483647
```

Tuttavia, a volte abbiamo la necessità di scrivere dei programmi in cui si debba garantire che un tipo abbia una precisa dimensione, e purtroppo il linguaggio `C` non ce lo può garantire.

**Anche se non c'è garanzia, ci si può aspettare dai moderni sistemi a 32 e 64 bit, al 99%* si abbia una certa uniformità.**

**In passato, sono stati creati sistemi in cui il byte stesso era grande 36 bit oppure anche da 9 bit, tuttavia oggi è molto standardizzato, anche se, ripetiamolo, non è assolutamente garantito!**



## stdint.h

Per avere la garanzia che un determinato dato abbia sempre una certa dimensione, esiste la libreria con tipi avanzati: `stdint.h`

```c
#include <stdio.h>
#include <limits.h>
#include <stdint.h>

int main(void){
    // tipi avanzati di stdint.h
    uint64_t  // intero senza segno da 64 bit
    int64_t     // interno con segno a 64 bit
    size_t       // puo' rappresnetare una grandezza in base al target del processore   
    

    // c
    char c = 1;         // intero a 8 bit, 1 byte
    short s = 2000;     // 16 bit, 2 byte
    int x = 5;          // 4 bytes -> 32 bit
    long l = 10;        // 8 byte -> 64 bit
    printf("Long is %lu bytes\n", sizeof(l));
    return 0;
}

```

La lunghezza del `long` è interessante ed è rappresentata in `8 byte` cioè 8*8 -> 64 bit su questo sistema.

Proprio il `long` nel 99% dei casi, risulta essere della stessa grandezza della parola (word) del microprocessore: 
- in un processore a 64 bit sarà grande 64 bit
- in un processore a 32 bit sarà grande 32 bit

Questo ci dice una cosa interessante.

Alcuni vecchi programmi, assumevano di poter registrare un indirizzo di memoria in un `int`.

Se in questi programmi l'int è grande come l'indirizzo di memoria non ci sono problemi di sorta.

Se invece l'int è più piccolo dell'indirizzo di memoria (come in tutte le macchine moderne) questi vecchi programmi non funzionano o si comporta in maniera subdola o addirittura andare in crash.


I tipi avanzati del `C` che sono inclusi in `stdint.h` e che non erano parte della specifica, permettono di specificare esattamente la grandezza voluta.

Ad esempio;

- `uint64_t`: è un intero senza segno da 64 bit
- `int64_t`: è un intero con segno a 64 bit
- `size_t`: può rappresentare una grandezza in base al target del processore per il quale sto compilando il programma. 
    Ad esempio può essere un pezzo di memoria allocato, la grandezza di un file oppure la dimensione massima di un oggetto di qualunque tipo.

Abbiamo anche anche dei tipi specifici nelle nuove implementazioni del C, ad esempio:

- `intptr_t`: un intero con una grandezza che ci sassicura che possa contenere un indirizzo di memoria, e cioè un puntatore.
- `uintptr_t`: stessa cosa ma senza il segno.

### Nota 
Se gli indirizzi di memoria non possono essere negativi, ma sono sempre positivi, (immaginiamo un blocco contiguo da zero fino a un tot, nel caso esteremo da 0 fino a 64 bit), perché esiste un tipo compatibili con gli indirizzi di memora ma con segno come `intptr_t`?

Il motivo è che a volte, facciamo delle operazioni di sottrazione sui puntatori che possono dare vita a un numero negativo.


## perché ci sono così tanti tipi? 

Per una questione di prestazioni ed ottimizzazioni della memoria:

- `char`: i caratteri è utilissi è il modo incui si rapprensetano le stringhe, che vengono rappresentati come array di char
- `short`: se voglio rappresentare numeri piccoli, mi permette di risparmiare molta memoria,: in una machcian a 64 bit in un long ci entrano 4 short.
- `uint64_t`: se usiamo il `long` oppure `uint64_t` siamo sicuri di poter fare delle operazioni matematiche per numeri a 32bit e non può succedere che possano andare in overflow: ho quindi un spazio maggiore di bit per fare operazioni più grandi e posso incremantarli senza avere paura di farli andare in overflow.

## Analisi della struttura del nostro programma

Guardando questo programma:

```c

#include <stdio.h>

                                // main: nome della funzione, 
// ritorna un int               // (void): parametri della funzione       
int                             main(void){
    
    // printf: chiamata alla funzione omonima
    // ("Hello world\n"): argomenti passati alla funzione
    printf      ("Hello world\n");

    // return: ritorno (dovrà tornare un int)
    // 0: valore di ritorno (0, ma può essere 3+2 o qualsiasi espressione di un intero)
    return 0;
}

```
Notiamo come questa sia una definizione di una funzione che:

- ha `int` come tipo di ritorno.
- `main` è il nome della funzione.
- tra parentesi `(void)` ci sono espressi i parametri della funzione separati da virgola, in altri casi potrebbe essere (int x, float y) etc. etc.
- `printf()` è una chiamata a funzione. 
            Una chiamata a funzione in C di sperime scrivendo il loro nome, aprendo la parentesi tonda e dando la lista degli argomenti richiesti (se sono previsti). 


## Creazione di una funzione che pulisce lo schermo e stampa 'Hello world'

Mettiamo il caso di voler creare una funzione che pulisca lo schermo e dubito dopo stampi `Hello World` a video.

Al momento, mettiamo il caso che non sappiamo la sequenza di escape per eseguire la pulizia dello schermo. 

Conosciamo però il comando apposito: `clear()`

Così, atraverso il pipe unix (`|`), possiamo inviarlo al comando `hexdump` che ci farà vedere la sequenza in uscita dal programma:

```sh
clear | hexdump -C

# output
# 00000000  1b 5b 48 1b 5b 32 4a 1b  5b 33 4a                 |.[H.[2J.[3J|
# 0000000b
```

### Nota
Con `man ascii` possiamo vedere a cosa corrispondono questi caratteri.


La visualizzazione di `hexdump` ci permette di scrivere una funzione `clear()` attraverso il nostro programma, utilizzando una sequenza simile:

```c

#include <stdio.h>

void clear(void){

    // antirez scrive questo che va bene sul suo sistema.
    // printf("\x1b[H");

    // nel mio sistema, arch linux, usare la forma semplificata non è sufficiente. 
    // Infatti dopo l'esecuzione il programma, lo schermo viene pulito, ma non pulisce il cursore
    // e viene lasciato scritto ./a.out:
    
    // ho creato anche delle alternative:
    // .[H.[2J.[3J
    // printf("\x1b[H\x1b[2J\x1b[3J"); 

    // oppure possiamo usare (tradotto) quello che è rappresentato nell'output di hexdump -C (canonico)
    // cioè: 1b 5b 48 1b 5b 32 4a 1b 5b 33 4a
    printf("\x1b\x5b\x48\x1b\x5b\x32\x4a\x1b\x5b\x33\x4a");
}

int main(void){
    clear();
    printf("Hello world\n");
    return 0;
}
```
Per i nostri scopi avremmo potuto usare anche `fflush()`, ma sono funzionalità che verranno affrontate durante lo studio di input/output della libreria del `C`.

Nel nostro caso, quanto fatto è sufficiente, perché alla fine della nostra `printf` c'è un `\n` (newline) che fa il flush del buffer.

Per spiegare meglio il funzionamento, possiamo dire che la `printf` accumula in memoria un buffer fino a quando non vede una newline o fino a quando non viene chiamato `fflush()`.

La strategia di usare il buffer di accumulo, viene usata per evitare ogni volta di fare tante operazioni di I/O, ottimizzando così le prestazioni.

Quando però viene incontrato un `newline` viene flushato il buffer e il contenuto va in `output`.

Nel nostro programma ` printf("\x1b\x5b\x48\x1b\x5b\x32\x4a\x1b\x5b\x33\x4a");` rimane in memoria e non viene fatto output.

Invece la seconda chiamata `printf("Hello world\n")` contiene il newline e provoca l'output su schermo.


### simbolo ; e indentazione come stile personale
Come detto `clear()` è una chiamata a funzione

Le diverse dichiarazioni e statement sono divisi da un `;`.

Noi potremmo scrivere anche una cosa del genere e sarebbe perfettamente valido.

```c
int main(void){    printf("Hello world\n");    return 0;}

```

Il compilatore non fa distinzione, l'indentazione serve all'umano per questioni di leggibilità.

Si consiglia di fare pratica scrivendo manualmente l'indentazione, senza affidarsi ad indentatori automatici, in modo da acquisre dimestichezza e coltivare il proprio stile di scrittura dei programmi.

### return
Il programma scritto è composto da una sola parola chiave che è `return`, che restituisce `0`.

Lo `0` è una espressione che potrebbe essere qualunque tipo di intero


Nel nostro programma `return` è una parola chiave (insieme a `int` e `void`), mentre le altre sono funzioni ed espressioni scritte da noi.


## Perché la printf pulisce lo schermo?

Quello che noi usiamo è un emulatore di terminale. 

Qualisiasi comando impartito ad un terminale viene interpretato per dare un output.

Il terminale ha la necessità di distinguere quando vogliamo stampare qualcosa sullo schermo, rispetto a quando vogliamo spedire dei caratteri che sono delle sequenze di controllo. 

Le sequenze di controllo dal teminale VT-100 (1978) funzionano sommariamente così:
- come prima cosa, viene inviato il carattere di escape `\x1b` 
- poi scrive una parentesi quadra `[` 
- poi altre lettere che indicano cosa fare.

In realtà, [H significa Home e dovrebbe portare il cursore in alto sulla finestra del terminale (dipende dal sistema)

In python, ad esempio, in modalità interprete, si deve scrivere una sequenza più completa, tuttavia se lanciamo lo script da file funziona alla stessa maniera con la stessa sequenza del C.

Probabilemnte questo dipende dalla modalità con la quale venfono interpretati i caratteri di escape nella REPL in modalità RAW, rispetto alla modalità cooked con file eseguito.
