#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    char buf[1024];
    char* args[256];
    pid_t pid;

    for( ; ; ){
        char* command;
        fprintf(stdout, "$ ");
        if((command = fgets(buf, sizeof(buf), stdin)) == NULL){
            break;
        }
        command[strlen(buf) -1] = '\0';
        if(!strcmp(args[0], "exit")) exit(EXIT_SUCCESS);
        FILE* f = fopen("mem.txt", "a");
        fwrite(command, sizeof(char), strlen(command), f);
        fputc('\n', f);
        fclose(f);
        int i = 0;
        do{
            if(i == 0) args[i] = strtok(command, " ");
            else args[i] = strtok(NULL, " ");
            i++;
        }while(args[i-1] != NULL);

        if((pid = fork()) == -1){
            fprintf(stderr, "%s: cant fork command: %s", 
                argv[0], strerror(errno));
            continue;
        } else if (pid == 0){
                execvp(args[0], args);
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