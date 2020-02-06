/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>
/*  1. This is intended to show the address of different local array variables
    in the stack. If work as intended, the output will be:
    {address of first array in foo()}
    {address of second array in bar(), the value will be bigger}
    42
    42
    42
    42
    42
    2. I got a warning: function returns address of local variable
    This means that the returned address belongs to a local variable and can
    become a null pointer after this function is finished. 
    3. I got this as an output: 
    0x7fffcae7f000
    0x7fffcae7f000
    Segmentation fault (core dumped)
    It printed out the address of the two arrays in foo() and bar(), and they
    were the same because the program removed the stack frame of foo() and 
    reused the same space for bar(). Because they shared the same code at the
    beginning, the address of the array variable was identical.
    4. I got a segmentation fault because the program cannot find the intended
    memory when printing the array in main().
*/

#define SIZE 5

int *foo() {
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    // printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
