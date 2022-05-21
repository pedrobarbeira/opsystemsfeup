#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    pid_t p;
    for(int i = 0; i < 4; i++){
        p = fork();
        printf("%u, %u\n", getpid(), p);
    }
    return EXIT_SUCCESS;
}