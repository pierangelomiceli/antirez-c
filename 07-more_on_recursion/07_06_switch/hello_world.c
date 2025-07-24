

#include <stdio.h>

int main(void){ 

    int i = 5;
    switch(i){

        case 5: 
            // entra qui
            printf("è un cinque\n");
            printf("Sì, proprio un bel cinque\n");
            break; 
        case 6: 
            // ma non qui
            printf("è un sei\n"); 
            break;
        case 7: 
            // e nemmeno qui
            printf("è un sette\n"); 
            break;        
            // e nemmeno qui
        default: printf("qualche altro numero\n"); 
            break;
    }
    return 0;
}