#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
    pid_t pid = fork();

if(pid == 0){
    printf("Hijo trabajando...\n");
    sleep(2);
    printf("Hijo terminado\n");
} else {
    wait(NULL);  // el padre espera a que el hijo termine
    printf("Padre: el hijo ha terminado, ahora sigo yo\n");
}

    return 0;
}