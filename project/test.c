#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define WORDSIZE 64

char wordBuffer[64];

void flush(char* buffer, int buffersize){
    for(int i = 0; i <buffersize;i++)
        buffer[i]='\0';
}

int hasPunct(int *where){
    for(int i = 0; i < strlen(wordBuffer); i++)
        if(ispunct(wordBuffer[i])){
            *where = i;
            return 0;
        }
    return 1;
}


void cypherWord(char* cypher){
    char* word;
    strcpy(word, wordBuffer);
    flush(wordBuffer, WORDSIZE);
    int where;
    if(!hasPunct(&where)) copyWord(cypher, 0);
    else{
        int j, i = 0;
        if(!where){
            for(j=0;ispunct(word[j]);j++){
             wordBuffer[i] = word[j];
             i++;
            }
        }
        copyWord(cypher, where);
        for(j = where;j < strlen(word);j++){
            if(ispunct(word[j])){
                wordBuffer[i+] = word[j];
                i++;
            }
        }
    }
}


int main(){
    char* test1 = "test";
    char* test2 = ".test";
    char* test3 = "test.";
    char* test4 = ".test.";
    char* cypher = "passed";

    copyWord(test1, 0);
    cypherWord(cypher);

    printf("%s\n", wordBuffer);

    return 0;
}