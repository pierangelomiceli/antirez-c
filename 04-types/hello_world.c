
#include <stdio.h>

void clear(void){

    // antirez scrive questo che va bene sul suo sistema.
    // nel mio sistema, arch linux, usando questa forma semplificata non è sufficiente, dopo il comando il programma pulisce lo schermo, ma non pulisce il cursore
    // e viene lasciato scritto ./a.out:
    // printf("\x1b[H");

    // alternative
    // .[H.[2J.[3J
    // printf("\x1b[H\x1b[2J\x1b[3J"); 

    // ma anche quello che è rappresentato nell'output di hexdump -C (canonico)
    // cioè: 1b 5b 48 1b 5b 32 4a 1b 5b 33 4a
    printf("òsadlasòà òlsaòdsad asdsk lskalkldklk laskdlsakdòlk òlaksòlklò klòaksalòkdalòk òlakslòckalòkò lasdas asdasda");
}

int main(void){
    clear();
    printf("Hello worldsdasàdl òàlasòàldòasàlòasàl òàlcàòalsàòl òà lòàalsòàldaàòl àòalòàslòà lòàa");
    return 0;
}