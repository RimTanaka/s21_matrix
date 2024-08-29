#include "test.h"

START_TEST(create_test_1) {
  int rows = 1;
  int columns = 1;
  matrix_t result;

  int flag = s21_create_matrix(rows, columns, &result);
  // s21_print_matrix(&result);
  ck_assert_int_eq(flag, OK);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(create_test_2) {
  int rows = 1;
  int columns = 5;
  matrix_t result;

  int flag = s21_create_matrix(rows, columns, &result);

  ck_assert_int_eq(flag, OK);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(create_null_test_1) {
  int rows = 7;
  int columns = 3;

  int flag = s21_create_matrix(rows, columns, NULL);
  ck_assert_int_eq(flag, Err_Incorrect_Matrix);
}
END_TEST

START_TEST(create_zero_test_1) {
  int rows = 1;
  int columns = 0;
  matrix_t result;

  int flag = s21_create_matrix(rows, columns, &result);

  ck_assert_int_eq(flag, Err_Incorrect_Matrix);
}
END_TEST

START_TEST(create_zero_test_2) {
  int rows = 0;
  int columns = 0;
  matrix_t result;

  int flag = s21_create_matrix(rows, columns, &result);

  ck_assert_int_eq(flag, Err_Incorrect_Matrix);
}
END_TEST

Suite *s21_create_matrix_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_create_matrix\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_create_matrix");

  tcase_add_test(tc_core, create_test_1);
  tcase_add_test(tc_core, create_test_2);

  tcase_add_test(tc_core, create_null_test_1);

  tcase_add_test(tc_core, create_zero_test_1);
  tcase_add_test(tc_core, create_zero_test_2);

  suite_add_tcase(s, tc_core);
  return s;
}
