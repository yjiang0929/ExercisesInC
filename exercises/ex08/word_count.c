#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <string.h>

#define BUFFER_MAX_SIZE 1000

/*
  Create hashtable of word freaquency from text file. The words will be
  stripped off punctuations specified in delim. 

  Parameters: table: pointer to Glib hashtable that stores word frequency
              filename: char string that represents file name to read from
*/
void create_hashtable_from_file(GHashTable **table, char *filename) {
    FILE *text;
    gchar word[BUFFER_MAX_SIZE];
    gchar *delim = " \n,.;:()'/\"";
    gchar *sub = "";
    gpointer value;

    text = fopen(filename, "r");
    if (!text) {
        exit(1);
    }
    while (fscanf(text, "%1000s", word) == 1) {
        gchar *key = g_strdelimit(word, delim, *sub);

        value = g_hash_table_lookup(*table, key);
        if (value) {
            gpointer new_value = GINT_TO_POINTER(GPOINTER_TO_INT(value) + 1);
            g_hash_table_insert(*table, g_strdup(key), new_value);
        } else {
            g_hash_table_insert(*table, g_strdup(key), GINT_TO_POINTER(1));
        }
    }
    fclose(text);
}

/*
  Print out frequency of each word on stdout

  Parameters: key: word that appears in the text file
              value: number of times that the word appears
              user_data: unused data field for GHFunc declaration
*/
void print_word_count(gpointer key, gpointer value, gpointer user_data) {
    printf("%s: %d\n", (char *)key, GPOINTER_TO_INT(value));
}

/*
  Main body of the program. 
  Creates a hashtable from input text, and then displays the word count from
  hashtable on stdout.
*/
int main() {
    GHashTable *table = g_hash_table_new(g_str_hash, g_str_equal);
    char *filename = "alice_in_wonderland.txt";

    create_hashtable_from_file(&table, filename);
    g_hash_table_foreach(table, print_word_count, NULL);

    return 0;
}