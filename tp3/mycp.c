#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_SIZE 256
char buffer[BUFFER_SIZE];

int main(int argc, char* argv[]){
    if(argc != 3){
        fprintf(stderr, "usage: ./mycp readfile.txt writefile.txt");
        exit(EXIT_FAILURE);
    }
    FILE* read = fopen(argv[1], "r");
    FILE* write = fopen(argv[2], "w");
    size_t nbytes;
    do{
        nbytes = fread(buffer, sizeof(char), BUFFER_SIZE, read);
        fwrite(buffer, sizeof(char), nbytes, write);
    }while(nbytes == BUFFER_SIZE);

    return EXIT_SUCCESS;
}
