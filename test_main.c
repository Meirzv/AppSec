#include <check.h>
#include "dictionary.h"
#include <stdlib.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_wordlist.txt"

START_TEST(test_dictionary_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    ck_assert(load_dictionary(TESTDICT, hashtable));// test (448) = tbvt (448)
    const char *test = "test";
    const char *tbvt = "tbvt";
    node *new_node = hashtable[448];
    ck_assert_msg(strcmp (test , new_node->word) == 0, "found the word %s instead of test", new_node->word);
    new_node = new_node->next;
    ck_assert_msg(strcmp (tbvt , new_node->word) == 0, "found the word %s instead of tbvt", new_node->word);
//checking expecting behvior for the same bucket
}
END_TEST

START_TEST(test_check_word_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    const char *correct_word = "Justice";
    const char *punctuation_word_2 = "pl.ace";
    const char *punctuation_word_3 = "?ethyl's?";
    ck_assert(check_word(correct_word, hashtable));
    ck_assert(!check_word(punctuation_word_2, hashtable));
    if (check_word (punctuation_word_3, hashtable)) {
        ck_abort_msg ("The word ethyl's should not be misspelled \n");
    }
    // Test here: What if a word begins and ends with "? -- tested the word  ?ethyl's? above       
}
END_TEST

START_TEST(test_check_words_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char *expected[3];
    expected[0] = "sogn";
    expected[1] = "skyn";
    expected[2] = "betta";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("test1.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 3);
    bool test = strlen(misspelled[0]) == strlen(expected[0]);
    printf(" \n%s \n", misspelled[0]);
    int len1 = strlen(misspelled[0]);
    int len2 = strlen(expected[0]);
    ck_assert_msg(test, "%d!=%d", len1, len2);
    ck_assert_msg(strcmp(misspelled[0], expected[0]) == 0);
    ck_assert_msg(strcmp(misspelled[1], expected[1]) == 0);
    ck_assert_msg(strcmp(misspelled[2], expected[2]) == 0);
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
    tcase_add_test(check_word_case, test_check_words_normal);
    tcase_add_test(check_word_case, test_dictionary_normal);
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