#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5 // Number of philosophers

// Define semaphores for forks and a mutex for mutual exclusion
sem_t forks[N];
sem_t mutex;

// Function to simulate philosopher actions
void *philosopher(void *arg) {
    int phil_id = *(int *)arg;
    int left_fork = phil_id;
    int right_fork = (phil_id + 1) % N;

    while (1) {
        // Think
        printf("Philosopher %d is thinking.\n", phil_id);

        // Pick up left fork
        sem_wait(&forks[left_fork]);
        printf("Philosopher %d picked up left fork %d.\n", phil_id, left_fork);

        // Pick up right fork
        sem_wait(&forks[right_fork]);
        printf("Philosopher %d picked up right fork %d.\n", phil_id, right_fork);

        // Eat
        printf("Philosopher %d is eating.\n", phil_id);

        // Put down right fork
        sem_post(&forks[right_fork]);
        printf("Philosopher %d put down right fork %d.\n", phil_id, right_fork);

        // Put down left fork
        sem_post(&forks[left_fork]);
        printf("Philosopher %d put down left fork %d.\n", phil_id, left_fork);
    }
}

int main() {
    pthread_t philosophers[N];
    int phil_ids[N];

    // Initialize semaphores
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }
    sem_init(&mutex, 0, 1);

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        phil_ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &phil_ids[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy semaphores
    for (int i = 0; i < N; i++) {
        sem_destroy(&forks[i]);
    }
    sem_destroy(&mutex);

    return 0;
}
