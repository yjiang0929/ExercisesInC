/* Code for a terminal based card game
   Author: Yichen Jiang
   Software System Spring 2020, Olin College
*/
#include <stdio.h>
#include <stdlib.h>
/* Converts user input into numeric value based on game rules.
   
   returns 10 if the input string is J, Q or K,
   the string's value if the input represents a number,
   0 if the string is X.

   prints an error message if the numeric value is not within 1 to 10. 

   card_name: variable where the input string is stored.
*/
int convert_value(char card_name[]) {
    int val = 0;
    switch(card_name[0]) {
            case 'K':
            case 'Q':
            case 'J':
                val = 10;
                break;
            case 'A':
                val = 11;
                break;
            case 'X':
                break;
            default:
                val = atoi(card_name);
                if ((val<1) || (val>10)) {
                    puts("I don't understand that value!");
                }
    }
    return val;
}

/* Modify the count based on the value of new_val variable.

   if new_val is between 2 and 7, increment count by 1 and output a message.
   if new_val is 10, decrement count by 1 and outputs a message.

   new_val: variable that determines how count should be modified.
   *count: address of the count variable to modify.
*/
void modify_count(int new_val, int *count) {
    if ((new_val > 2) && (new_val < 7)) {
        *count += 1;
        printf("Current count: %i\n", *count);
    } else if (new_val == 10) {
        *count -= 1;
        printf("Current count: %i\n", *count);
    }
}

/* Main function of the program. 
   loops the program until an input 'X' is received.

   returns 0 if the program is finished successfully.
*/
int main()
{
    char card_name[3];
    int count = 0;
    while (card_name[0] != 'X') {
        int val = 0;
        puts("Enter the card_name: ");
        scanf("%2s", card_name);
        val = convert_value(card_name);
        modify_count(val, &count);
    }
    return 0;
}