/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: linspace.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "linspace.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_types.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static void ib_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                    int aLineNum);

/* Function Definitions */
/*
 * Arguments    : const char *r
 *                const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void ib_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                    int aLineNum)
{
  fprintf(stderr, "For code generation, %.*s must not be NaN.", 1, r);
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : double d2
 *                double n
 *                emxArray_real_T *y
 * Return Type  : void
 */
void linspace(double d2, double n, emxArray_real_T *y)
{
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      33,        /* lineNo */
      "linspace" /* fName */
  };
  double *y_data;
  int k;
  if (!(n >= 0.0)) {
    ib_rtErrorWithMessageID("N", n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  } else {
    int i;
    int y_tmp;
    y_tmp = y->size[0] * y->size[1];
    y->size[0] = 1;
    i = (int)floor(n);
    y->size[1] = i;
    emxEnsureCapacity_real_T(y, y_tmp);
    y_data = y->data;
    y_tmp = i - 1;
    y_data[i - 1] = d2;
    if (y->size[1] >= 2) {
      y_data[0] = 0.0;
      if (y->size[1] >= 3) {
        if (-d2 == 0.0) {
          double delta1;
          delta1 = d2 / ((double)y->size[1] - 1.0);
          for (k = 2; k <= y_tmp; k++) {
            y_data[k - 1] = (double)(((k << 1) - y->size[1]) - 1) * delta1;
          }
          if ((y->size[1] & 1) == 1) {
            y_data[y->size[1] >> 1] = 0.0;
          }
        } else if ((d2 < 0.0) && (fabs(d2) > 8.9884656743115785E+307)) {
          double delta1;
          delta1 = d2 / ((double)y->size[1] - 1.0);
          for (k = 0; k <= i - 3; k++) {
            y_data[k + 1] = delta1 * ((double)k + 1.0);
          }
        } else {
          double delta1;
          delta1 = d2 / ((double)y->size[1] - 1.0);
          for (k = 0; k <= i - 3; k++) {
            y_data[k + 1] = ((double)k + 1.0) * delta1;
          }
        }
      }
    }
  }
}

/*
 * File trailer for linspace.c
 *
 * [EOF]
 */
