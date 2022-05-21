#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    char buf[1024];
    char* command;
    pid_t pid;

    for( ; ; ){
        fprintf(stdout, "$ ");
        if((command = fgets(buf, sizeof(buf), stdin)) == NULL){
            break;
        }
        command[strlen(buf) -1] = '\0';

        if((pid = fork()) == -1){
            fprintf(stderr, "%s: cant fork command: %s", 
                argv[0], strerror(errno));
            continue;
        } else if (pid == 0){
            execlp(command, command, (char*) 0);
            fprintf(stderr, "%s: couldn't exec %s: %s\n", 
                argv[0], buf, strerror(errno));
            exit(EXIT_FAILURE);
        }
        if((pid = waitpid(pid, NULL, 0)) < 0)
            fprintf(stderr, "%s: waitpid error: %s\n",
                argv[0], strerror(errno));
    }
    exit(EXIT_SUCCESS);
}