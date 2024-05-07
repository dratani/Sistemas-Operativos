#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int semid;

void operacionP(int i){
  struct sembuf operacion;
  operacion.sem_num = i;
  operacion.sem_op = -1; //Operación P
  operacion.sem_flg = 0;
  printf("El proceso %d intenta acceder a la zona crítica\n",i);
  semop (semid, &operacion, 1);
}
void operacionV(int i){
  struct sembuf operacion;
  printf("El proceso %d abre el sem %d\n",i-1,i);
  operacion.sem_num =i;
  operacion.sem_op =1;
  operacion.sem_flg = 0;
  semop (semid, &operacion,1);
}
void esperaHijo(int i){
  int wstatus;
    printf("Esperando al hijo %d \n",i);
    waitpid(i,&wstatus,0);
}
int main(int argc, char const *argv[]) {
  int i,j;
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
  semctl (semid,SETALL,0);
  semctl (semid,0,SETVAL,1);

  operacionP(0);
  printf("Soy el proceso 0 pid=%d \n",getpid());
  /*Abrimos semáforo del proceso 1*/
  operacionV(1);
  /*Creación de 4 procesos*/
  for (int i = 1; i <nprocesos; i++) {
    printf("**********************************************i:%d\n",i );
    if ((pid[i]=fork())==-1){
      perror ("fork");
      exit (-1);
    } else if(pid[i]==0){
      operacionP(i);
      printf("Soy el proceso %d pid=%d \n",i,getpid());
      /*Abrimos semáforo del proceso siguiente verificando que no sea el último proceso*/
      if (i != nprocesos-1)
        operacionV(i+1);

      printf("Fin del proceso %d\n",i );
      exit(1);
    }else{ //proceso padre
        esperaHijo(pid[i]);
      }
    }
    for (int i=0; i <nprocesos;i++) {
      semctl (semid,i, IPC_RMID,0);
    }
    exit(1);
}
