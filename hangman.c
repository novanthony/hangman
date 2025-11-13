#include <stdio.h>
void clearInputBuffer(void){
    int c;
    while((c = getchar()) != '\n'){
        ;
    }
}
