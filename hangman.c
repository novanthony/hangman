#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void clearInputBuffer(void){
    int c = getchar();
    while(c != '\n'){
        if(c == EOF){
            exit(EXIT_FAILURE);
        }
    }
}

bool validateInput(char* character){
    if(*character >= 65 && *character <= 90){
        return true;
    }

    if(*character == EOF){
        exit(EXIT_FAILURE);
    }

    if(*character >= 97 && *character <= 122){
        return true;
    } else {
        return false;
    }
}

int updateWord(int* character, char wordToGuess[], int* size, char* word){
    int count = 0;
    for(int i = 0; i < *size; i++){
        if(word[i] == (char)(*character)){
            wordToGuess[i] = (char)(*character);
            count += 1;
        }
    }
    return count;
}

void mainFrame(char wordToGuess[], char alreadyTypedChars[], int attempts){
    printf("Attempts: %d\n", attempts);
    printf("Already typed chars: ");
    for(int i = 0; alreadyTypedChars[i] != '\0'; i++){
        printf("%c, ", alreadyTypedChars[i]);
    }
    putchar('\n');

    printf("Word to guess: %s\n", wordToGuess);

}
