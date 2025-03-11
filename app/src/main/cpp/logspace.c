/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: logspace.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "logspace.h"
#include "analyse_periodecity_data.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double d2
 *                double n
 *                emxArray_real_T *y
 * Return Type  : void
 */
void logspace(double d2, double n, emxArray_real_T *y)
{
  double delta1;
  double *y_data;
  int i;
  int k;
  int y_tmp_tmp;
  if ((!(n >= 1.0)) || (!(floor(n) == n))) {
    u_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  i = (int)n;
  y->size[1] = (int)n;
  emxEnsureCapacity_real_T(y, k);
  y_data = y->data;
  if ((int)n >= 1) {
    y_tmp_tmp = (int)n - 1;
    y_data[(int)n - 1] = d2;
    if (y->size[1] >= 2) {
      y_data[0] = 1.0;
      if (y->size[1] >= 3) {
        if (-d2 == 1.0) {
          delta1 = d2 / ((double)y->size[1] - 1.0);
          for (k = 2; k <= y_tmp_tmp; k++) {
            y_data[k - 1] = (double)(((k << 1) - y->size[1]) - 1) * delta1;
          }
          if ((y->size[1] & 1) == 1) {
            y_data[y->size[1] >> 1] = 0.0;
          }
        } else if ((d2 < 0.0) && (fabs(d2) > 8.9884656743115785E+307)) {
          double delta2;
          delta1 = 1.0 / ((double)y->size[1] - 1.0);
          delta2 = d2 / ((double)y->size[1] - 1.0);
          for (k = 0; k <= i - 3; k++) {
            y_data[k + 1] =
                (delta2 * ((double)k + 1.0) + 1.0) - delta1 * ((double)k + 1.0);
          }
        } else {
          delta1 = (d2 - 1.0) / ((double)y->size[1] - 1.0);
          for (k = 0; k <= i - 3; k++) {
            y_data[k + 1] = ((double)k + 1.0) * delta1 + 1.0;
          }
        }
      }
    }
  }
  k = y->size[0] * y->size[1];
  y->size[0] = 1;
  emxEnsureCapacity_real_T(y, k);
  y_data = y->data;
  y_tmp_tmp = y->size[1] - 1;
  for (k = 0; k <= y_tmp_tmp; k++) {
    delta1 = y_data[k];
    y_data[k] = rt_powd_snf(10.0, delta1);
  }
}

/*
 * File trailer for logspace.c
 *
 * [EOF]
 */
