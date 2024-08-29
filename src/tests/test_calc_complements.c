#include "test.h"

START_TEST(calc_complements_test_1) {
  matrix_t A;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 6;

  matrix_t expected;
  s21_create_matrix(3, 3, &expected);
  expected.matrix[0][0] = 24;
  expected.matrix[0][1] = 5;
  expected.matrix[0][2] = -4;
  expected.matrix[1][0] = -12;
  expected.matrix[1][1] = 3;
  expected.matrix[1][2] = 2;
  expected.matrix[2][0] = -2;
  expected.matrix[2][1] = -5;
  expected.matrix[2][2] = 4;

  matrix_t result;
  s21_calc_complements(&A, &result);

  for (int i = 0; i < result.rows; i++) {
    for (int j = 0; j < result.columns; j++) {
      ck_assert_double_eq_tol(result.matrix[i][j], expected.matrix[i][j], 1e-6);
    }
  }

  s21_remove_matrix(&A);
  s21_remove_matrix(&expected);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(calc_complements_err_test_1) {
  int rows = 1;
  int columns = 2;
  matrix_t result1;

  s21_create_matrix(rows, columns, &result1);
  result1.matrix[0][0] = 2.;
  result1.matrix[0][1] = 3.;
  //  s21_print_matrix(&result1);
  int flag = s21_calc_complements(&result1, NULL);
  //  s21_print_matrix(&end);
  ck_assert_int_eq(flag, Err_Incorrect_Matrix);

  s21_remove_matrix(&result1);
}
END_TEST

Suite *s21_calc_complements_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_calc_complements_matrix\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_calc_complements_matrix");
  tcase_add_test(tc_core, calc_complements_test_1);

  tcase_add_test(tc_core, calc_complements_err_test_1);

  suite_add_tcase(s, tc_core);
  return s;
}
