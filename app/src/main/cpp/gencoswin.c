/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: gencoswin.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "gencoswin.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : double m
 *                double n
 *                emxArray_real_T *w
 * Return Type  : void
 */
void b_calc_window(double m, double n, emxArray_real_T *w)
{
  static rtEqualityCheckInfo
      emlrtECI =
          {
              -1,            /* nDims */
              89,            /* lineNo */
              13,            /* colNo */
              "calc_window", /* fName */
              "C:\\Program "
              "Files\\MATLAB\\R2024a\\toolbox\\signal\\signal\\private\\gencosw"
              "in.m" /* pName */
          };
  __m128d r;
  emxArray_real_T *x;
  emxArray_real_T *y;
  double *w_data;
  double *x_data;
  int i;
  int loop_ub;
  int scalarLB;
  int vectorUB;
  emxInit_real_T(&y, 2);
  w_data = y->data;
  if (rtIsNaN(m - 1.0)) {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i);
    w_data = y->data;
    w_data[0] = rtNaN;
  } else if (m - 1.0 < 0.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(m - 1.0) + 1;
    emxEnsureCapacity_real_T(y, i);
    w_data = y->data;
    loop_ub = (int)(m - 1.0);
    for (i = 0; i <= loop_ub; i++) {
      w_data[i] = i;
    }
  }
  emxInit_real_T(&x, 1);
  loop_ub = y->size[1];
  i = x->size[0];
  x->size[0] = y->size[1];
  emxEnsureCapacity_real_T(x, i);
  x_data = x->data;
  scalarLB = (y->size[1] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    r = _mm_loadu_pd(&w_data[i]);
    _mm_storeu_pd(&x_data[i], _mm_div_pd(r, _mm_set1_pd(n - 1.0)));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    x_data[i] = w_data[i] / (n - 1.0);
  }
  emxFree_real_T(&y);
  loop_ub = x->size[0];
  i = w->size[0];
  w->size[0] = x->size[0];
  emxEnsureCapacity_real_T(w, i);
  w_data = w->data;
  scalarLB = (x->size[0] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    r = _mm_loadu_pd(&x_data[i]);
    _mm_storeu_pd(&w_data[i], _mm_mul_pd(_mm_set1_pd(6.2831853071795862), r));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    w_data[i] = 6.2831853071795862 * x_data[i];
  }
  loop_ub = w->size[0];
  if (w->size[0] > 2147483646) {
    check_forloop_overflow_error();
  }
  for (scalarLB = 0; scalarLB < loop_ub; scalarLB++) {
    w_data[scalarLB] = cos(w_data[scalarLB]);
  }
  scalarLB = (w->size[0] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    r = _mm_loadu_pd(&w_data[i]);
    _mm_storeu_pd(&w_data[i], _mm_mul_pd(_mm_set1_pd(0.5), r));
    r = _mm_loadu_pd(&x_data[i]);
    _mm_storeu_pd(&x_data[i], _mm_mul_pd(_mm_set1_pd(12.566370614359172), r));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    w_data[i] *= 0.5;
    x_data[i] *= 12.566370614359172;
  }
  loop_ub = x->size[0];
  if (x->size[0] > 2147483646) {
    check_forloop_overflow_error();
  }
  for (scalarLB = 0; scalarLB < loop_ub; scalarLB++) {
    x_data[scalarLB] = cos(x_data[scalarLB]);
  }
  scalarLB = (x->size[0] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    r = _mm_loadu_pd(&x_data[i]);
    _mm_storeu_pd(&x_data[i], _mm_mul_pd(_mm_set1_pd(0.08), r));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    x_data[i] *= 0.08;
  }
  loop_ub = w->size[0];
  if (w->size[0] != x->size[0]) {
    rtSizeEq1DError(w->size[0], x->size[0], &emlrtECI);
  }
  scalarLB = (w->size[0] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    __m128d r1;
    r = _mm_loadu_pd(&w_data[i]);
    r1 = _mm_loadu_pd(&x_data[i]);
    _mm_storeu_pd(&w_data[i], _mm_add_pd(_mm_sub_pd(_mm_set1_pd(0.42), r), r1));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    w_data[i] = (0.42 - w_data[i]) + x_data[i];
  }
  emxFree_real_T(&x);
  if (w->size[0] != 0) {
    w_data[0] = 0.0;
  }
}

/*
 * Arguments    : double m
 *                double n
 *                emxArray_real_T *w
 * Return Type  : void
 */
void c_calc_window(double m, double n, emxArray_real_T *w)
{
  __m128d r;
  emxArray_real_T *y;
  double *w_data;
  double *y_data;
  int i;
  int loop_ub;
  int scalarLB;
  int vectorUB;
  emxInit_real_T(&y, 2);
  y_data = y->data;
  if (rtIsNaN(m - 1.0)) {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    y_data[0] = rtNaN;
  } else if (m - 1.0 < 0.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(m - 1.0) + 1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    loop_ub = (int)(m - 1.0);
    for (i = 0; i <= loop_ub; i++) {
      y_data[i] = i;
    }
  }
  loop_ub = y->size[1];
  i = w->size[0];
  w->size[0] = y->size[1];
  emxEnsureCapacity_real_T(w, i);
  w_data = w->data;
  scalarLB = (y->size[1] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    r = _mm_loadu_pd(&y_data[i]);
    _mm_storeu_pd(&w_data[i], _mm_mul_pd(_mm_set1_pd(6.2831853071795862),
                                         _mm_div_pd(r, _mm_set1_pd(n - 1.0))));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    w_data[i] = 6.2831853071795862 * (y_data[i] / (n - 1.0));
  }
  emxFree_real_T(&y);
  loop_ub = w->size[0];
  if (w->size[0] > 2147483646) {
    check_forloop_overflow_error();
  }
  for (scalarLB = 0; scalarLB < loop_ub; scalarLB++) {
    w_data[scalarLB] = cos(w_data[scalarLB]);
  }
  scalarLB = (w->size[0] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    r = _mm_loadu_pd(&w_data[i]);
    _mm_storeu_pd(&w_data[i], _mm_sub_pd(_mm_set1_pd(0.54),
                                         _mm_mul_pd(_mm_set1_pd(0.46), r)));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    w_data[i] = 0.54 - 0.46 * w_data[i];
  }
}

/*
 * Arguments    : double m
 *                double n
 *                emxArray_real_T *w
 * Return Type  : void
 */
void calc_window(double m, double n, emxArray_real_T *w)
{
  __m128d r;
  emxArray_real_T *y;
  double *w_data;
  double *y_data;
  int i;
  int loop_ub;
  int scalarLB;
  int vectorUB;
  emxInit_real_T(&y, 2);
  y_data = y->data;
  if (rtIsNaN(m - 1.0)) {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    y_data[0] = rtNaN;
  } else if (m - 1.0 < 0.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)(m - 1.0) + 1;
    emxEnsureCapacity_real_T(y, i);
    y_data = y->data;
    loop_ub = (int)(m - 1.0);
    for (i = 0; i <= loop_ub; i++) {
      y_data[i] = i;
    }
  }
  loop_ub = y->size[1];
  i = w->size[0];
  w->size[0] = y->size[1];
  emxEnsureCapacity_real_T(w, i);
  w_data = w->data;
  scalarLB = (y->size[1] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    r = _mm_loadu_pd(&y_data[i]);
    _mm_storeu_pd(&w_data[i], _mm_mul_pd(_mm_set1_pd(6.2831853071795862),
                                         _mm_div_pd(r, _mm_set1_pd(n - 1.0))));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    w_data[i] = 6.2831853071795862 * (y_data[i] / (n - 1.0));
  }
  emxFree_real_T(&y);
  loop_ub = w->size[0];
  if (w->size[0] > 2147483646) {
    check_forloop_overflow_error();
  }
  for (scalarLB = 0; scalarLB < loop_ub; scalarLB++) {
    w_data[scalarLB] = cos(w_data[scalarLB]);
  }
  scalarLB = (w->size[0] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    __m128d r1;
    r = _mm_loadu_pd(&w_data[i]);
    r1 = _mm_set1_pd(0.5);
    _mm_storeu_pd(&w_data[i], _mm_sub_pd(r1, _mm_mul_pd(r1, r)));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    w_data[i] = 0.5 - 0.5 * w_data[i];
  }
}

/*
 * File trailer for gencoswin.c
 *
 * [EOF]
 */
