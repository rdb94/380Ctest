/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: movmedian.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "movmedian.h"
#include "SortedBuffer.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_internal_types.h"
#include "analyse_periodecity_types.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void movmedian(const emxArray_real_T *x, emxArray_real_T *y)
{
  coder_internal_SortedBuffer s;
  const double *x_data;
  double *y_data;
  int iLeftLast;
  int k;
  int loop_ub;
  x_data = x->data;
  loop_ub = x->size[0];
  iLeftLast = y->size[0];
  y->size[0] = x->size[0];
  emxEnsureCapacity_real_T(y, iLeftLast);
  y_data = y->data;
  for (iLeftLast = 0; iLeftLast < loop_ub; iLeftLast++) {
    y_data[iLeftLast] = 0.0;
  }
  if (x->size[0] != 0) {
    double xnew;
    double xold;
    int iRightLast;
    xold = 0.0;
    xnew = 0.0;
    s.buf[0] = 0.0;
    s.buf[1] = 0.0;
    s.buf[2] = 0.0;
    s.nbuf = 0;
    s.nnans = 0;
    iRightLast = x->size[0];
    if (iRightLast > 2) {
      iRightLast = 2;
    }
    iLeftLast = 1;
    for (k = 1; k <= iRightLast; k++) {
      SortedBuffer_insert(&s, x_data[k - 1]);
    }
    y_data[0] = SortedBuffer_median(s.buf, s.nbuf, s.nnans);
    if (x->size[0] < 3) {
      for (k = 2; k <= loop_ub; k++) {
        int iRight;
        boolean_T b_remove;
        boolean_T guard1;
        boolean_T insert;
        if (k + 1 > loop_ub) {
          iRight = loop_ub;
        } else {
          iRight = 2;
        }
        if (k - 1 > iLeftLast) {
          xold = x_data[iLeftLast - 1];
          b_remove = true;
          iLeftLast = k - 1;
        } else {
          b_remove = false;
        }
        guard1 = false;
        if (iRight > iRightLast) {
          xnew = x_data[iRight - 1];
          insert = true;
          iRightLast = iRight;
          if (b_remove) {
            SortedBuffer_replace(&s, xold, xnew);
          } else {
            guard1 = true;
          }
        } else {
          insert = false;
          guard1 = true;
        }
        if (guard1) {
          if (insert) {
            SortedBuffer_insert(&s, xnew);
          } else if (b_remove) {
            SortedBuffer_remove(&s, xold);
          }
        }
        y_data[k - 1] = SortedBuffer_median(s.buf, s.nbuf, s.nnans);
      }
    } else {
      iLeftLast = x->size[0] - 1;
      SortedBuffer_insert(&s, x_data[2]);
      y_data[1] = SortedBuffer_median(s.buf, s.nbuf, s.nnans);
      for (k = 3; k <= iLeftLast; k++) {
        SortedBuffer_replace(&s, x_data[k - 3], x_data[k]);
        y_data[k - 1] = SortedBuffer_median(s.buf, s.nbuf, s.nnans);
      }
      if (x->size[0] > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = loop_ub; k <= loop_ub; k++) {
        SortedBuffer_remove(&s, x_data[k - 3]);
        y_data[k - 1] = SortedBuffer_median(s.buf, s.nbuf, s.nnans);
      }
    }
  }
}

/*
 * File trailer for movmedian.c
 *
 * [EOF]
 */
