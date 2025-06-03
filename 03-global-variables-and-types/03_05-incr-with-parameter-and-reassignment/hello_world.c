#include <stdio.h>

int incr(int x){// viene creata una variabile locale x con valore a (ma non è a!)
    x = x + 1; // increamenta questo  valore 
    return x; // lo restitiuisce
}

int main(void){
    int a = 10;
    a = incr(a); // riassegno ad a il valore restituito da incr
    printf("%d\n", a); // stamperà 10
    return 0;
}
