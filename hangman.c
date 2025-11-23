#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAX_WORD_LENGTH 1024

#include "hangman.h"

void clearInputBuffer(void){
    int c = getchar();
    while(c != '\n'){
        if(c == EOF){
            exit(EXIT_FAILURE);
        }
        c = getchar();
    }
}

bool checkAlreadyEnteredChars(char alreadyEnteredChars[], int* character){
    for(int i = 0; alreadyEnteredChars[i] != '\0'; i++){
        if(*character == alreadyEnteredChars[i]){
            return true;
        }
    }
    return false;
}

bool validateInput(int* character){
    if(*character >= 'A' && *character <= 'Z'){
        return true;
    }

    if(*character >= 'a' && *character <= 'z'){
        return true;
    }
    return false;
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
    // HANGMANPICS code is AI generated
    const char *HANGMANPICS[7] = {
            "  +---+\n  |   |\n      |\n      |\n      |\n      |\n=========",
            "  +---+\n  |   |\n  O   |\n      |\n      |\n      |\n=========",
            "  +---+\n  |   |\n  O   |\n  |   |\n      |\n      |\n=========",
            "  +---+\n  |   |\n  O   |\n /|   |\n      |\n      |\n=========",
            "  +---+\n  |   |\n  O   |\n /|\\  |\n      |\n      |\n=========",
            "  +---+\n  |   |\n  O   |\n /|\\  |\n /    |\n      |\n=========",
            "  +---+\n  |   |\n  O   |\n /|\\  |\n / \\  |\n      |\n========="};

    printf("%s",    HANGMANPICS[attempts]);
    printf("\n\nAttempts: %d\n", attempts);
    if(alreadyTypedChars[0] != '\0'){
        printf("Already typed chars: ");
        for(int i = 0; alreadyTypedChars[i] != '\0'; i++){
            printf("%c, ", alreadyTypedChars[i]);
        }
    }

    putchar('\n');

    printf("Word to guess: %s\n", wordToGuess);
}

bool continueGame(char wordToGuess[], int* size, int* attempts){
    bool dashInWord = false;
    for(int i = 0; i < *size; i++){
        if(wordToGuess[i] == '_'){
            dashInWord = true;
        }
    }

    if(*attempts < MAX_ATTEMPTS && dashInWord){
        return true;
    }

    return false;
}

void clear_screen(void){
    //printf("\033[2J\033[H"); // It keeps the previous frame if scroll up the terminal on linux
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        // It appends clear command on history...
        system("clear");  // Linux
    #endif
}

char* takeWord(void){
    FILE *fp;
    static char word[MAX_WORD_LENGTH];
    int lineCount = 0;

    fp = fopen("./wordlist.txt", "r");
    if(fp == NULL){
        goto file_error;
    }

    // count words in the wordlist.txt file
    while(fgets(word, sizeof word, fp) != NULL){
        lineCount++;
    }

    rewind(fp);

    if(ferror(fp)){
        fclose(fp);
        goto file_error;
    }

    // Dynamic allocation sice it's illegal jump on the label if I have a VLA
    char (*wordList)[MAX_WORD_LENGTH] = malloc(lineCount * MAX_WORD_LENGTH);
    if(!wordList){
        fclose(fp);
        fputs("\nMemory allocation for the wordlist failed.\n", stderr);
        return NULL;
        }

    // Copy the words from the file to the array
    for(int i = 0; fgets(word, sizeof word, fp) != NULL && i < lineCount; i++){
        word[strcspn(word, "\n")] = '\0';
        word[0] = tolower(word[0]);
        strcpy(wordList[i], word);
    }
    fclose(fp);

    // take a random word
    srand(time(0));
    int choice = rand() % lineCount;
    strcpy(word, wordList[choice]);
    free(wordList);
    return word;

    file_error:
        fputs("\nSome errors eccoured with I/O file.\n", stderr);
        return NULL;
}
