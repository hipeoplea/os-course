#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void){
    int pipe1[2], pipe2[2];
    char buf[5];
    int pid;

    if (pipe(pipe1) < 0 || pipe(pipe2) < 0) {
        printf("pipe creation failed\n");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        printf("fork failed\n");
        exit(1);
    }

    if (pid > 0){
        close(pipe1[0]); 
        write(pipe1[1], "ping", 4);
        close(pipe1[1]);

        close(pipe2[1]);
        read(pipe2[0], buf, 4);
        printf("%d: got %s\n", getpid(), buf);

        close(pipe2[0]);
        wait(0);
    }
    else {
        close(pipe1[1]);
        read(pipe1[0], buf, 4);
        printf("%d: got %s\n", getpid(), buf);

        close(pipe1[0]);
        close(pipe2[0]);
        write(pipe2[1], "pong", 4);
        close(pipe2[1]);
    }

    exit(0);
    
}
