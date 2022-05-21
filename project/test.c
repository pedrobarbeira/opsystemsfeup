#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
#define C 0
#define CPP 1

#define BUFFERSIZE 256

char buffer[BUFFERSIZE];
char buffer1[BUFFERSIZE];
char buffer2[BUFFERSIZE];
int flag = 0;

int main(){
    int fd1[2], fd2[2], nbytes;
    pid_t pid;
    
    read(STDIN_FILENO, buffer, BUFFERSIZE);

    if(pipe(fd1) < 0) {
        perror( "fd1 pipe error\n");
        exit(EXIT_FAILURE);
    }

    if(pipe(fd2) < 0) {
        perror("fd2 pipe error\n");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0) {
        perror("fork error\n");
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        close(fd1[READ_END]);
        write(fd1[WRITE_END], buffer, strlen(buffer));
        close(fd1[WRITE_END]);
        flag = 1;
        waitpid(0, NULL, 0);
        read(fd2[READ_END], buffer2, BUFFERSIZE);
        write(STDOUT_FILENO, buffer2, strlen(buffer2));
        exit(EXIT_SUCCESS);

    } else {
        close(fd1[WRITE_END]);
        read(fd1[READ_END], buffer1, BUFFERSIZE); // stdin from pipe
        close(fd1[READ_END]);
        strcat(buffer1, "All hail Master Barbeira\n");
        write(fd2[WRITE_END], buffer1, strlen(buffer1));
        close(fd2[WRITE_END]);
        
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);
}