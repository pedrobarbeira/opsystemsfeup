#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
    struct stat info;
    if(argc < 2){
        fprintf(stderr, "usage: %s file1, file2, ..., fileN\n", argv[0]);
        return EXIT_FAILURE;
    }
    for(int i = 1; i < argc; i++){
        if(lstat(argv[i], &info) == -1){
            fprintf(stderr, "fsize: Can't state %s\n", argv[i]);
            return EXIT_FAILURE;
        }
        printf("%s size: %d byles, disk_blocks: %d, user id: %d, last modification: %li\n", 
                argv[i], (int)info.st_size, (int)info.st_blocks, (int)info.st_uid, info.st_mtim.tv_nsec);
    }
    return EXIT_SUCCESS;
}