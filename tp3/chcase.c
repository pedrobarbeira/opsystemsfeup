#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER_SIZE 256

int main(char argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "usage: chcase file.txt -option\n");
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    size_t nchars;
    FILE* f = fopen(argv[1], "r");
    do{
        nchars = fread(buffer, sizeof(char), BUFFER_SIZE, f);
        for(int i = 0; i < nchars; i++){
            if(!strcmp(argv[2], "-u"))
                buffer[i] = toupper(buffer[i]);
            else if (!strcmp(argv[2], "-l"))
                buffer[i] = tolower(buffer[i]);
            else exit(EXIT_FAILURE);
        }
        printf("%s", buffer); 
    }while(nchars == BUFFER_SIZE);
    printf("\n");
    exit(EXIT_SUCCESS);
}