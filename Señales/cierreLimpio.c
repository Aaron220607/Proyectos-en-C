#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

int activo = 1;  // variable global que controla el bucle

void manejador(int sig){
    printf("\nSeñal recibida, cerrando limpiamente...\n");
    activo = 0;  // para el bucle
}

int main(){
    signal(SIGINT, manejador);

    while(activo){
        printf("Ejecutando...\n");
        sleep(1);
    }

    // aquí harías free(), closedir(), close()...
    printf("Programa terminado correctamente\n");
    return 0;
}