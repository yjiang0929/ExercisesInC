/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

/* 6. There is 32 bytes between them for any number between 1 and 32. 
*/

int var1;

int main ()
{
    int var2 = 5;
    void *p = malloc(20);
    void *q = malloc(20);
    char *s = "Hello, World";
    char *t = "another variable";

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p points to %p\n", p);
    printf ("q points to %p\n", q);
    printf ("s points to %p\n", s);
    printf ("t points to %p\n", t);

    return 0;
}
