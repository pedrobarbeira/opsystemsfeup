#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){

    if(argc != 1){
        fprintf(stderr, "usage: %s\n", argv[0]);
        return EXIT_FAILURE;
    }
    
    int flag = 1, BUFFER_SIZE = 256;
    char* buffer;
    
    do{
        buffer = malloc(sizeof(char) * BUFFER_SIZE);
        if(getcwd(buffer, BUFFER_SIZE) == NULL) 
            BUFFER_SIZE *= 2;
        else flag = 0;
    }while(flag);
    
    printf("%s\n", buffer);
    
    return EXIT_SUCCESS;
}