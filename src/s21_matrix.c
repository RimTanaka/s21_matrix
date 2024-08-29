#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (result == NULL || rows <= 0 || columns <= 0) return Err_Incorrect_Matrix;
  int flag = OK;

  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)malloc(rows * sizeof(double *));

  if (result->matrix == NULL) flag = Err_Incorrect_Matrix;

  for (int i = 0; i < rows && !flag; i++) {
    result->matrix[i] = (double *)malloc(columns * sizeof(double));
    if (result->matrix[i] == NULL) {
      s21_remove_matrix(result);
      flag = Err_Incorrect_Matrix;
    }
    for (int j = 0; j < columns && !flag; j++) result->matrix[i][j] = 0.;
  }

  return flag;
}

// debug
/*
int s21_print_matrix(matrix_t *result) {
  if (result == NULL || result->matrix == NULL || result->rows <= 0 ||
      result->columns <= 0)
    return Err_Incorrect_Matrix;

  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      printf("%.6lf ", result->matrix[i][j]);
    }
    printf("\n");
  }

  return 0;
}
*/

void s21_remove_matrix(matrix_t *A) {
  if (A == NULL || A->matrix == NULL || A->rows <= 0 || A->columns <= 0) return;

  for (int i = 0; i < A->rows; i++) {
    if (A->matrix[i] != NULL) free(A->matrix[i]);
  }

  free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL ||
      A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0)
    return FAILURE;

  int flag = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns) flag = FAILURE;

  for (int i = 0; i < A->rows && flag; i++) {
    for (int j = 0; j < A->columns && flag; j++) {
      if (round(A->matrix[i][j] * 10000000) !=
          round(B->matrix[i][j] * 10000000))
        flag = FAILURE;
    }
  }

  return flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL || A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
      B->columns <= 0)
    return Err_Incorrect_Matrix;

  int flag = OK;
  if (A->rows != B->rows || A->columns != B->columns) flag = Err_Calculation;
  if (!flag) flag = s21_create_matrix(B->rows, B->columns, result);

  for (int i = 0; i < A->rows && !flag; i++) {
    for (int j = 0; j < A->columns && !flag; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }

  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL || A->matrix == NULL ||
      B->matrix == NULL || A->rows <= 0 || A->columns <= 0 || B->rows <= 0 ||
      B->columns <= 0)
    return Err_Incorrect_Matrix;

  int flag = OK;
  if (A->rows != B->rows || A->columns != B->columns) flag = Err_Calculation;
  if (!flag) flag = s21_create_matrix(B->rows, B->columns, result);

  for (int i = 0; i < A->rows && !flag; i++) {
    for (int j = 0; j < A->columns && !flag; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }

  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0)
    return Err_Incorrect_Matrix;

  int flag = OK;
  flag = s21_create_matrix(A->rows, A->columns, result);

  int rows = A->rows;
  int columns = A->columns;
  for (int i = 0; i < rows && !flag; i++) {
    for (int j = 0; j < columns && !flag; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }

  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL || A->rows <= 0 ||
      A->columns <= 0 || B->rows <= 0 || B->columns <= 0)
    return Err_Incorrect_Matrix;

  int flag = OK;
  if (A->columns != B->rows) flag = Err_Calculation;
  if (!flag) flag = s21_create_matrix(A->rows, B->columns, result);

  for (int k = 0; k < A->columns && !flag; k++) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return flag;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0)
    return Err_Incorrect_Matrix;

  int flag = OK;
  flag = s21_create_matrix(A->columns, A->rows, result);

  int rows = A->rows;
  int columns = A->columns;
  for (int i = 0; i < rows && !flag; i++) {
    for (int j = 0; j < columns && !flag; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }

  return flag;
}

int s21_minor(matrix_t *A, int rows, int columns, matrix_t *result) {
  if (A == NULL || result == NULL || A->rows <= 1 || A->columns <= 1)
    return Err_Incorrect_Matrix;

  int flag = OK;
  if (A->columns != A->rows) flag = Err_Calculation;

  int ro = 0;
  for (int i = 0; i < A->rows && !flag; i++) {
    if (i == rows) continue;
    int co = 0;
    for (int j = 0; j < A->columns && !flag; j++) {
      if (j == columns) continue;
      result->matrix[ro][co] = A->matrix[i][j];
      co++;
    }
    ro++;
  }
  return flag;
}

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0)
    return Err_Incorrect_Matrix;

  int flag = OK;
  if (A->columns != A->rows) flag = Err_Calculation;

  if (A->rows == 1) {
    *result = A->matrix[0][0];
    return flag;
  }

  if (A->rows == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    return flag;
  }

  double det = 0.0;
  for (int j = 0; j < A->rows && !flag; j++) {
    matrix_t tmp;
    flag = s21_create_matrix(A->columns - 1, A->rows - 1, &tmp);

    if (!flag) flag = s21_minor(A, j, 0, &tmp);
    double minor_det = 0.0;
    if (!flag && !s21_determinant(&tmp, &minor_det)) {
      det += A->matrix[j][0] * ((j % 2 == 0) ? 1.0 : -1.0) * minor_det;
    }
    s21_remove_matrix(&tmp);
  }
  *result = det;

  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0)
    return Err_Incorrect_Matrix;

  int flag = OK;
  if (A->columns != A->rows) flag = Err_Calculation;

  if (!flag) flag = s21_create_matrix(A->rows, A->columns, result);

  for (int j = 0; j < A->rows && !flag; j++) {
    for (int i = 0; i < A->columns && !flag; i++) {
      matrix_t tmp;
      flag = s21_create_matrix(A->columns - 1, A->rows - 1, &tmp);

      if (!flag) flag = s21_minor(A, j, i, &tmp);
      // s21_print_matrix(&tmp);
      double minor_det = 0;
      if (!flag && !s21_determinant(&tmp, &minor_det)) {
        result->matrix[j][i] = ((j + i) % 2 == 0) ? minor_det : -minor_det;
      }
      s21_remove_matrix(&tmp);
    }
  }

  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->rows <= 0 || A->columns <= 0)
    return Err_Incorrect_Matrix;

  int flag = OK;
  if (A->columns != A->rows) flag = Err_Calculation;

  if (!flag && A->rows == 1) {
    if (A->matrix[0][0] != 0 && fabs(A->matrix[0][0]) > 1e-6) {
      flag = s21_create_matrix(A->rows, A->rows, result);
      result->matrix[0][0] = 1.0 / A->matrix[0][0];
    } else
      flag = Err_Calculation;
  } else {
    double det = 0;
    if (!flag) flag = s21_determinant(A, &det);
    if (!det && fabs(det) < 1e-6) flag = Err_Calculation;

    matrix_t tmp_calc = {0};
    if (!flag) flag = s21_calc_complements(A, &tmp_calc);

    matrix_t tmp_tranpose = {0};

    if (!flag) flag = s21_transpose(&tmp_calc, &tmp_tranpose);
    s21_remove_matrix(&tmp_calc);

    if (!flag) flag = s21_mult_number(&tmp_tranpose, 1.0 / det, result);
    s21_remove_matrix(&tmp_tranpose);
  }
  return flag;
}
