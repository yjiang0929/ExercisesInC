#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "util.h"
#include "minunit.h"

int tests_run = 0;

/*
  Tests if icmpcode_v4() works for code = 0
  Function under test should return "network unreachable"
*/
static char *test1() {
    char *result = icmpcode_v4(0);
    char *expected = "network unreachable";
    char *message = "test1 failed: icompcode_v4(0) should return \"network unreachable\"";
    mu_assert(message, strcmp(result, expected)==0);
    return NULL;
}

/*
  Tests if icmpcode_v4() works for code = 5
  Function under test should return "source route failed"
*/
static char *test2() {
    char *result = icmpcode_v4(5);
    char *expected = "source route failed";
    char *message = "test1 failed: icompcode_v4(5) should return \"source route failed\"";
    mu_assert(message, strcmp(result, expected)==0);
    return NULL;
}

/*
  Tests if icmpcode_v4() works for code = 10
  Function under test should return "destination host administratively
  prohibited"
*/
static char *test3() {
    char *result = icmpcode_v4(10);
    char *expected = "destination host administratively prohibited";
    char *message = "test1 failed: icompcode_v4(10) should return \"destination host administratively prohibited\"";
    mu_assert(message, strcmp(result, expected)==0);
    return NULL;
}

/*
  Tests if icmpcode_v4() works for code = 25
  Function under test should return "[unknown code]"
*/
static char *test4() {
    char *result = icmpcode_v4(25);
    char *expected = "[unknown code]";
    char *message = "test1 failed: icompcode_v4(25) should return \"[unknown code]\"";
    mu_assert(message, strcmp(result, expected)==0);
    return NULL;
}

/*
  Runs all the unit tests and returns NULL if all passed
*/
static char *all_tests() {
    mu_run_test(test1);
    mu_run_test(test2);
    mu_run_test(test3);
    mu_run_test(test4);
    return NULL;
}

/*
  Main function. Prints a success message when all tests pass or an error
  message from the failed test case.
*/
int main() {
    char *result = all_tests();
    if (result != NULL) {
        printf("%s\n", result);
    } else {
        printf("All tests passed!\n");
    }
    printf("Test run: %d\n", tests_run);

    return result != 0;
}