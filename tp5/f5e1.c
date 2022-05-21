#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    pid_t f1 = getpid();
    
    pid_t f2 = fork();

    pid_t f3 = fork();

    pid_t f4 = fork();

    printf("f1: %u, f2: %u, f3: %u, f4: %u\n", f1, f2, f3, f4);

    return EXIT_SUCCESS;
}