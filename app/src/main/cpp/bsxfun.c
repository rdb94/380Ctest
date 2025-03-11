/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: bsxfun.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "bsxfun.h"
#include "analyse_periodecity_data.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_creal_T *a
 *                const emxArray_creal_T *b
 *                emxArray_creal_T *c
 * Return Type  : void
 */
void b_bsxfun(const emxArray_creal_T *a, const emxArray_creal_T *b,
              emxArray_creal_T *c)
{
  const creal_T *a_data;
  const creal_T *b_data;
  creal_T *c_data;
  int b_k;
  int csz_idx_0;
  int i;
  int k;
  b_data = b->data;
  a_data = a->data;
  if (b->size[0] == 1) {
    csz_idx_0 = a->size[0];
  } else if (a->size[0] == 1) {
    csz_idx_0 = b->size[0];
  } else if (a->size[0] == b->size[0]) {
    csz_idx_0 = a->size[0];
  } else {
    m_rtErrorWithMessageID(d_emlrtRTEI.fName, d_emlrtRTEI.lineNo);
  }
  i = c->size[0] * c->size[1];
  c->size[0] = csz_idx_0;
  c->size[1] = a->size[1];
  emxEnsureCapacity_creal_T(c, i);
  c_data = c->data;
  if ((csz_idx_0 != 0) && (a->size[1] != 0)) {
    int acoef;
    int bcoef;
    csz_idx_0 = (a->size[1] != 1);
    i = a->size[1] - 1;
    acoef = (a->size[0] != 1);
    bcoef = (b->size[0] != 1);
    for (k = 0; k <= i; k++) {
      int i1;
      int varargin_2;
      varargin_2 = csz_idx_0 * k;
      i1 = c->size[0] - 1;
      for (b_k = 0; b_k <= i1; b_k++) {
        double d;
        double d1;
        double d2;
        double d3;
        int i2;
        int i3;
        i2 = acoef * b_k;
        d = a_data[i2 + a->size[0] * varargin_2].re;
        i3 = bcoef * b_k;
        d1 = b_data[i3].im;
        d2 = a_data[i2 + a->size[0] * varargin_2].im;
        d3 = b_data[i3].re;
        c_data[b_k + c->size[0] * k].re = d * d3 - d2 * d1;
        c_data[b_k + c->size[0] * k].im = d * d1 + d2 * d3;
      }
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *a
 *                const emxArray_real_T *b
 *                emxArray_real_T *c
 * Return Type  : void
 */
void bsxfun(const emxArray_real_T *a, const emxArray_real_T *b,
            emxArray_real_T *c)
{
  const double *a_data;
  const double *b_data;
  double *c_data;
  int b_k;
  int csz_idx_0;
  int i;
  int k;
  b_data = b->data;
  a_data = a->data;
  if (b->size[0] == 1) {
    csz_idx_0 = a->size[0];
  } else if (a->size[0] == 1) {
    csz_idx_0 = b->size[0];
  } else if (a->size[0] == b->size[0]) {
    csz_idx_0 = a->size[0];
  } else {
    m_rtErrorWithMessageID(d_emlrtRTEI.fName, d_emlrtRTEI.lineNo);
  }
  i = c->size[0] * c->size[1];
  c->size[0] = csz_idx_0;
  c->size[1] = a->size[1];
  emxEnsureCapacity_real_T(c, i);
  c_data = c->data;
  if ((csz_idx_0 != 0) && (a->size[1] != 0)) {
    int acoef;
    int bcoef;
    csz_idx_0 = (a->size[1] != 1);
    i = a->size[1] - 1;
    acoef = (a->size[0] != 1);
    bcoef = (b->size[0] != 1);
    for (k = 0; k <= i; k++) {
      int i1;
      int varargin_2;
      varargin_2 = csz_idx_0 * k;
      i1 = c->size[0] - 1;
      for (b_k = 0; b_k <= i1; b_k++) {
        c_data[b_k + c->size[0] * k] =
            a_data[acoef * b_k + a->size[0] * varargin_2] * b_data[bcoef * b_k];
      }
    }
  }
}

/*
 * File trailer for bsxfun.c
 *
 * [EOF]
 */
