#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256
char buffer[BUFFER_SIZE];

int main(int argc, char* argv[]){
    if(argc > 3 || argc < 2){
        printf("usage: ./mywc filename -opt");
        exit(EXIT_FAILURE);
    }
    
    FILE* f = fopen(argv[1], "r");
    int nbytes, count = 0;

    do{
        nbytes = fread(buffer, sizeof(char), BUFFER_SIZE, f);
        if(argc == 2 || !strcmp(argv[2], "-c")) count += nbytes;
        else if (!strcmp(argv[2], "-w")){
            strtok(buffer, " ");
            do{
                count++;
            }while(strtok(NULL, " ") != NULL);
        }
        else if(!strcmp(argv[2], "-l")){
            for(int i = 0; i < nbytes; i++)
                if(buffer[i] == '\n') count++;

        }

    }while(nbytes == BUFFER_SIZE);

    printf("%d\n", count);
    
    return 0;
}