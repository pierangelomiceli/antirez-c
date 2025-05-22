#include <stdio.h>

int sum(int a, int b){
    int c;
    c = a+b;
    return c;
}

int main(void){
    printf("Ciao: %d\n", sum(10, 20));
    return 0;
}