#include "dictionary.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXCHAR 1000

int check_words(FILE *fp, hashmap_t hashtable[], char *misspelled[]){
    int num_misspelled = 0;
    bool flag_bof = false;
    for (int i = 0 ; i < MAXCHAR; i++){
        misspelled[i] = NULL;
    }
    if (fp == NULL) //check if file is NULL
        return 0;
    
    char c, word[LENGTH+1];
    int length_word = 0; //length for word reading from file
    int ascii_char = 0;
    bool first = false;
    
    
    while ((c = fgetc(fp)) != EOF)
    {
        if (c == ' ' || c == '\n') //Space or new line means a begining of a new word
        {
            if (flag_bof == true){
                flag_bof = false;
//                length_word = 0;
//                for (int i = 0; i<=LENGTH; i++){
//                    word[i] = '\0';
//                }
//                continue;
            }
            ascii_char = (int)word[length_word-1];
            if (((ascii_char > 64) && (ascii_char < 91)) || ((ascii_char > 96) && (ascii_char < 123))) { //Checking ASCII punctuation
                word[length_word] = '\0'; //End of char array
            }
            else{
                word[length_word-1] = '\0'; //found punctuation
                length_word--;
            }
            
            if (length_word > 0){ // if a word is bigger than at least 0 chars -> check word
                if (check_word(word, hashtable) == false){ //found  misspelled word.
                    misspelled[num_misspelled] = malloc(sizeof(char) * length_word);
                    if (misspelled[num_misspelled] == NULL){
                        exit(0);
                    }
                    first = false;
                    strcat(misspelled[num_misspelled], word);
                    num_misspelled++;
                }
            }
            length_word = 0; //new word
            for (int i = 0; i<=LENGTH; i++){
                word[i] = '\0';
            }
            
        }
        else
        {
            if(length_word > 45){
                flag_bof = true;
                continue;
            }
            else{
                if (length_word == 0){
                    ascii_char = (int)c;
                    if (((ascii_char > 64) && (ascii_char < 91)) || ((ascii_char > 96) && (ascii_char < 123))) { //Checking ASCII punctuation
                        word[0] = c; //Beginning of word
                    }
                    else{
                        continue; // word starts with punctuation, therefore continue.
                    }
                }
                word[length_word] = c;
                length_word += 1;   //next char in the word
            }
        }
    }
    
    ascii_char = (int)word[length_word-1];
    if (((ascii_char > 64) && (ascii_char < 91)) || ((ascii_char > 96) && (ascii_char < 123))) { //Checking ASCII punctuation
        word[length_word] = '\0'; //End of char array
    }
    else{
        word[length_word-1] = '\0'; //found punctuation
        length_word--;
    }
    
    if (length_word > 0){ // if a word is bigger than at least 0 chars -> check word
        if (check_word(word, hashtable) == false){ //found  misspelled word.
            misspelled[num_misspelled] = malloc(sizeof(char) * length_word);
            if (misspelled[num_misspelled] == NULL){
                exit(0);
            }
            first = false;
            strcat(misspelled[num_misspelled], word);
            num_misspelled++;

        }
    }
    
    return num_misspelled;
}



bool check_word(const char *word, hashmap_t hashtable[]){
    bool result = false;
    int bucket = hash_function(word); //Get hash value for given word.
    node *new_node = hashtable[bucket]; //Set new_node to the right node in the array
    /**************************************** checking is word misspelled without lower case****************************************/
    while (new_node != NULL){
        int cmp = strcmp(new_node->word, word);
        if (cmp == 0){ // words are equal
            result = true;
            break;
        }
        new_node = new_node->next; //checking the next node in the linked list
    }
    /* ***********************************************************************************/
    /**************************************** checking is word misspelled for lower case****************************************/
    if (result == false) { //didn't match regular case in the first time
        size_t word_length =  strlen(word);
        char lower_case_word[word_length];
        strcpy(lower_case_word, word);
        for(int i = 0; word[i]; i++){
          lower_case_word[i] = tolower(word[i]);
        }
        bucket = hash_function(lower_case_word);
        node *new_node = hashtable[bucket];
        while (new_node != NULL){
            int cmp = strcmp(new_node->word, lower_case_word);
            if (cmp == 0){ // words are equal
                result = true;
                break;
            }
            new_node = new_node->next; //checking the next node in the linked list
        }
    }
    /* ***********************************************************************************/
    return result;
}

void add_new_value_to_hash_array(int bucket,const char *word, hashmap_t hashtable[]){
    node *curr = hashtable[bucket];
    if ( curr == NULL){
        node *new_node;
        new_node = (node *) malloc(sizeof(node));
        if (new_node == NULL){
            exit(0);
        }
        strcpy(new_node->word, word);
        new_node->next = NULL;
        curr = new_node;
        hashtable[bucket] = curr;

    }
    else{
        node *new_node;
        new_node = (node *) malloc(sizeof(node));
        if (new_node == NULL){
            exit(0);
        }
        strcpy(new_node->word, word);
        new_node->next = hashtable[bucket];
        hashtable[bucket] = new_node;
    }
}
bool load_dictionary(const char *dictionary_file, hashmap_t hashtable[]){
    FILE *fp;
    fp = fopen(dictionary_file, "r");
    if (fp == NULL) //check if file is NULL
        return 0;
    
    for (int i = 0; i < HASH_SIZE; i++){ //Initialize the array to NULL
        hashtable[i] = NULL;
    }
    char c, word[LENGTH+1];
    int length_word = 0; //length for word reading from file
    int count_words = 1; //number of words in the file
    int bucket = 0; //reminder of hash function, value 0-1999
    bool flag_bof = false;
    
    while ((c = fgetc(fp)) != EOF)
    {
        if (c == ' ' || c == '\n') //Space or new line means a begining of a new word
        {
            if (flag_bof == true){
                flag_bof = false;
            }
            else{
                count_words++;
                word[length_word] = '\0'; //End of char array
                bucket = hash_function(word);
                add_new_value_to_hash_array(bucket, word, hashtable);
            }
            length_word = 0; //new word
        }
        else
        {
            if (length_word > LENGTH){ // Ignore this input -> More than 45 chars
                flag_bof = true;
                continue;
            }
            word[length_word] = c;
            length_word++;   //next char in the word
        }
    }
    count_words += 1;
    word[length_word] = '\0'; //End of char array
    length_word = 0; //new word
    bucket = hash_function(word);
    add_new_value_to_hash_array(bucket, word, hashtable);
    fclose(fp);
    return false;
}



//int main(){
//    bool check;
//    char * file_path = "/Users/maorzeevi/Documents/GitHub/AppSec/wordlist.txt";
//    hashmap_t hashtable[HASH_SIZE];
//    check = load_dictionary(file_path, hashtable);
//
//
//    FILE *fp_test;
//    fp_test = fopen("/Users/maorzeevi/Documents/GitHub/AppSec/test.txt", "r");
//    char *misspelled[MAXCHAR];
//    //misspelled[0] = malloc(1 * sizeof(char));
//    int num_misspelled = check_words(fp_test, hashtable, misspelled);
//    printf("Number of misspeled word are %d", num_misspelled);
//    printf("\n %s",misspelled[0]);
//
//    return 0;
//}
