# 02 appendice: La vita delle variabili locali

Questo è un estratto [dell'appronfondimento](https://www.youtube.com/watch?v=r6mU_IHXEps) della seconda lezione [seconda lezione](https://www.youtube.com/watch?v=Z84vlG1RRtg) **Let's learn C** creato da [Salvatore Sanfilippo (antirez)](https://github.com/antirez)


## Il concetto di distruzione delle variabili

Il concetto affrontato nella *lezione 2*, di ***distruzione delle variabili*** una volta esaurita la loro funzione ha senso quando parliamo di linguaggi ad alto livello che fanno uso di strumenti automatici quali il **garbage collector (GC)**.

Per tale scopo esiste un **reference counter**: è un contatore che tiene conto di quanti riferimenti a una determinato oggetto ci sono in un programma, e quando i riferimenti diminuiscono fino ad arrivare a zero, la variabile viene distrutta in automatico dal **GC**. 
<br />In particolare la referenza a zero significa che gli oggetti creati non sono più referenziati da nessuna variabile globale o locale ed il **garbage collector** elimina l'oggetto che non sarà più recuperabile.

### Cosa significa che una variabile locale viene creata e distrutta?
Per capire questo concetto è necessario capire il funzionamento di alcuni aspetti del microprocessore e lo vedremo in due diversi tipi:

- il 6502: quello del Commodore64 (tra gli altri!)
- il processore 386 (un processore CISC)

## Risorse
- [Easy 6502](https://skilldrick.github.io/easy6502/)
- [Compiler Explorer](https://godbolt.org/) 


## Uno sguardo al 6502

Il 6502 è un processore utile per la sua semplicità, per mostrare come funziona un microprocessore.

Un processore ha 2 possibilità per operare nei dati:
- un set di registri: delle variabili che possono contenere solo numeri (anche numeri in virgola mobile nei processori di nuova generazione). i cosiddetti **registri a microprocessore**
- delle istruzioni che muovono contenuti di una data locazione di memoria della ram, dalla ram ai registri o dai registri alla ram.

Alcuni processori evoluti riescono addirittura a passare un dato da una locazione di memoria ad un'altra locazione di memoria senza passare dai registri (CISC)

Il 6502 ha pochi registri ed è molto semplice.

Ecco un esempio di codice che fa la somma di due numeri, con le istruzioni commentate (ordine tra parentesi)

```s
START:
    LDA #50         ; (1)  LOAD nel registro A, il valore 50
    JSR FILL_FIVE   ; (2) JUMP alla funzione FILL_FIVE
    BRK

FILL_FIVE:
                    
    TAX             ; (3) TRANSFER A to X, questa prima istruzione 
                    ; (4) copia il valore del registro A
                    ; (5) nel registro X
    BEQ DONE        ; (6) se il valore vale 0, e quindi il flag Z fosse 1 
                    ;     allora salterebbe alla istruzione DONE
                    ;     in pratica, si protegge dal fatto che si passi 0.                    
    LDY #$00        ; (7) carica nel registro Y il valore 0
    LDA #$05        ; (8) carica nel registro A il valore 5 
                   
LOOP:               ; questa funzione è importante perché esegue il loop stampando a video (memory-mapped video - la memoria è direttamente collegata ai pixel)
    STA $0200,Y     ; registra il valore di A, aggiungendo Y al valore $0200
    INY             ; INcrementa Y
    DEX             ; DEcrementa X
    BNE LOOP        ; RICOMINCIA DA LOOP, se il valore del "flag Z" è diverso da 1 
                    ; (il flag z avrà valore 1 se l'ultimo valore scambiato è 0,
                    ; dato che l'ultimo valore scambiato fa riferimento a X,
                    ; allora flag z = 1 quando x = 1, cioè alla fine del loop)
DONE:
    RTS
```


Come visto interno di **FILL_FIVE**, abbiamo assegnato 5 ad A (step 8), sovrascrivendo il valore precedentemente assegnato (50) ad A nello **START**.

Tuttavia questo non è un problema, perché il valore di A, prima di essere sovrascritto, è stato scritto nel registro X (TAX) poche istruzioni prima (in FILL_FIVE)

La conclusione da trarre è che i registri vengono usati spesso e vengono sovrascritti altrettanto facilmente, e data questa facilità di sovrascrittura bisogna salvare i valori che ci interessa salvaguardare in altri registri.


## Processore CISC

Per capire come vengono salvati i valori faremo degli esempi con il processore 386 processori CISC, che usano una rappresentazione molto semplice e leggibile delle chiamate, ma prima dobbiamo capire come funziona lo stack.

I valori che vogliamo salvare vengono salvati principalmente nello stack.

Tramite lo stack, come accennato all'inizio, abbiamo la possibilità di spostare dati dai registri alla memoria e viceversa.

Il processore 386 (una tipologia di CISC) ha delle funzioni molto veloci chiamate **"push and pop"** che permettonno questi spostamenti.


### Lo stack

Lo stack è un pezzo della memoria del computer, (un pezzo di memoria uguale alle altre, ma riservata a questo utilizzo) divisa in pezzi da 4 bytes ognuno.

Immaginiamo lo stack come dei blocchi posti uno sopra l'altro, ogni posizione è distante dall'altra di 4 byte (32bit).

Inoltre esiste un "cursore" chiamato "stack pointer", che è un altro registro, che tiene traccia della posizione attuale nello stack.

La funzionalità di **push and pop** non fa altro che prendere il valore di un registro e salvarlo nello stack in maniera veloce e viceversa, spostandosi di volta in volta di una posizione. 

Le posizioni vengono salvate sullo stack pointer.

- push: salva dal registro allo stack
- pop: prende dallo stack al registro

L'ordine della chiamata è molto importante.

### PUSH
Ad esempio:

Push EAX (Push A per semplificare): vogliamo prendere il valore **305419896** salvato nel registro EAX (A) e volerlo salvare nello stack.

L'operazione si articola in 3 fasi.

- Fase 1: Lo SP punta attualemnte punta all'inidirizzo **2147450872** dove c'è il valore **2864434397** (un valore qualsiasi che non ci interessa)
- Fase 2: Lo SP a seguito della richiesta di push viene decrementato di 4 byte per farlo puntare al un nuovo indirizzo: 2147450872 - 4 = **2147450868**
          che ospiterà il valore da memorizzare dal registro EAX
Fase 3: Il valore **305419896** viene inserito nella nuova posizione **2147450868** dello stack. 

```
Fase 1: Iniziale                    Fase 2: Decremento ESP             Fase 3: Trasferimento del valore 305419896

┌─────────────────┐ ← (2147450868)  ┌─────────────────┐ ← (2147450868)   ┌─────────────────┐ ← (2147450868 nuova)
│      VUOTO      │                 │      VUOTO      │                  │   305419896     │ ← Nuovo elemento
├─────────────────┤ ← (2147450872)  ├─────────────────┤ ← (2147450872)   ├─────────────────┤ ← (2147450872)
│   2864434397    │ ← ESP           │   2864434397    │                  │   2864434397    │
├─────────────────┤ ← (2147450876)  ├─────────────────┤ ← (2147450876)   ├─────────────────┤ ← (2147450876)
│      VUOTO      │                 │      VUOTO      │                  │      VUOTO      │
├─────────────────┤ ← (2147450880)  ├─────────────────┤ ← (2147450880)   ├─────────────────┤ ← (2147450880)
│      VUOTO      │                 │      VUOTO      │                  │      VUOTO      │
└─────────────────┘                 └─────────────────┘                  └─────────────────┘
                                                       ↑                                      ↑
                                                       ESP decrementato                      ESP (2147450868)
```


### POP 

Nel pop avviene l'operazione opposta: il valore viene preso dallo stack per poter essere inserito in uno dei registri.

Mettiamo caso che vogliamo memorizzare il nel registro EBX il valore dello stack. 

Fase 1: ESP punta a **2147450868** dove c'è il valore **305419896** (top dello stack)
Fase 2: Il valore **305419896** viene letto e copiato nel registro EAX
Fase 3: ESP viene incrementato di 4 byte: 2147450868 + 4 = **2147450872**


```
Fase 1: Iniziale                    Fase 2: Lettura Valore             Fase 3: Incremento ESP

┌─────────────────┐ ← (2147450868)  ┌─────────────────┐ ← (2147450868)   ┌─────────────────┐ ← (2147450868)
│   305419896     │ ← ESP           │   305419896     │ ← ESP (letto)    │      VUOTO      │
├─────────────────┤ ← (2147450872)  ├─────────────────┤ ← (2147450872)   ├─────────────────┤ ← (2147450872)
│   2864434397    │                 │   2864434397    │                  │   2864434397    │ ← ESP
├─────────────────┤ ← (2147450876)  ├─────────────────┤ ← (2147450876)   ├─────────────────┤ ← (2147450876)
│      VUOTO      │                 │      VUOTO      │                  │      VUOTO      │
├─────────────────┤ ← (2147450880)  ├─────────────────┤ ← (2147450880)   ├─────────────────┤ ← (2147450880)
│      VUOTO      │                 │      VUOTO      │                  │      VUOTO      │
└─────────────────┘                 └─────────────────┘                  └─────────────────┘
                                                       ↑                                      ↑
Registro EBX = (vuoto o con altro valore)               EBX = 305419896                      ESP incrementato

```
**Nota:**
Nel push abbiamo salvato il valore da EAX nello Stack Pointer, mentre nell'operazione di POP abbiamo preso dallo stack al registro EBX.

L'intento di usare due registri differenti per il push ed il pop nell'esempio è voluto, per chiarire che non necessariamente deve esserci una corrispondenza tra il registro che salva sullo stack con quello registro che prende dallo stack.

In sostanza, uno qualunque dei registri può prendere il valore dallo stack usando il pop, ad esempio se abbiamo usato il registro A per fare il push alla posizione X non è detto che sia il registro A a fare il pop in quella posizione.

Questo spiega quanto detto in precedenza e cioè che i registri possono essere sovrascritti e che è nostra cura salvaguardare i dati che sono necessari.


## Codice compilato

Andiamo ad analizzare il codice:

```c
int sum(int a, int b){
    return a+b;
}

int main(void) {
    int d = ciao();
    return sum(10,20);
}

```

Quando andiamo a decompilare sul 386 otteniamo le due sezioni di `_sum` e `_main`, di seguito le operazioni con la loro sequenza tra parentesi:

```s
_a$ = 8                                             ; size = 4
_b$ = 12                                            ; size = 4
_sum    PROC
        push    ebp                                 ; (6)  Salva il base pointer precedente per poterlo ripristinare
        mov     ebp, esp                            ; (7)  salva il contenuto di esp nel base pointer
        mov     eax, DWORD PTR _a$[ebp]             ; (8)  viene salvato nel registro EAX il valore presente all'indirizzo di ebp+8 (8 perché è _a)
        add     eax, DWORD PTR _b$[ebp]             ; (9)  allo stesso registro, aggiunge il valore memorizzato all'inidirizzo ebp+12 (12 perché _b è 12)
        pop     ebp                                 ; (10) ripristina ebp
        ret     0                                   ; (11) ritorna, ripristinando il program counter
_sum    ENDP

_main   PROC
        push    ebp                                 ; (1)  Salva il base pointer precedente per poterlo ripristinare
        mov     ebp, esp                            ; (2)  salva il contenuto di esp nel base pointer
        push    20                                  ; (3)  Push di 20 nello stack
        push    10                                  ; (4)  Push di 10 nello stack
        call    _sum                                ; (5)  Chiama e salta alla funzione sum
        add     esp, 8                              ; (12) Si sposta di 2 word (8 byte) per ignorare i parametri
        pop     ebp                                 ; (13) può ripristinare l'ebp
        ret     0
_main   ENDP
```

Rappresentando i vari livelli di operazioni nello stack, abbiamo:

```
┌─────────────┐ ← ESP (top dello stack)  
│     EBP     │ ← Ultimo inserito
├─────────────┤
│     PC      │ ← Program Counter (indirizzo ritorno)
├─────────────┤
│     10      │ ← Primo parametro
├─────────────┤
│     20      │ ← Secondo parametro  
├─────────────┤
│     EBP     │ ← EBP precedente (salvato) posizione 
├─────────────┤
│     ---     │ ← Altri dati/bottom/precedenti
└─────────────┘
```

Questa semplificazione serve ad avere una mappa mentale di ciò che avviene quando vengono modificati i valori nei registri, prendendo i valori dalla memoria e viceversa. <br /> Man mano che si prosegue con le operazioni di chiamate a funzione, vengono eseguiti dei push che spostano lo stack pointer avanti e indietro continuamente, stessa cosa avviene per ogni chiamata a funzione.

Oltre ai push dei valori dei parametri, i salti nello stack avvengono tramite il pattern di salvataggio e ripristino dell'ebp, questo sovrascrive costantemente i registri ed è cio che avviene in C quando si usano le variabili locali.

Capire sommariamente come funziona è necessario per avere una migliore comprensione di ciò che avviene in C.