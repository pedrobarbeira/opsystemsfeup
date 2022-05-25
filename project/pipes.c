#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){
    int fd1[2], fd2[2];
    pid_t pid;

    pipe(fd1);
    pipe(fd2);
    //redirect here
        //parent replace fd1[WE] for STDIN
        //child replace fd1[RE] FOR STDIN 
        //parent replace fd2[RE] for STDOUT
        //child replace fd2[WE] for STDOUT

    pid = fork();

    if(pid > 0){
        dup2(fd1[0], STDIN_FILENO);
        dup2(fd2[1], STDOUT_FILENO);
    }
    else{
        dup2(fd1[1], STDOUT_FILENO);
        dup2(fd2[0], STDIN_FILENO);
        int nbytes;
        char buffer[256];
        nbytes= read(fd1[0], buffer, 256);
        buffer[15]='x';
        write(fd2[1], buffer, 256);
        exit(EXIT_SUCCESS);
    }
    return 0;
    
}