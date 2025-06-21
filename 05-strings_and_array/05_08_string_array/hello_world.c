#include <stdio.h>

int main(void){
    // dichiaro array di char   // inizializzo un array 
    char str[6] =               {'h','e','l','l','o', 0}; // lo 0 è il terminatore NULL
    printf("%s\n", str); // uso indicizzato

    return 0;
}