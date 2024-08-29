#include "test.h"

START_TEST(remove_test_1) {
  int rows = 1;
  int columns = 1;
  matrix_t result;
  matrix_t result1;
  matrix_t end;

  s21_create_matrix(rows, columns, &result);
  s21_create_matrix(rows, columns, &result1);
  result.matrix[0][0] = 2;
  result1.matrix[0][0] = 2;
  // s21_print_matrix(&result);
  s21_remove_matrix(&result);
  int flag = s21_sum_matrix(&result, &result1, &end);
  ck_assert_int_eq(flag, Err_Incorrect_Matrix);
  s21_remove_matrix(&result1);
}
END_TEST

START_TEST(remove_test_2) {
  int rows = 1;
  int columns = 2;
  matrix_t result;
  matrix_t end;

  s21_create_matrix(rows, columns, &result);
  result.matrix[0][0] = 2;
  result.matrix[0][1] = 1;
  // s21_print_matrix(&result);
  s21_remove_matrix(&result);
  int flag = s21_sum_matrix(&result, &result, &end);
  ck_assert_int_eq(flag, Err_Incorrect_Matrix);
}
END_TEST

Suite *s21_remove_matrix_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_remove_matrix\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_remove_matrix");
  tcase_add_test(tc_core, remove_test_1);
  tcase_add_test(tc_core, remove_test_2);

  suite_add_tcase(s, tc_core);
  return s;
}
