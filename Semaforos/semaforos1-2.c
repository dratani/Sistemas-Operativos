#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#define SEM_1 0
#define SEM_2 1
#define SEM_3 2
#define SEM_4 3

int main(int argc, char const *argv[]) {
  int i=10, semid;
  int pid[3];
  struct sembuf operacion;
  key_t llave;

  /*Petición de un identificador con dos semáforos*/
  llave = ftok (argv[0], 'k');
  if ((semid =semget (llave, 4, IPC_CREAT | 0600)) == -1){
    perror ("semget");
    exit (-1);
  }

  /*Inicialización de los semáforos en cero, nadie puede acceder*/
  semctl (semid,SEM_1,SETVAL,1);
  for (size_t i = 1; i < 4; i++) {
    semctl (semid,i,SETVAL,0);
  }
  /*Creación de 4 procesos*/
  switch(pid[0]=fork())
 {
   case -1 :
     perror("Error en creación del segundo proceso");
     exit(2);

   case 0  : /* Segundo proceso */
     /*MECANISMO DE EXCLUSIÖN MUTUA*/
     operacion.sem_num = SEM_2;
     operacion.sem_op = -1; //Operación P
     operacion.sem_flg = 0;
     printf("El proceso 2 intenta acceder a la zona crítica\n");
     semop (semid, &operacion, 1);
     printf("Soy el proceso 2\n");
  //   sleep(3);
     /*Abrimos semáforo del proceso siguiente*/
     printf("El proceso 2 abre el sem 3\n");
     operacion.sem_num =SEM_3;
     operacion.sem_op =1;
     operacion.sem_flg = 0;
     semop (semid, &operacion,1);
     exit(1);

   default : /* Primer proceso */
     switch(pid[1]=fork())
     {
       case -1 :
         perror("Error en creación del tercer proceso");
         exit(3);

       case 0  : /* Tercer proceso */
          /*MECANISMO DE EXCLUSIÖN MUTUA*/
          operacion.sem_num = SEM_3;
          operacion.sem_op = -1; //Operación P
          operacion.sem_flg = 0;
          printf("El proceso 3 intenta acceder a la zona crítica\n");
          semop (semid, &operacion, 1);
          printf("Soy el proceso 3 \n");
    //      sleep(3);
          /*Abrimos semáforo del proceso siguiente*/
          printf("El proceso 3 abre el sem 4\n");
          operacion.sem_num =SEM_4;
          operacion.sem_op =1;
          operacion.sem_flg = 0;
          semop (semid, &operacion,1);
          exit(1);
       default : /* Primer proceso */
         switch(pid[2]=fork())
         {
           case -1 :
             perror("Error en creación del cuarto proceso");
             exit(4);

           case 0  : /* Cuarto proceso */
             /*MECANISMO DE EXCLUSIÖN MUTUA*/
             operacion.sem_num = SEM_4;
             operacion.sem_op = -1; //Operación P
             operacion.sem_flg = 0;
             printf("El proceso 4 intenta acceder a la zona crítica\n");
             semop (semid, &operacion, 1);
             printf("Soy el proceso 4 \n");
  //           sleep(3);
             /*Abrimos semáforo del proceso 1*/
             printf("El proceso 4 abre el sem 1\n");
             operacion.sem_num =SEM_1;
             operacion.sem_op =1;
             operacion.sem_flg = 0;
             semop (semid, &operacion,1);
             exit(1);

           default : /* Primer proceso */
              /*MECANISMO DE EXCLUSIÖN MUTUA*/
              operacion.sem_num = SEM_1;
              operacion.sem_op = -1; //Operación P
              operacion.sem_flg = 0;
              printf("El proceso 1 intenta acceder a la zona crítica\n");
              semop (semid, &operacion, 1);
              printf("Soy el proceso 1\n");
              /*Abrimos semáforo del proceso siguiente*/
              printf("El proceso 1 abre el sem 2\n");
              operacion.sem_num =SEM_2;
              operacion.sem_op =1;//Operación V
              operacion.sem_flg = 0;
              semop (semid, &operacion,1);
         }
     }
  }
  for (size_t i = 0; i < 4; i++) {
    /* Eliminar semáforos */
    semctl (semid,i, IPC_RMID,0);
  }
  exit(1);
}
