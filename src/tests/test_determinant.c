#include "test.h"

START_TEST(determinant_test_1) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  double result;
  int flag = s21_determinant(&A, &result);

  ck_assert_int_eq(flag, OK);
  ck_assert_double_eq_tol(result, -2.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_2) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 1.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 0.0;

  double result;
  int flag = s21_determinant(&A, &result);

  ck_assert_int_eq(flag, OK);
  ck_assert_double_eq_tol(result, 1.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_3) {
  matrix_t A;
  s21_create_matrix(4, 4, &A);

  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 3.0;
  A.matrix[0][2] = 4.0;
  A.matrix[0][3] = 5.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 7.0;
  A.matrix[1][2] = 8.0;
  A.matrix[1][3] = 9.0;
  A.matrix[2][0] = 10.0;
  A.matrix[2][1] = 11.0;
  A.matrix[2][2] = 11.0;
  A.matrix[2][3] = 0.0;
  A.matrix[3][0] = 1.0;
  A.matrix[3][1] = 2.0;
  A.matrix[3][2] = 3.0;
  A.matrix[3][3] = 4.0;

  double result;
  int flag = s21_determinant(&A, &result);

  ck_assert_int_eq(flag, OK);
  ck_assert_double_eq_tol(result, 0.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_test_4) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 1.0;

  double result;
  int flag = s21_determinant(&A, &result);

  ck_assert_int_eq(flag, OK);
  ck_assert_double_eq_tol(result, 1.0, 1e-6);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_err_test_1) {
  matrix_t A;
  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 1.0;

  int flag = s21_determinant(&A, NULL);

  ck_assert_int_eq(flag, Err_Incorrect_Matrix);

  s21_remove_matrix(&A);
}
END_TEST

Suite *s21_determinant_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_determinant_matrix\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_determinant_matrix");
  tcase_add_test(tc_core, determinant_test_1);
  tcase_add_test(tc_core, determinant_test_2);
  tcase_add_test(tc_core, determinant_test_3);
  tcase_add_test(tc_core, determinant_test_4);

  tcase_add_test(tc_core, determinant_err_test_1);

  suite_add_tcase(s, tc_core);
  return s;
}
