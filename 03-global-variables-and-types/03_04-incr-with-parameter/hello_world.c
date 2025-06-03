#include <stdio.h>

int incr(int x){// viene creata una variabile locale x con valore a (ma non è a!)
    x = x + 1;
    return x;
}

int main(void){
    int a = 10;
    incr(a);
    printf("%d\n", a); // stamperà 10
    return 0;
}
