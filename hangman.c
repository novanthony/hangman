#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ATTEMPTS 6

void clearInputBuffer(void){
    int c = getchar();
    while(c != '\n'){
        if(c == EOF){
            exit(EXIT_FAILURE);
        }
    }
}

bool checkAlreadyEnteredChars(char alreadyEnteredChars[], int* size, char* character){
    for(int i = 0; alreadyEnteredChars[i] != '\0'; i++){
        if(*character == alreadyEnteredChars[i]){
            return true;
        }
    }
    return false;
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
    char word[1024];
    int lineCount = 0;
    char wordList[1024][1024];

    fp = fopen("./wordlist.txt", "r");
    if(fp == NULL){
        printf("Some errors eccoured with I/O file.");
        sleep(3);
        exit(EXIT_FAILURE);
    } else {
        while(fgets(word, sizeof word, fp) != NULL){
            word[strcspn(word, "\n")] = '\0';
            strcpy(wordList[lineCount], word);
            lineCount++;
        }
    }
    fclose(fp);

    int size = 0;
    // Calculate the number of words in the wordlist
    // Pick a random numbet between 0 and the numbers in the wordlist
    // Return wordlist[index of that random number]

}
