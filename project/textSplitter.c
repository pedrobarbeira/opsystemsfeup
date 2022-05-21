#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char out[256];



int main(){
    char* test = "last char is a\0";
    printf("%c", test[strlen(test)-1]);

    return 0;
}