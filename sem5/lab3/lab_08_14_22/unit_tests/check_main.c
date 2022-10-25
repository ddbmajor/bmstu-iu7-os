#include "check_add.h"
#include "check_mult.h"
#include "check_invert.h"

int main(void)
{
    int no_failed = 0;
    Suite *s;
    Suite *p;
    Suite *q;
    SRunner *runner;

    s = add_suite();
    p = mult_suite();
    q = invert_suite();

    runner = srunner_create(s);
    srunner_add_suite(runner, p);
    srunner_add_suite(runner, q);

    // Вот таким образом запускаются все тесты. С помощью второго параметра (в данном случаев
    // CK_VERBOSE) можно детализировать вывод.
    srunner_run_all(runner, CK_VERBOSE);
    // После того, как все тесты будут выполнены, можно получить по ним дополнительную информацию,
    // например, вот так.
    no_failed = srunner_ntests_failed(runner);
    // Перед завершением main "runner" нужно обязательно освободить.
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
