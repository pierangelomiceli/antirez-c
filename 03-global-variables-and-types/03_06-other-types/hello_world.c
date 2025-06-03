#include <stdio.h>

int main(void){
    char c = 10; // di solito va da -128 a +127 (1 byte, 8 bit, non garantito da specifica)
    short s = 234; // di solito 2 byte 16bit (non garantito da specifica)
    int a = 10; // intero
    unsigned int b = 20; // intero unsigned
    float y = 1.2349856;// numero a virgola mobile a 32bit fp32
    // double = 
    printf("%d %f\n ",  a, y); //
    return 0;
}


