#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define NUM_SEMAFOROS 1

// Estructura para las operaciones semop
struct sembuf operacion;

int crear_semaforos(key_t key) {
    int  id_semaforos = semget(key, NUM_SEMAFOROS, IPC_CREAT | 0666);
    if (id_semaforos == -1) {
        perror("Error al crear/obtener el conjunto de semáforos");
        exit(EXIT_FAILURE);
    }
    return id_semaforos;
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
void operacion_P(int id_semaforo) {
    operacion.sem_num = id_semaforo; // Índice del semáforo en el conjunto (en este caso solo hay uno)
    operacion.sem_op = -1; // Valor a añadir al semáforo
    operacion.sem_flg = 0; // Flags adicionales (en este caso no se necesitan)

    if (semop(id_semaforo, &operacion, 1) == -1) {
        perror("Error al realizar la operación de semáforo");
        exit(EXIT_FAILURE);
    }
}

int main() {
    key_t key = ftok("/tmp", 'S'); // Generar una clave única para el conjunto de semáforos
    int id_semaforo = crear_semaforo(key); // Obtener el ID del conjunto de semáforos

    // Inicializar el semáforo
    inicializar_semaforo(id_semaforo);

    // Realizar operaciones de semáforo
    printf("Proceso 1 intentando acceder a la región crítica...\n");
    operacion_P(id_semaforo, -1); // Decrementar el valor del semáforo
    printf("Proceso 1 entrando en la región crítica.\n");
    // Región crítica
    sleep(2); // Simular trabajo en la región crítica
    printf("Proceso 1 saliendo de la región crítica.\n");
    operacion_V(id_semaforo, 1); // Incrementar el valor del semáforo

    // Destruir el conjunto de semáforos
    destruir_semaforos(id_semaforo);

    return 0;
}
