/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

/* 2. Synchronization errors start to frequently occur when the length of the
   shared array becomes very large, in my case, 100000000. This may be caused
   because modern computer are fast and optimized to minimize synchronization
   errors in threads.
   4. ./counter_array takes 3.791s to complete, and ./counter_array_mutex
   takes 4.896s to complete. Using mutex for synchronization does cause some
   amount of overhead.
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mutex.h"

#define NUM_CHILDREN 2

void perror_exit(char *s)
{
    perror(s);
    exit(-1);
}

void *check_malloc(int size)
{
    void *p = malloc(size);
    if (p == NULL) {
        perror_exit("malloc failed");
    }
    return p;
}

typedef struct {
    int counter;
    int end;
    Mutex *mutex;
    int *array;
} Shared;

Shared *make_shared(int end)
{
    int i;
    Shared *shared = check_malloc(sizeof(Shared));

    shared->counter = 0;
    shared->end = end;
    shared->mutex = make_mutex();

    shared->array = check_malloc(shared->end * sizeof(int));
    for (i=0; i<shared->end; i++) {
        shared->array[i] = 0;
    }
    return shared;
}

pthread_t make_thread(void *(*entry)(void *), Shared *shared)
{
    int ret;
    pthread_t thread;

    ret = pthread_create(&thread, NULL, entry, (void *) shared);
    if (ret != 0) {
        perror_exit("pthread_create failed");
    }
    return thread;
}

void join_thread(pthread_t thread)
{
    int ret = pthread_join(thread, NULL);
    if (ret == -1) {
        perror_exit("pthread_join failed");
    }
}

void perform_task(int task_number) {
    // actual work goes here
}

void child_code(Shared *shared)
{
    // printf("Starting child at counter %d\n", shared->counter);

    while (1) {
        // check if we're done
        if (shared->counter >= shared->end) {
            return;
        }

        // get the next task and lock mutex to preven synchronization error
        mutex_lock(shared->mutex);
        int task_number = shared->counter;
        shared->array[shared->counter]++;
        shared->counter++;
        mutex_unlock(shared->mutex);

        // update the progress bar
        // if (task_number % 10000 == 0) {
        //     printf("%d\n", task_number);
        // }

        // go off and do the task
        perform_task (task_number);
    }
}

void *entry(void *arg)
{
    Shared *shared = (Shared *) arg;
    child_code(shared);
    // printf("Child done.\n");
    pthread_exit(NULL);
}

void check_array(Shared *shared)
{
    int i, errors=0;

    // printf("Checking...\n");

    for (i=0; i<shared->end; i++) {
        if (shared->array[i] != 1) errors++;
    }
    // printf("%d errors.\n", errors);
}

int main()
{
    int i;
    pthread_t child[NUM_CHILDREN];

    Shared *shared = make_shared(100000000);

    for (i=0; i<NUM_CHILDREN; i++) {
        child[i] = make_thread(entry, shared);
    }

    for (i=0; i<NUM_CHILDREN; i++) {
        join_thread(child[i]);
    }

    check_array(shared);
    return 0;
}
