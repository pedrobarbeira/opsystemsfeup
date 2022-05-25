#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/**
 * @brief Sees if a string has punctuation in it
 * 
 * @param where the index where the punctuation starts
 * @return int 0 if there is punctuation, 1 otherwise
 */
int hasPunct(int *where){
    for(int i = 0; i < strlen(wordBuffer); i++)
        if(ispunct(wordBuffer[i])){
            *where = i;
            return 0;
        }
    return 1;
}

/**
 * @brief Cyphers words when there's punctuation at the start of the string
 * 
 * @param cyphr the cypher table
 * @param index index of the cypher table to be accessed
 * @param target if 0 swaps target for swap, if 1 swaps swap for target
 */
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

/**
 * @brief Cyphers words when there's punctuation at the end of the string
 * 
 * @param cyphr the cypher table
 * @param index the index of the cypher table to be accessed
 * @param where index of the string where punctuation starts
 * @param target if 0 swaps target for swap, if 1 swaps swap for target
 */
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

/**
 * @brief Cyphers words when there is no punctuation involved
 * 
 * @param cyphr the cypher table
 * @param index the index of the cypher table
 * @param target if 0 swaps target for swap, if 1 swaps swap for target
 */
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

int cmpwrd(char* w1, char* w2){
    int where;
    if(strlen(w1) == strlen(w2) || strlen(w1) < strlen(w2)) return (!strcmp(w1, w2));
    
    else{
        int i = 0, size;
        if(strlen(w1) < strlen(w2)) size = strlen(w1);
        else size = strlen(w2);
        while(i < size){
            printf("%c %c\n", w1[i], w2[0]);
            if(w1[i] == w2[0]) break;
            else i++;
        }
        printf("%d\n", i);
        if(i == size) return 0;
        else{
            for(int j = 0; j < size; j++){
                printf("%c %c\n", w1[i+j], w2[j]);
                if(w1[i+j] != w2[j]) {
                    return 0;
                }
            }
        }
        return 1; 
    }
}

int main(){
    char* test1 = "test";
    char* test2 = ".test";
    char* test3 = "test.";
    char* test4 = ".test.";
    char* cypher = "passed";

    printf("%lu\n",strlen("1234 "));

    return 0;
}