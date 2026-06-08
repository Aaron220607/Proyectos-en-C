#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h> 

int main() {
    int fd = open("archivo.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        fprintf(stderr, "Error al abrir el archivo \n"); // Corregido a fprintf
        return 1;
    }

    char buffer[1024]; // Única declaración de buffer
    printf("Ingrese el texto a escribir en el archivo: ");
    scanf("%1023s", buffer); 

    write(fd, buffer, strlen(buffer));
    close(fd);

    // Leer el contenido del archivo
    fd = open("archivo.txt", O_RDONLY);
    if(fd == -1){
        fprintf(stderr, "Error al abrir el archivo \n"); // Corregido a fprintf
        return 1;
    }

    char lectura[1024];
    int bytes_leidos = read(fd, lectura, sizeof(lectura) - 1);
    if (bytes_leidos >= 0) {
        lectura[bytes_leidos] = '\0';
        printf("Contenido del archivo: %s\n", lectura);
    }
    
    close(fd);
    return 0;
}