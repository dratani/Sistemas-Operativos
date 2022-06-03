#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

#define SEM_HIJO 0
#define SEM_PADRE 1

int main(int argc, char const *argv[]) {
  int i=10, semid, pid;
  struct sembuf operacion;
  key_t llave;

  /*Petición de un identificador con dos semáforos*/
  llave = ftok (argv[0], 'K');
  if ((semid =semget (llave, 2, IPC_CREAT | 0600)) == -1){
    perror ("semget");
    exit (-1);
  }

  /*Inicialización de dos semáforos*/

  /*Cerramos el semáforo del proceso hijo*/
  semctl (semid, SEM_HIJO,SETVAL,0);

  /*Abrimos el semáforo del proceso padre*/
  semctl (semid,SEM_PADRE,SETVAL,1);

  /*Creación del proceso hijo*/
  if ((pid=fork()) == -1){
    perror ("fork");
    exit (-1);
  } else if (pid ==0){ //Código del proceso hijo
    while (i) {
      /* Cerramos el semáforo del proceso hijo */
      operacion.sem_num = SEM_HIJO;
      operacion.sem_op = -1; //Operación P
      operacion.sem_flg = 0;
      semop (semid, &operacion, 1);
      printf("Proceso hijo: %d\n", i--);

      /*Abrimos semáforo del proceso padre*/
      operacion.sem_num =SEM_PADRE;
      operacion.sem_op =1;
      semop (semid, &operacion,1);
    }
    /*Borrado del semáforo*/
    semctl (semid,0, IPC_RMID,0);
  }else { /*Código del proceso padre*/
    operacion.sem_flg =0;
    while (i) {
      /* cerramos el semáforo del proceso padre */
      operacion.sem_num =SEM_PADRE;
      operacion.sem_op = -1;
      semop (semid, &operacion, 1);
      printf("Proceso Padre: %d\n", i--);
      /* Abrimos el semáforo del proceso hijo */
      operacion.sem_num = SEM_HIJO;
      operacion.sem_op = 1; //Operación v
      semop (semid, &operacion, 1);
    }
    /*Borramos el semáforo*/
    semctl (semid,0,IPC_RMID,0);
  }
  return 0;
}
