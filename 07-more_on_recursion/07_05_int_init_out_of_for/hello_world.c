#include <stdio.h>

int main(void){ 

    // dichiarando fuori possiamo riutiizzare i dopo il ciclo while
    int i=0;
    for (i = 0; i < 10; i++) printf("%d\n", i); 

    printf(">>%d", i); // comodo
    
    return 0;
}