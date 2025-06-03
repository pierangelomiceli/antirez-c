# 03: Variabili locali, globali, static e tipi di dati

Questo è un estratto della [terza lezione](https://www.youtube.com/watch?v=mw4gUqsGPZw) del corso **Let's learn C** creato da [Salvatore Sanfilippo (antirez)](https://github.com/antirez)


## Una funzione che incrementa un valore

```c
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
```
Possiamo notare che la funzione viene chiamata 4 volte e tutte e quattro le volte stamperà in output il valore **2**.

In base alle informazioni delle precedenti lezioni possiamo individuare il concetto già espresso: la variabile locale `x` dentro la funzione **incr** viene creata localmente al suo interno e distrutta ogni singola volta.


## La variabile globale

Andando a modificare il codice in questa maniera:
```c

#include <stdio.h>

int x = 0;

void incr(void){
    x = x + 1; 
    printf("%d\n", x); 
}

int main(void){
    incr(); // stampa 1
    incr(); // stampa 2
    incr(); // stampa 3
    incr(); // stampa 4
    return 0;
}

```

All'interno della funzione **incr**, il compilatore, non trovando una variabile locale **x** dichiarata al suo interno, tenterà la ricerca della variabile globale con lo stesso nome.

La differenza tra una variabile locale e globale, è che quella globale non perde il suo stato, viene creata all'inizio del programma ed esisterà fino a quando il programma continuerà a girare, fina a che il processo esiste e l'effetto sarà che il valore verrà incrementato ad ogni chiamata.

Le variabili locali e globali non sono le uniche due variabili che ha il C.


## la variabile static


Il seguente codice:
```c

#include <stdio.h>

void incr(void){
    static int x = 0;
    x = x + 1;
    printf("%d\n", x); 
}

int main(void){
    incr(); // 1
    incr(); // 2
    incr(); // 3
    incr(); // 4
    // questo darebbe errore di compilazione
    // printf("%d\n", x); 

    return 0;
}

```

Dichiarando la variabile int x come static, avremo una variabile globale, che tuttavia sarà visibile solamente dentro la funzione **incr**.

Nel caso in cui tentassimo di usare la vriabile all'esterno di **incr** avremmo un errore di compilazione simile a questo:

```bash
hello_world.c:16:20: error: ‘x’ undeclared (first use in this function)
   16 |     printf("%d\n", x);
      |                    ^
hello_world.c:16:20: note: each undeclared identifier is reported only once for each function it appears in

```

Il programma non compila perché **x** non può essere visto dalla funzione main, perché **x** è globale dal punto di vista della sua vita (della sua lifetime), ma è locale da punto di vista della visibiilità del simbolo **x**, che si può vedere solo al'interno della funzione **incr** però è a tutti gli effetti una variabile globale ccon tutti i limiti derivanti, tra cui il fatto che non è adatta ad essere usata con più **thread** in quanto non sarebbe sicura per via dei problemi di sincronizzazione (perché lo stesso stato globale è condiviso tra i vari thread).

Si potrebbe proteggere con dei mutex etc, ma è un approccio che al momento non ci interessa ai fini della spiegazione.


## Funzione incr con parametro
```c
#include <stdio.h>

int incr(int x){// viene creata una variabile locale x con valore a (ma non è a!)
    x = x + 1; // increamenta questo  valore 
    return x; // lo restitiuisce
}

int main(void){
    int a = 10;
    incr(a);
    printf("%d\n", a); // stamperà 10
    return 0;
}

```

La variabile **x** con valore 10 viene incrementata di 1 e restituita. 

Tuttavia questo non aumenterà il valore della variabile **a** (non viene usato il valore restituito da **incr**) e verrà stampato **10**

## Il passaggio degli argomenti per valore

Se invece scrivessimo:
```c
#include <stdio.h>

int incr(int x){// viene creata una variabile locale x con valore a (ma non è a!)
    x = x + 1; // incrementa questo valore 
    return x; // lo restitiuisce
}

int main(void){
    int a = 10;
    a = incr(a); // riassegno ad a il valore restituito da incr
    printf("%d\n", a); // stamperà 11
    return 0;
}

```
In questo caso, il valore resituito da **incr** viene utilizzato e riassegnato ad **a** e verrà stampato **11**.

Questa ultima modalità è una maniera più funzionale di agire, ma quello che ci interessa capire è che in C, di default, gli argomenti vengono passati alle funzioni per valore e non per riferimento.

Cioè le funzioni ricevono sempre una copia e non un riferimento ai valori che noi passiamo alla funzione.

Questo vale anche per le strutture, cioè oggetti che contengono al loro interno più campi, i corrispettivi degli oggetti per altri linguaggi.

L'unico modo in C per passare un oggetto per riferimento è tramite l'uso dei puntatori.

Sui puntatori bisogna dire una cosa importante: in sostanza non si può fare nulla di buono con il C senza i puntatori, che hanno un ruolo importantissimo, e verrano introdotti molto presto nel corso.

Il motivo è che senza un uso precoce dei puntatori nelle lezioni future, tutta la comprensione del linguaggio ne risulterebbe limitata dal fatto che non c'è modo di esprimere, anche degli esempi semplici, di concetti che sono profondamente idiomatici del C.


## Altri tipi di dati

Il linguaggio C è un programma che ha un certo grado di 'pericolosità'

Guardiamo il codice:

```c
#include <stdio.h>

int main(void){
    int a = 10; // intero
    float y = 1.234;// numero a virgola mobile 
    printf("%d %f\n ",  a, y); //
    return 0;
}
```

restituirà:

```bash
gcc -W -Wall hello_world.c && ./a.out

# output atteso
# 10 1.234000

```

Se invertissimo **y** con **a** nella **printf** avremmo dei warning (in alcuni ambienti è necessario compilare con le opzioni -W -Wall per avere i warning) in fase di compilazione.

Una cosa del tipo:
```bash
hello_world.c:6:14: warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘double’ [-Wformat=]
    6 |     printf("%d %f\n ",  y, a);
      |             ~^          ~
      |              |          |
      |              int        double
      |             %f
hello_world.c:6:17: warning: format ‘%f’ expects argument of type ‘double’, but argument 3 has type ‘int’ [-Wformat=]
    6 |     printf("%d %f\n ",  y, a);
      |                ~^          ~
      |                 |          |
      |                 double     int
      |                %d
```

Questo significa che il compilatore si aspettava dei valori e invece ne ha ricevuti altri:
- dove si aspettava un **int** è stato dato un **double** (??? perché double)
- dove si aspetta un **float** è stato dato un **int**


Tuttavia il programma sarà eseguibile e darà dei valori che potrebbero non avere un senso: C permette comunque di compilare ugualmente, ma deve essere cura del programmatore controllare la correttezza dell'esecuzione.

## Trasformazioni

```c
int main(void){
    char c = 10; // di solito va da -128 a +127 (1 byte, 8 bit, non garantito da specifica)
    short s = 234; // di solito 2 byte 16bit (non garantito da specifica)
    int a = 10; // intero
    unsigned int b = 20;
    float y = 1.2349856;// numero a virgola mobile a 32bit fp32
    // double = 
    printf("%d %f\n ",  a, y); //
    return 0;
}
```

Perché il warning del compilatore ha indicato `double` nonostante avessimo trattato con dei `float`?

Un intero è un numero senza la parte decimale che può essere positivo o negatvo

Volendo può essere solo positivo senza un segno con `unsigned int = 20`

Invece il float è un numero floating piint che rappresenta un numero decimale con un certa precisione che possiamo stabilire.

Il bello del float è che usa una rappresentazione interessante, che è stantard in tutti i linguaggi di prgrammazione, e sono costituiti da una mantissa e un esponente.

Il float è un floating point a 32 bit, mentre il double è a 64bit fp64.

Ma come mai il warning indica un double.

La risposta è che il C ha molti tipi:   

char ad esempio è un interno ancora più piccolo che va da -127 a +128, anche se non è garantito. Di solito è un byte (8 bit)

lo short invece è tradizionalmente, ma non garantito da specifica di 2 byte cioè 16 bit


Immaginiamo se la **printf** dovesse avere un formato per ogni tipo: sarebbe molto più complessa, innanzitutto per quanto riguarda i formati e secondariamente, le funzioni variadiche che accettano questi valori dovrebbe avere a che fare con più valori. 

Dovrebbe avere una funzione apposita, per accedere ad ognuno di questi argomenti passati, per riuscire a runtime ad accedere allo stack per gestire questi argomenti in entrata, dalla coda di argomenti fornita. Distinguere tra i vari tipi la renderebbe troppo complessa da gestire.

Quindi per semplificare quello che succede è che vengono usate delle regole di **promozione** automatiche.

Ad esemio se passo a una funzione variadica un intero che è più piccolo di un **int**, come uno **short**, prima di passare questo short alla **printf** lo converte ad **int**  e poi glielo passa

Alla stessa maniera i **float**, quando vengono apassati a funzioni variadiche, prima di essere passati, vengono promossi a **double**.


Quidni la printf non è in grado di stampare un **float**, ma solamente **double**, perché i **float** vengono promossi a **double**.

Il tutto avviene in maniera del tutto trasparente, ma è bene sapere che esistono queste conversioni implicite .

Qesto tipo di conversioni sono presenti anche in altri casi.


Ad esempio:


```c
int main(void){
    char c  = 127; 
    printf("%d\n ", c); // stampa 127 come previsto
    return 0;
}

```

Se impostaimo 127 che è il numero massimo che può assumere un char (nella maggiorparte dei sistemi) il numero viene stampato come ci aspettiamo.

Se invece:

```c
int main(void){
    char c  = 128; 
    printf("%d\n ", c); 
    return 0;
}

```

Il valore di 128 è fuori dal range massimo da quello che si può rappresentare con un intero con segno da 8 bit, quindi quello che avviene è che verrà stampato -128 (il numero minimo del range -128 e +127 ) come se fosse andato a ricominciare il giro.

Ma ora vedremo in C il wrapping dopo l'overflow (overflow e quando un valore è troppo grande per un dato numero) è garantito solo negli interi con segno.

Negli interi senza segno è una UB undefined behavior, comporatamento non specificato:
```c

int main(void){
    char c  = 12; 
    int i = c+1; // questo ci da un valore corretto perché le regole di converions eautomatica si applicano anche alle espressioni
    printf("%d\n ", c);
    return 0;
}

```

Si potrebbe immaginare che siccome la variabile `c` è un **char**, allora `c+1` è a sua volta un **char** e ci possa riportare a -128 come prima oppure darci un qualsiasi altro comportamento non atteso.

Invece, compilando ed eseguendo, non abbiamo nè un warning, nè un comportamento inaspettato, ma otteniamo il valore corretto.

Questo perché le reole di conversione automatica valgono anche per le espressioni, quindi quando faccio matematica tra interi, avviene una conversione dei valori, ad esempio i signed vengono convertiti in unsigned, i numeri più piccoli di int vengono convertiti in int, e così via per i numeri più grandi.

In questa cosa è facile sbagliare.

In alcuni linguaggi più **safe** preferiscono in realtà avere delle regole più ferree, ad esempio si dichiara un tipo e si fa matematica tra tipi omogenei e non esistono delle regole automatiche di conversione.

In C, linguaggio crato negli anni 60, per questioni di praticità e di risparmio di spazio, si avevano gli `int`, i `char`, gli `short` in quanto era saggio pensare di non usare dei tipi più grandi del necessario.

Per questo motivo c'era questa grande varietà di tipi, ma per funzionare bene però c'era anche la necessità di usare queste regole di conversione per poterli usare insieme.

La **undefined behavior (UB)**, non definisce cosa succede quando gli interi con il segno vanno in overflow.

Esempio:

```c
int main(void){
    char c = 127;
    c++;
    printf("%d\n ", c);
    return 0;
}

```

in questo caso ci restitisce **-128**, ma non essendo specificato dal linguaggio, avrebbe potuto anche dare 0 oppure andare in crash: sugli interi con segno, il C non individua un comportamento standard in caso di overflow, e in questo caso si deve stare attenti a non crearne uno.


Invece, nel caso di **interi unsigned**:

```c
#include <stdio.h>

int main(void){
    unsigned char c = 254;
    c++; // 0 restituisce 0 perché va in overflow
    c++; // 1
    
    printf("%d\n ", c); // stampa 1
    return 0;
}
```

Abbiamo la sicurezza, perché il C lo dichiara nelle specifiche, che nel caso di **interi unsigned** dopo il valore massimo va in overflow e riparte da 0.
