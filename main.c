#include <stdio.h>
#include <stdlib.h>

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
            int **temp = realloc(text[radky], sizeof(*text[radky]) * velikost_textu);
            if (temp == NULL){
                for (int i = 0; i < radky; i++)
                    free(text[i]);
                free(text);
                printf("Nespravny vstup.\n");
                return 1;
            }
            text[radky] = temp;
            **temp = NULL;
            text[radky][znaky] = c;
            znaky++;
        }
        else if (c == '\n'){
            text[radky][znaky] = '\0';
            velikost_textu = 8;
            znaky = 0;
        }
        else{
            text[radky][znaky] = c;
            znaky++;
        }
    }
    
    





    return 0;
}