#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCHAR 1000

int main (int argc, char *argv[]){
    char * file_path = "/Users/maorzeevi/Desktop/NYU/Classes/Application Security/Assignments/Assignment 1/wordlist.txt";
    FILE *fp_test;

    if(argc > 1){
        file_path = argv[1];
        fp_test = fopen(argv[2], "r");
    }
    else{
         fp_test = fopen("/Users/maorzeevi/Desktop/NYU/Classes/Application Security/Assignments/Assignment 1/test_wordlist.txt", "r");
    }
    printf("\n value of %d ", argc);
    
    bool check = false;
    hashmap_t hashtable[HASH_SIZE];
    check = load_dictionary(file_path, hashtable);


    char *misspelled[MAXCHAR];
    int num_misspelled = check_words(fp_test, hashtable, misspelled);
    if (check){
        //pass
        num_misspelled++;
        num_misspelled--;
    }

    for (int miss = 0; miss < MAXCHAR ; miss++){
      free(misspelled[miss]);
    }
    for (int ll = 0; ll < 2000 ; ll++){
        node *new_node = hashtable[ll];
        while (new_node != NULL){
            node *next_new_node = new_node->next;
            free(new_node);
            new_node = next_new_node;
        }
    }

    return 0;
}

