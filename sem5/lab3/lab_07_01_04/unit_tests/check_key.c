#include "check_key.h"

START_TEST(test_key_bad_array)
{
    int rc;

    rc = key(NULL, NULL, NULL, NULL);
    ck_assert_int_eq(rc, BAD_ARRAY_ERROR);
}
END_TEST

START_TEST(test_key_empty_array)
{
    int rc;
    int data[] = { 1 };
    int *new_data = NULL;
    int *new_data_end = NULL;

    rc = key(data, data, &new_data, &new_data_end);
    ck_assert_int_eq(rc, EMPTY_FILE_ERROR);
}
END_TEST

START_TEST(test_key_res_empty_array)
{
    int rc;
    int data[] = {3, 3, 3};
    
    rc = key(data, data + 3, NULL, NULL);
    ck_assert_int_eq(rc, EMPTY_FILE_ERROR);
}
END_TEST

START_TEST(test_key_usual_array)
{
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *new_data = NULL;
    int *new_data_end = NULL;
    int res[] = {6, 7, 8, 9};
    int rc;

    rc = key(data, data + 9, &new_data, &new_data_end);
    ck_assert_int_eq(rc, 0);
    ck_assert_mem_eq(res, new_data, sizeof(int) * (int)(new_data_end - new_data));
    free(new_data);
}
END_TEST

Suite* key_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("key");
    
    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_key_bad_array);
    tcase_add_test(tc_neg, test_key_empty_array);
    tcase_add_test(tc_neg, test_key_res_empty_array);

    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_key_usual_array);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}