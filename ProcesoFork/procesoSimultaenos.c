#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();

    if(pid == 0){
        printf("Hijo ejecutando...\n");
        sleep(1);
        return 42;  // el hijo sale con código 42
    } else {
        int status;
        wait(&status);  // recoge el estado de salida

        if(WIFEXITED(status)){
            printf("Hijo terminó con código: %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}