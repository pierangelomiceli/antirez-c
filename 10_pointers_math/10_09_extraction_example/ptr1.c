
#include <stdio.h>

int main(void){
    char mystr[] = "AABBCCDDEEFF";
    
    char *p = mystr;

    char **p2 = &p;

    // prima estrazione 
    printf("Address of **p is %p\n", p2);
    printf("Address of **p is %p\n", p2);

    // seconda estrazione
    printf("Address of *p is %p\n", p2[0]);
    printf("Address of *p is %p\n", *p2);

    // valore del carattere
    printf("Value of char is %c\n", p2[0][0]);
    printf("Value of char is %c\n", **p2);
    
    return 0;
}
