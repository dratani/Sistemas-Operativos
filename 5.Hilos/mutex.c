#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 10

// Variable global compartida
int shared_var = 0;

// Mutex para proteger la variable compartida
pthread_mutex_t lock;

// Estructura para pasar datos a los threads
typedef struct {
    int thread_num;
} thread_data_t;

// Función que ejecutarán los threads
void* thread_function(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;

    // Bloquear el mutex antes de acceder a la variable compartida
    pthread_mutex_lock(&lock);

    // Sección crítica
    int temp = shared_var;
    printf("Thread %d: valor actual de shared_var = %d\n", data->thread_num, temp);
    shared_var = temp + 1;
    printf("Thread %d: nuevo valor de shared_var = %d\n", data->thread_num, shared_var);

    // Desbloquear el mutex después de acceder a la variable compartida
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];

    // Inicializar el mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Error al inicializar el mutex\n");
        return 1;
    }

    // Crear los threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].thread_num = i + 1;

        if (pthread_create(&threads[i], NULL, thread_function, &thread_data[i]) != 0) {
            printf("Error al crear el thread %d\n", i + 1);
            return 1;
        }
    }

    // Esperar a que todos los threads terminen
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destruir el mutex
    pthread_mutex_destroy(&lock);

    printf("Valor final de shared_var = %d\n", shared_var);

    return 0;
}

