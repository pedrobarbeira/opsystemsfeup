#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "filelib.h"

int main (int argc, char** argv) {
    
    if(argc != 2){
        fprintf(stderr, "usage: %s, filename\n", argv[0];
        return EXIT_FAILURE;
    }

    

    return EXIT_SUCCESS;
}