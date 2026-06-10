#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    pid_t cpid;
    char buf;

    if (pipe(pipefd) == -1) {
        fprintf(stderr, "Pipe failed\n");
        return (1);
    }

    pid_t hijo1= fork();
    if (hijo1 == -1) {
        fprintf(stderr, "Fork failed\n");
        return (1);
    }
    if (hijo1 == 0) {    // Hijo 1
        close(pipefd[0]);          // Cierra el extremo de lectura
        dup2(pipefd[1],1);
        close(pipefd[1]);          // Cierra el extremo de escritura
        char *args[] = {"ls", "-l", argv[1], NULL};
        execvp(args[0], args);
        fprintf(stderr, "Exec failed\n");
        return (1);
    }
    pid_t hijo2 = fork();
    if (hijo2 == -1) {
        fprintf(stderr, "Fork failed\n");
        return (1);
    }
    if (hijo2 == 0) {    // Hijo 2
        close(pipefd[1]);          // Cierra el extremo de escritura
        dup2(pipefd[0],0);
        close(pipefd[0]);          // Cierra el extremo de lectura
        char *args[] = {"grep", ".txt", NULL};
        execvp(args[0], args);
        fprintf(stderr, "Exec failed\n");
        return (1);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);                // Espera a que el hijo 1 termine
    wait(NULL);                // Espera a que el hijo 2 termine
    return (0);

}