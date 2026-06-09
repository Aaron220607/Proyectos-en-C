#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATH 4096
void recorrerDirectorio(const char *ruta){
    DIR *dir;
    struct dirent *objeto;
    struct stat st;
    char rutaCompleta[MAX_PATH];
    if((dir = opendir(ruta))==NULL){
        fprintf(stderr, "Error al abrir el directorio %s\n", ruta);
        return;
    }
    while((objeto = readdir(dir))!=NULL){
        if(strcmp(objeto->d_name, ".")==0 || strcmp(objeto->d_name, "..")==0){
            continue;
        }
        snprintf(rutaCompleta, MAX_PATH, "%s/%s", ruta, objeto->d_name);
        if(stat(rutaCompleta, &st)==-1){
            fprintf(stderr, "Error al obtener información de %s\n", rutaCompleta);
            continue;
        }
        if(S_ISDIR(st.st_mode)){
            recorrerDirectorio(rutaCompleta);

        }else
        {
            long tamanio = st.st_size;
            if(st.st_mode & S_IXUSR){
                printf("Archivo ejecutable: %s (Tamaño: %ld bytes)\n", rutaCompleta, tamanio);
            }else{
                printf("Archivo: %s (Tamaño: %ld bytes)\n", rutaCompleta, tamanio);
            }
            char *extension = strrchr(rutaCompleta, '.');
            if(extension != NULL && strcmp(extension, ".txt") == 0){
            int fd = open(rutaCompleta, O_RDONLY);
            if(fd == -1){
                fprintf(stderr, "Error al abrir el archivo %s\n", rutaCompleta);
                continue;
            }
            char *buffer = malloc(st.st_size + 1);
                if(buffer == NULL){
                    fprintf(stderr, "Error al asignar memoria para el archivo %s\n", rutaCompleta);
                    close(fd);
                    continue;
                }
            int bytesLeidos = read(fd, buffer, st.st_size);
             if (bytesLeidos >= 0) {
                buffer[bytesLeidos] = '\0';
            printf("Contenido del archivo: %s\n", buffer);
            free(buffer);
             }
            close(fd);}
        }
    }   
    closedir(dir);
}
int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr, "Uso: %s <ruta_directorio>\n", argv[0]);
        return EXIT_FAILURE;
    }
    recorrerDirectorio(argv[1]);
    return EXIT_SUCCESS;
}