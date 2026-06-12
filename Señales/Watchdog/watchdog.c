#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
bool activo = true;
void manejador (int sig){
    printf("Terminando el proceso: %d\n",getpid());
    activo = false;
}
void ejecutarHijo(){
    signal(SIGTERM, manejador);
    signal(SIGINT, SIG_IGN);
    while(activo){
        printf("Hijo %d trabajando...\n", getpid());
        sleep(1);
    }
    exit(0);
}
pid_t lanzarHijo(){
    pid_t pid = fork();
    if(pid == -1){
        fprintf(stderr, "Error en fork\n");
        exit(1);
    }
    if(pid == 0){
        ejecutarHijo();  // el hijo nunca vuelve de aquí
    }
    return pid;  // el padre recibe el PID del hijo
}
int main(){
    signal(SIGINT, manejador);  // una sola vez al principio
    pid_t pid = lanzarHijo();

    while(activo){
        pid_t resultado = waitpid(pid,NULL, WNOHANG);
        if(resultado == pid){
            printf("Hijo muerto, reiniciando...\n");
            pid = lanzarHijo();
        }
        sleep(1);
    }

    kill(pid, SIGTERM);
    wait(NULL);
    printf("Watchdog terminado\n");
    return 0;
}
