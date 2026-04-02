/*
Producer-Consumer Algorithm Implementation 

Algorithm :-

1. Start the program.

2. Initialize buffer of size N.

3. Initialize semaphores:
   -> mutex = 1
   -> empty = N
   -> full = 0

4. Initialize variables:
   -> in = 0
   -> out = 0

5. Create producer and consumer processes.

6. Repeat forever:

   -> Producer:

       -> Produce an item.

       -> wait(empty)

       -> wait(mutex)

       -> Insert item into buffer[in].

       -> in = (in + 1) mod N

       -> signal(mutex)

       -> signal(full)

   -> Consumer:

       -> wait(full)

       -> wait(mutex)

       -> Remove item from buffer[out].

       -> out = (out + 1) mod N

       -> signal(mutex)

       -> signal(empty)

       -> Consume the item.

7. Stop the program.

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t mutex;
sem_t empty;
sem_t full;

// Producer function
void* producer(void* arg) {
    int item;

    for (int count = 0; count < 5; count++) {   // fixed iterations
        item = rand() % 100;

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Produced: %d at index %d\n", item, in);
        fflush(stdout);

        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);
    }

    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    int item;

    for (int count = 0; count < 5; count++) {   // fixed iterations
        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[out];
        printf("Consumed: %d from index %d\n", item, out);
        fflush(stdout);

        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        sleep(2);
    }

    return NULL;
}

int main() {
    pthread_t prod, cons;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Create threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    printf("Execution completed successfully.\n");

    return 0;
}