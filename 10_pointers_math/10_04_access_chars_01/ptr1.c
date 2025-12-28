
#include <stdio.h>

int main(void){
    char mystr[] = "Hello World";

    char *p = mystr; 

    printf("%c%c\n", p[0], p[1]);


    return 0;
}