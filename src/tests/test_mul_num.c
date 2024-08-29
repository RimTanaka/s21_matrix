#include "test.h"

START_TEST(mult_number_test_1) {
  int rows = 1;
  int columns = 1;
  matrix_t result1;
  matrix_t end;

  s21_create_matrix(rows, columns, &result1);
  result1.matrix[0][0] = 2;
  // s21_print_matrix(&result);
  double num = 5.;
  s21_mult_number(&result1, num, &end);
  double res = end.matrix[0][0];
  double must_by = 10.;
  ck_assert_double_eq_tol(res, must_by, 1e6);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&end);
}
END_TEST

START_TEST(mult_number_test_2) {
  int rows = 1;
  int columns = 2;
  matrix_t result1;
  matrix_t end;

  s21_create_matrix(rows, columns, &result1);
  result1.matrix[0][0] = 3.12345;
  result1.matrix[0][1] = 2;
  // s21_print_matrix(&result);
  double num = 5.;

  s21_mult_number(&result1, num, &end);
  double res1 = end.matrix[0][0];
  double must_by_1 = 15.61725;
  double res2 = end.matrix[0][1];
  double must_by_2 = 10.;
  ck_assert_double_eq_tol(res1, must_by_1, 1e6);
  ck_assert_double_eq_tol(res2, must_by_2, 1e6);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&end);
}
END_TEST

START_TEST(mult_number_err_test_1) {
  int rows = 1;
  int columns = 2;
  matrix_t result1;

  s21_create_matrix(rows, columns, &result1);
  result1.matrix[0][0] = 3.12345;
  result1.matrix[0][1] = 2;
  // s21_print_matrix(&result);
  double num = 5.;

  int flag = s21_mult_number(&result1, num, NULL);
  ck_assert_int_eq(flag, Err_Incorrect_Matrix);

  s21_remove_matrix(&result1);
}
END_TEST

Suite *s21_mult_number_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_mult_number_matrix\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_mult_number_matrix");
  tcase_add_test(tc_core, mult_number_test_1);
  tcase_add_test(tc_core, mult_number_test_2);

  tcase_add_test(tc_core, mult_number_err_test_1);

  suite_add_tcase(s, tc_core);
  return s;
}
