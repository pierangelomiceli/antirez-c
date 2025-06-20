#include <stdio.h>

int main(void){
    int x = 5;
    // con il casting si converte il risultato di sizeof(x) in un (int)
    printf("Hello world: int is %d bytes\n", (int)sizeof(x));
    return 0;
}
