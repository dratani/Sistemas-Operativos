#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#define MAX 256

int tuberia_emisor_receptor[2];
//int tuberia_receptor_emisor[2];
int pid;
char mensaje[MAX];

int main(int argc, char const *argv[]) {
  //Creación de tuberías
  if (pipe (tuberia_emisor_receptor)==-1){
    perror ("pipe");
    exit (-1);
  }
  //Creación de proceso hijo
  if ((pid=fork())==-1){
    perror ("fork");
    exit (-1);
  } else if (pid==0){ /*Código del proceso hijo*/
    /*El proceso hijo (receptor) se encarga de leer un mensaje de la tubería
    y presentarlo en la pantalla. Al recibir el mensaje "FIN\n" termina el proceso"*/
    while (read(tuberia_emisor_receptor[0],mensaje,MAX) > 0 &&
           strcmp (mensaje,"FIN\n")!=0){
      printf("Proceso receptor. MENSAJE:%s\n",mensaje);
      /*Aquí se debe implementar el envío de mensaje "LISTO" al proceso receptor (usando la segunda tubería)
       para indicar que el proceso está listo para recibir otro mensaje*/
    }
    close (tuberia_emisor_receptor[0]);
    close (tuberia_emisor_receptor[1]);
    exit (0);
  }else { /*Código del proceso padre*/
    /*El proceso padre (emisor) se encarga de leer un mensaje de la entrada estándar (teclado)
    y acto seguido escribirlo la tubería, para que lo reciba el proceso hijo. Al escribir el MENSAJE
    "FIN\n" acaban los dos procesos.*/
    while (printf("Proceso emisor. Introduce el mensaje:\n")!=0 &&
           fgets (mensaje,sizeof (mensaje),stdin)!=NULL &&
          write(tuberia_emisor_receptor[1],mensaje,strlen(mensaje)+1)>0 &&
          strcmp(mensaje,"FIN\n")!=0);
    close (tuberia_emisor_receptor[1]);
    close (tuberia_emisor_receptor[0]);
    wait(NULL);
    exit (0);
  }
}
