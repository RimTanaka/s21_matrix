#include "test.h"

START_TEST(eq_test_1) {
  int rows = 1;
  int columns = 1;
  matrix_t result1;
  matrix_t result2;

  s21_create_matrix(rows, columns, &result1);
  s21_create_matrix(rows, columns, &result2);
  result1.matrix[0][0] = 2;
  result2.matrix[0][0] = 2;
  // s21_print_matrix(&result);
  int flag = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(flag, SUCCESS);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(eq_test_2) {
  int rows = 1;
  int columns = 1;
  matrix_t result1;
  matrix_t result2;

  s21_create_matrix(rows, columns, &result1);
  s21_create_matrix(rows, columns, &result2);
  result1.matrix[0][0] = 2;
  result2.matrix[0][0] = 1;
  // s21_print_matrix(&result);
  int flag = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(flag, FAILURE);
  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(eq_test_3) {
  int rows = 1;
  int columns = 2;
  matrix_t result1;
  matrix_t result2;

  s21_create_matrix(rows, columns, &result1);
  columns = 3;
  s21_create_matrix(rows, columns, &result2);
  result1.matrix[0][0] = 2;
  result1.matrix[0][1] = 2;
  result2.matrix[0][0] = 2;
  result2.matrix[0][1] = 2;
  result2.matrix[0][2] = 2;
  // s21_print_matrix(&result);
  int flag = s21_eq_matrix(&result1, &result2);
  ck_assert_int_eq(flag, FAILURE);

  s21_remove_matrix(&result1);
  s21_remove_matrix(&result2);
}
END_TEST

START_TEST(eq_test_err_1) {
  int rows = 1;
  int columns = 2;
  matrix_t result1;

  s21_create_matrix(rows, columns, &result1);
  result1.matrix[0][0] = 2;
  result1.matrix[0][1] = 2;
  // s21_print_matrix(&result);
  int flag = s21_eq_matrix(&result1, NULL);
  ck_assert_int_eq(flag, FAILURE);

  s21_remove_matrix(&result1);
}
END_TEST

Suite *s21_eq_matrix_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_eq_matrix\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_eq_matrix");
  tcase_add_test(tc_core, eq_test_1);
  tcase_add_test(tc_core, eq_test_2);
  tcase_add_test(tc_core, eq_test_3);

  tcase_add_test(tc_core, eq_test_err_1);

  suite_add_tcase(s, tc_core);
  return s;
}
