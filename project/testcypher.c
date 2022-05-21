#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* target;
    char* swap;
}cypherEntry;

#define READ "r"
#define BUFFSIZE 256

cypherEntry* loadCypher(cypherEntry* cypher, int *cypherEntries){
    int nbytes, bufferSize = BUFFSIZE;
    char* buffer = (char*) malloc(sizeof(char) * bufferSize);
    while(1){
        FILE* f = fopen("cypher.txt", READ);
        nbytes = fread(buffer, sizeof(char), bufferSize, f);
        fclose(f);
        if(nbytes == bufferSize) {
            bufferSize *= 2;
            buffer = (char*)realloc(buffer, sizeof(char) * bufferSize);
        }
        else break;
    }
    for(int i = 0; i < bufferSize; i++)
        if(buffer[i] == '\n')(*cypherEntries)++;
    cypher = (cypherEntry*)malloc(sizeof(cypherEntry)* (*cypherEntries));
    char* swap, *target = strtok(buffer, " ");
    int i=0;
    do{
        swap = strtok(NULL, "\n");
        cypher[i].target = (char*)malloc(sizeof(char)*strlen(target));
        cypher[i].swap = (char*)malloc(sizeof(char)*strlen(swap));
        strcpy(cypher[i].target, target);
        strcpy(cypher[i].swap, swap);
        target=strtok(NULL, " ");
        i++;
    }while(target != NULL);

    return cypher;
}

int main(int argc, char* argv[]){
    cypherEntry* cypher;
    int cypherEntries = 0;

    cypher = loadCypher(cypher, &cypherEntries);

    for(int i = 0; i <cypherEntries;i++)
        printf("%s %s\n", cypher[i].target, cypher[i].swap);


    return 0;
}