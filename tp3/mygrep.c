#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

int isNeedle(char* buffer, char* target, int i, int length){
    for(int j = 1; j < length; j++){
        if(buffer[i+j] != target[j]){
        return 0;
        }
    }
    return 1;
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("usage: ./mygrep target filename.ext\n");
        exit(EXIT_FAILURE);
    }

    FILE* in = fopen(argv[2], "r");
    char buffer[BUFFER_SIZE];
    int nbytes, length = strlen(argv[1]), line = 1, col = 0;
    do{
        nbytes = fread(buffer, sizeof(char), BUFFER_SIZE, in);
        for(int i = 0; i < BUFFER_SIZE; i++){
            if(buffer[i] == '\n'){
                line++;
                col = 0;
            }
            else{
                col++;
                if(buffer[i] == argv[1][0])
                    if(isNeedle(buffer, argv[1], i , length)) 
                        printf("[%d:%d]\n", line, col);
            }
        }
    }while(nbytes == BUFFER_SIZE);

    return EXIT_SUCCESS;
}