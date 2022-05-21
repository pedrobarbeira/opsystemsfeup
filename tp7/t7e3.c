#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

#define LINESIZE 256

char* cmd1[3];
char* cmd2[3];
char* cmd3[3];


int cmdloader(char* args){
    int j = 0;
    int cm = 0;
    char* buff = strtok(args, " ");
    do{ 
        if(!strcmp(buff, "|")) {
            cm++;
            j = 0;
        }
        else {
            switch(cm){
                case 0: cmd1[j] = buff; break;
                case 1: cmd2[j] = buff; break;
                case 2: cmd3[j] = buff; break;
                default:{
                    fprintf(stderr, "command limit exceeded\n");
                    exit(EXIT_FAILURE);
                }
            }
            j++;
        }
        buff = strtok(NULL, " ");
    }while((buff != NULL));

    return 0;
}


int main (int argc, char* argv[]) {
    int fd[2];
    pid_t pid;
    char buffer[LINESIZE];

    if(argc != 2){
        fprintf(stderr, "usage: tube \"cmd1 | cmd2\"");
        exit(EXIT_FAILURE);
    }
    
    cmdloader(argv[1]);

    
    if (pipe(fd) < 0) {
        perror("pipe error\n");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0) {
        perror("fork error\n");
        exit(EXIT_FAILURE);
    }


    if (pid > 0) {
        close(fd[READ_END]);
        dup2(fd[WRITE_END], STDOUT_FILENO); // stdout to pipe
        close(fd[WRITE_END]);
        // parent writes to the pipe
        if (execvp(cmd1[0], cmd1) < 0) {
            perror("exec error");
            exit(EXIT_FAILURE);
        }
    } else {
        close(fd[WRITE_END]);
        dup2(fd[READ_END], STDIN_FILENO); // stdin from pipe
        close(fd[READ_END]);
        if (execvp(cmd2[0], cmd2) < 0) {
            perror("exec error");
            exit(EXIT_FAILURE);
        }
    }
    exit(EXIT_SUCCESS);
}