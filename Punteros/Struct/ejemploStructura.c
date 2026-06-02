#include <stdio.h>
#include <string.h> // librería para usar strcpy Strings

struct Persona { //Creamos una estructura llamada Persona (como si fuera una clase de POO)
    char nombre[50]; 
    int edad;
    char dni[9];
};

int main(){
struct Persona persona1; // Creamos una instancia de la estructura Persona llamada persona1
persona1.edad = 30; // Definimos los atributos de la estructura persona1
strcpy(persona1.nombre, "Juan Perez"); // Usamos la función strcpy para copiar el string "Juan Perez" en el atributo nombre de la estructura persona1
strcpy(persona1.dni, "12345678D");
printf("Nombre: %s\n", persona1.nombre);
printf("Edad: %d\n", persona1.edad);
printf("DNI: %s\n", persona1.dni);
struct Persona *ptr = &persona1; // Creamos un puntero a la estructura Persona llamado ptr y lo inicializamos con la dirección de memoria de persona1
printf("Nombre: %s\n", ptr->nombre); // Usamos el operador -> para acceder a los atributos de la estructura a través del puntero ptr
ptr->edad = 35; // Modificamos el valor del atributo edad de la estructura persona1 a través del puntero ptr usando el operador ->
// Imprimimos el valor del atributo edad de la estructura persona1 y del puntero ptr para verificar que se ha modificado correctamente
printf("Edad %d \n",persona1.edad);
printf("Edad que apunta al puntero: %d \n",ptr->edad);
}