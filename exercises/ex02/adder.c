/* Code for a terminal based card game
   Author: Yichen Jiang
   Software System Spring 2020, Olin College
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_ARRAY_SIZE = 20;
const int MAX_BUFFER_SIZE = 20;
const int MAX_NUMBER_SIZE = 9;

/*  Receives user input from the input buffer, converts string to a number and
    outputs an array of number after the user presses Ctrl+D. 

    The function will print out an error if (1) the input string is longer
    than the maximum number length, (2) the user has reached the maximum size
    of the array or (3) the input is not a valid number.

    numbers: an empty array of integers
    len_numbers: final length of array, zero initially
*/
void getUserInput(int numbers[], int *len_numbers) {
    char str[MAX_NUMBER_SIZE];
    int index = 0;

    printf("Please enter at most %d numbers:\n", );
    while (1) {
        char *res = fgets(str, MAX_BUFFER_SIZE, stdin);
        if (res == 0) {
            break;
        }
        if (index == MAX_ARRAY_SIZE) {
            printf("Maximum array length reached. Press Ctrl+D to exit the program.\n");
            continue;
        }
        if (strlen(str) > MAX_NUMBER_SIZE) {
            printf("String length exceeds the maximum length! Max is 8 digits.\n");
            continue;
        }
        if (atoi(str) == 0 && !(str[0]=='0' && strlen(str)==2)){
            printf("Enter a valid number as input!\n");
            continue;
        }
        numbers[index] = atoi(str);
        index += 1;
    }
    *len_numbers = index;
}

/* calculates the sum of the numbers and returns the sum as an integer.

    numbers: an array of integers to calculate the sum
    len_numbers: numbers of integers in the array
*/
int calculateSum(int numbers[], int len_numbers) {
    int sum = 0;
    for (int i=0; i<len_numbers; i++) {
        sum += numbers[i];
    }
    return sum;
}

/* Main function. Initializes array and other variables, calls the two helper
    functions and prints out the sum at the end.
*/
int main() {
    int numbers[MAX_ARRAY_SIZE];
    int len_numbers = 0;
    int sum = 0;

    getUserInput(numbers, &len_numbers);
    sum = calculateSum(numbers, len_numbers);

    printf("Sum is %d\n", sum);
}