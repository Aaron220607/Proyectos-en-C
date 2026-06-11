#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void manejador (int sing){
    printf("Terminando el proceso %d debido a la señal SIGTERM \n",getpid());
    exit(1);
}

int main(){
    pid_t pid =  fork();
    if(pid == -1){
        fprintf(stderr,"Error al hacer el fork");
    }
    if(pid==0){
        signal(SIGTERM,manejador);
        while(1){
            printf("Ejecuntando el proceso... \n");
            sleep(1);
        }
    } else{
        sleep(3);
        printf("Mandando señal SIGTERM a hijo %d\n",pid);
        kill(pid,SIGTERM);
        wait(NULL);
        printf("Proceso acabado del hijo \n");
    }
    return 0;
}