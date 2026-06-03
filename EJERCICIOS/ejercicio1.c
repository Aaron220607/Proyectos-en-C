// En este primer ejercicio, crea un struct Coche con campos marca (texto), modelo (texto) y anio (entero). 
// Crea un coche, rellénalo, y modifica el año usando un puntero

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Coche {
    char *marca;
    char *modelo;
    int anio;
};

int main() {
    struct Coche miCoche;
    struct Coche *prt = &miCoche;
    char  marca [99];
    printf("Ingrese la marca del coche: ");
    scanf("%99s", marca);
   char *nuevaMarca= malloc((strlen(marca)+1)*sizeof(char));
    strcpy(nuevaMarca, marca);
    prt->marca = nuevaMarca;
    char modelo [99];
    printf("Ingrese el modelo del coche: ");
    scanf("%99s", modelo);
    char *nuevoModelo = malloc((strlen(modelo)+1)*sizeof(char));
    strcpy(nuevoModelo, modelo);
    prt->modelo = nuevoModelo;
    printf("Ingrese el año del coche: ");
    scanf("%d", &prt->anio);
    printf("Coche creado: %s %s %d\n", prt->marca, prt->modelo, prt->anio);
    free(prt->marca);
    free(prt->modelo);

}