# 05: Variabili locali, globali, static e tipi di dati

Questo è un estratto della [quinta lezione](https://www.youtube.com/watch?v=SWWHqgSwQFw) del corso **Let's learn C** creato da [Salvatore Sanfilippo (antirez)](https://github.com/antirez)

## Stringhe di C


Entriamo adesso dentro alcune delle peculiartià del C addentrandoci nelle stringhe del C.ù

Finora, abbiamo visto i tipi interi e la sintassi di un programma scritto in C.

```c
#include <stdio.h>

int main(void){
    printf("Hello world %d\n", 10);
    return 0;
}
```

Abbiamo anche visto he la `printf` prende una stringa di formato con caratteri ed il segnaposto con `%d` ovvero il simbolo percentuale e delle lettere per indicare cosa daremo come argomenti e cosa deve stampato.

In questo specific caso si aspetta un intero e lo stampa.


Eseguendo abbiamo:

```sh

gcc -W -O2 -Wall hello_world.c && ./a.out

# output
# Hello world 10
```


In C, esiste un modo differente per esprimere i numeri, ma prima diciamo che scrivendo: 

```c
#include <stdio.h>

int main(void){
    char c = 10;
    printf("Hello world %d\n", c);
    return 0;
}
```

cioè dichiarando un `char` o uno `short` ed usandoli come argomento nella `printf`, questi verranno promossi a `int` (infatti non ci sarà nessun warning di incongurenza di tipo da parte della printf come nelle invece visto in alcuni passaggi delle lezione precedente)

C'è un modo differente di indicare i numeri interi di tipo `char` e cioè con gli apicini (apici singoli)

```c
#include <stdio.h>

int main(void){
    char c = 'a'; // usiamo gli apici singoli
    printf("Hello world %d\n", c);
    return 0;
}
```

Nell'esempio, abbiamo un intero di tipo `char`.

Si potrebbe obiettare che si tratta di una stringa qualsiasi, che invece di usare apici doppi usi solamente gli apici singoli.

Questo è indifferente per linguaggi coem il `Python` o `JavaScript`, ma in C c'è una netta differenza.

**In C gli apici possono contenere solo un singolo carattere** e qusto caratte verrà espanso al numero che rappresetna la posizione di quel carattere nello standard `ASCII`.


Se inseriamo nel carattere dentro gli apici, un valore fuori dall'ASCII, verrà mappato ad un byte specifico per l'architettura.

Tuttavia questa è una rarità, ed è un caso che si sta bene attenti a non fare mai accadere, in quanto di solito si rimane all'interno di ASCII (da 0 a 255).

Adesso ad esempio andiamo ad assegnare alla variabile c assegniamo la `A`. 

La a maiuscola in ASCII corrisponde al numero 64


```sh
man asci
# parte dell'output della mappatura
#     001   1     01    SOH (start of heading)      101   65    41    A
```



Compilando ed eseguendo il seguente programma:
```c

#include <stdio.h>

int main(void){
    char c = 'A'; // usiamo gli apicini
    printf("Hello world %d\n", c);
    return 0;
}
```
abbiamo:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# Hello world 65

```

Usando `vi` (quando siamo in modalità insert) se inviamo `Ctrl+V` e poi `Ctrl+A` si va ad inserire un carattere `verbatim`, cioè dice che il prossimo carattere non verrà interpretato, ma verrà letto dalla tastiera in `raw` ed inserito così com'è.

Possiamo vedere a cosa corrisponde questo valoe `^A`

```c
#include <stdio.h>

int main(void){
    char c = ''; 
    printf("Hello world %d\n", c);
    return 0;
}
```
restituisce:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# Hello world 1
```

Quindi, quelli dentro gli apici sono interi e da questo si vede che il **C gestisce tutto come numeri anche quando si parla di stringhe**.

La particolarità è che:

- `char c` è u tipo letterale che è un carattere
- `239240` è un tipo numerico che è un intero
- `1.2349293402` è un tipo numerico float

sono tuti **tipi letterali** che ha una certa sintassi per avere un determinato tipo.

Ad esempio potrei avere un linguaggio che può avere:

```sh
a = 1
b = 1.5
```
ma potrebbe essere sprovvisto di una sintassi per scrivere gli array con `[]`

in quel caso potrebbe avere un funzione per esprimere gli array fatta in questa maniera.

```sh
Array(1,2,3) oppure per gli array nested Array(1,2,Array(1,2,))
```

Questo per spiegare che non sempre un tipo supportato da un linguaggio, debba avere per forza il relativo tipo letterale.

Il C ha pochi tipi letterali.
Il carattere è uno, e la stringa è un altro.

## printf alternative output

Un altro modo di scrivere la stringa `Hello World` potrebbe essere questo:

```c
#include <stdio.h>

int main(void){
    printf("%s", "Hello World");
    return 0;
}

```

in questo caso, nel primo argomento specifichiamo il tipo che noi vogliamo in output, cioè `%s` e poi stampiamo una stringa, che è quello che passiamo come secondo argomento, `Hello World`.ù

Quindi nel C abbiamo anche il tipo letterale `string`

In output abbiamo:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
Hello World
```


Potremmo anche scrivere:


```c
#include <stdio.h>

int main(void){
    printf("[%s]\n", "Hello World");
    return 0;
}
```
per avere il nostro output tra parentesi quadre.

```sh

gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# [Hello World]
```

# specificatore di carattere

Il C ha anche la possibilità di stampare il carattere, con l'uso dello specificatore di stringa `%c`:

```c
#include <stdio.h>

int main(void){
    printf("[%c%c%c%c%c]\n", 65, 66, 67, 68, 'x' );
    return 0;
}
```

in output avremo ad esempio:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# [ABCDx]
```

Possiamo quindi fornire sia dei numeri interi che verranno convertiti nel corrispondente valore `ASCII`, oppure fornire direttamente il singolo carattere voluto (in questo caso `x`) e funzionerebbe in entrambi i casi senza problemi di sorta.


## Array

Nelle lezioni precedenti abbiamo visto che possiamo dichiarare una variabile e inizializzarla successivamente.

Ad esempio:

```c
#include <stdio.h>

int main(void){
    int a = 10;
    printf("%d\n", a );

    return 0;
}
```

La variabile `a` in questo caso è un `int`, ma potrebbe essere inizializzata come un array:

```c
#include <stdio.h>

int main(void){
    // dichiara array       // inizializza un array
    int a[5] =              {10,5,50, 100, 7};
    printf("%d %d %d\n", a[0],a[1],a[2]  ); // uso indicizzato

    return 0;
}
```

La sintassi per indicizzare gli array con la parentesi quadra ([0], [1], [2] etc.) è comune a molti linguaggi successivi al C.

Invece l'inizializzazione con le parentesi graffe è meno comune.

Il motivo è che i progettisti dei linguaggi successivi al C, hanno intuito che sarebbe stato meglio unificare il modo di inizializzare e di indicizzare gli array, per dare uniformità al linguaggio stesso e facilitarne la mnemonicità.

Compilando ed eseguendo abbiamo:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# 10 5 50
```


## Array di char: le stringhe

In C le stringhe non sono altro che array di char:

```c
#include <stdio.h>

int main(void){
    // dichiaro array di char   // inizializzo un array 
    char str[6] =               {'h','e','l','l','o', 0}; // lo 0 è il terminatore NULL
    printf("%s\n", str); // uso indicizzato

    return 0;
}
```

In questo caso stiamo usando lo specificatore di tipo `%s` per indicare una stringa.

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# hello

```

Lo `0`, che viene usato alla fine dell'array, è il `Terminatore NULL` e serve per indicare al C che la stringa è finita.

In alcuni sistemi, non inserire il terminatore NULL, provoca errori di visualizzazione della stringa ed effetti inattesi, dopo i caratteri voluti.

Dato che la stringa in C è una sequenza di byte, senza intestazione e altri elementi, non potrebbe sapere quando la stringa è finita, e l'unico modo per indicarlo è con un carattere speciale, lo 0, anche detto **Terminatore NULL**

Quindi abbiamo visto che:

**In C, la stringa è un array di interi di tipo char, che sono interi di 8 bit (1 byte) ciascuno (8 bit è vero per il 99% delle architetture moderne).**


## Stampare una stringa usando %c

Abbiamo usato lo specificatore di tipo stringa `%s`, ma nessuno ci vieta di trovare un modo per stampare la stringa utilizzando lo specificatore di tipo `%c`

Essendo la stringa un array, potremmo fare:

```c
#include <stdio.h>

int main(void){
   
    char str[6] = {'h','e','l','l','o', 0};
    
    int i = 0;
    while(str[i] != 0){
        printf("%c", str[i]);
        i++;
    }
    printf("\n");

    return 0;
}
```
in output avremmo:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# hello
```

Cioè andiamo a ciclare il nostro array di `char` inserendo un `newline` dopo il completamento del ciclo, ciclo che viene completato non appena si arriva al terminatore NULL.


## Un modo più semplice per trattare le stringhe

Sappiamo che `C` è un linguaggio ostico, ma devo sempre per forza definire una stringa in questa maniera?

Fortunatamente no.

```c
#include <stdio.h>

int main(void){
    
    // possiamo scriverla così (primo formato)
    char str[6] = {'h','e','l','l','o', 0};

    // possiamo scriverla così (secondo formato)
    char str2[6] = "hello";                     
    
    printf("Hello World: %s %s\n", str, str2);

    return 0;
}
```

che produce:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# Hello World: hello hello
```

**Nota**
Dato che abbiamo il secondo formato (quello i doppi apici), che è molto più immediato, quando usiamo le stringhe possiamo anche evitare di usare il primo formato (quello con le parentesi graffe).

Tuttavia, il primo formato sarebbe stato necessario nel caso in cui avessimo voluto creare un array di `int` o altri array che non fossero stringhe.
 

## Dimensione dell'array

Scrivendo:

```c
#include <stdio.h>

int main(void){
    char str2[4] = "hello";                     
    
    printf("Hello World: %s \n", str2);

    return 0;
}
```

in fase di compilazione avremmo un `warning` di questo tipo (lo eseguiamo anche dato che è "solo" un `warning`):

```sh
    gcc -W -O2 -Wall hello_world.c && ./a.out 

    # output
    # hello_world.c:4:20: warning: initializer-string for array of ‘char’ is too long (6 chars into 4 available)
    # 4 |     char str2[4] = "hello";
    # Hello World: hell 
```

Ci sta dicendo che l'array che dovrebbe contenere la stringa è troppo piccolo e la stringa verrà troncata (come si vede dall'output)

Se invece l'array contenitore fosse più grande della stringa non rileverebbe alcun problema.


## Dichiarazione di un array senza la dimensione

Possiamo anche eliminare il numero che indica il numero di caratteri dell'array.

In questo caso sarà C che calcolerà la dimensione corretta

```c
#include <stdio.h>

int main(void){
    char str2[] = "hello";  // non indichiamo la dimensione           
    
    printf("Hello World: %s \n", str2);

    return 0;
}
```

Funziona perfettamente:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# Hello World: hello
```

# Uso di sizeof() sull'array

Usando `sizeof()` possiamo ottenere la grandezza del nostro array:

```c
#include <stdio.h>

int main(void){
    char str2[] = "hello";                     
    
    printf("Hello World: %s \n", str2);
    printf("sizeof: %lu\n", sizeof(str2));

    return 0;
}
```
ci aspettiamo 6:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# Hello World: hello 
# sizeof: 6

```

La chiamata a funzione `sizeof` avviene in fase di compilazione e non a runtime. Sono quindi chiamate che possono essere considerate gratuite, non esiste nessun tempo di chiamata.

## Assegnazione di un valore a un elemento della stringa

Essendo che la nostra stringa è un array di caratteri, così come possiamo accedere ai singoli elementi con l'indicizzazatore, alla stessa maniera potremo anche settarli, sia impostando un `char` che impostando un `numero` perché

**ricordiamo sempre che in C le stringhe sono array di numeri, ognuno dei quali prende lo spazio di un byte da 0 a 127 (ASCII)**

```c
#include <stdio.h>

int main(void){
    char str[] = "hello";                     
    str[2] = 'X';   // posso assegnare un char (la prima 'l' diventa 'X')
    str[3] = 65;    // posso assegnare un numero (la seconda 'l' diventa 'A')
    str[4]++;       // posso incrementare il valore (la 'o' diventa 'p')
    printf("Hello World: %s \n", str);

    return 0;
}
```
in output abbiamo:

```sh
gcc -W -O2 -Wall hello_world.c && ./a.out 

# output
# Hello World: heXAp
```
In questo caso abbiamo fatto le nostre sostituzioni:

- `str[2] = 'X'`   // posso assegnare un char (la prima 'l' diventa 'X')
- `str[3] = 65`    // posso assegnare un numero (la seconda 'l' diventa 'A')
- `str[4]++`       // posso incrementare il valore (la 'o' diventa 'p')

