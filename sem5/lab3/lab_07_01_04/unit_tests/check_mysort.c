#include "check_mysort.h"


START_TEST(test_mysort_usual_array)
{
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int res[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    mysort(data, 9, sizeof(int), compare_int);

    ck_assert_mem_eq(res, data, 9 * sizeof(int));
}
END_TEST

START_TEST(test_mysort_revers_array)
{
    int data[] = {5, 4, 0};
    int res[] = {0, 4, 5};

    mysort(data, 3, sizeof(int), compare_int);

    ck_assert_mem_eq(res, data, 3 * sizeof(int));
}
END_TEST

START_TEST(test_mysort_random_array)
{
    int data[] = {1, -9, 19};
    int res[] = {-9, 1, 19};

    mysort(data, 3, sizeof(int), compare_int);

    ck_assert_mem_eq(res, data, 3 * sizeof(int));
}
END_TEST

START_TEST(test_mysort_random_array_float)
{
    float data[] = {1.4, -9.0, 19.9};
    float res[] = {-9.0, 1.4, 19.9};

    mysort(data, 3, sizeof(float), compare_float);

    ck_assert_mem_eq(res, data, 3 * sizeof(float));
}
END_TEST

START_TEST(test_mysort_random_array_string)
{
    char data[][5] = {"abc", "qts", "crt"};
    char res[][5] = {"abc", "crt", "qts"};

    mysort(data, 3, sizeof(char [5]), compare_string);

    ck_assert_mem_eq(res, data, 3 * sizeof(char [5]));
}
END_TEST

START_TEST(test_mysort_one_el_array)
{
    int data[] = { 1 };
    int res[] = { 1 };

    mysort(data, 1, sizeof(int), compare_int);

    ck_assert_mem_eq(res, data, 1 * sizeof(int));
}
END_TEST

Suite* mysort_suite(void)
{
    Suite *s;
    TCase *tc_pos;

    s = suite_create("key");
    
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_mysort_usual_array);
    tcase_add_test(tc_pos, test_mysort_revers_array);
    tcase_add_test(tc_pos, test_mysort_random_array);
    tcase_add_test(tc_pos, test_mysort_one_el_array);
    tcase_add_test(tc_pos, test_mysort_random_array_float);
    tcase_add_test(tc_pos, test_mysort_random_array_string);

    suite_add_tcase(s, tc_pos);
    

    return s;
}