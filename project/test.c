#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* driver(char* arr){
    arr = (char*)malloc(sizeof(char) * 256);
    arr = strcpy(arr,"This is the point of it");
    printf("%s\n", arr);
    return arr;
}

int main(){
    char* arr, *rra;

    strcat(arr, "hey");
    strcat(rra, "oh");

    if(strcmp(arr, rra))
        printf("lets goh\n");

    return 0;
}