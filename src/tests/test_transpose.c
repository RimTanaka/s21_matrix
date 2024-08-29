#include "test.h"

START_TEST(transpose_test_1) {
  int rows = 1;
  int columns = 1;
  matrix_t result1;
  matrix_t end;

  s21_create_matrix(rows, columns, &result1);
  result1.matrix[0][0] = 2.;
  // s21_print_matrix(&result);
  s21_transpose(&result1, &end);
  double res = end.matrix[0][0];
  double must_by = 2.;
  ck_assert_double_eq_tol(res, must_by, 1e6);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&end);
}
END_TEST

START_TEST(transpose_test_2) {
  int rows = 1;
  int columns = 2;
  matrix_t result1;
  matrix_t end;

  s21_create_matrix(rows, columns, &result1);
  result1.matrix[0][0] = 2.;
  result1.matrix[0][1] = 3.;
  //  s21_print_matrix(&result1);
  s21_transpose(&result1, &end);
  //  s21_print_matrix(&end);
  double res1 = end.matrix[0][0];
  double must_by1 = result1.matrix[0][0];
  double res2 = end.matrix[1][0];
  double must_by2 = result1.matrix[0][1];
  ck_assert_double_eq_tol(res1, must_by1, 1e6);
  ck_assert_double_eq_tol(res2, must_by2, 1e6);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&end);
}
END_TEST

START_TEST(transpose_err_test_1) {
  int rows = 1;
  int columns = 2;
  matrix_t result1;

  s21_create_matrix(rows, columns, &result1);
  result1.matrix[0][0] = 2.;
  result1.matrix[0][1] = 3.;
  //  s21_print_matrix(&result1);
  int flag = s21_transpose(&result1, NULL);
  //  s21_print_matrix(&end);
  ck_assert_int_eq(flag, Err_Incorrect_Matrix);

  s21_remove_matrix(&result1);
}
END_TEST

Suite *s21_transpose_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_transpose_matrix\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_transpose_matrix");
  tcase_add_test(tc_core, transpose_test_1);
  tcase_add_test(tc_core, transpose_test_2);

  tcase_add_test(tc_core, transpose_err_test_1);

  suite_add_tcase(s, tc_core);
  return s;
}
