#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define READ_END    0
#define WRITE_END   1
#define TARGET      0
#define SWAP        1

#define LINESIZE    256

int main(int argc, char* argv[]){
    int nbytes, cyph[2], fd[2];
    pid_t pid;
    char line[LINESIZE];

    if(argc != 2){
        fprintf(stderr, "Not enough arguments\n
                        Usage: %s < tocypher > cyphered\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    if(pipe(fd) < 0 || pipe(cyph)){
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0){
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if(pid > 0){
        /*parent*/
        close(cyph[READ_END]);
        dup2(cyph[WRITE_END], STDIN_FILENO);
        close(cyph[WRITE_END]);
        if(wait(pid, NULL, 0) == -1){
            perror("waitpid");
            exit(EXIT_FAILURE);
        }
        open(fd[READ_END]);
        dup2(fd[READ_END], STDOUT_FILENO);
        close(fd[READ_END]);
    }
    else{
        /*child*/
        //load cypher
        int nbytes;
        char buff[LINESIZE];
        char* cypher;
        
        FILE* f = fopen("cypher.txt", "r");
        do{
            nbytes = fread(f, sizeof(char), LINESIZE, buff);
            strcat(cypher, buff);
        }while(nbytes == LINESIZE);
        close(cypher[READ_END]);
        
        int lineCount = 0;
        for(int i = 0; cypher[i] != '\0'; i++){
            if(cypher[i] == '\n') lineCount++;
        }

        char*** cypherTable = (char**) malloc(sizeof(char**)*lineCount);
        for(int i = 0; i < lineCount; i++){
            cypherTable[i] = (char*[2] malloc(sizeof(char*[2])))
        }
        char* target, swap;
        target = strtok(cypher, " ");
        int i = 0;
        do{
            swap = strtok(NULL, "\n");
            cypherTable[i][TARGET] = target;
            cypherTable[i][SWAP] = swap;
            target = strtok(NULL, " ");
        }while(target != NULL);
        
        //read text from file
        char* textToCypher;
        char* word;
        open(cyph[READ_END]);
        do{
            nbytes = fread(cyph[READ_END], sizeof(char), LINESIZE, buff);
            strcat(textToCypher, buff);
        }while(nbytes == LINESIZE);
        close(cypher[READ_END]);
        //cypher text
        char* cypheredText;
        word = strtok(textToCypher, " ");
        while(word != NULL){
            for(int i = 0; i < lineCount; i++){
                if(!strcmp(word, cypher[i][TARGET], strlen(cypher[i][TARGET]))){
                 
                    strcat(cypheredText, word)
                }
            }
        }
        //send to pipe
        close(fd[READ_END);
        open(fd[WRITE_END]);
        do{
            nbytes = fwrite(fd[WRITE_END], sizeof(char*), LINESIZE, cypheredText);
        } while(nbytes == LINESIZE);
        close(fd[WRITE_END]);
    }
    exit(EXIT_SUCCESS);
}