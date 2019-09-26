#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCHAR 1000

int main(){
    char * file_path = "/home/appsec/appsec/AppSec/wordlist.txt";
    bool check = false;
    hashmap_t hashtable[HASH_SIZE];
    check = load_dictionary(file_path, hashtable);


    FILE *fp_test;
    fp_test = fopen("/home/appsec/appsec/AppSec/input.txt", "r");
    char *misspelled[MAXCHAR];
    int num_misspelled = check_words(fp_test, hashtable, misspelled);
 //   printf("Number of misspeled word are %d", num_misspelled);
 //   printf("\n %s",misspelled[0]);
    if (check){
//	printf("Dictinory function good");
    }

    for (int miss = 0; miss < MAXCHAR ; miss++){
      free(misspelled[miss]);
    }
 //   free(*misspelled);
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
