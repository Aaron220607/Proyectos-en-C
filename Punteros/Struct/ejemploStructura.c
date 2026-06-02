#include <stdio.h>
#include <string.h>

struct Persona {
    char nombre[50];
    int edad;
    char dni[9];
};

int main(){
struct Persona persona1;
persona1.edad = 30;
strcpy(persona1.nombre, "Juan Perez");
strcpy(persona1.dni, "12345678D");
printf("Nombre: %s\n", persona1.nombre);
printf("Edad: %d\n", persona1.edad);
printf("DNI: %s\n", persona1.dni);
struct Persona *ptr = &persona1;
printf("Nombre: %s\n", ptr->nombre);
ptr->edad = 35;
printf("Edad %d \n",persona1.edad);
printf("Edad que apunta al puntero: %d \n",ptr->edad);
}