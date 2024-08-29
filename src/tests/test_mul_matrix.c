#include "test.h"

START_TEST(mult_matrix_test_1) {
  int rows = 1;
  int columns = 1;
  matrix_t result1;
  matrix_t result2;
  matrix_t end;

  s21_create_matrix(rows, columns, &result1);
  s21_create_matrix(rows, columns, &result2);
  result1.matrix[0][0] = 2;
  result2.matrix[0][0] = 2;
  // s21_print_matrix(&result);
  s21_mult_matrix(&result1, &result2, &end);
  double res = end.matrix[0][0];
  double must_by = 4.;
  ck_assert_double_eq_tol(res, must_by, 1e6);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&end);
}
END_TEST

START_TEST(mult_matrix_test_2) {
  int rows = 2;
  int columns = 2;
  matrix_t result1;
  matrix_t result2;
  matrix_t end;

  s21_create_matrix(rows, columns, &result1);
  s21_create_matrix(rows, columns, &result2);
  result1.matrix[0][0] = 2;
  result1.matrix[0][1] = 4;
  result1.matrix[1][0] = 2;
  result1.matrix[1][1] = 4;
  result2.matrix[0][0] = 2;
  result2.matrix[0][1] = 3;
  result2.matrix[1][0] = 2;
  result2.matrix[1][1] = 3;
  s21_mult_matrix(&result1, &result2, &end);
  //  s21_print_matrix(&end);
  double res1 = end.matrix[0][0];
  double must_by1 = 8.;
  double res2 = end.matrix[0][1];
  double must_by2 = 12.;
  double res3 = end.matrix[1][0];
  double must_by3 = 8.;
  double res4 = end.matrix[1][1];
  double must_by4 = 12.;
  ck_assert_double_eq_tol(res1, must_by1, 1e6);
  ck_assert_double_eq_tol(res2, must_by2, 1e6);
  ck_assert_double_eq_tol(res3, must_by3, 1e6);
  ck_assert_double_eq_tol(res4, must_by4, 1e6);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&end);
}
END_TEST

START_TEST(mult_matrix_test_3) {
  const int rows = 2;
  const int cols = 2;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(cols, rows, &mtx);
  double c = 1.;
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = c++;
    }

  c = 7.;
  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++) {
      mtx.matrix[i][j] = c++;
    }

  matrix_t check = {0};
  s21_create_matrix(m.rows, mtx.columns, &check);
  check.matrix[0][0] = 25.;
  check.matrix[0][1] = 28.;
  check.matrix[1][0] = 57.;
  check.matrix[1][1] = 64.;

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_matrix(&m, &mtx, &res), OK);
  //  s21_print_matrix(&m);
  //  s21_print_matrix(&mtx);
  //  s21_print_matrix(&res);
  //  s21_print_matrix(&check);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_matrix_test_err_1) {
  int rows = 1;
  int rows2 = 2;
  int columns = 1;
  matrix_t result1;
  matrix_t result2;
  matrix_t end;

  s21_create_matrix(rows, columns, &result1);
  s21_create_matrix(rows2, columns, &result2);
  result1.matrix[0][0] = 2;
  result2.matrix[0][0] = 2;
  result2.matrix[1][0] = 2;
  // s21_print_matrix(&result);
  int flag = s21_mult_matrix(&result1, &result2, &end);
  ck_assert_int_eq(flag, Err_Calculation);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(mult_matrix_test_err_2) {
  int rows = 1;
  int rows2 = 2;
  int columns = 1;
  matrix_t result1;
  matrix_t result2;

  s21_create_matrix(rows, columns, &result1);
  s21_create_matrix(rows2, columns, &result2);
  result1.matrix[0][0] = 2;
  result2.matrix[0][0] = 2;
  result2.matrix[1][0] = 2;
  // s21_print_matrix(&result);
  int flag = s21_mult_matrix(&result1, &result2, NULL);
  ck_assert_int_eq(flag, Err_Incorrect_Matrix);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

Suite *s21_mult_matrix_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_mult_matrix\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_mult_matrix");
  tcase_add_test(tc_core, mult_matrix_test_1);
  tcase_add_test(tc_core, mult_matrix_test_2);
  tcase_add_test(tc_core, mult_matrix_test_3);

  tcase_add_test(tc_core, mult_matrix_test_err_1);
  tcase_add_test(tc_core, mult_matrix_test_err_2);

  suite_add_tcase(s, tc_core);
  return s;
}
