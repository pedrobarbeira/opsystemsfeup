#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFERSIZE 256;

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

int hasPunct(char* word, int *where){
    for(int i = 0; i < strlen(word); i++)
        if(ispunct(word[i])){
            *where = i;
            return 0;
        }
    return 1;
}

char string[256] = "testsubject\0";

char* handlePrefix(char* word){
    char punct;
    punct= word[0];
    word = strcpy(word, string);
    //realloc(word, sizeof(char)*(strlen(word)+1));
    for(int i = strlen(word); i > 0 ; i--){
        word[i] = word[i-1];
    }
    word[0] = punct;
    word[strlen(string)+1] = '\0';
    printf("%s----", word);
    return NULL;
}

char* handleSuffix(char* word, int where){
    char punct[4];
    for(int i = where; word[i] != '\0'; i++){
        punct[i-where] = word[i];
    }
    strcat(word, punct);
    strcat(word, "\0");
    return word;
}

int main(){
    char* text;
    text = loadText("text.txt", text);
    printf("%s\n\n", text);
    char* word = strtok(text, " ");
    int where;
    do{
        if(!hasPunct(word, &where)){
            if(where == 0){
                char out[256];
                out[0] = word[0];
                for(int i = 0; i < strlen(string); i++)
                    out[i+1] = string[i];
                printf("%s ", out);
            }
            else {
                char out [256];
                for(int i = 0; i < strlen(string); i++)
                    out[i] = string[i];
                for(int i = where; i < strlen(string); i++)
                    out[strlen(string) + (i-where)] = word[i];
                printf("%s ", out);
            }
        }
        else printf("%s ", word);
        word = strtok(NULL, " ");
    }while(word != NULL);

    return 0;
}