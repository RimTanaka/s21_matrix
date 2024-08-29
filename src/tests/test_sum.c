#include "test.h"

START_TEST(sum_test_1) {
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
  s21_sum_matrix(&result1, &result2, &end);
  double res = end.matrix[0][0];
  double must_by = 4.;
  ck_assert_double_eq_tol(res, must_by, 1e6);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&end);
}
END_TEST

START_TEST(sum_test_2) {
  int rows = 1;
  int columns = 2;
  matrix_t result1;
  matrix_t result2;
  matrix_t end;

  s21_create_matrix(rows, columns, &result1);
  s21_create_matrix(rows, columns, &result2);
  result1.matrix[0][0] = 3;
  result1.matrix[0][1] = 2;
  result2.matrix[0][0] = 2;
  result2.matrix[0][1] = 5;
  // s21_print_matrix(&result);
  s21_sum_matrix(&result1, &result2, &end);
  double res1 = end.matrix[0][0];
  double must_by_1 = 5.;
  double res2 = end.matrix[0][1];
  double must_by_2 = 7.;
  ck_assert_double_eq_tol(res1, must_by_1, 1e6);
  ck_assert_double_eq_tol(res2, must_by_2, 1e6);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
  s21_remove_matrix(&end);
}
END_TEST

START_TEST(sum_test_err_1) {
  int rows = 1;
  int columns = 1;
  matrix_t result1;
  matrix_t result2;

  s21_create_matrix(rows, columns, &result1);
  s21_create_matrix(rows, columns, &result2);
  result1.matrix[0][0] = 2;
  result2.matrix[0][0] = 2;
  // s21_print_matrix(&result);
  int flag = s21_sum_matrix(&result1, &result2, NULL);
  ck_assert_int_eq(flag, Err_Incorrect_Matrix);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(sum_test_err_2) {
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
  int flag = s21_sum_matrix(&result1, &result2, &end);
  ck_assert_int_eq(flag, Err_Calculation);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

Suite *s21_sum_matrix_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_sum_matrix\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_sum_matrix");
  tcase_add_test(tc_core, sum_test_1);
  tcase_add_test(tc_core, sum_test_2);

  tcase_add_test(tc_core, sum_test_err_1);
  tcase_add_test(tc_core, sum_test_err_2);

  suite_add_tcase(s, tc_core);
  return s;
}
