
#include <stdio.h>

void incr(int *p){
    printf("Before incr: %d\n", *p);

    p[0] = p[0] + 1;
}


int main(void){
    int x = 5;
    
    printf("x was %d\n", x);

    incr(&x);

    printf("x now is %d\n", x);
    return 0;
}
