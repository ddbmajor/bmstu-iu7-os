#include "check_mult.h"

START_TEST(test_mult_dim_error)
{
    int rc;
    matrix_t *m1 = init_matrix();
    m1->data = allocate_matrix(3, 3);
    m1->rows = 3;
    m1->columns = 3;
    m1->head = m1->data[0];
    m1->elements = 0;

    matrix_t *m2 = init_matrix();
    m2->data = allocate_matrix(2, 4);
    m2->rows = 2;
    m2->columns = 4;
    m2->head = m2->data[0];
    m2->elements = 0;

    matrix_t *res = init_matrix();

    rc = mult(res, m1, m2);
    free_matrix(m1);
    free_matrix(m2);
    free_matrix(res);
    ck_assert_int_eq(rc, DIMENSION_ERROR);
}
END_TEST


START_TEST(test_mult_usual_matrix)
{
    int rc;
    matrix_t *m1 = init_matrix();
    m1->data = allocate_matrix(3, 3);
    m1->rows = 3;
    m1->columns = 3;
    m1->head = m1->data[0];
    m1->elements = 3;
    m1->data[0][0] = 1;
    m1->data[1][1] = 2;
    m1->data[2][2] = 3;

    matrix_t *m2 = init_matrix();
    m2->data = allocate_matrix(3, 3);
    m2->rows = 3;
    m2->columns = 3;
    m2->head = m2->data[0];
    m2->elements = 3;
    m2->data[0][2] = 1;
    m2->data[1][1] = 2;
    m2->data[2][0] = 3;

    matrix_t *result = init_matrix();
    result->data = allocate_matrix(3, 3);
    result->rows = 3;
    result->columns = 3;
    result->head = result->data[0];
    result->elements = 3;
    result->data[0][2] = 1;
    result->data[1][1] = 4;
    result->data[2][0] = 9;


    matrix_t *res = init_matrix();

    rc = mult(res, m1, m2);
    ck_assert_int_eq(rc, 0);
    rc = matrix_cmp(res, result);
    free_matrix(m1);
    free_matrix(m2);
    free_matrix(result);
    free_matrix(res);
    ck_assert_int_eq(rc, 0);
}
END_TEST

Suite* mult_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    s = suite_create("mult");

    tc_neg = tcase_create("negatives");

    tcase_add_test(tc_neg, test_mult_dim_error);


    suite_add_tcase(s, tc_neg);
    
    tc_pos = tcase_create("positives");

    tcase_add_test(tc_pos, test_mult_usual_matrix);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}
