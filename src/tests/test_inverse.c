#include "test.h"

void fill_matrix(matrix_t *A, const double values[]) {
  int index = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = values[index++];
    }
  }
}

START_TEST(inverse_test_1) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  double values[] = {2, 5, 7, 6, 3, 4, 5, -2, -3};
  fill_matrix(&A, values);

  double expected_values[] = {1.0,   -1.0, 1.0,   -38.0, 41.0,
                              -34.0, 27.0, -29.0, 24.0};
  fill_matrix(&expected, expected_values);

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &expected), 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_test_2) {
  matrix_t A, result, expected;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &expected);

  double identity_values[] = {1, 0, 0, 0, 1, 0, 0, 0, 1};
  fill_matrix(&A, identity_values);
  fill_matrix(&expected, identity_values);

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, OK);
  ck_assert(s21_eq_matrix(&result, &expected));

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_test_3) {
  matrix_t A, result;
  s21_create_matrix(2, 3, &A);

  double values[] = {1, 2, 3, 4, 5, 6};
  fill_matrix(&A, values);

  int status = s21_inverse_matrix(&A, &result);

  ck_assert_int_eq(status, Err_Calculation);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_test_4) {
  matrix_t test_matrix_1;
  matrix_t test_matrix_2;
  matrix_t test_matrix_3;
  s21_create_matrix(3, 3, &test_matrix_1);
  s21_create_matrix(3, 3, &test_matrix_3);

  test_matrix_1.matrix[0][0] = 2.0;
  test_matrix_1.matrix[0][1] = 5.0;
  test_matrix_1.matrix[0][2] = 7.0;
  test_matrix_1.matrix[1][0] = 6.0;
  test_matrix_1.matrix[1][1] = 3.0;
  test_matrix_1.matrix[1][2] = 4.0;
  test_matrix_1.matrix[2][0] = 5.0;
  test_matrix_1.matrix[2][1] = -2.0;
  test_matrix_1.matrix[2][2] = -3.0;

  test_matrix_3.matrix[0][0] = 1.0;
  test_matrix_3.matrix[0][1] = -1.0;
  test_matrix_3.matrix[0][2] = 1.0;
  test_matrix_3.matrix[1][0] = -38.0;
  test_matrix_3.matrix[1][1] = 41.0;
  test_matrix_3.matrix[1][2] = -34.0;
  test_matrix_3.matrix[2][0] = 27.0;
  test_matrix_3.matrix[2][1] = -29.0;
  test_matrix_3.matrix[2][2] = 24.0;

  int res = s21_inverse_matrix(&test_matrix_1, &test_matrix_2);

  int eq = s21_eq_matrix(&test_matrix_2, &test_matrix_3);
  ck_assert_int_eq(eq, SUCCESS);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&test_matrix_1);
  s21_remove_matrix(&test_matrix_2);
  s21_remove_matrix(&test_matrix_3);
}
END_TEST

START_TEST(inverse_test_5) {
  matrix_t A = {0};
  matrix_t result = {0};
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), Err_Incorrect_Matrix);
}
END_TEST

START_TEST(inverse_test_6) {
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t eq_matrix = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &eq_matrix);
  A.matrix[0][0] = 21;
  eq_matrix.matrix[0][0] = 1.0 / 21.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_test_7) {
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t eq_matrix = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);
  A.matrix[0][0] = 2, A.matrix[0][1] = 5, A.matrix[0][2] = 7;
  A.matrix[1][0] = 6, A.matrix[1][1] = 3, A.matrix[1][2] = 4;
  A.matrix[2][0] = 5, A.matrix[2][1] = -2, A.matrix[2][2] = -3;
  eq_matrix.matrix[0][0] = 1, eq_matrix.matrix[0][1] = -1,
  eq_matrix.matrix[0][2] = 1;
  eq_matrix.matrix[1][0] = -38, eq_matrix.matrix[1][1] = 41,
  eq_matrix.matrix[1][2] = -34;
  eq_matrix.matrix[2][0] = 27, eq_matrix.matrix[2][1] = -29,
  eq_matrix.matrix[2][2] = 24;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_test_8) {
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t eq_matrix = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &eq_matrix);
  A.matrix[0][0] = 4, A.matrix[0][1] = 7;
  A.matrix[1][0] = 2, A.matrix[1][1] = 6;
  eq_matrix.matrix[0][0] = 0.6, eq_matrix.matrix[0][1] = -0.7;
  eq_matrix.matrix[1][0] = -0.2, eq_matrix.matrix[1][1] = 0.4;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_test_9) {
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t eq_matrix = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = (i == j) ? 1 : 0;
      eq_matrix.matrix[i][j] = (i == j) ? 1 : 0;
    }
  }
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_test_10) {
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t eq_matrix = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);
  A.matrix[0][0] = 2, A.matrix[0][1] = -1, A.matrix[0][2] = 0;
  A.matrix[1][0] = -1, A.matrix[1][1] = 2, A.matrix[1][2] = -1;
  A.matrix[2][0] = 0, A.matrix[2][1] = -1, A.matrix[2][2] = 2;
  eq_matrix.matrix[0][0] = 3.0 / 4.0, eq_matrix.matrix[0][1] = 1.0 / 2.0,
  eq_matrix.matrix[0][2] = 1.0 / 4.0;
  eq_matrix.matrix[1][0] = 1.0 / 2.0, eq_matrix.matrix[1][1] = 1.0,
  eq_matrix.matrix[1][2] = 1.0 / 2.0;
  eq_matrix.matrix[2][0] = 1.0 / 4.0, eq_matrix.matrix[2][1] = 1.0 / 2.0,
  eq_matrix.matrix[2][2] = 3.0 / 4.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_test_11) {
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t eq_matrix = {0};

  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &eq_matrix);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 2;
  A.matrix[0][3] = -1;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 0;
  A.matrix[1][3] = 5;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 4;
  A.matrix[2][3] = -3;
  A.matrix[3][0] = 1;
  A.matrix[3][1] = 0;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = 0;

  eq_matrix.matrix[0][0] = 0.8333333;
  eq_matrix.matrix[0][1] = 0.1666667;
  eq_matrix.matrix[0][2] = 0.0;
  eq_matrix.matrix[0][3] = -0.3333333;
  eq_matrix.matrix[1][0] = -2.5000000;
  eq_matrix.matrix[1][1] = 0.1000000;
  eq_matrix.matrix[1][2] = 1.0;
  eq_matrix.matrix[1][3] = 0.2000000;
  eq_matrix.matrix[2][0] = -0.1666667;
  eq_matrix.matrix[2][1] = -0.0333333;
  eq_matrix.matrix[2][2] = 0.0;
  eq_matrix.matrix[2][3] = 0.2666667;
  eq_matrix.matrix[3][0] = -0.5;
  eq_matrix.matrix[3][1] = 0.1;
  eq_matrix.matrix[3][2] = 0.0;
  eq_matrix.matrix[3][3] = 0.2000000;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  //  s21_print_matrix(&result);
  //  s21_print_matrix(&eq_matrix);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_test_12) {
  matrix_t A = {0};
  matrix_t result = {0};
  matrix_t eq_matrix = {0};
  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &eq_matrix);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 0;
  A.matrix[0][2] = 2;
  A.matrix[0][3] = -1;
  A.matrix[0][4] = 3;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 0;
  A.matrix[1][3] = 5;
  A.matrix[1][4] = -2;
  A.matrix[2][0] = 2;
  A.matrix[2][1] = 1;
  A.matrix[2][2] = 4;
  A.matrix[2][3] = -3;
  A.matrix[2][4] = 1;
  A.matrix[3][0] = 1;
  A.matrix[3][1] = 0;
  A.matrix[3][2] = 5;
  A.matrix[3][3] = 0;
  A.matrix[3][4] = -1;
  A.matrix[4][0] = 2;
  A.matrix[4][1] = -3;
  A.matrix[4][2] = 1;
  A.matrix[4][3] = 4;
  A.matrix[4][4] = 2;
  eq_matrix.matrix[0][0] = -0.3030303;
  eq_matrix.matrix[0][1] = 0.1017316;
  eq_matrix.matrix[0][2] = 0.4870130;
  eq_matrix.matrix[0][3] = -0.3008658;
  eq_matrix.matrix[0][4] = 0.1623377;
  eq_matrix.matrix[1][0] = 0.6363636;
  eq_matrix.matrix[1][1] = 0.2792208;
  eq_matrix.matrix[1][2] = -0.3441558;
  eq_matrix.matrix[1][3] = 0.1103896;
  eq_matrix.matrix[1][4] = -0.4480519;
  eq_matrix.matrix[2][0] = 0.1515152;
  eq_matrix.matrix[2][1] = -0.0151515;
  eq_matrix.matrix[2][2] = -0.1363636;
  eq_matrix.matrix[2][3] = 0.2575758;
  eq_matrix.matrix[2][4] = -0.0454545;
  eq_matrix.matrix[3][0] = 0.3636364;
  eq_matrix.matrix[3][1] = 0.1493506;
  eq_matrix.matrix[3][2] = -0.3701299;
  eq_matrix.matrix[3][3] = 0.1753247;
  eq_matrix.matrix[3][4] = -0.1233766;
  eq_matrix.matrix[4][0] = 0.4545455;
  eq_matrix.matrix[4][1] = 0.0259740;
  eq_matrix.matrix[4][2] = -0.1948052;
  eq_matrix.matrix[4][3] = -0.0129870;
  eq_matrix.matrix[4][4] = -0.0649351;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(inverse_test_13) {
  matrix_t A = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 8;
  A.matrix[2][0] = 4;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 16;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), Err_Calculation);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}

START_TEST(inverse_test_one_by_one) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    m.matrix[0][0] = 1431.12312331;
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(result.matrix[0][0] == (1.0 / m.matrix[0][0]), 1);
    ck_assert_int_eq(code, OK);
    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
  }
}
END_TEST

START_TEST(inverse_test_zero_det) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, Err_Calculation);
  }
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(inverse_test_incorrect) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, Err_Incorrect_Matrix);
}
END_TEST

START_TEST(inverse_test_correct) {
  matrix_t m = {0};
  matrix_t result = {0};
  matrix_t must = {0};

  s21_create_matrix(2, 2, &m);
  s21_create_matrix(2, 2, &result);
  m.matrix[0][0] = 5.;
  m.matrix[0][1] = 1.;
  m.matrix[1][1] = 1.;
  m.matrix[1][0] = 1.;
  result.matrix[0][0] = 0.25;
  result.matrix[0][1] = -0.25;
  result.matrix[1][0] = -0.25;
  result.matrix[1][1] = 1.25;
  int code = s21_inverse_matrix(&m, &must);
  ck_assert_int_eq(s21_eq_matrix(&result, &must), SUCCESS);
  ck_assert_int_eq(code, OK);

  s21_remove_matrix(&result);
  s21_remove_matrix(&must);
  s21_remove_matrix(&m);
}
END_TEST

Suite *s21_inverse_matrix_suite(void) {
  Suite *s;
  s = suite_create("\033[33ms21_inverse_matrix\033[0m");

  TCase *tc_core;
  tc_core = tcase_create("s21_inverse_matrix");
  tcase_add_test(tc_core, inverse_test_1);
  tcase_add_test(tc_core, inverse_test_2);
  tcase_add_test(tc_core, inverse_test_3);
  tcase_add_test(tc_core, inverse_test_4);
  tcase_add_test(tc_core, inverse_test_5);
  tcase_add_test(tc_core, inverse_test_6);
  tcase_add_test(tc_core, inverse_test_7);
  tcase_add_test(tc_core, inverse_test_8);
  tcase_add_test(tc_core, inverse_test_9);
  tcase_add_test(tc_core, inverse_test_10);
  tcase_add_test(tc_core, inverse_test_11);
  tcase_add_test(tc_core, inverse_test_12);
  tcase_add_test(tc_core, inverse_test_13);

  tcase_add_test(tc_core, inverse_test_incorrect);
  tcase_add_test(tc_core, inverse_test_correct);
  tcase_add_test(tc_core, inverse_test_zero_det);
  tcase_add_test(tc_core, inverse_test_one_by_one);

  suite_add_tcase(s, tc_core);
  return s;
}
