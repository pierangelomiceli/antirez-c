#include <stdio.h>

int main(void){
    char str[] = "hello";                     
    str[2] = 'X';   // posso assegnare un char (la prima 'l' diventa 'X')
    str[3] = 65;    // posso assegnare un numero (la seconda 'l' diventa 'A')
    str[4]++;       // posso incrementare il valore (la 'o' diventa 'p')
    printf("Hello World: %s \n", str);

    return 0;
}