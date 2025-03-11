/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: NCF.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "NCF.h"
#include "FFTImplementationCallback.h"
#include "analyse_periodecity_data.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "eml_int_forloop_overflow_check.h"
#include "fft.h"
#include "getCandidates.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *y
 *                double fs
 *                emxArray_real_T *f0
 * Return Type  : void
 */
void NCF(const emxArray_real_T *y, double fs, emxArray_real_T *f0)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      26,    /* lineNo */
      15,    /* colNo */
      "",    /* aName */
      "NCF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\NCF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo d_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      31,    /* lineNo */
      16,    /* colNo */
      "",    /* aName */
      "NCF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\NCF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo e_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      27,    /* lineNo */
      16,    /* colNo */
      "",    /* aName */
      "NCF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\NCF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo f_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      27,    /* lineNo */
      37,    /* colNo */
      "",    /* aName */
      "NCF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\NCF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo g_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      26,    /* lineNo */
      41,    /* colNo */
      "",    /* aName */
      "NCF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\NCF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo h_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      26,    /* lineNo */
      43,    /* colNo */
      "",    /* aName */
      "NCF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\NCF.m", /* pName */
      0               /* checkKind */
  };
  static rtDoubleCheckInfo e_emlrtDCI = {
      26,   /* lineNo */
      "NCF" /* fName */
  };
  static rtDoubleCheckInfo f_emlrtDCI = {
      31,   /* lineNo */
      "NCF" /* fName */
  };
  static rtDoubleCheckInfo g_emlrtDCI = {
      37,   /* lineNo */
      "NCF" /* fName */
  };
  static rtDoubleCheckInfo h_emlrtDCI = {
      37,   /* lineNo */
      "NCF" /* fName */
  };
  static rtDoubleCheckInfo i_emlrtDCI = {
      27,   /* lineNo */
      "NCF" /* fName */
  };
  static rtDoubleCheckInfo j_emlrtDCI = {
      26,   /* lineNo */
      "NCF" /* fName */
  };
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      13,    /* lineNo */
      "sqrt" /* fName */
  };
  __m128d r;
  emxArray_creal_T *x;
  emxArray_real_T *Rt;
  emxArray_real_T *c1;
  emxArray_real_T *peak;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  emxArray_real_T *varargin_1;
  emxArray_real_T *yRMS;
  creal_T *x_data;
  double edge[2];
  double f;
  double m2;
  double mxl;
  double *Rt_data;
  double *c1_data;
  double *varargin_1_data;
  double *yRMS_data;
  int acoef;
  int b_acoef;
  int csz_idx_1;
  int i;
  int i1;
  int i2;
  int k;
  int loop_ub;
  int nx;
  int sizes_idx_0;
  boolean_T b;
  boolean_T empty_non_axis_sizes;
  boolean_T useRadix2;
  edge[0] = rt_roundd_snf(fs / 200.0);
  edge[1] = rt_roundd_snf(fs / 70.0);
  mxl = fmin(edge[1], (double)y->size[0] - 1.0);
  f = frexp(fabs(2.0 * (double)y->size[0] - 1.0), &nx);
  if (f == 0.5) {
    nx--;
  }
  m2 = rt_powd_snf(2.0, nx);
  emxInit_real_T(&c1, 2);
  emxInit_creal_T(&x, 2);
  b_fft(y, m2, x);
  x_data = x->data;
  nx = x->size[0] * x->size[1];
  i = c1->size[0] * c1->size[1];
  c1->size[0] = x->size[0];
  c1->size[1] = x->size[1];
  emxEnsureCapacity_real_T(c1, i);
  c1_data = c1->data;
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < nx; k++) {
    c1_data[k] = rt_hypotd_snf(x_data[k].re, x_data[k].im);
  }
  acoef = c1->size[0] * c1->size[1];
  for (i = 0; i < acoef; i++) {
    f = c1_data[i];
    c1_data[i] = f * f;
  }
  emxInit_real_T(&yRMS, 2);
  yRMS_data = yRMS->data;
  if ((c1->size[0] == 0) || (c1->size[1] == 0)) {
    i = x->size[0] * x->size[1];
    x->size[0] = c1->size[0];
    x->size[1] = c1->size[1];
    emxEnsureCapacity_creal_T(x, i);
    x_data = x->data;
    acoef = c1->size[0] * c1->size[1];
    for (i = 0; i < acoef; i++) {
      x_data[i].re = 0.0;
      x_data[i].im = 0.0;
    }
  } else {
    useRadix2 = ((c1->size[0] & (c1->size[0] - 1)) == 0);
    nx = c_FFTImplementationCallback_get(c1->size[0], useRadix2, &b_acoef);
    emxInit_real_T(&sintab, 2);
    emxInit_real_T(&sintabinv, 2);
    d_FFTImplementationCallback_gen(b_acoef, useRadix2, yRMS, sintab,
                                    sintabinv);
    yRMS_data = yRMS->data;
    if (useRadix2) {
      f_FFTImplementationCallback_r2b(c1, c1->size[0], yRMS, sintab, x);
      x_data = x->data;
    } else {
      d_FFTImplementationCallback_dob(c1, nx, c1->size[0], yRMS, sintab,
                                      sintabinv, x);
      x_data = x->data;
    }
    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
  }
  f = sqrt(m2);
  i = x->size[0];
  i1 = c1->size[0] * c1->size[1];
  c1->size[0] = x->size[0];
  acoef = x->size[1];
  c1->size[1] = x->size[1];
  emxEnsureCapacity_real_T(c1, i1);
  c1_data = c1->data;
  loop_ub = x->size[0] * x->size[1];
  for (i1 = 0; i1 < loop_ub; i1++) {
    c1_data[i1] = x_data[i1].re / f;
  }
  if (mxl + 1.0 < 1.0) {
    loop_ub = 0;
  } else {
    if (x->size[0] < 1) {
      rtDynamicBoundsError(1, 1, x->size[0], &g_emlrtBCI);
    }
    if (mxl + 1.0 != (int)(mxl + 1.0)) {
      rtIntegerError(mxl + 1.0, &j_emlrtDCI);
    }
    if (((int)(mxl + 1.0) < 1) || ((int)(mxl + 1.0) > x->size[0])) {
      rtDynamicBoundsError((int)(mxl + 1.0), 1, x->size[0], &h_emlrtBCI);
    }
    loop_ub = (int)(mxl + 1.0);
  }
  if (mxl < 1.0) {
    yRMS->size[0] = 1;
    yRMS->size[1] = 0;
  } else {
    i1 = yRMS->size[0] * yRMS->size[1];
    yRMS->size[0] = 1;
    i2 = (int)mxl;
    yRMS->size[1] = i2;
    emxEnsureCapacity_real_T(yRMS, i1);
    yRMS_data = yRMS->data;
    b_acoef = i2 - 1;
    for (i1 = 0; i1 <= b_acoef; i1++) {
      yRMS_data[i1] = (double)i1 + 1.0;
    }
  }
  m2 -= mxl;
  emxInit_real_T(&varargin_1, 2);
  b_acoef = yRMS->size[1];
  i1 = varargin_1->size[0] * varargin_1->size[1];
  varargin_1->size[0] = yRMS->size[1];
  varargin_1->size[1] = x->size[1];
  emxEnsureCapacity_real_T(varargin_1, i1);
  varargin_1_data = varargin_1->data;
  for (i1 = 0; i1 < acoef; i1++) {
    for (i2 = 0; i2 < b_acoef; i2++) {
      f = m2 + yRMS_data[i2];
      if (f != (int)floor(f)) {
        rtIntegerError(f, &e_emlrtDCI);
      }
      if (((int)f < 1) || ((int)f > i)) {
        rtDynamicBoundsError((int)f, 1, i, &c_emlrtBCI);
      }
      varargin_1_data[i2 + varargin_1->size[0] * i1] =
          c1_data[((int)f + c1->size[0] * i1) - 1];
    }
  }
  useRadix2 = ((yRMS->size[1] != 0) && (c1->size[1] != 0));
  if (useRadix2) {
    b_acoef = x->size[1];
  } else if ((loop_ub != 0) && (c1->size[1] != 0)) {
    b_acoef = x->size[1];
  } else {
    b_acoef = x->size[1];
    if (c1->size[1] > x->size[1]) {
      b_acoef = x->size[1];
    }
  }
  if ((c1->size[1] != b_acoef) &&
      ((yRMS->size[1] != 0) && (c1->size[1] != 0))) {
    t_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  if ((c1->size[1] != b_acoef) && ((loop_ub != 0) && (c1->size[1] != 0))) {
    t_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  empty_non_axis_sizes = (b_acoef == 0);
  if (empty_non_axis_sizes || useRadix2) {
    nx = yRMS->size[1];
  } else {
    nx = 0;
  }
  if (empty_non_axis_sizes || ((loop_ub != 0) && (c1->size[1] != 0))) {
    sizes_idx_0 = loop_ub;
  } else {
    sizes_idx_0 = 0;
  }
  for (i = 0; i < acoef; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      c1_data[i1 + loop_ub * i] = c1_data[i1 + c1->size[0] * i];
    }
  }
  i = c1->size[0] * c1->size[1];
  c1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(c1, i);
  c1_data = c1->data;
  emxInit_real_T(&Rt, 2);
  i = nx + sizes_idx_0;
  i1 = Rt->size[0] * Rt->size[1];
  Rt->size[0] = i;
  Rt->size[1] = b_acoef;
  emxEnsureCapacity_real_T(Rt, i1);
  Rt_data = Rt->data;
  for (i1 = 0; i1 < b_acoef; i1++) {
    for (i2 = 0; i2 < nx; i2++) {
      Rt_data[i2 + Rt->size[0] * i1] = varargin_1_data[i2 + nx * i1];
    }
    for (i2 = 0; i2 < sizes_idx_0; i2++) {
      Rt_data[(i2 + nx) + Rt->size[0] * i1] = c1_data[i2 + sizes_idx_0 * i1];
    }
  }
  f = (edge[1] + 1.0) + edge[0];
  if (f > Rt->size[0]) {
    i1 = 0;
    i2 = 0;
  } else {
    if (f != (int)f) {
      rtIntegerError(f, &i_emlrtDCI);
    }
    if (((int)f < 1) || ((int)f > i)) {
      rtDynamicBoundsError((int)f, 1, i, &e_emlrtBCI);
    }
    i1 = (int)f - 1;
    if (i < 1) {
      rtDynamicBoundsError(i, 1, i, &f_emlrtBCI);
    }
    i2 = i;
  }
  if (edge[1] + 1.0 != (int)(edge[1] + 1.0)) {
    rtIntegerError(edge[1] + 1.0, &f_emlrtDCI);
  }
  if (((int)(edge[1] + 1.0) < 1) || ((int)(edge[1] + 1.0) > i)) {
    rtDynamicBoundsError((int)(edge[1] + 1.0), 1, i, &d_emlrtBCI);
  }
  i = yRMS->size[0] * yRMS->size[1];
  yRMS->size[0] = 1;
  yRMS->size[1] = x->size[1];
  emxEnsureCapacity_real_T(yRMS, i);
  yRMS_data = yRMS->data;
  useRadix2 = false;
  for (k = 0; k < acoef; k++) {
    f = Rt_data[((int)(edge[1] + 1.0) + Rt->size[0] * k) - 1];
    yRMS_data[k] = f;
    if (useRadix2 || (f < 0.0)) {
      useRadix2 = true;
    }
  }
  if (useRadix2) {
    s_rtErrorWithMessageID(4, "sqrt", n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  if (Rt->size[1] > 2147483646) {
    check_forloop_overflow_error();
  }
  b_acoef = (Rt->size[1] / 2) << 1;
  nx = b_acoef - 2;
  for (k = 0; k <= nx; k += 2) {
    r = _mm_loadu_pd(&yRMS_data[k]);
    _mm_storeu_pd(&yRMS_data[k], _mm_sqrt_pd(r));
  }
  for (k = b_acoef; k < acoef; k++) {
    yRMS_data[k] = sqrt(yRMS_data[k]);
  }
  if (yRMS->size[1] == 1) {
    csz_idx_1 = x->size[1];
  } else if (Rt->size[1] == 1) {
    csz_idx_1 = yRMS->size[1];
  } else if (Rt->size[1] == yRMS->size[1]) {
    csz_idx_1 = x->size[1];
  } else {
    m_rtErrorWithMessageID(d_emlrtRTEI.fName, d_emlrtRTEI.lineNo);
  }
  emxFree_creal_T(&x);
  sizes_idx_0 = i2 - i1;
  i = c1->size[0] * c1->size[1];
  c1->size[0] = sizes_idx_0;
  c1->size[1] = csz_idx_1;
  emxEnsureCapacity_real_T(c1, i);
  c1_data = c1->data;
  useRadix2 = ((sizes_idx_0 != 0) && (csz_idx_1 != 0));
  if (useRadix2) {
    int bcoef;
    acoef = (Rt->size[1] != 1);
    bcoef = (yRMS->size[1] != 1);
    i = csz_idx_1 - 1;
    b_acoef = (sizes_idx_0 != 1);
    for (k = 0; k <= i; k++) {
      nx = acoef * k;
      loop_ub = bcoef * k;
      i2 = c1->size[0] - 1;
      for (csz_idx_1 = 0; csz_idx_1 <= i2; csz_idx_1++) {
        c1_data[csz_idx_1 + c1->size[0] * k] =
            Rt_data[(i1 + b_acoef * csz_idx_1) + Rt->size[0] * nx] /
            yRMS_data[loop_ub];
      }
    }
  }
  emxFree_real_T(&yRMS);
  emxFree_real_T(&Rt);
  if (!(edge[0] - 1.0 >= 0.0)) {
    rtNonNegativeError(edge[0] - 1.0, &g_emlrtDCI);
  }
  if (edge[0] - 1.0 != (int)(edge[0] - 1.0)) {
    rtIntegerError(edge[0] - 1.0, &h_emlrtDCI);
  }
  b = (((int)(edge[0] - 1.0) != 0) && (c1->size[1] != 0));
  if (b) {
    b_acoef = c1->size[1];
  } else if (useRadix2) {
    b_acoef = c1->size[1];
  } else {
    b_acoef = c1->size[1];
  }
  if ((c1->size[1] != b_acoef) &&
      (((int)(edge[0] - 1.0) != 0) && (c1->size[1] != 0))) {
    t_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  if ((c1->size[1] != b_acoef) && ((c1->size[0] != 0) && (c1->size[1] != 0))) {
    t_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  empty_non_axis_sizes = (b_acoef == 0);
  if (empty_non_axis_sizes || b) {
    nx = (int)(edge[0] - 1.0);
  } else {
    nx = 0;
  }
  if ((!empty_non_axis_sizes) && (!useRadix2)) {
    sizes_idx_0 = 0;
  }
  i = varargin_1->size[0] * varargin_1->size[1];
  varargin_1->size[0] = nx + sizes_idx_0;
  varargin_1->size[1] = b_acoef;
  emxEnsureCapacity_real_T(varargin_1, i);
  varargin_1_data = varargin_1->data;
  for (i = 0; i < b_acoef; i++) {
    for (i1 = 0; i1 < nx; i1++) {
      varargin_1_data[i1 + varargin_1->size[0] * i] = 0.0;
    }
    for (i1 = 0; i1 < sizes_idx_0; i1++) {
      varargin_1_data[(i1 + nx) + varargin_1->size[0] * i] =
          c1_data[i1 + sizes_idx_0 * i];
    }
  }
  emxFree_real_T(&c1);
  emxInit_real_T(&peak, 1);
  getCandidates(varargin_1, edge, peak, f0);
  c1_data = f0->data;
  emxFree_real_T(&varargin_1);
  emxFree_real_T(&peak);
  acoef = f0->size[0];
  b_acoef = (f0->size[0] / 2) << 1;
  nx = b_acoef - 2;
  for (i = 0; i <= nx; i += 2) {
    r = _mm_loadu_pd(&c1_data[i]);
    _mm_storeu_pd(&c1_data[i], _mm_div_pd(_mm_set1_pd(fs), r));
  }
  for (i = b_acoef; i < acoef; i++) {
    c1_data[i] = fs / c1_data[i];
  }
}

/*
 * File trailer for NCF.c
 *
 * [EOF]
 */
