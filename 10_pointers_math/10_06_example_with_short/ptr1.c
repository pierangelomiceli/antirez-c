
#include <stdio.h>

int main(void){
    char mystr[] = "AABBCCDDEEFF";
    
    short *p = (short*)mystr;

    p += 1;
    
    printf("%d\n", *p);

    return 0;
}