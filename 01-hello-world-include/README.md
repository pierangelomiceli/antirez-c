# 01: HelloWorld 

Questo è un estratto della [prima lezione](https://www.youtube.com/watch?v=HjXBXBgfKyk) del corso **Let's learn C** creato da [Salvatore Sanfilippo (antirez)](https://github.com/antirez)


## Il caso più semplice: Hello World

Il seguente codice:

```c
#include <stdio.h>

int main(){
    printf("Hello world\n");
}
```

che noi andiamo a compilare tramite il compilatore, ad esempio `cc` o `gcc`,
viene trasformato in linguaggio macchina.


```sh
# dopo avere lanciato il comando 

cc hello_world.c

# viene creato un file di output a.out che contiene 
# sia il linguaggio macchina che altre informazioni utili


# con il comando 'file' possiamo guardare effettivamente le intestazioni, 
# che saranno differenti a seconda della piattaforma (Mac, Linux, WSL)
# in cui viene eseguita l'operazione
file a.out 

# per vedere il contenuto del file possiamo andare ad usare comando hexdump 
hexdump -C a.out 
```

## Assembly generato

Con certi compilatori di linguaggio C, ad esempio usando `cc -S` si può vedere l'assembly generato a partire dal programma.

il comando genera un file dello stesso nome con estensione .s contenente il linguaggio assembly.

```sh
cc -S hello_world.c
```

### Perché soffermarsi sull'assembly? 
Perché ci soffermiamo sul punto in cui generiamo l'assembly, cioè nella fase che precede la generazione del linguaggio macchina?

Perché è importante capire che, a seconda delle opzioni che diamo al compilatore, vengono generati assembly differenti, che portano con sé differenti livelli di ottimizzazione e performance.


```sh
# quando si compila un programma in C, di solito lo si fa con l'opzione -O 
cc -O2 hello_world.c
```

L'uso di questa opzione, attiva un certo grado di ottimizzazione, già molto spinto. A questo livello il compilatore si accorge di cose che potrebbero essere scritte meglio e farà delle operazioni e modifiche, traducendo il programma in uno più efficiente a parità di comportamento.

Se facciamo:
```sh
cc -O2 -S hello_world.c
```

Notiamo che il codice assembly generato sarà molto differente rispetto a quello generato senza l'uso dell'opzione `-O2`

## Un esempio banale di quello che il compilatore fa con le opzioni attivate

Ad esempio:

Senza ottimizzazione, il codice generato conterrebbe sostanzialmente la chiamata alla funzione `printf` come scritta nel codice. 

Ecco un estratto dei punti interessanti:

```s
; qui viene chiamata la printf
	bl	_printf

; la stringa presenta il carattere di newline
	.asciz	"Hello world\n"
```

Usando invece l'opzione `-O2` viene richiamata la funzione `puts`.

Altra cosa interessante da notare è che, dato che **puts**, di per sè, aggiunge un carattere newline `\n` quando  viene usato, il compilatore, "sapendolo", va a rimuovere il carattere di newline dalla nostra stringa, di fatto, modificandola.
 
```s
; qui viene chiamata la puts
	bl	_puts
; la stringa viene modificata eliminando il carattere di newline
	.asciz	"Hello world"
```

Altre differenze possono essere osservate, se facciamo un output su due file differenti ci accorgiamo a vista delle differenze:
```sh
# con -O0
cc -S -O0 hello_world.c -o hello_world_o0.s

# con -O2
cc -S -O2 hello_world.c -o hello_world_o2.s
```

Tramite questo esempio si vuole sottolineare il fatto che il compilatore è uno strumento evoluto e le ottimizzazioni che fa sono le più disparate.

Nello specifico caso, la differenza tra la scelta del compilatore di usare **puts** piuttosto che usare **printf**, è un caso base, ma dice molto sulla raffinatezza.

La differenza di performance tra le due funzioni, è evidente anche andando a vedere il manuale di printf e di puts, [dove ci si accorge della differenza che è molta, anche solo a guardare la complessità tra le due funzioni](#kissandry)

```sh
man 3 printf
man 3 puts
```

# Analisi delle parti del programma

```c
#include <stdio.h>

int main(){
    printf("Hello world\n");
}
```

## Analisi di #include <stdio.h>: la direttiva di preprocessore

```c
#include <stdio.h> 
```
Questa è una direttiva di preprocessore.

Il compilatore, prima di compilare chiama un altro programma, a volte parte del compilatore stesso, che processa queste direttive.

Le direttive non sono parte del linguaggio, ma sono delle istruzioni di operazioni preliminari da eseguire prima della compilazione vera e propria.

Nel caso specifico la `#include` non fa altro che prendere il contenuto di un file `stdio.h`, scompattarlo e piazzarlo nel punto in cui è scritto. 

Dentro ci sono tutte le intestazioni delle funzioni che man mano andiamo usando.

La `printf` è una funzione di libreria e non fa parte del linguaggio C stesso, quindi per usarla gli si deve dire dove si trova.

Il file .h è un file di intestazione (header) che non contiene davvero la logica del programma, ma delle informazioni di "contorno".

Avremmo potuto scrivere anche:

```c 
#include <stdio.h>

int main(){
    #include "file.c"
}
```
e nel `file.c`
```c
#include <stdio.h>

printf("Hello worldo\n");
```
e non sarebbe cambiato nulla.
in sostanza l'inclusione è un segnaposto per una inclusione di file.

### Se togliessimo l'inclusione il compilatore andrebbe in errore.

- compilatori evoluti, che sanno che stai cercando di usare la printf ci dice che non puoi chiamare in maniera implicita

- altri compilatori semplicemente direbbero che non trova la funzione voluta, come se fosse una funzione sconosciuta.

### prototipo di funzione

Andando a vedere il manuale della printf della libreria standard `man 3 printf`

```c
    int printf(const char *restrict format, ...);
```
al contrario di una ipotetica `main()`, questa funzione non presenta le parentesi graffe con il corpo contenente l'implmentazione, e termina con un `;`

Questo è il prototipo di funzione, che serve a definire il tipo di ritorno e gli argomenti che la funzione prende affinché un altro programma che la usa conosca il tipo di ritorno e gli argomenti senza necessariamente curarsi del [suo comportamento interno](#blackbox). 

## quindi abbiamo visto

- .h file: sorgente che non contiene la logica vera e proprio ma informazioni
- .c file: il file con il programma o contenenti le funzioni con le implementazioni.


# Pensiero laterale: a cosa mi ha fatto pensare
Man mano che seguivo i ragionamenti di [antirez](https://github.com/antirez), mi sono sovvenute delle pratiche o delle associazioni di idee che non necessariamente sono legate al corso.

Mi pareva utile metterle per iscritto.


<a id="blackbox"></a>
### BLACKBOX:  Nascondere i dettagli di implementazione.

Una pratica comune nei linguaggi di programmazione in generale, sopratutto in quelli ad alto livello con l'uso delle interfacce, è sapere come chiamare una una API o un interfaccia tramite la sua firma (che è il prototipo della funzione), senza dover conoscere come la questa implementa i comportamenti interni. Il nostro software è una scatola chiusa è il dettaglio implementativo non è di interesse della funzione chiamante.

Trovo anche una affinità con la DI dependency injection, la IOC (inversion of control) dei linguaggi di alto livello come C#
 
<a id="kissandry"></a> 
### KISS, DRY, SOLID, SRP, SOC OVVERO: La differenza tra fare una cosa e farla bene, oppure tante cose però male

Un software o un pezzo di codice, è tanto più efficiente e veloce, tanto meno sono i compiti che questo deve svolgere, di contro, quando un programma aumenta le sue funzionalità, aumenta anche la complessità e la sua inefficienza.

Se un software deve fare tanti tipi di attività è più difficile da manutenere, da testare e da ottimizzare.

Non è il caso della printf o della puts, ovviamente :D
