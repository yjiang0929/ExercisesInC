/*
  3. Biggest challenge was to remember how getopt() works, and once I got that
  working correctly, the rest becomes more straight forward. If this were a
  bigger project, I would do more research about the functions to use before
  I start.
  4. Professional code has error handling and checkings for edge cases. This
  makes the tool easier to use and more robust to problems. It also uses a
  different method to open and write to file.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int MAX_BUFFER_SIZE = 100;

/*
  Parse input arguments from command line.

  *argc, **argv[]: pointers to the main function's argc and *argv[].
  *is_append: pointer to int variable that decides how the input is saved.
*/
void parse_arg(int *argc, char **argv[], int *is_append) {
    char ch;
    while ((ch=getopt(*argc, *argv, "a")) != EOF) {
        switch (ch) {
            case 'a':
                *is_append = 1;
                break;
            default:
                *is_append = 0;
                break;
        }
    }

    *argc -= optind;
    *argv += optind;
}

/*
  Get input from stdin, terminates when Ctrl+D is received.

  *file_output: output file location.
*/
void get_text_input(FILE *file_output) {
    char text[MAX_BUFFER_SIZE];
    while (1) {
        char *res = fgets(text, MAX_BUFFER_SIZE, stdin);
        if (res == 0) {
            break;
        }
        fprintf(file_output, "%s",text);
    }
}

/*
  Parses save options, reads input from command line and saves it to file.
*/
int main (int argc, char *argv[]) {
    int is_append = 0;
    FILE *file_output;

    parse_arg(&argc, &argv, &is_append);

    if (is_append) {
        file_output = fopen(argv[0], "a");
    } else {
        file_output = fopen(argv[0], "w");
    }

    get_text_input(file_output);

    fclose(file_output);
    return 0;
}