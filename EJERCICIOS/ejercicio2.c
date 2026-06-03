//Pide al usuario cuántos números quiere meter. 
//Reserva memoria dinámica para guardarlos, pídeselos uno a uno, y al final muestra el mayor de todos.
//Acuérdate de liberar la memoria al final
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main() {
    int cantidad;
    printf("indique el numero de dijitos a ingresar:");
    scanf("%d", &cantidad);
    int *numeros = malloc(cantidad*sizeof(int));
    if (numeros == NULL) {
        printf("Error al reservar memoria\n");
        return 1;
    }
    int mayor = INT_MIN;
    for (int i = 0;i < cantidad; i++) {
        printf("Ingrese el numero %d: ", i+1);
        scanf("%d", &numeros[i]);
        if (numeros[i] > mayor) {
            mayor = numeros[i];
        }
    }
    printf("El mayor es: %d\n", mayor);
    free(numeros);
    numeros = NULL;
    return 0;
}