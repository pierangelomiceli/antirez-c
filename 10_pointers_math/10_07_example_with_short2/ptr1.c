#include <stdio.h>

int main(void){
    char mystr[] = "AABBCCDDEEFF";
    
    short *p = (short*)mystr;

    // stampo la posizione del quarto short 0 1 2 3 4
    printf("%d\n", p[4]); 

    return 0;
}