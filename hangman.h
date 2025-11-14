#include <stdbool.h>

void clearInputBuffer(void);
int updateWord(int* character, char wordToGuess[], int* size, char* word);
bool validateInput(int* character);
void mainFrame(char wordToGuess[], char alreadyTypedChars[], int attempts);
