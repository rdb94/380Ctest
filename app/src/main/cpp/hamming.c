/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: hamming.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "hamming.h"
#include "analyse_periodecity_data.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "gencoswin.h"
#include "indexShapeCheck.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double varargin_1
 *                emxArray_real_T *w
 * Return Type  : void
 */
void hamming(double varargin_1, emxArray_real_T *w)
{
  emxArray_real_T *b_w;
  double L;
  double *b_w_data;
  double *c_w_data;
  int i;
  int i1;
  int trivialwin;
  int w_size;
  signed char w_data;
  w_size = 1;
  w_data = 0;
  trivialwin = 0;
  if (varargin_1 == floor(varargin_1)) {
    L = varargin_1;
  } else {
    L = rt_roundd_snf(varargin_1);
  }
  if (L == 0.0) {
    w_size = 0;
    trivialwin = 1;
  } else if (L == 1.0) {
    w_data = 1;
    trivialwin = 1;
  }
  i = w->size[0];
  w->size[0] = w_size;
  emxEnsureCapacity_real_T(w, i);
  b_w_data = w->data;
  for (i = 0; i < w_size; i++) {
    b_w_data[0] = w_data;
  }
  if (trivialwin == 0) {
    double r;
    emxInit_real_T(&b_w, 1);
    if ((L + 1.0) - (L + 1.0) != 0.0) {
      k_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
    }
    r = fmod(L + 1.0, 2.0);
    if (r == 0.0) {
      r = 0.0;
    }
    if (r == 0.0) {
      int iv[2];
      int b_loop_ub;
      int loop_ub;
      c_calc_window((L + 1.0) / 2.0, L + 1.0, w);
      b_w_data = w->data;
      if (w->size[0] < 2) {
        i = 0;
        w_size = 1;
        i1 = -1;
      } else {
        i = w->size[0] - 1;
        w_size = -1;
        i1 = 1;
      }
      iv[0] = 1;
      trivialwin = div_s32(i1 - i, w_size);
      iv[1] = trivialwin + 1;
      indexShapeCheck(w->size[0], iv);
      loop_ub = (w->size[0] + trivialwin) + 1;
      i1 = b_w->size[0];
      b_w->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_w, i1);
      c_w_data = b_w->data;
      b_loop_ub = w->size[0];
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        c_w_data[i1] = b_w_data[i1];
      }
      for (i1 = 0; i1 <= trivialwin; i1++) {
        c_w_data[i1 + w->size[0]] = b_w_data[i + w_size * i1];
      }
      i = w->size[0];
      w->size[0] = loop_ub;
      emxEnsureCapacity_real_T(w, i);
      b_w_data = w->data;
      for (i = 0; i < loop_ub; i++) {
        b_w_data[i] = c_w_data[i];
      }
    } else {
      int iv[2];
      int b_loop_ub;
      int loop_ub;
      c_calc_window(((L + 1.0) + 1.0) / 2.0, L + 1.0, w);
      b_w_data = w->data;
      if (w->size[0] - 1 < 2) {
        i = 0;
        w_size = 1;
        i1 = -1;
      } else {
        if ((w->size[0] - 1 < 1) || (w->size[0] - 1 > w->size[0])) {
          rtDynamicBoundsError(w->size[0] - 1, 1, w->size[0], &b_emlrtBCI);
        }
        i = w->size[0] - 2;
        w_size = -1;
        if (w->size[0] < 2) {
          rtDynamicBoundsError(2, 1, w->size[0], &emlrtBCI);
        }
        i1 = 1;
      }
      iv[0] = 1;
      trivialwin = div_s32(i1 - i, w_size);
      iv[1] = trivialwin + 1;
      indexShapeCheck(w->size[0], iv);
      loop_ub = (w->size[0] + trivialwin) + 1;
      i1 = b_w->size[0];
      b_w->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_w, i1);
      c_w_data = b_w->data;
      b_loop_ub = w->size[0];
      for (i1 = 0; i1 < b_loop_ub; i1++) {
        c_w_data[i1] = b_w_data[i1];
      }
      for (i1 = 0; i1 <= trivialwin; i1++) {
        c_w_data[i1 + w->size[0]] = b_w_data[i + w_size * i1];
      }
      i = w->size[0];
      w->size[0] = loop_ub;
      emxEnsureCapacity_real_T(w, i);
      b_w_data = w->data;
      for (i = 0; i < loop_ub; i++) {
        b_w_data[i] = c_w_data[i];
      }
    }
    emxFree_real_T(&b_w);
  }
}

/*
 * File trailer for hamming.c
 *
 * [EOF]
 */
