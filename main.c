#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "./hangman.h"

#define MAX_CHARS 26

int main(void){

    char* word = "hello";
    int size = strlen(word);
    char dashedWord[size];
    char alreadyTypedChars[MAX_CHARS] = {'\0'};
    int attempts = 0;

    for(int i = 0; i < strlen(word); i++){
        dashedWord[i] = '_';
    }


    while(continueGame(dashedWord ,&size, &attempts)){
        clear_screen();

        mainFrame(dashedWord, alreadyTypedChars, attempts);
        putchar('\n');



        printf("Insert a character: ");
        int character = getchar();
        clearInputBuffer();
        if(validateInput(&character)){
            for(int i = 0; i < MAX_CHARS; i++){
                if(alreadyTypedChars[i] == '\0'){
                    alreadyTypedChars[i] = character;
                    break;
                }
            }
        } else {
            continue;
        }
        if(updateWord(&character, dashedWord, &size, word) == 0){
            attempts += 1;
            continue;
        }
    }

    clear_screen();
    mainFrame(dashedWord, alreadyTypedChars, attempts);
    return 0;
}
