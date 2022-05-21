#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFERSIZE 256

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "usage: %s n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char* fileName = "mem.txt";
    char buffer[BUFFERSIZE];
    int lineCount = 0, nbytes;

    FILE* f = fopen(fileName, "r");
    do{
        nbytes = fread(buffer, sizeof(char), BUFFERSIZE, f);
        for(int i = 0; i < BUFFERSIZE; i++)
            if(buffer[i] == '\n') lineCount++;
    }while(nbytes == BUFFERSIZE);

    if(lineCount < atoi(argv[1])){
        fprintf(stderr, "memory size of %d exceeded\n", lineCount);
        exit(EXIT_FAILURE);
    }

    char* args[] = {"tail", "-n", argv[1], fileName, NULL};

    if(execvp("tail", args) < 0){
        perror("execvp error\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}