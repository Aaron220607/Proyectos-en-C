#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#define PATH_MAX 4096
int activoHijo = 1;
int activoPadre = 1;
void manjeador(int sig){
    char *mensaje = "Saliendo del proceso \n";
    write(STDOUT_FILENO,mensaje,strlen(mensaje));
    activoHijo = 0;
    
}
void manejadorPadre(int sig){
    char *mensajePadre = "Terminando el proceso\n";
    write(STDOUT_FILENO,mensajePadre,strlen(mensajePadre));
    activoPadre = 0;
}
void buscarDir(const char* ruta,const char * archivo,int fdEscritura){
    DIR *d;
    struct stat st;
    struct dirent *item;
    int encontrado = 0;
    signal(SIGINT,SIG_IGN);
      signal(SIGTERM, manjeador);
    while(activoHijo){
        encontrado = 0;
        if((d=opendir(ruta))==NULL){
            char *errorDirectorio = "Error al Directorio";
            write(STDOUT_FILENO,errorDirectorio,strlen(errorDirectorio));
            return;
        }
        while((item=readdir(d))!= NULL){
             if(strcmp(item->d_name,".")==0 || strcmp(item->d_name,"..")==0){
                continue;
             }
            if(strcmp(item->d_name,archivo)==0){
                encontrado = 1;
                break;
            }
        }
        closedir(d);
        if (encontrado) {
            const char *alerta = " ALERTA: ¡Archivo config.txt detectado!\n";
            write(STDOUT_FILENO, alerta, strlen(alerta));
            write(fdEscritura,"1",1);
        } else {
            const char *limpio = "Escaneando... Carpeta limpia.\n";
            write(STDOUT_FILENO, limpio, strlen(limpio));
        }

        // Dormir 3 segundos, pero protegiendo el bucle si nos despierta una señal
        // sleep() se interrumpe si llega SIGTERM, lo cual es perfecto para salir rápido
        sleep(3); 
    }
    const char *hijo_fin = "Hijo: Buscador finalizado limpiamente.\n";
    write(STDOUT_FILENO, hijo_fin, strlen(hijo_fin));
    exit(0);
}
int main(int argc, char *argv[]){
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <ruta_a_vigilar> <nombre_archivo>\n", argv[0]);
        return 1;
    }
    
    int fd[2];
    if(pipe(fd) != 0){
        fprintf(stderr, "Error al crear la tuberia\n");
        return 1;
    }
    fcntl(fd[0], F_SETFL, O_NONBLOCK);

    printf("Padre: Iniciando sistema de vigilancia sobre %s...\n", argv[1]);
    
    // Registramos la señal en el padre antes del fork para evitar condiciones de carrera
    signal(SIGINT, manejadorPadre);

    pid_t pid = fork();
    if(pid == -1){
        perror("Error en fork");
        return 1;
    }
    
    if(pid == 0){
        // El hijo no lee de la tubería, cierra su descriptor de lectura
        close(fd[0]);
        buscarDir(argv[1], argv[2], fd[1]);
        close(fd[1]);
        exit(0);
    }
    
    // El padre no escribe en la tubería, cierra su descriptor de escritura
    close(fd[1]);

    while(activoPadre){
        char buf[1];
        // Al ser O_NONBLOCK, si no hay datos, read() devuelve -1 inmediatamente 
        // en lugar de bloquear el proceso.
        int bytes = read(fd[0], buf, 1);

        if(bytes > 0){
            printf("Padre: ¡Alerta recibida desde el pipe! Archivo encontrado. Cerrando...\n");
            break; // Salimos del bucle para ir a la fase de apagado
        }

        // Comprobamos si el hijo ha muerto por su cuenta (ej: error en opendir)
        pid_t resul = waitpid(pid, NULL, WNOHANG);
        if(resul == pid){
            printf("Padre: El hijo ha terminado de forma imprevista. Cerrando supervisor.\n");
            break;
        }

        sleep(1);
    }

    // Fase de apagado limpio y recolección
    printf("Padre: Desactivando servicios y limpiando procesos...\n");
    kill(pid, SIGTERM);
    waitpid(pid, NULL, 0); // Esperamos de verdad a que el hijo termine su manejador
    
    close(fd[0]); // Cerramos el pipe al terminar
    printf("Padre: Sistema cerrado con éxito.\n");
    return 0;
}