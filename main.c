#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "./hangman.h"

#define MAX_CHARS 26

int main(void){

    char* word = takeWord();
    int size = strlen(word);
    char dashedWord[size];
    dashedWord[size] = '\0';
    char alreadyTypedChars[MAX_CHARS] = {'\0'};
    int attempts = 0;

    for(unsigned long i = 0; i < strlen(word); i++){
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
            character = tolower(character);
            if(checkAlreadyEnteredChars(alreadyTypedChars, &character)){
                printf("\nWARNING: You already typed this character.\n");
                sleep(2);
                continue;
            }
            for(int i = 0; i < MAX_CHARS; i++){
                if(alreadyTypedChars[i] == '\0'){
                    alreadyTypedChars[i] = character;
                    break;
                }
            }
        } else {
            printf("\nWARNING: Invalid input.\n");
            sleep(2);
            continue;
        }
        if(updateWord(&character, dashedWord, &size, word) == 0){
            attempts += 1;
            printf("\nWARNING: The character isn't in the word to guess.\n");
            sleep(2);
            continue;
        }
    }

    clear_screen();
    mainFrame(dashedWord, alreadyTypedChars, attempts);

    // Banners code is AI generated.
    if(attempts == MAX_ATTEMPTS){
        putchar('\n');
        printf("=========================================================\n");
        printf(" Y   Y    OOO    U   U        L       OOO    SSS   TTTTT \n");
        printf("  Y Y    O   O   U   U        L      O   O  S        T   \n");
        printf("   Y     O   O   U   U   ---  L      O   O   SSS     T   \n");
        printf("   Y     O   O   U   U        L      O   O      S    T   \n");
        printf("   Y      OOO     UUU         LLLLL   OOO    SSS     T   \n");
        printf("=========================================================\n");
        printf("                      YOU LOST\n");
        putchar('\n');


    } else {
        putchar('\n');
        printf("====================================================\n");
        printf(" Y   Y    OOO    U   U        W   W    OOO    N   N \n");
        printf("  Y Y    O   O   U   U        W   W   O   O   NN  N \n");
        printf("   Y     O   O   U   U   ---  W W W   O   O   N N N \n");
        printf("   Y     O   O   U   U        WW WW   O   O   N  NN \n");
        printf("   Y      OOO     UUU         W   W    OOO    N   N \n");
        printf("====================================================\n");
        printf("                     YOU WON!\n");
        putchar('\n');
    }
    return 0;
}
