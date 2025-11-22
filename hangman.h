#include <stdbool.h>

#define MAX_ATTEMPTS 6

void clearInputBuffer(void);
int updateWord(int* character, char wordToGuess[], int* size, char* word);
bool validateInput(int* character);
void mainFrame(char wordToGuess[], char alreadyTypedChars[], int attempts);
bool continueGame(char wordToGuess[],int* size, int* attempts);
void clear_screen(void);
bool checkAlreadyEnteredChars(char alreadyEnteredChars[], int* character);
char* takeWord(void);
