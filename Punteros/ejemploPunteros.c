
#include <stdio.h>

int main() {
    int a = 5;
    int *prt = &a; // prt es un puntero que apunta a la dirrecion de a
    printf("El valor de a es: %d \n",a);
    printf("El valor donde apunta prt es : %p \n",prt);
    // Imaginemos que cambiambos el valor de a
    // Para ello podemos hacer uso de su puntero
    *prt = 10; // Vamos a cambiar el valor donde esta apuntando actaulmente prt
    printf("El valor de a es: %d \n",a);
     printf("El valor donde apunta prt es : %p \n",prt);
    // Vemos como su valor a cambiado

}