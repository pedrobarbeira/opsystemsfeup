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
#define FILE        2

#define LINESIZE    256

int next_block_size(int count, int buffer_size){
    return (count >= buffer_size)? buffer_size : count % buffer_size;
}

int main(int argc, char* argv[]){
    int nbytes, fd[3];
    pid_t pid;
    char line[LINESIZE];

    if(argc != 2){
        fprintf(stderr, "Not enough arguments\nUsage: f7e1 <filename.extension>\n");
        exit(EXIT_FAILURE);
    }

    if(pipe(fd) < 0){
        perror("pipe error");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0){
        perror("fork error");
        exit(EXIT_FAILURE);
    } else if(pid > 0){
        /*parent*/
        close(fd[READ_END]);
        printf("Parent process with pid %d\n", getpid());
        printf("Messaging the child process (pid %d):\n", pid);

        struct stat info;

        fd[FILE] = open(argv[1], O_RDONLY);
        if(fd[FILE] == -1){
            printf("Error: cannot open %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        int ret = lstat(argv[1], &info);

        if(ret == -1){
            printf("Error: cannot stat %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }

        int count = info.st_size;

        while(count != 0){
            int bytesin = read(fd[FILE], line, next_block_size(count, LINESIZE));
            count -= bytesin;
            if((nbytes = write(fd[WRITE_END], line, strlen(line)))<0){
                fprintf(stderr, "Unable to write to pipe %s\n", strerror(errno));
            }        
        }

    
        close(fd[WRITE_END]);
        /*wait for child and exit*/
        if(waitpid(pid, NULL, 0)< 0){
            fprintf(stderr, "Cannot wait for child: %s\n", strerror(errno));
        }
        exit(EXIT_SUCCESS);
    }else{
        /*child*/
        close(fd[WRITE_END]);
        printf("Child process with pid %d\n", getpid());
        printf("Receiving message from parent (pid %d):\n", getpid());
        if((nbytes = read(fd[READ_END], line, LINESIZE))< 0){
            fprintf(stderr, "Unable to read from pipe: %s\n", strerror(errno));
        }
        close(fd[READ_END]);
        /*write message from parent*/
        write(STDOUT_FILENO, line, nbytes);
        /*exit gracefully*/
        exit(EXIT_SUCCESS);
    }

}