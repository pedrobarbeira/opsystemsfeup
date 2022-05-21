#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE        64

void print_file(FILE* f){
    char* content = (char*)malloc(MAX_SIZE*sizeof(char));
    fread(content, MAX_SIZE, 1, f);
    printf("%s", content);
}


int main(int argc, char* argv[]){
    for(int i = 1; argv[i] != NULL; i++){
        FILE* infile = fopen(argv[i], "r");
        print_file(infile);
    }

    return EXIT_SUCCESS;
}