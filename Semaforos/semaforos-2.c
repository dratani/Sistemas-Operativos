/* ::::::::Esto tiene que ir antes de los ficheros de cabecera::::::::: */
#ifndef _HPUX_SOURCE
  #define _HPUX_SOURCE
#endif

#include <stdio.h>    /* printf()... */
#include <signal.h>   /* sigaction()... */
#include <unistd.h>   /* system(), fork(),... */
#include <sys/sem.h>  /* semctl(), semop(),... */
#include <sys/wait.h> /* wait() */

/* ::::::::Macros, contantes::::::::: */
/* ::::::::¡Buena idea!::::::::: */
#define SEM_P(x,n)\
  x##.sem_num=n;\
  x##.sem_op=-1;\
  x##.sem_flg=0;

#define SEM_V(x,n)\
  x##.sem_num=n;\
  x##.sem_op=1;\
  x##.sem_flg=0;


/* ::::::::Variables Globales::::::::: */
/* ::::::::¡Yu, yu!::::::::: */
int semid;
pid_t pid[3];

/* ::::::::Prototipos::::::::: */
void newsigint(int signal);
void MEZ_algoritm(int semid); /

/* ::::::::MAIN::::::::: */
int main(int argc, char *argv[])
{
  int info;
  struct sigaction new, old;
  sigset_t mask;

  if((semid=semget(IPC_PRIVATE, 1, IPC_CREAT | 0600)) == -1)
  {
    perror("Error en creación de semáforo");
    exit(1);
  }
  semctl(semid,0,SETVAL,2);

  system("clear");

  switch(pid[0]=fork())
  {
    case -1 :
      perror("Error en creación del segundo proceso");
      exit(2);

    case 0  : /* Segundo proceso */
      MEZ_algoritm(semid);

    default : /* Primer proceso */
      switch(pid[1]=fork())
      {
        case -1 :
          perror("Error en creación del tercer proceso");
          exit(3);

        case 0  : /* Tercer proceso */
          MEZ_algoritm(semid);

        default : /* Primer proceso */
          switch(pid[2]=fork())
          {
            case -1 :
              perror("Error en creación del cuarto proceso");
              exit(4);

            case 0  : /* Cuarto proceso */
              MEZ_algoritm(semid);

            default : /* Primer proceso */
              new.sa_handler=newsigint;
              sigemptyset(&mask);
              new.sa_mask=mask;
              new.sa_flags=SA_RESTART | SA_RESETHAND;
              /* ¿Para qué sirven aquí estos flags?
                 Todavía SA_RESTART hace que los semops no fallen cuando se recibe una señal,
                 pero el otro... */

              if(sigaction(SIGINT, &new, &old)==-1)
              {
                perror("Error en registro de SIGINT");
                exit(-5);
              }

              MEZ_algoritm(semid);
          }
      }
   }
}


/* ::::::::Funciones propias::::::::: */

void newsigint(int signal)
{
  int i, data;

  for(i=0;i<3;i++)
  {
    kill(pid[i],SIGINT);
    wait(&data);
  }

  if(semctl(semid,0,IPC_RMID)==-1)
  {
    perror("Error en borrado de semáforo");
    exit(5);
  }

  system("clear"); /* Bueno para borrar huellas... */
  exit(0);
}

void MEZ_algoritm(int semid)
{
  /* Poner código antes de haber acabado con las variables es propio de C++ */
  int somnolencia=((getpid() % 10) >> 1) + 1;
  /* Forma de dividir por dos -----^^^^ */
  struct sembuf semact;
  char command[20];

  while(666)
  {
    sleep(somnolencia);

    SEM_WAIT(semact,0);
    if(semop(semid,&semact,1)==-1)
    {
      perror("Operación WAIT en semáforo");
      exit(6);
    }

    sprintf(command,"tput cup %d 1",getpid() % 10);
    system(command);
    printf("%d\b",getpid() % 10);
    fflush(stdout);
    sleep(somnolencia);
    printf(" \b");
    fflush(stdout);

    SEM_SIGNAL(semact,0);
    if(semop(semid,&semact,1)==-1)
    {
      perror("Operación SIGNAL en semáforo");
      exit(7);
    }
  }
}
