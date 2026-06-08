#include <sys/stat.h>    // Para stat() — obtener info de archivos
#include <unistd.h>      // Llamadas al sistema POSIX (read, write, close...)
#include <dirent.h>      // Para trabajar con directorios (opendir, readdir...)
#include <stdio.h>       // printf, fprintf
#include <stdlib.h>      // EXIT_SUCCESS, EXIT_FAILURE
#include <string.h>      // strcmp, strcpy...
#define PATH_MAX 4096  // Tamaño máximo de una ruta
void RecorrerDir (const char *dir){
DIR *d;
struct dirent *objeto;
struct stat st;
char ruta[PATH_MAX];
if ((d = opendir(dir)) == NULL) {
fprintf(stderr, "Error al abrir el directorio: %s\n", dir);
return;
    }
while((objeto = readdir(d)) != NULL) {
if(strcmp(objeto->d_name, ".") == 0 || strcmp(objeto->d_name, "..") == 0) {
continue; // Ignorar "." y ".."
        }
snprintf(ruta, sizeof(ruta), "%s/%s", dir, objeto->d_name); // Construir la ruta completa
if(stat(ruta, &st) == -1) {
fprintf(stderr, "Error al obtener información de: %s\n", ruta);
continue;
        }
if(S_ISDIR(st.st_mode)) {
RecorrerDir(ruta); // Llamada recursiva para subdirectorios
        } else {
printf("%s\n", ruta); 
    }
    }
closedir(d);
}
int main(int argc, char *argv[]) {
if (argc != 2) {
fprintf(stderr, "Uso: %s <directorio>\n", argv[0]);
return EXIT_FAILURE;
    }
RecorrerDir(argv[1]);
return EXIT_SUCCESS;
}