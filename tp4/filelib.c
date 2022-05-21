#include "filelib.h"

char* getpath(){
        int flag = 1, BUFFER_SIZE = 256;
    char* buffer;
    
    do{
        buffer = malloc(sizeof(char) * BUFFER_SIZE);
        if(getcwd(buffer, BUFFER_SIZE) == NULL) 
            BUFFER_SIZE *= 2;
        else flag = 0;
    }while(flag);
    
    return buffer;
}