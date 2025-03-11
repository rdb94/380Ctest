/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: colon.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "colon.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double a
 *                double b
 *                emxArray_real_T *y
 * Return Type  : void
 */
void eml_float_colon(double a, double b, emxArray_real_T *y)
{
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      419,              /* lineNo */
      "assert_pmaxsize" /* fName */
  };
  double apnd;
  double cdiff;
  double ndbl;
  double *y_data;
  int k;
  int n;
  int nm1d2;
  ndbl = floor((b - a) + 0.5);
  apnd = a + ndbl;
  cdiff = apnd - b;
  if (fabs(cdiff) < 4.4408920985006262E-16 * fmax(fabs(a), fabs(b))) {
    ndbl++;
    apnd = b;
  } else if (cdiff > 0.0) {
    apnd = a + (ndbl - 1.0);
  } else {
    ndbl++;
  }
  if (ndbl >= 0.0) {
    n = (int)ndbl;
  } else {
    n = 0;
  }
  if (ndbl > 2.147483647E+9) {
    i_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  nm1d2 = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_real_T(y, nm1d2);
  y_data = y->data;
  if (n > 0) {
    y_data[0] = a;
    if (n > 1) {
      y_data[n - 1] = apnd;
      nm1d2 = (n - 1) / 2;
      for (k = 0; k <= nm1d2 - 2; k++) {
        y_data[k + 1] = a + ((double)k + 1.0);
        y_data[(n - k) - 2] = apnd - ((double)k + 1.0);
      }
      if (nm1d2 << 1 == n - 1) {
        y_data[nm1d2] = (a + apnd) / 2.0;
      } else {
        y_data[nm1d2] = a + (double)nm1d2;
        y_data[nm1d2 + 1] = apnd - (double)nm1d2;
      }
    }
  }
}

/*
 * File trailer for colon.c
 *
 * [EOF]
 */
