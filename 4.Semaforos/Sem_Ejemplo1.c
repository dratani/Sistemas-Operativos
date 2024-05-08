#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define SEM_1 0

// Estructura para las operaciones semop
struct sembuf operacion;

int crear_semaforos(int num_sem) {
	int semid, llave;
	llave = ftok ("/tmp", 'k');
  if ((semid =semget (llave, 2, IPC_CREAT | 0600)) == -1){
    perror ("semget");
    exit (-1);
  }
    return semid;
}
void inicializar_semaforos(int id_semaforo) {
	//Inicializar semáforo 0 en 1
    if (semctl(id_semaforo, 0, SETVAL, 1) == -1) {
        perror("Error al inicializar el semáforo");
        exit(EXIT_FAILURE);
    }
}

void destruir_semaforos(int id_semaforo) {
    if (semctl(id_semaforo, 0, IPC_RMID) == -1) {
        perror("Error al destruir el conjunto de semáforos");
        exit(EXIT_FAILURE);
    }
}

// Función para realizar la operación de semáforo (semop)
void operacion_P(int semid, int id_semaforo) {
	printf("%d\n",id_semaforo);
    operacion.sem_num = id_semaforo; // Índice del semáforo en el conjunto (en este caso solo hay uno)
     operacion.sem_op = -1; 
    operacion.sem_flg = 0; // Flags adicionales (en este caso no se necesitan)

    if (semop(semid, &operacion, 1) == -1) {
        perror("Error al realizar la operación de semáforo");
        exit(EXIT_FAILURE);
    }
}
void operacion_V(int semid, int id_semaforo) {
    operacion.sem_num = id_semaforo; // Índice del semáforo en el conjunto (en este caso solo hay uno)
    operacion.sem_op = 1; // Valor a añadir al semáforo
    operacion.sem_flg = 0; // Flags adicionales (en este caso no se necesitan)

    if (semop(semid, &operacion, 1) == -1) {
        perror("Error al realizar la operación de semáforo");
        exit(EXIT_FAILURE);
    }
}
int main(int argc, char const *argv[]) {

    int id_semaforos = crear_semaforos(1); // Obtener el ID del conjunto de semáforos

    // Inicializar el semáforo
    inicializar_semaforos(id_semaforos);

    // Realizar operaciones de semáforo
    printf("Proceso 1 intentando acceder a la región crítica...\n");
    operacion_P(id_semaforos, SEM_1); // Decrementar el valor del semáforo
    printf("Proceso 1 entrando en la región crítica.\n");
    // Región crítica
    sleep(2); // Simular trabajo en la región crítica
    printf("Proceso 1 saliendo de la región crítica.\n");
    operacion_V(id_semaforos, SEM_1); // Incrementar el valor del semáforo

    // Destruir el conjunto de semáforos
    destruir_semaforos(id_semaforos);

    return 0;
}
