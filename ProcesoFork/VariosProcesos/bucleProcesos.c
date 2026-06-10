#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char *archivos[] = {"archivo1.txt", "archivo2.txt", "archivo3.txt"};
    int num_archivos = sizeof(archivos) / sizeof(archivos[0]);
    for(int i=0;i<num_archivos;i++){
        pid_t pid = fork();
        if(pid == 0){
            printf("Hijo procesando %d: %s\n",getpid(),archivos[i]);
            sleep(2); // Simula el procesamiento del archivo
            printf("Hijo %d ha terminado de procesar %s\n",getpid(),archivos[i]);
            return 0;// Termina el proceso hijo
        }
    }
    for(int i=0;i<num_archivos;i++){
        wait(NULL); // Espera a que cada proceso hijo termine
    }
    printf("Todos los archivos han sido procesados.\n");
    return 0;
    
}