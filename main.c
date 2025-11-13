#include <stdio.h>
#include <string.h>

#include "./hangman.h"

int main(void){
    char* word = "hello";
    char dashedWord[strlen(word)];
    for(int i = 0; i < strlen(word); i++){
        dashedWord[i] = '_';
    }

    printf("%s\n\n",dashedWord);
    printf("Insert a character: ");
    int character = getchar();
    clearInputBuffer();


    return 0;
}
