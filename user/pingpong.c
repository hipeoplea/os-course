#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void){
    int pipes[2];
    char buf[5];
    int pid;

    if (pipe(pipes) < 0) {
        printf("pipe creation failed\n");
        exit(1);
    }

    pid = fork();

    if (pid < 0) {
        printf("fork failed\n");
        exit(1);
    }

    if (pid > 0){
        write(pipes[1], "ping", 4);
        wait(0);
        close(pipes[1]);

        read(pipes[0], buf, 4);
        printf("%d: got %s\n", getpid(), buf);

        close(pipes[0]);
    }
    else {
        read(pipes[0], buf, 4);
        printf("%d: got %s\n", getpid(), buf);

        write(pipes[1], "pong", 4);
        close(pipes[1]);

        close(pipes[0]);
    }

    exit(0);
    
}
