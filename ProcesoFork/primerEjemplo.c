#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
    int x = 5;

    pid_t pid = fork();

    if(pid == 0){
        x = 99;  // el hijo cambia x
        printf("Hijo: x = %d\n", x);
    } else {
        sleep(1);  // espera un momento para que el hijo ejecute primero
        printf("Padre: x = %d\n", x);  // ¿cuánto vale x aquí?
    }

    return 0;
}