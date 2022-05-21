#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_STR_SIZE     64  

int lowercase(char* s){
    char* ret = (char*)malloc(MAX_STR_SIZE * sizeof(char));
    
    for(int i = 0; s[i] != '\0'; i++){
        ret[i] = tolower(s[i]);
    }
    printf("%s\n", ret);
    
    free(ret);

    return 0;
}

char* extract_substr(char* s1, int start, int len){
    char* ret = (char*)malloc(len * sizeof(char));

    for(int i = 0; i < len; i++){
        ret[i] = s1[start + i];
    }

    return ret;
}

int count_substr(char* s1, char*s2){
    int size2 = strlen(s2),
        size1 = strlen(s1),
        ret = 0;
    for(int i = 0; i + size1 <= size2; i++){
        if(*extract_substr(s2, i, size1) == *s1)
            ret++;
    }

    return ret;
}

int main(int argc, char* argv[]){
    if(argv[3] != NULL || argv[1] == NULL){
        if(argv[1] == NULL) printf("function requires arguments\n");
        else printf("too many arguments\n");
        printf("use either [./t3e1 \"s1\"] or [./t3e1 \"s1\" \"s2\"]\n");
    }
    else if(argv[2] == NULL){
        if(strlen(argv[1]) > MAX_STR_SIZE){
            printf("maximum limit of 64 characters exceeded\n");
            return 1;
        }    
        else if(lowercase(argv[1])) return 1;    
    }
    else{
        if(strstr(argv[2], argv[1]) != NULL){
            printf("%s occurs in %s %u times\n", argv[1], argv[2], 
                                        count_substr(argv[1], argv[2]));
        }
        else{
            printf("%s does not occur in %s", argv[1], argv[2]);
        }
    }


    return 0;
}

