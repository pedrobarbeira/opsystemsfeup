#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        (void)fprintf(stderr, "usage: %s filename", argv[0]);
        return EXIT_FAILURE;
    }
    
    mode_t mask = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    int fd = open(argv[1], O_CREAT, umask(mask));

    if(fd == -1){
        printf("error: cannot open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    if(close(fd)){
        printf("error: cannot close %s\n", argv[1]);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}