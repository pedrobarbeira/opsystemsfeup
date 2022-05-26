#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ 0
#define WRITE 1

int main(){
    int fd1[2], fd2[2];
    pid_t pid;

    pipe(fd1);
    pipe(fd2);

    pid = fork();

    if(pid > 0){
        printf("stdi to fd1 write\n");
        dup2(fd1[WRITE], STDIN_FILENO);
        close(fd1[READ]);
        printf("stdout to fd2 read\n");
        dup2(fd2[READ], STDOUT_FILENO);
        close(fd2[WRITE]);
        waitpid(0, NULL, 0);
    }
    else{
        printf("stdin to fd1 read\n");
        dup2(fd1[READ], STDIN_FILENO);
        close(fd1[WRITE]);
        printf("stdout to fd2 write\n");
        dup2(fd2[WRITE], STDOUT_FILENO);
        close(fd2[READ]);
        printf("there\n");
        exit(EXIT_SUCCESS);
    }
    return 0;
    
}