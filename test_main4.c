#include <check.h>
#include "dictionary.h"
#include <stdlib.h>


#define DICTIONARY "test4.txt"

// Unit testing to check numbers and money word ($25.4). It should not work because filtering punctuation happens in the word_checks functions
/* test 4 file:
Zeevi
$25.4
12345678
65.65
*/
START_TEST(general_punc_test)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);

    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("test4.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert(num_misspelled == 0);
}
END_TEST

Suite *
check_word_suite(void)
{
    Suite *suite;
    TCase *check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, general_punc_test);
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