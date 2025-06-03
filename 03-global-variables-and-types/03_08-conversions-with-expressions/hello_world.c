#include <stdio.h>

int main(void){
    char c  = 127;
    // questo ci da un valore corretto (128) perché le regole di 
    // conversione automatiche si applicano anche alle espressioni
    int i = c+1; 
    printf("%d\n ", c);
    return 0;
}

