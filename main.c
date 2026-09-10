#include <stdio.h>
#include <stdlib.h>

void uvolni_text(char **text, int radky){

    for (int i = 0; i < radky; i++){
        if (text[i] != NULL)
            free(text[i]);
    }

    free(text);
}

char realokuj_text(char **text, int radky, int velikost_textu){

    char *temp = realloc(text[radky], sizeof(*text[radky]) * velikost_textu);
    if (temp == NULL){
        uvolni_text(text, radky);
        return 1;
    }
    text[radky] = temp;
    temp = NULL;

    return 0;
}

int main(void){

    int c;
    int velikost_textu = 8;
    int znaky = 0;
    int radky = 0;

    printf("Write any text:\n");

    char **text = malloc(sizeof(**text) * velikost_textu);
    if (text == NULL){
        printf("Nespravny vstup.\n");
        return 1;
    }
    text[0] = malloc(sizeof(*text[0]) * velikost_textu);
  
    while ((c = getchar()) != EOF){
        if (znaky + 1 == velikost_textu && c != '\n'){
            velikost_textu *= 2;
            if(realokuj_text(text, radky, velikost_textu)){
                printf("Nespravny vstup.\n");
                return 1;
            }
            text[radky][znaky] = c;
            znaky++;
        }
        else if (c == '\n'){
            text[radky][znaky] = '\0';
            velikost_textu = 8;
            znaky = 0;
            radky++;
            if(realokuj_text(text, radky, velikost_textu)){
                printf("Nespravny vstup.\n");
                return 1;
            }
        }
        else{
            text[radky][znaky] = c;
            znaky++;
        }
    }
    
    printf("--- Obracene poradi ---\n");
    for (int i = radky; i >= 0; i--)
        printf("[%d]: %s\n", radky + 1, text[radky]);
    uvolni_text(text, radky);

    return 0;
}