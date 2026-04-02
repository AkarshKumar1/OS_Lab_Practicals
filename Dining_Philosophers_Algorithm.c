/*
Dining Philosophers Algorithm Implementation 

Algorithm :-

1. Start the program.

2. Initialize number of philosophers n = 5.

3. Initialize semaphores:
   -> fork[i] = 1 for all i
   -> mutex = 1

4. Create philosopher processes.

5. Repeat forever:

   -> For each philosopher i:

       -> Philosopher is thinking.

       -> wait(mutex)

       -> wait(fork[i])              // pick left fork

       -> wait(fork[(i+1) mod n])   // pick right fork

       -> signal(mutex)

       -> Philosopher starts eating.

       -> signal(fork[i])           // release left fork

       -> signal(fork[(i+1) mod n]) // release right fork

       -> Philosopher goes back to thinking.

6. Stop the program.

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

sem_t forks[N];   // semaphore for each fork
sem_t mutex;      // for mutual exclusion

// Philosopher function
void* philosopher(void* num) {
    int id = *(int*)num;

    for (int count = 0; count < 5; count++) {   // fixed iterations
        printf("Philosopher %d is thinking\n", id);
        fflush(stdout);
        sleep(1);

        // Pick forks
        sem_wait(&mutex);

        sem_wait(&forks[id]);
        printf("Philosopher %d picked LEFT fork %d\n", id, id);
        fflush(stdout);

        sem_wait(&forks[(id + 1) % N]);
        printf("Philosopher %d picked RIGHT fork %d\n", id, (id + 1) % N);
        fflush(stdout);

        sem_post(&mutex);

        // Eating
        printf("Philosopher %d is eating\n", id);
        fflush(stdout);
        sleep(2);

        // Release forks
        sem_post(&forks[id]);
        printf("Philosopher %d released LEFT fork %d\n", id, id);
        fflush(stdout);

        sem_post(&forks[(id + 1) % N]);
        printf("Philosopher %d released RIGHT fork %d\n", id, (id + 1) % N);
        fflush(stdout);

        printf("Philosopher %d finished eating\n\n", id);
        fflush(stdout);
    }

    return NULL;
}

int main() {
    pthread_t ph[N];
    int ids[N];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);

    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < N; i++) {
        pthread_join(ph[i], NULL);
    }

    printf("All philosophers have finished execution.\n");

    return 0;
}