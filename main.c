#include <stdio.h>
#include <stdlib.h>

int main(void){

    int c;
    int velikost_textu = 8;

    printf("Write any text:\n");

    char **text = malloc(sizeof(**text) * velikost_textu);
    if (text == NULL){
        printf("Nespravny vstup.\n");
        return 1;
    }
  
    while ((c = getchar()) != EOF){
        
    }
    
    





    return 0;
}