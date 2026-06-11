// Usaremos la funcion de recorrer directorios
// buscaremos arhcivos .txt y ejecutaremos el comando wc -l para contar las lineas de cada archivo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_PATH 4096
struct resumen{
    int numeroArchivos;
};

void recorrerDirectorio(const char *ruta,const char *archivo,struct resumen *r){
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char path[MAX_PATH];
    if((dir=opendir(ruta))==NULL){
        fprintf(stderr,"Error al abrir el directorio %s\n",ruta);
        return;
    }
    while((entry=readdir(dir))!=NULL){
        char *extension = strrchr(entry->d_name,'.');
        if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0){
            continue;
        }
        snprintf(path,sizeof(path),"%s/%s",ruta,entry->d_name);
        if(stat(path,&st)==-1){
            fprintf(stderr,"Error al obtener informacion del archivo %s\n",path);
            continue;
        }
        if(S_ISDIR(st.st_mode)){
            recorrerDirectorio(path,archivo,r);
        }else if(extension != NULL && strcmp(extension,archivo)==0){
            r->numeroArchivos++;
            pid_t pid = fork();
            if(pid == -1){
                fprintf(stderr,"Error al crear el proceso hijo\n");
                continue;
            }else if(pid == 0){
                char *args[]={"wc","-l",path,NULL};
                execvp(args[0],args);
                fprintf(stderr,"Error al ejecutar el comando wc\n");
                exit(1);
            
                
            }
        }
    
    }  
    closedir(dir);


}
int main(int argc,char *argv[]){
    if(argc != 3){
        fprintf(stderr,"Uso: %s <ruta_directorio> <extension_archivo>\n",argv[0]);
        return 1;
    }
    struct resumen r;
    r.numeroArchivos=0;
    recorrerDirectorio(argv[1],argv[2],&r);
    for(int i = 0; i < r.numeroArchivos; i++){
    wait(NULL);
    }
    printf("Numero de archivos con extension %s: %d\n",argv[2],r.numeroArchivos);
    return 0;
}