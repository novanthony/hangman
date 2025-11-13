#include <stdio.h>
#include <stdbool.h>

void clearInputBuffer(void){
    int c;
    while((c = getchar()) != '\n'){
        ;
    }
}

bool validateInput(char* character){
    if(*character >= 65 && *character <= 90){
        return true;
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
