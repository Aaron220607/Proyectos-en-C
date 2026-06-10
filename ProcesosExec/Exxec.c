#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if(pid ==-1){
        fprintf(stderr, "Fork failed");
        return 1;

    } else if(pid == 0){
        char *args[] = {"ls","-l",NULL};
        printf("Child process: PID = %d\n", getpid());
        execvp(args[0], args);
        fprintf(stderr, "Exec failed");
        return 1;
    }else{
        wait(NULL);
        printf("Parent process: PID = %d\n", getpid());
    }
}