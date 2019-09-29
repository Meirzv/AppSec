#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "wordlist.txt"

//This Unit testing tests punctuation at the beginning and the end of a valid word. Also it checks punctuation at the middle of the word.
// It checks it directly from the function check words instead of input file. It should work because punctuation filters made in check words function

START_TEST(test_check_word_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char *correct_word = ".Justice";
    const char *correct_word1 = ".Justice.";
    const char *correct_word2 = "Justice..";
    const char *punctuation_word = "Justi*ce";
    const char *punctuation_word2 = "Jus0tice";
    bool testt = check_word(correct_word , hashtable);
    ck_assert_msg( !check_word(correct_word , hashtable) , "Cant find correct word %s", correct_word);
    ck_assert_msg( !check_word(correct_word1 , hashtable) , "Cant find correct word %s", correct_word1);
    ck_assert_msg( !check_word(correct_word2 , hashtable) , "Cant find correct word %s", correct_word2);
    ck_assert_msg( check_word(punctuation_word , hashtable) == false , "%s should return false" , punctuation_word);
    ck_assert_msg( check_word(punctuation_word , hashtable) == false , "%s should return false" , punctuation_word); 
}
END_TEST


Suite *
check_word_suite(void)
{
    Suite *suite;
    TCase *check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_check_word_normal);
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