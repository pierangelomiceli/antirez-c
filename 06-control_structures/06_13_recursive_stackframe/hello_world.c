#include <stdio.h>

void conta(int start, int end){

    printf("%p %p\n", &start, &end);

    if(start> end) return;

    printf("%d\n", start);

    conta(start+1, end);

}


int main(void){  
   
    conta(0,9);

    return 0;
} 