#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "test3_wordlist.txt"

// Unit testing to check numbers and money word ($25.4). It should work because filtering punctuation happens in the word_checks functions

START_TEST(test_check_word_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char *correct_word = "Zeevi";
    const char *correct_word1 = "$25.4";
    const char *correct_word2 = "12345678";
    const char *correct_word3 = "65.65";
    bool testt = check_word(correct_word , hashtable);
    ck_assert_msg( check_word(correct_word , hashtable) , "Cant find correct word %s", correct_word);
    ck_assert_msg( check_word(correct_word2 , hashtable) , "Cant find correct word %s", correct_word2);
    ck_assert_msg( check_word(correct_word3 , hashtable) , "Cant find correct word %s", correct_word3);
    ck_assert_msg( check_word(correct_word1 , hashtable) , "Cant find correct word %s", correct_word1);
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