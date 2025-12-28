
#include <stdio.h>

void incr(int *p){
    *p = *p +1;
    // equivalente
    //p[0] = p[0] + 1;
}


int main(void){
    int x = 5;
    int *y = NULL; 

    printf("x was %d\n", x);
    y = &x;
    incr(y);


    // ma anche
    incr(&x);



    printf("x now is %d\n", x);
    return 0;
}
