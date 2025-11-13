#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "./hangman.h"

int main(void){

    char* word = "hello";
    int size = strlen(word);
    char dashedWord[size];

    for(int i = 0; i < strlen(word); i++){
        dashedWord[i] = '_';
    }

    while(true){

        printf("Insert a character: ");
        int character = getchar();
        clearInputBuffer();
        if(!validateInput(&character)){
            continue;
        }
        if(updateWord(&character, dashedWord, &size, word) == 0){
            continue;
        }

        printf("\n\n%s\n", dashedWord);
    }

    return 0;
}
