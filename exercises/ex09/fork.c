/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

*/

/* I modified the code to initialize variables in stack, heap, static and
 * global segments, modify them in the child process and check their final
 * values in the parent process. I also printed the addresses of functions in
 * the parent and child processes to see if they share the code segment. The
 * result is that parent and child processes only share the same code segment,
 * but have different stack, heap, static and global segments. 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;

// create variable in global segment
int global_var = 1;

// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i)
{
    sleep(i);
    printf("Hello from child %d.\n", i);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;

    // create variables in stack, heap and static segments
    int stack_var = 2;
    int *heap_var = malloc(sizeof(int));
    *heap_var = 3;
    static int static_var = 4;
    printf("Original global variable is %d\n", global_var);
    printf("Original stack variable is %d\n", stack_var);
    printf("Original heap variable is %d\n", *heap_var);
    printf("Original static variable is %d\n", static_var);
    printf("Main function is at %p\n", main);
    printf("Child_code function is at %p\n", child_code);

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            child_code(i);
            
            // modify variables in the child node
            stack_var += 1;
            *heap_var += 1;
            global_var += 1;
            static_var += 1;
            printf("Modified global variable in child is %d\n", global_var);
            printf("Modified stack variable in child is %d\n", stack_var);
            printf("Modified heap variable in child is %d\n", *heap_var);
            printf("Modified static variable in child is %d\n", static_var);
            printf("Main function in child is at %p\n", main);
            printf("Child_code function in child is at %p\n", child_code);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }

    // Check if parent process and child process share the same result
    printf("Final global variable in parent is %d\n", global_var);
    printf("Final stack variable in parent is %d\n", stack_var);
    printf("Final heap variable in parent is %d\n", *heap_var);
    printf("Final static variable in parent is %d\n", static_var);

    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    exit(0);
}
