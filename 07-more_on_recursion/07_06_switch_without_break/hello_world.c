

#include <stdio.h>

int main(void){ 

    int i = 5;
    switch(i){
        case 3: 
            // non entrerebbe perché il valore non corrisponde
            printf("è un tre\n");
            // break; 
        case 5: 
            // entrerebbe qui
            printf("è un cinque\n");
            printf("Sì, proprio un bel cinque\n");
            break; 
        case 6: 
            // entrerebbe anche qui perchè prima non c'è break nel case precendente in cui è entrato
            printf("è un sei\n"); 
            break;
        case 7: 
            // qui non entra perché prima c'è sopra c'è il break
            printf("è un sette\n"); 
            break;
        
        default: printf("qualche altro numero\n"); 
            break;
    }
    return 0;
}