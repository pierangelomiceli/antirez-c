#include <stdio.h>

int main(void){
    int x = 5;
    int *y = &x;
    int **z = &y;
    printf("x is stored in %p and y is stored in  %p\n", y, z );
    printf("%d, %d, %d\n", (int)sizeof(x), (int)sizeof(y), (int)sizeof(z) );

    return 0;
}