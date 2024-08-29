#include "test.h"

int main() {
  srand(time(NULL));
  int all = 0, successed = 0, failed = 0;
  Suite *suite[] = {s21_create_matrix_suite(),  s21_remove_matrix_suite(),
                    s21_eq_matrix_suite(),      s21_sum_matrix_suite(),
                    s21_sub_matrix_suite(),     s21_mult_number_suite(),
                    s21_mult_matrix_suite(),    s21_transpose_suite(),
                    s21_determinant_suite(),    s21_calc_complements_suite(),
                    s21_inverse_matrix_suite(), NULL};

  for (int i = 0; suite[i] != NULL; i++) {
    SRunner *sr = srunner_create(suite[i]);
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);
    all += srunner_ntests_run(sr);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }

  successed = all - failed;

  printf(
      "========= ALL: %d ========= SUCCESSED: %d ========= FAILED: %d "
      "=========\n",
      all, successed, failed);
  return failed == 0 ? 0 : 1;
}
