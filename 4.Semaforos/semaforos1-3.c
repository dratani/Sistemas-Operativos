#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>

struct sembuf operacion;
int semid;

int operacionP(int i){
  operacion.sem_num = i;
  operacion.sem_op = -1; //Operación P
  operacion.sem_flg = 0;
  printf("El proceso %d intenta acceder a la zona crítica\n",i);
  semop (semid, &operacion, 1);
}
int operacionV(int i){
  printf("El proceso %d abre el sem %d\n",i,i-1);
  operacion.sem_num =i;
  operacion.sem_op =1;
  operacion.sem_flg = 0;
  semop (semid, &operacion,1);
}

int procesos (int n){
  int pid[n];
  if (n == 0) return 0;
  else if (pid[n]=fork()==0){
    operacionP(n);
    printf("soy el proceso%d\n",n);
    operacionV(n-1);
    exit(1);
  } else if (n>1) return procesos(n-1);
}



int main(int argc, char const *argv[]) {
  int i=10, semid;

  struct sembuf operacion;
  key_t llave;
  int nprocesos =atoi(argv[1]);
  int pid[nprocesos];
  /*Petición de un identificador con dos semáforos*/
  llave = ftok (argv[0], 'k');
  if ((semid =semget (llave, nprocesos, IPC_CREAT | 0600)) == -1){
    perror ("semget");
    exit (-1);
  }

  /*Inicialización de los semáforos en cero, nadie puede acceder*/
  semctl (semid,SETALL,-1);
//  semctl (semid,0,SETVAL,0);
  procesos(nprocesos);
  /*Creación de 4 procesos*/

      for (int i=0; i <nprocesos;i++) {
        semctl (semid,i, IPC_RMID,0);
      }

      exit(1);

}
