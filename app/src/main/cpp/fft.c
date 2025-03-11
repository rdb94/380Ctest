/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: fft.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "analyse_periodecity_data.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                double varargin_1
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void b_fft(const emxArray_real_T *x, double varargin_1, emxArray_creal_T *y)
{
  static rtDoubleCheckInfo e_emlrtDCI = {
      32,   /* lineNo */
      "fft" /* fName */
  };
  static rtDoubleCheckInfo f_emlrtDCI = {
      53,               /* lineNo */
      "executeCallback" /* fName */
  };
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  creal_T *y_data;
  int nRows;
  if (!(varargin_1 == floor(varargin_1))) {
    n_rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
  }
  if (!(varargin_1 <= 2.147483647E+9)) {
    o_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
  }
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  if ((x->size[0] == 0) || (x->size[1] == 0) || ((int)varargin_1 == 0)) {
    int N2blue;
    if ((int)varargin_1 < 0) {
      rtNonNegativeError((int)varargin_1, &e_emlrtDCI);
    }
    nRows = y->size[0] * y->size[1];
    y->size[0] = (int)varargin_1;
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, nRows);
    y_data = y->data;
    N2blue = (int)varargin_1 * x->size[1];
    for (nRows = 0; nRows < N2blue; nRows++) {
      y_data[nRows].re = 0.0;
      y_data[nRows].im = 0.0;
    }
  } else {
    int N2blue;
    boolean_T useRadix2;
    if ((int)varargin_1 < 0) {
      rtNonNegativeError((int)varargin_1, &f_emlrtDCI);
    }
    useRadix2 = (((int)varargin_1 > 0) &&
                 (((int)varargin_1 & ((int)varargin_1 - 1)) == 0));
    N2blue =
        c_FFTImplementationCallback_get((int)varargin_1, useRadix2, &nRows);
    c_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab,
                                    sintabinv);
    if (useRadix2) {
      c_FFTImplementationCallback_r2b(x, (int)varargin_1, costab, sintab, y);
    } else {
      c_FFTImplementationCallback_dob(x, N2blue, (int)varargin_1, costab,
                                      sintab, sintabinv, y);
    }
  }
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                double varargin_1
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void fft(const emxArray_real_T *x, double varargin_1, emxArray_creal_T *y)
{
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  creal_T *y_data;
  int nRows;
  if (x->size[0] == 1) {
    rtErrorWithMessageID(e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
  if ((!(varargin_1 >= 0.0)) || (!(varargin_1 == floor(varargin_1)))) {
    n_rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
  }
  if (!(varargin_1 <= 2.147483647E+9)) {
    o_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
  }
  emxInit_real_T(&costab, 2);
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  if ((x->size[0] == 0) || (x->size[1] == 0) || ((int)varargin_1 == 0)) {
    int N2blue;
    nRows = y->size[0] * y->size[1];
    y->size[0] = (int)varargin_1;
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, nRows);
    y_data = y->data;
    N2blue = (int)varargin_1 * x->size[1];
    for (nRows = 0; nRows < N2blue; nRows++) {
      y_data[nRows].re = 0.0;
      y_data[nRows].im = 0.0;
    }
  } else {
    int N2blue;
    boolean_T useRadix2;
    useRadix2 = (((int)varargin_1 > 0) &&
                 (((int)varargin_1 & ((int)varargin_1 - 1)) == 0));
    N2blue =
        c_FFTImplementationCallback_get((int)varargin_1, useRadix2, &nRows);
    c_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab,
                                    sintabinv);
    if (useRadix2) {
      c_FFTImplementationCallback_r2b(x, (int)varargin_1, costab, sintab, y);
    } else {
      c_FFTImplementationCallback_dob(x, N2blue, (int)varargin_1, costab,
                                      sintab, sintabinv, y);
    }
  }
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
