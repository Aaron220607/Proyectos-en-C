#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void manejador(int sig){
    printf("Se ha recibido la señal %d -Ctrl-c ignorada\n", sig);
}
int main(){
    printf("Presiona Ctrl-C para enviar la señal SIGINT\n");
    signal(SIGINT,manejador);
    while(1){
        printf("Ejecuntando...");
        sleep(2);
    }
    return 0;
}