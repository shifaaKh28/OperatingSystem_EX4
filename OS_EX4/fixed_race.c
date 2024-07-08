#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 20

long accum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Thread function to calculate the square of a number and add it to the global accumulator.
 *
 * This function retrieves the integer value passed to it, calculates its square, and adds the result
 * to the global variable `accum`. A mutex is used to protect the shared resource `accum` to prevent
 * race conditions. The dynamically allocated memory for the parameter is freed before the thread exits.
 *
 * @param param Pointer to the integer value to be squared.
 * @return NULL
 */
void *square(void *param) {
    int x = *(int *)param;
    pthread_mutex_lock(&mutex);
    accum += x * x;
    pthread_mutex_unlock(&mutex);
    free(param);
    pthread_exit(NULL);
}

/**
 * Main function to create threads and calculate the sum of squares of numbers from 1 to NUM_THREADS.
 *
 * This function creates NUM_THREADS threads, each calculating the square of a unique number and adding
 * it to the global accumulator `accum`. The function ensures proper memory allocation and handles any
 * allocation failures. All threads are joined before the final result is printed.
 *
 * @return Exit status of the program.
 */
int main() {
    pthread_t threads[NUM_THREADS];

    for (long t = 0; t < NUM_THREADS; t++) {
        int *param = malloc(sizeof(int));
        if (param == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        *param = t + 1;
        pthread_create(&threads[t], NULL, square, param);
    }

    for (long t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    printf("%ld\n", accum);
    pthread_exit(NULL);
}

/**
 * Documentation of Changes:
 *
 * 1. Added Mutex Initialization:
 *    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 *    - A mutex is initialized to protect the shared resource `accum` from race conditions.
 *
 * 2. Added Mutex Locking and Unlocking:
 *    pthread_mutex_lock(&mutex);
 *    accum += x * x;
 *    pthread_mutex_unlock(&mutex);
 *    - The shared resource `accum` is accessed within a critical section protected by a mutex.
 *
 * 3. Memory Management:
 *    free(param);
 *    - The dynamically allocated memory for the thread parameter is freed inside the thread function before it exits.
 *
 * 4. Error Handling for Memory Allocation:
 *    int *param = malloc(sizeof(int));
 *    if (param == NULL) {
 *        fprintf(stderr, "Memory allocation failed\n");
 *        exit(1);
 *    }
 *    - Checks if `malloc` returns `NULL` and handles the failure by printing an error message and exiting.
 *
 * Summary:
 *
 * These changes ensure that the program correctly handles multithreading with proper synchronization using a mutex.
 * The memory management is improved by freeing the dynamically allocated memory for thread parameters within the thread function.
 * The code now prevents race conditions by protecting the shared resource `accum` with a mutex, making the program thread-safe.
 */
