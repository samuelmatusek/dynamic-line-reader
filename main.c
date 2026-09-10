#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void uvolni_text(char **text, int radky){

    for (int i = 0; i <= radky; i++){
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
    int velikost_textu_vnejsi = 8;
    int znaky = 0;
    int radky = 0;
    bool enter = false;

    printf("Write any text:\n");

    char **text = malloc(sizeof(**text) * velikost_textu_vnejsi);
    if (text == NULL){
        printf("Nespravny vstup.\n");
        return 1;
    }
    text[0] = malloc(sizeof(*text[0]) * velikost_textu);
  
    while ((c = getchar()) != EOF){
        if (enter){
            text[radky] = calloc(velikost_textu, sizeof(*text[radky]));
            if (text[radky] == NULL){
                uvolni_text(text, radky - 1);
                printf("Nespravny vstup.\n");
                return 1;
            }
        }
        enter = false;

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
            enter = true;

            if (radky == velikost_textu_vnejsi){
                velikost_textu_vnejsi *= 2;
                char **temp = realloc(text, sizeof(**text) * velikost_textu_vnejsi);
                if (temp == NULL){
                    uvolni_text(text, radky);
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                text = temp;
                temp = NULL;
            }
        }
        else {
            text[radky][znaky] = c;
            znaky++;
        }
    }

    if(!enter)
        text[radky][znaky] = '\0';
    else
        radky--;
    
    printf("--- Obracene poradi ---\n");
    for (int i = radky; i >= 0; i--)
        printf("[%d]: %s\n", i + 1, text[i]);
    uvolni_text(text, radky);

    return 0;
}