#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define READ "r"
#define BUFFERSIZE 256
#define PBUFFSIZE 8

char wordBuffer[64];

typedef struct{
    char target[64];
    char swap[64];
}cypherEntry;

typedef struct{
    cypherEntry* table;
    int size;
}cypher;

cypher* loadCypher(cypher* cyphr){
    int nbytes, bufferSize = BUFFERSIZE;
    char* buffer = (char*) malloc(sizeof(char) * bufferSize);
    cyphr->size = 0;
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
        if(buffer[i] == '\n')cyphr->size++;
    cyphr->table = (cypherEntry*)malloc(sizeof(cypherEntry)* cyphr->size);
    char* swap, *target = strtok(buffer, " ");
    int i=0;
    do{
        swap = strtok(NULL, "\n");
        strcpy(cyphr->table[i].target, target);
        strcpy(cyphr->table[i].swap, swap);
        target=strtok(NULL, " ");
        i++;
    }while(target != NULL);

    return cyphr;
}

char* loadText(char* path, char* text){
    int nbytes, bufferSize = BUFFERSIZE;
    char* buff = (char*) malloc(sizeof(char) * bufferSize);
    while(1){
        FILE* f = fopen(path, "read");
        nbytes = fread(buff, sizeof(char), bufferSize, f);
        fclose(f);
        if(nbytes == bufferSize){
            bufferSize *= 2;
            buff = (char*) malloc(sizeof(char) * bufferSize);
        }
        else break;
    }
    text = buff;
    return text;
}

int hasPunct(int *where){
    for(int i = 0; i < strlen(wordBuffer); i++)
        if(ispunct(wordBuffer[i])){
            *where = i;
            return 0;
        }
    return 1;
}

int compareCypher(cypher* cyphr, int* index, int* target){
    for(int i=0;i<cyphr->size;i++){
        if(!strncmp(wordBuffer, cyphr->table[i].target,
                strlen(cyphr->table[i].target))){
            *index = i;
            *target =0;
            return 0;
        }
        if(!strncmp(wordBuffer, cyphr->table[i].swap,
                strlen(cyphr->table[i].swap))){
            *index = i;
            *target = 1;
            return 0;
        }
    }
    return 1;
}

void handlePrefix(cypher* cyphr, int index, int target){
    char lastChar = wordBuffer[strlen(wordBuffer)-1];
    int i=1;
    char* shift;
    if(target) shift = cyphr->table[index].target;
    else shift = cyphr->table[index].swap;
    for(;i<strlen(shift);i++)
        wordBuffer[i]=shift[i];
    wordBuffer[i] = lastChar;
    wordBuffer[i+1]='\0';
}

void handleSuffix(cypher* cyphr, int index, int where, int target){
    char punct[PBUFFSIZE];
    int i = where;
    for(;wordBuffer[i]!='\0';i++){
        punct[i-where]=wordBuffer[i];
    }
    punct[i-where] = '\0';
    char*shift;
    if(target) shift = cyphr->table[index].target;
    else shift = cyphr->table[index].swap;
    int usedBuffer = strlen(wordBuffer);
    for(i=0;i<strlen(shift);i++)
        wordBuffer[i]=shift[i];
    for(int j=0;punct[j]!='\0';j++){
        wordBuffer[i+j]=punct[j];
    }
    wordBuffer[i+strlen(punct)]='\0';
}

void handleNoffix(cypher* cyphr, int index, int target){
    char lastChar = wordBuffer[strlen(wordBuffer)-1];
    int i=0;
    char*shift;
    if(target) shift = cyphr->table[index].target;
    else shift = cyphr->table[index].swap;
    for(;i<strlen(shift);i++)
        wordBuffer[i]=shift[i];
    wordBuffer[i]=lastChar;
    wordBuffer[i+1]='\0';
}

char* cypherText(cypher* cyphr, char* text){
    char* cypheredText;
    strcpy(cypheredText, "\0");
    int lastIndex = 0, foundWord = 0;
    for(int i = 0; i <strlen(text); i++){
        if(text[i] == ' ' || text[i] == '\n'){
            int j=0;
            for(; j<=i-lastIndex;j++)
                wordBuffer[j] = text[lastIndex+j];
            wordBuffer[j]='\0';
            lastIndex=i+1;
            foundWord=1;
        }
        if(foundWord){
            int index, target;
            if(!compareCypher(cyphr, &index, &target)){
                int where;
                if(!hasPunct(&where)){
                    if(!where) handlePrefix(cyphr, index, target);
                    else handleSuffix(cyphr, index, where, target);
                }
                else handleNoffix(cyphr, index, target);
            }
            strcat(cypheredText, wordBuffer);
            foundWord=0;
        }
    }
    text = cypheredText;
    return cypheredText;
}

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "usage: %s filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("Regular:\n");
    char* text, *cypheredText; 
    cypher* cyphr = (cypher*)malloc(sizeof(cypher));
    cyphr = loadCypher(cyphr);
    text = loadText(argv[1], text);
    printf("%s", text);
    cypheredText = cypherText(cyphr, text);
    printf("\nCyphered:\n");
    printf("%s", cypheredText);
    
    return 0;
}