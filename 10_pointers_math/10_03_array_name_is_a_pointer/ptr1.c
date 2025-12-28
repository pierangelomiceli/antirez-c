
#include <stdio.h>

int main(void){
    char mystr[] = "Hello World";

    char *p = mystr; // non serve &mystr, il nome mystr è già un puntatore

    printf("At %p I can see: %s\n", mystr, mystr );

    return 0;
}