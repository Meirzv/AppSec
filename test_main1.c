#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_wordlist1.txt"

//Unit Testing to read input file to check mispelled list. The input file includes symboles with no words and a lot of 
//difference spances and new lines. input file
/*
custodian's    $      caseworker's

         Meir                       geed # %%             


         Zeevi   
         */

START_TEST(test_check_words_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char *expected[3];
    expected[0] = "Meir";
    expected[1] = "Zeevi";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("test2.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 2);
    bool test = strlen(misspelled[0]) == strlen(expected[0]);
    int len1 = strlen(misspelled[0]);
    int len2 = strlen(expected[0]);
    ck_assert_msg(test, "%d!=%d", len1, len2);
    ck_assert_msg(!strcmp(misspelled[0], expected[0]) == 0 , "Word %s is exist", expected[0]);
    ck_assert_msg(strcmp(misspelled[1], expected[1]) == 0 , "Expected %s", expected[0]);
}
END_TEST

Suite *
check_word_suite(void)
{
    Suite *suite;
    TCase *check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_check_words_normal);
    suite_add_tcase(suite, check_word_case);

    return suite;
}

int main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;

    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}