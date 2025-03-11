/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: PEF.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "PEF.h"
#include "FFTImplementationCallback.h"
#include "analyse_periodecity_data.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "bsxfun.h"
#include "eml_int_forloop_overflow_check.h"
#include "fft.h"
#include "getCandidates.h"
#include "hamming.h"
#include "ifft.h"
#include "indexShapeCheck.h"
#include "linspace.h"
#include "logspace.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static void ab_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void binary_expand_op_10(emxArray_real_T *in1,
                                const emxArray_real_T *in2, int in3, int in4,
                                int in5);

static void binary_expand_op_8(emxArray_real_T *in1, const emxArray_real_T *in2,
                               int in3, int in4, int in5);

static double binary_expand_op_9(const emxArray_real_T *in1,
                                 const emxArray_real_T *in2);

static void createPitchEstimationFilter(const emxArray_real_T *freq,
                                        emxArray_real_T *PEFFilter,
                                        double PEFNumToPad_data[],
                                        int PEFNumToPad_size[2]);

static void getZ(const emxArray_real_T *linSpacedFrequency,
                 const emxArray_real_T *y, const emxArray_real_T *win,
                 double nCol, const emxArray_real_T *logSpacedFrequency,
                 const emxArray_real_T *bw, const double numToPad_data[],
                 const int numToPad_size[2], double NFFT, emxArray_real_T *Z);

static void r_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void rtSizeEqNDCheck(const int *aDims1, const int *aDims2,
                            const rtEqualityCheckInfo *aInfo);

static void v_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void w_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void x_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void y_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

/* Function Definitions */
/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void ab_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr,
          "The data abscissae must be distinct and strictly monotonic.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                int in3
 *                int in4
 *                int in5
 * Return Type  : void
 */
static void binary_expand_op_10(emxArray_real_T *in1,
                                const emxArray_real_T *in2, int in3, int in4,
                                int in5)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,                            /* iFirst */
      -1,                            /* iLast */
      70,                            /* lineNo */
      45,                            /* colNo */
      "",                            /* aName */
      "createPitchEstimationFilter", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  emxArray_real_T *b_in2;
  const double *in2_data;
  double *b_in2_data;
  double *in1_data;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in2_data = in2->data;
  emxInit_real_T(&b_in2, 2);
  i = b_in2->size[0] * b_in2->size[1];
  b_in2->size[0] = 1;
  stride_1_1 = in5 - in4;
  if (stride_1_1 == 1) {
    loop_ub = in3;
  } else {
    loop_ub = stride_1_1;
  }
  b_in2->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_in2, i);
  b_in2_data = b_in2->data;
  stride_0_1 = (in3 != 1);
  stride_1_1 = (stride_1_1 != 1);
  for (i = 0; i < loop_ub; i++) {
    b_in2_data[i] =
        (in2_data[i * stride_0_1] + in2_data[in4 + i * stride_1_1]) / 2.0;
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = 1;
  in1->size[1] = b_in2->size[1] + 2;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  in1_data[0] = in2_data[0];
  for (i = 0; i < loop_ub; i++) {
    in1_data[i + 1] = b_in2_data[i];
  }
  i = in2->size[1];
  if (i < 1) {
    rtDynamicBoundsError(i, 1, i, &c_emlrtBCI);
  }
  in1_data[b_in2->size[1] + 1] = in2_data[i - 1];
  emxFree_real_T(&b_in2);
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                int in3
 *                int in4
 *                int in5
 * Return Type  : void
 */
static void binary_expand_op_8(emxArray_real_T *in1, const emxArray_real_T *in2,
                               int in3, int in4, int in5)
{
  const double *in2_data;
  double *in1_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  in2_data = in2->data;
  i = in4 - in3;
  if (in5 == 1) {
    loop_ub = i;
  } else {
    loop_ub = in5;
  }
  stride_0_0 = in1->size[0];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, stride_0_0);
  in1_data = in1->data;
  stride_0_0 = (i != 1);
  stride_1_0 = (in5 != 1);
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] =
        (in2_data[in3 + i * stride_0_0] - in2_data[i * stride_1_0]) / 2.0;
  }
}

/*
 * Arguments    : const emxArray_real_T *in1
 *                const emxArray_real_T *in2
 * Return Type  : double
 */
static double binary_expand_op_9(const emxArray_real_T *in1,
                                 const emxArray_real_T *in2)
{
  emxArray_real_T *b_in1;
  const double *in1_data;
  const double *in2_data;
  double out1;
  double *b_in1_data;
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 2);
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = 1;
  if (in2->size[1] == 1) {
    loop_ub = in1->size[1];
  } else {
    loop_ub = in2->size[1];
  }
  b_in1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_1 = (in1->size[1] != 1);
  stride_1_1 = (in2->size[1] != 1);
  for (i = 0; i < loop_ub; i++) {
    b_in1_data[i] = in1_data[i * stride_0_1] * in2_data[i * stride_1_1];
  }
  out1 = sum(b_in1) / sum(in2);
  emxFree_real_T(&b_in1);
  return out1;
}

/*
 * Arguments    : const emxArray_real_T *freq
 *                emxArray_real_T *PEFFilter
 *                double PEFNumToPad_data[]
 *                int PEFNumToPad_size[2]
 * Return Type  : void
 */
static void createPitchEstimationFilter(const emxArray_real_T *freq,
                                        emxArray_real_T *PEFFilter,
                                        double PEFNumToPad_data[],
                                        int PEFNumToPad_size[2])
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,                            /* iFirst */
      -1,                            /* iLast */
      70,                            /* lineNo */
      25,                            /* colNo */
      "",                            /* aName */
      "createPitchEstimationFilter", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtEqualityCheckInfo b_emlrtECI = {
      2,                             /* nDims */
      71,                            /* lineNo */
      13,                            /* colNo */
      "createPitchEstimationFilter", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m" /* pName */
  };
  static rtEqualityCheckInfo emlrtECI = {
      2,                             /* nDims */
      70,                            /* lineNo */
      21,                            /* colNo */
      "createPitchEstimationFilter", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m" /* pName */
  };
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      81,        /* lineNo */
      "eml_find" /* fName */
  };
  static rtRunTimeErrorInfo o_emlrtRTEI = {
      447,                /* lineNo */
      "find_last_indices" /* fName */
  };
  __m128d r;
  __m128d r1;
  emxArray_boolean_T *b_x;
  emxArray_real_T *b_y1;
  emxArray_real_T *h;
  emxArray_real_T *q;
  emxArray_real_T *x;
  double delta1;
  double *PEFFilter_data;
  double *h_data;
  double *q_data;
  double *y1_data;
  int i;
  int idx;
  int ii_data;
  int k;
  int n_tmp;
  int nx;
  boolean_T exitg1;
  boolean_T *x_data;
  n_tmp = (int)rt_roundd_snf((double)freq->size[1] / 2.0);
  if (n_tmp < 1) {
    u_rtErrorWithMessageID(m_emlrtRTEI.fName, m_emlrtRTEI.lineNo);
  }
  emxInit_real_T(&q, 2);
  i = q->size[0] * q->size[1];
  q->size[0] = 1;
  q->size[1] = n_tmp;
  emxEnsureCapacity_real_T(q, i);
  q_data = q->data;
  q_data[n_tmp - 1] = 1.0211892990699381;
  if (q->size[1] >= 2) {
    q_data[0] = -0.3010299956639812;
    if (q->size[1] >= 3) {
      delta1 = 1.3222192947339193 / ((double)q->size[1] - 1.0);
      for (k = 0; k <= n_tmp - 3; k++) {
        q_data[k + 1] = ((double)k + 1.0) * delta1 - 0.3010299956639812;
      }
    }
  }
  i = q->size[0] * q->size[1];
  q->size[0] = 1;
  emxEnsureCapacity_real_T(q, i);
  q_data = q->data;
  nx = q->size[1] - 1;
  for (i = 0; i <= nx; i++) {
    delta1 = q_data[i];
    q_data[i] = rt_powd_snf(10.0, delta1);
  }
  emxInit_real_T(&h, 2);
  i = h->size[0] * h->size[1];
  h->size[0] = 1;
  h->size[1] = n_tmp;
  emxEnsureCapacity_real_T(h, i);
  h_data = h->data;
  nx = (q->size[1] / 2) << 1;
  idx = nx - 2;
  for (i = 0; i <= idx; i += 2) {
    r = _mm_loadu_pd(&q_data[i]);
    _mm_storeu_pd(&h_data[i], _mm_mul_pd(_mm_set1_pd(6.2831853071795862), r));
  }
  for (i = nx; i < n_tmp; i++) {
    h_data[i] = 6.2831853071795862 * q_data[i];
  }
  nx = h->size[1];
  for (k = 0; k < nx; k++) {
    h_data[k] = cos(h_data[k]);
  }
  i = h->size[0] * h->size[1];
  h->size[0] = 1;
  emxEnsureCapacity_real_T(h, i);
  h_data = h->data;
  ii_data = h->size[1] - 1;
  nx = (h->size[1] / 2) << 1;
  idx = nx - 2;
  for (i = 0; i <= idx; i += 2) {
    r = _mm_loadu_pd(&h_data[i]);
    _mm_storeu_pd(&h_data[i], _mm_div_pd(_mm_set1_pd(1.0),
                                         _mm_sub_pd(_mm_set1_pd(1.8), r)));
  }
  for (i = nx; i <= ii_data; i++) {
    h_data[i] = 1.0 / (1.8 - h_data[i]);
  }
  if (q->size[1] - 1 < 1) {
    ii_data = 0;
  } else {
    if ((q->size[1] - 1 < 1) || (q->size[1] - 1 > n_tmp)) {
      rtDynamicBoundsError(q->size[1] - 1, 1, n_tmp, &c_emlrtBCI);
    }
    ii_data = q->size[1] - 1;
  }
  if (q->size[1] < 2) {
    i = 0;
    k = 0;
  } else {
    i = 1;
    k = n_tmp;
  }
  nx = k - i;
  if ((ii_data != nx) && ((ii_data != 1) && (nx != 1))) {
    emlrtDimSizeImpxCheckR2021b(ii_data, nx, &emlrtECI);
  }
  emxInit_real_T(&x, 2);
  if (ii_data == nx) {
    k = x->size[0] * x->size[1];
    x->size[0] = 1;
    x->size[1] = ii_data + 2;
    emxEnsureCapacity_real_T(x, k);
    PEFFilter_data = x->data;
    PEFFilter_data[0] = q_data[0];
    nx = (ii_data / 2) << 1;
    idx = nx - 2;
    for (k = 0; k <= idx; k += 2) {
      r = _mm_loadu_pd(&q_data[k]);
      r1 = _mm_loadu_pd(&q_data[i + k]);
      _mm_storeu_pd(&PEFFilter_data[k + 1],
                    _mm_div_pd(_mm_add_pd(r, r1), _mm_set1_pd(2.0)));
    }
    for (k = nx; k < ii_data; k++) {
      PEFFilter_data[k + 1] = (q_data[k] + q_data[i + k]) / 2.0;
    }
    PEFFilter_data[ii_data + 1] = q_data[n_tmp - 1];
  } else {
    binary_expand_op_10(x, q, ii_data, i, k);
    PEFFilter_data = x->data;
  }
  nx = x->size[1];
  emxInit_real_T(&b_y1, 2);
  i = b_y1->size[0] * b_y1->size[1];
  b_y1->size[0] = 1;
  b_y1->size[1] = x->size[1] - 1;
  emxEnsureCapacity_real_T(b_y1, i);
  y1_data = b_y1->data;
  delta1 = PEFFilter_data[0];
  for (idx = 2; idx <= nx; idx++) {
    double d;
    double tmp1;
    tmp1 = PEFFilter_data[idx - 1];
    d = tmp1;
    tmp1 -= delta1;
    delta1 = d;
    y1_data[idx - 2] = tmp1;
  }
  ii_data = h->size[1];
  if ((h->size[1] != x->size[1] - 1) &&
      ((h->size[1] != 1) && (x->size[1] - 1 != 1))) {
    emlrtDimSizeImpxCheckR2021b(h->size[1], x->size[1] - 1, &b_emlrtECI);
  }
  if (h->size[1] == b_y1->size[1]) {
    i = x->size[0] * x->size[1];
    x->size[0] = 1;
    x->size[1] = h->size[1];
    emxEnsureCapacity_real_T(x, i);
    PEFFilter_data = x->data;
    nx = (h->size[1] / 2) << 1;
    idx = nx - 2;
    for (i = 0; i <= idx; i += 2) {
      r = _mm_loadu_pd(&h_data[i]);
      r1 = _mm_loadu_pd(&y1_data[i]);
      _mm_storeu_pd(&PEFFilter_data[i], _mm_mul_pd(r, r1));
    }
    for (i = nx; i < ii_data; i++) {
      PEFFilter_data[i] = h_data[i] * y1_data[i];
    }
    delta1 = sum(x) / sum(b_y1);
  } else {
    delta1 = binary_expand_op_9(h, b_y1);
  }
  emxFree_real_T(&b_y1);
  emxFree_real_T(&x);
  ii_data = h->size[1];
  i = PEFFilter->size[0];
  PEFFilter->size[0] = h->size[1];
  emxEnsureCapacity_real_T(PEFFilter, i);
  PEFFilter_data = PEFFilter->data;
  nx = (h->size[1] / 2) << 1;
  idx = nx - 2;
  for (i = 0; i <= idx; i += 2) {
    r = _mm_loadu_pd(&h_data[i]);
    _mm_storeu_pd(&PEFFilter_data[i], _mm_sub_pd(r, _mm_set1_pd(delta1)));
  }
  for (i = nx; i < ii_data; i++) {
    PEFFilter_data[i] = h_data[i] - delta1;
  }
  emxFree_real_T(&h);
  emxInit_boolean_T(&b_x);
  i = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 1;
  ii_data = q->size[1];
  b_x->size[1] = q->size[1];
  emxEnsureCapacity_boolean_T(b_x, i);
  x_data = b_x->data;
  for (i = 0; i < ii_data; i++) {
    x_data[i] = (q_data[i] < 1.0);
  }
  k = (b_x->size[1] >= 1);
  if (k > b_x->size[1]) {
    p_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  nx = q->size[1];
  emxFree_real_T(&q);
  idx = 0;
  exitg1 = false;
  while ((!exitg1) && (nx > 0)) {
    if (x_data[nx - 1]) {
      idx = 1;
      ii_data = nx;
      exitg1 = true;
    } else {
      nx--;
    }
  }
  emxFree_boolean_T(&b_x);
  if (idx > k) {
    p_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
  if (k == 1) {
    if (idx == 0) {
      k = 0;
    }
  } else {
    k = (idx >= 1);
  }
  PEFNumToPad_size[0] = 1;
  PEFNumToPad_size[1] = k;
  if (k - 1 >= 0) {
    PEFNumToPad_data[0] = ii_data;
  }
}

/*
 * Arguments    : const emxArray_real_T *linSpacedFrequency
 *                const emxArray_real_T *y
 *                const emxArray_real_T *win
 *                double nCol
 *                const emxArray_real_T *logSpacedFrequency
 *                const emxArray_real_T *bw
 *                const double numToPad_data[]
 *                const int numToPad_size[2]
 *                double NFFT
 *                emxArray_real_T *Z
 * Return Type  : void
 */
static void getZ(const emxArray_real_T *linSpacedFrequency,
                 const emxArray_real_T *y, const emxArray_real_T *win,
                 double nCol, const emxArray_real_T *logSpacedFrequency,
                 const emxArray_real_T *bw, const double numToPad_data[],
                 const int numToPad_size[2], double NFFT, emxArray_real_T *Z)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,     /* iFirst */
      -1,     /* iLast */
      81,     /* lineNo */
      12,     /* colNo */
      "",     /* aName */
      "getZ", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo d_emlrtBCI = {
      -1,     /* iFirst */
      -1,     /* iLast */
      81,     /* lineNo */
      14,     /* colNo */
      "",     /* aName */
      "getZ", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo e_emlrtBCI = {
      -1,     /* iFirst */
      -1,     /* iLast */
      91,     /* lineNo */
      21,     /* colNo */
      "",     /* aName */
      "getZ", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo f_emlrtBCI = {
      -1,     /* iFirst */
      -1,     /* iLast */
      81,     /* lineNo */
      25,     /* colNo */
      "",     /* aName */
      "getZ", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo g_emlrtBCI = {
      -1,     /* iFirst */
      -1,     /* iLast */
      81,     /* lineNo */
      27,     /* colNo */
      "",     /* aName */
      "getZ", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtDoubleCheckInfo e_emlrtDCI = {
      81,    /* lineNo */
      "getZ" /* fName */
  };
  static rtEqualityCheckInfo emlrtECI = {
      2,      /* nDims */
      82,     /* lineNo */
      15,     /* colNo */
      "getZ", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m" /* pName */
  };
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      208,           /* lineNo */
      "interp1_work" /* fName */
  };
  static rtRunTimeErrorInfo o_emlrtRTEI = {
      130,           /* lineNo */
      "interp1_work" /* fName */
  };
  static rtRunTimeErrorInfo p_emlrtRTEI = {
      139,           /* lineNo */
      "interp1_work" /* fName */
  };
  static rtRunTimeErrorInfo q_emlrtRTEI = {
      155,           /* lineNo */
      "interp1_work" /* fName */
  };
  static rtRunTimeErrorInfo r_emlrtRTEI = {
      166,           /* lineNo */
      "interp1_work" /* fName */
  };
  emxArray_creal_T *Y;
  emxArray_creal_T *r;
  emxArray_real_T *Ylog;
  emxArray_real_T *Ypower;
  emxArray_real_T *x;
  creal_T *Y_data;
  creal_T *r1;
  const double *linSpacedFrequency_data;
  const double *logSpacedFrequency_data;
  double d;
  double *Ylog_data;
  double *Ypower_data;
  double *x_data;
  int sizes[2];
  int i;
  int i1;
  int j;
  int k;
  int loop_ub;
  int n;
  int nd2;
  int nycols_tmp;
  int offset;
  boolean_T b;
  boolean_T empty_non_axis_sizes;
  logSpacedFrequency_data = logSpacedFrequency->data;
  linSpacedFrequency_data = linSpacedFrequency->data;
  emxInit_real_T(&Ypower, 2);
  bsxfun(y, win, Ypower);
  emxInit_creal_T(&Y, 2);
  fft(Ypower, NFFT, Y);
  Y_data = Y->data;
  if (Y->size[0] < 1) {
    rtDynamicBoundsError(1, 1, Y->size[0], &c_emlrtBCI);
  }
  d = NFFT / 2.0 + 1.0;
  if (d != (int)floor(d)) {
    rtIntegerError(d, &e_emlrtDCI);
  }
  n = (int)d;
  if (((int)d < 1) || ((int)d > Y->size[0])) {
    rtDynamicBoundsError((int)d, 1, Y->size[0], &d_emlrtBCI);
  }
  if (nCol < 1.0) {
    loop_ub = 0;
  } else {
    if (Y->size[1] < 1) {
      rtDynamicBoundsError(1, 1, Y->size[1], &f_emlrtBCI);
    }
    if (((int)nCol < 1) || ((int)nCol > Y->size[1])) {
      rtDynamicBoundsError((int)nCol, 1, Y->size[1], &g_emlrtBCI);
    }
    loop_ub = (int)nCol;
  }
  emxInit_creal_T(&r, 2);
  i = r->size[0] * r->size[1];
  r->size[0] = (int)d;
  r->size[1] = loop_ub;
  emxEnsureCapacity_creal_T(r, i);
  r1 = r->data;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < n; i1++) {
      r1[i1 + r->size[0] * i].re = Y_data[i1 + Y->size[0] * i].re;
      r1[i1 + r->size[0] * i].im = -Y_data[i1 + Y->size[0] * i].im;
    }
  }
  sizes[0] = (int)d;
  sizes[1] = loop_ub;
  if (((int)d != r->size[0]) || (loop_ub != r->size[1])) {
    rtSizeEqNDCheck(&sizes[0], &r->size[0], &emlrtECI);
  }
  i = Ypower->size[0] * Ypower->size[1];
  Ypower->size[0] = (int)d;
  Ypower->size[1] = loop_ub;
  emxEnsureCapacity_real_T(Ypower, i);
  Ypower_data = Ypower->data;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < n; i1++) {
      Ypower_data[i1 + Ypower->size[0] * i] =
          Y_data[i1 + Y->size[0] * i].re * r1[i1 + r->size[0] * i].re -
          Y_data[i1 + Y->size[0] * i].im * r1[i1 + r->size[0] * i].im;
    }
  }
  emxFree_creal_T(&r);
  emxFree_creal_T(&Y);
  emxInit_real_T(&x, 1);
  loop_ub = linSpacedFrequency->size[0];
  i = x->size[0];
  x->size[0] = linSpacedFrequency->size[0];
  emxEnsureCapacity_real_T(x, i);
  x_data = x->data;
  for (i = 0; i < loop_ub; i++) {
    x_data[i] = linSpacedFrequency_data[i];
  }
  if (((Ypower->size[0] != 1) || (Ypower->size[1] != 1)) &&
      ((Ypower->size[0] == 1) || (Ypower->size[1] == 1)) &&
      (Ypower->size[0] == 1)) {
    v_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
  nycols_tmp = Ypower->size[1] - 1;
  if (linSpacedFrequency->size[0] != Ypower->size[0]) {
    w_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
  }
  if (linSpacedFrequency->size[0] <= 1) {
    x_rtErrorWithMessageID(q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  emxInit_real_T(&Ylog, 2);
  i = logSpacedFrequency->size[0];
  i1 = Ylog->size[0] * Ylog->size[1];
  Ylog->size[0] = logSpacedFrequency->size[0];
  Ylog->size[1] = Ypower->size[1];
  emxEnsureCapacity_real_T(Ylog, i1);
  Ylog_data = Ylog->data;
  n = logSpacedFrequency->size[0] * Ypower->size[1];
  for (i1 = 0; i1 < n; i1++) {
    Ylog_data[i1] = rtNaN;
  }
  if (logSpacedFrequency->size[0] != 0) {
    if (loop_ub > 2147483646) {
      check_forloop_overflow_error();
    }
    k = 0;
    int exitg1;
    do {
      exitg1 = 0;
      if (k <= loop_ub - 1) {
        if (rtIsNaN(linSpacedFrequency_data[k])) {
          y_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
        } else {
          k++;
        }
      } else {
        double xtmp;
        int low_i;
        if (linSpacedFrequency_data[1] < linSpacedFrequency_data[0]) {
          i1 = loop_ub >> 1;
          for (nd2 = 0; nd2 < i1; nd2++) {
            xtmp = x_data[nd2];
            n = (loop_ub - nd2) - 1;
            x_data[nd2] = x_data[n];
            x_data[n] = xtmp;
          }
          if ((Ypower->size[1] != 0) && (Ypower->size[0] > 1)) {
            n = Ypower->size[0] - 1;
            nd2 = Ypower->size[0] >> 1;
            for (j = 0; j <= nycols_tmp; j++) {
              offset = j * Ypower->size[0];
              for (k = 0; k < nd2; k++) {
                low_i = offset + k;
                xtmp = Ypower_data[low_i];
                i1 = (offset + n) - k;
                Ypower_data[low_i] = Ypower_data[i1];
                Ypower_data[i1] = xtmp;
              }
            }
          }
        }
        for (k = 2; k <= loop_ub; k++) {
          if (x_data[k - 1] <= x_data[k - 2]) {
            ab_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
          }
        }
        if (logSpacedFrequency->size[0] > 2147483646) {
          check_forloop_overflow_error();
        }
        for (k = 0; k < i; k++) {
          if (rtIsNaN(logSpacedFrequency_data[k])) {
            for (j = 0; j <= nycols_tmp; j++) {
              Ylog_data[k + j * i] = rtNaN;
            }
          } else if ((!(logSpacedFrequency_data[k] > x_data[x->size[0] - 1])) &&
                     (!(logSpacedFrequency_data[k] < x_data[0]))) {
            n = loop_ub;
            low_i = 1;
            nd2 = 2;
            while (n > nd2) {
              offset = (low_i >> 1) + (n >> 1);
              if (((low_i & 1) == 1) && ((n & 1) == 1)) {
                offset++;
              }
              if (logSpacedFrequency_data[k] >= x_data[offset - 1]) {
                low_i = offset;
                nd2 = offset + 1;
              } else {
                n = offset;
              }
            }
            xtmp = x_data[low_i - 1];
            xtmp = (logSpacedFrequency_data[k] - xtmp) / (x_data[low_i] - xtmp);
            if (xtmp == 0.0) {
              for (j = 0; j <= nycols_tmp; j++) {
                Ylog_data[k + j * i] = Ypower_data[(low_i + j * (int)d) - 1];
              }
            } else if (xtmp == 1.0) {
              for (j = 0; j <= nycols_tmp; j++) {
                Ylog_data[k + j * i] = Ypower_data[low_i + j * (int)d];
              }
            } else {
              for (j = 0; j <= nycols_tmp; j++) {
                double b_y1;
                double y2;
                n = low_i + j * (int)d;
                b_y1 = Ypower_data[n - 1];
                y2 = Ypower_data[n];
                if (b_y1 == y2) {
                  Ylog_data[k + j * i] = b_y1;
                } else {
                  Ylog_data[k + j * i] = (1.0 - xtmp) * b_y1 + xtmp * y2;
                }
              }
            }
          }
        }
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
  emxFree_real_T(&x);
  i = Ypower->size[0] * Ypower->size[1];
  Ypower->size[0] = Ylog->size[0];
  Ypower->size[1] = Ylog->size[1];
  emxEnsureCapacity_real_T(Ypower, i);
  Ypower_data = Ypower->data;
  loop_ub = Ylog->size[0] * Ylog->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    Ypower_data[i] = Ylog_data[i];
  }
  bsxfun(Ypower, bw, Ylog);
  Ylog_data = Ylog->data;
  emxFree_real_T(&Ypower);
  if (numToPad_size[1] < 1) {
    rtDynamicBoundsError(1, 1, numToPad_size[1], &e_emlrtBCI);
  }
  i = (int)numToPad_data[0];
  b = ((i != 0) && (Ylog->size[1] != 0));
  if (b) {
    n = Ylog->size[1];
  } else if ((Ylog->size[0] != 0) && (Ylog->size[1] != 0)) {
    n = Ylog->size[1];
  } else {
    n = Ylog->size[1];
  }
  if ((Ylog->size[1] != n) && ((i != 0) && (Ylog->size[1] != 0))) {
    t_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  if ((Ylog->size[1] != n) && ((Ylog->size[0] != 0) && (Ylog->size[1] != 0))) {
    t_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  empty_non_axis_sizes = (n == 0);
  if (empty_non_axis_sizes || b) {
    nd2 = (int)numToPad_data[0];
  } else {
    nd2 = 0;
  }
  if (empty_non_axis_sizes || ((Ylog->size[0] != 0) && (Ylog->size[1] != 0))) {
    offset = Ylog->size[0];
  } else {
    offset = 0;
  }
  i = Z->size[0] * Z->size[1];
  Z->size[0] = nd2 + offset;
  Z->size[1] = n;
  emxEnsureCapacity_real_T(Z, i);
  Ypower_data = Z->data;
  for (i = 0; i < n; i++) {
    for (i1 = 0; i1 < nd2; i1++) {
      Ypower_data[i1 + Z->size[0] * i] = 0.0;
    }
    for (i1 = 0; i1 < offset; i1++) {
      Ypower_data[(i1 + nd2) + Z->size[0] * i] = Ylog_data[i1 + offset * i];
    }
  }
  emxFree_real_T(&Ylog);
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void r_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Matrix dimensions must agree.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const int *aDims1
 *                const int *aDims2
 *                const rtEqualityCheckInfo *aInfo
 * Return Type  : void
 */
static void rtSizeEqNDCheck(const int *aDims1, const int *aDims2,
                            const rtEqualityCheckInfo *aInfo)
{
  int i;
  char b_dims2Str[1024];
  char dims1Str[1024];
  char dims2Str[1024];
  for (i = 0; i < aInfo->nDims; i++) {
    if (aDims1[i] != aDims2[i]) {
      rtGenSizeString(aInfo->nDims, aDims1, dims1Str);
      rtGenSizeString(aInfo->nDims, aDims2, dims2Str);
      memcpy(&b_dims2Str[0], &dims2Str[0], 1024U * sizeof(char));
      fprintf(stderr, "Sizes mismatch: %s ~= %s.", dims1Str, b_dims2Str);
      fprintf(stderr, "\n");
      rtReportErrorLocation(aInfo->fName, aInfo->lineNo);
      fflush(stderr);
      abort();
    }
  }
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void v_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "A variable-size input matrix or N-D array must not become a "
                  "row vector at runtime.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void w_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Y must have length(X) rows.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void x_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "A minimum of two data points is required.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void y_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "NaN is not an appropriate value for X.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const emxArray_real_T *y
 *                double fs
 *                const double params_Range[2]
 *                double params_WindowLength
 *                emxArray_real_T *f0
 * Return Type  : void
 */
void PEF(const emxArray_real_T *y, double fs, const double params_Range[2],
         double params_WindowLength, emxArray_real_T *f0)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      50,    /* lineNo */
      11,    /* colNo */
      "",    /* aName */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo d_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      35,    /* lineNo */
      14,    /* colNo */
      "",    /* aName */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo e_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      35,    /* lineNo */
      31,    /* colNo */
      "",    /* aName */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo f_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      56,    /* lineNo */
      25,    /* colNo */
      "",    /* aName */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo g_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      58,    /* lineNo */
      7,     /* colNo */
      "",    /* aName */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo h_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      51,    /* lineNo */
      12,    /* colNo */
      "",    /* aName */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo i_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      51,    /* lineNo */
      24,    /* colNo */
      "",    /* aName */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo j_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      50,    /* lineNo */
      37,    /* colNo */
      "",    /* aName */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo k_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      50,    /* lineNo */
      39,    /* colNo */
      "",    /* aName */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo l_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      34,    /* lineNo */
      58,    /* colNo */
      "",    /* aName */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo m_emlrtBCI = {
      -1,    /* iFirst */
      -1,    /* iLast */
      34,    /* lineNo */
      60,    /* colNo */
      "",    /* aName */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m", /* pName */
      0               /* checkKind */
  };
  static rtDoubleCheckInfo e_emlrtDCI = {
      50,   /* lineNo */
      "PEF" /* fName */
  };
  static rtEqualityCheckInfo emlrtECI = {
      1,     /* nDims */
      34,    /* lineNo */
      11,    /* colNo */
      "PEF", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\PEF.m" /* pName */
  };
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      15,                    /* lineNo */
      "assertCompatibleDims" /* fName */
  };
  __m128d r;
  emxArray_creal_T *b_y;
  emxArray_creal_T *r2;
  emxArray_creal_T *r3;
  emxArray_real_T *R;
  emxArray_real_T *Z;
  emxArray_real_T *b_bwTemp;
  emxArray_real_T *bwTemp;
  emxArray_real_T *costab;
  emxArray_real_T *linSpacedFrequency;
  emxArray_real_T *logSpacedFrequency;
  emxArray_real_T *peaks;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  emxArray_real_T *varargin_1;
  emxArray_real_T *win;
  creal_T *y_data;
  double wBandEdges[2];
  double NFFT;
  double absn;
  double f;
  double numToPad_data;
  double *Z_data;
  double *bwTemp_data;
  double *costab_data;
  double *linSpacedFrequency_data;
  double *logSpacedFrequency_data;
  int numToPad_size[2];
  int sizes[2];
  int b_i;
  int b_loop_ub;
  int eint;
  int i;
  int input_sizes_idx_0;
  int loop_ub;
  int m;
  int mxl;
  int scalarLB;
  int vectorUB;
  boolean_T empty_non_axis_sizes;
  boolean_T useRadix2;
  absn = fabs(2.0 * params_WindowLength - 1.0);
  if ((!rtIsInf(absn)) && (!rtIsNaN(absn))) {
    f = frexp(absn, &m);
    absn = m;
    if (f == 0.5) {
      absn = (double)m - 1.0;
    }
  }
  NFFT = rt_powd_snf(2.0, absn);
  absn = fmin(fs / 2.0 - 1.0, 4000.0);
  if (absn < 0.0) {
    s_rtErrorWithMessageID(5, "log10", k_emlrtRTEI.fName, k_emlrtRTEI.lineNo);
  }
  absn = log10(absn);
  emxInit_real_T(&costab, 2);
  logspace(absn, NFFT, costab);
  costab_data = costab->data;
  emxInit_real_T(&logSpacedFrequency, 1);
  loop_ub = costab->size[1];
  i = logSpacedFrequency->size[0];
  logSpacedFrequency->size[0] = costab->size[1];
  emxEnsureCapacity_real_T(logSpacedFrequency, i);
  logSpacedFrequency_data = logSpacedFrequency->data;
  for (i = 0; i < loop_ub; i++) {
    logSpacedFrequency_data[i] = costab_data[i];
  }
  linspace(fs / 2.0, rt_roundd_snf(NFFT / 2.0) + 1.0, costab);
  costab_data = costab->data;
  emxInit_real_T(&linSpacedFrequency, 1);
  b_loop_ub = costab->size[1];
  i = linSpacedFrequency->size[0];
  linSpacedFrequency->size[0] = costab->size[1];
  emxEnsureCapacity_real_T(linSpacedFrequency, i);
  linSpacedFrequency_data = linSpacedFrequency->data;
  for (i = 0; i < b_loop_ub; i++) {
    linSpacedFrequency_data[i] = costab_data[i];
  }
  emxInit_real_T(&bwTemp, 1);
  emxInit_real_T(&peaks, 1);
  scalarLB = (loop_ub / 2) << 1;
  vectorUB = scalarLB - 2;
  for (b_i = 0; b_i < 2; b_i++) {
    absn = params_Range[b_i];
    i = bwTemp->size[0];
    bwTemp->size[0] = loop_ub;
    emxEnsureCapacity_real_T(bwTemp, i);
    bwTemp_data = bwTemp->data;
    for (i = 0; i <= vectorUB; i += 2) {
      r = _mm_loadu_pd(&logSpacedFrequency_data[i]);
      _mm_storeu_pd(&bwTemp_data[i], _mm_sub_pd(r, _mm_set1_pd(absn)));
    }
    for (i = scalarLB; i < loop_ub; i++) {
      bwTemp_data[i] = logSpacedFrequency_data[i] - absn;
    }
    mxl = bwTemp->size[0];
    i = peaks->size[0];
    peaks->size[0] = bwTemp->size[0];
    emxEnsureCapacity_real_T(peaks, i);
    linSpacedFrequency_data = peaks->data;
    if (bwTemp->size[0] > 2147483646) {
      check_forloop_overflow_error();
    }
    for (b_loop_ub = 0; b_loop_ub < mxl; b_loop_ub++) {
      linSpacedFrequency_data[b_loop_ub] = fabs(bwTemp_data[b_loop_ub]);
    }
    if (peaks->size[0] < 1) {
      q_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
    }
    if (peaks->size[0] <= 2) {
      if (peaks->size[0] == 1) {
        m = 1;
      } else if ((linSpacedFrequency_data[0] > linSpacedFrequency_data[1]) ||
                 (rtIsNaN(linSpacedFrequency_data[0]) &&
                  (!rtIsNaN(linSpacedFrequency_data[1])))) {
        m = 2;
      } else {
        m = 1;
      }
    } else {
      if (!rtIsNaN(linSpacedFrequency_data[0])) {
        m = 1;
      } else {
        boolean_T exitg1;
        m = 0;
        if (peaks->size[0] > 2147483646) {
          check_forloop_overflow_error();
        }
        b_loop_ub = 2;
        exitg1 = false;
        while ((!exitg1) && (b_loop_ub <= mxl)) {
          if (!rtIsNaN(linSpacedFrequency_data[b_loop_ub - 1])) {
            m = b_loop_ub;
            exitg1 = true;
          } else {
            b_loop_ub++;
          }
        }
      }
      if (m == 0) {
        m = 1;
      } else {
        absn = linSpacedFrequency_data[m - 1];
        input_sizes_idx_0 = m + 1;
        if ((m + 1 <= peaks->size[0]) && (peaks->size[0] > 2147483646)) {
          check_forloop_overflow_error();
        }
        for (b_loop_ub = input_sizes_idx_0; b_loop_ub <= mxl; b_loop_ub++) {
          f = linSpacedFrequency_data[b_loop_ub - 1];
          if (absn > f) {
            absn = f;
            m = b_loop_ub;
          }
        }
      }
    }
    wBandEdges[b_i] = m;
  }
  if (logSpacedFrequency->size[0] < 3) {
    i = 0;
    b_i = 0;
  } else {
    i = 2;
    b_i = loop_ub;
  }
  sizes[0] = 1;
  m = b_i - i;
  sizes[1] = m;
  indexShapeCheck(logSpacedFrequency->size[0], sizes);
  if (logSpacedFrequency->size[0] - 2 < 1) {
    vectorUB = 0;
  } else {
    if (loop_ub < 1) {
      rtDynamicBoundsError(1, 1, loop_ub, &l_emlrtBCI);
    }
    if ((logSpacedFrequency->size[0] - 2 < 1) ||
        (logSpacedFrequency->size[0] - 2 > loop_ub)) {
      rtDynamicBoundsError(logSpacedFrequency->size[0] - 2, 1, loop_ub,
                           &m_emlrtBCI);
    }
    vectorUB = logSpacedFrequency->size[0] - 2;
  }
  sizes[0] = 1;
  sizes[1] = vectorUB;
  indexShapeCheck(logSpacedFrequency->size[0], sizes);
  if ((m != vectorUB) && ((m != 1) && (vectorUB != 1))) {
    emlrtDimSizeImpxCheckR2021b(m, vectorUB, &emlrtECI);
  }
  if (m == vectorUB) {
    b_i = bwTemp->size[0];
    bwTemp->size[0] = m;
    emxEnsureCapacity_real_T(bwTemp, b_i);
    bwTemp_data = bwTemp->data;
    scalarLB = (m / 2) << 1;
    vectorUB = scalarLB - 2;
    for (b_i = 0; b_i <= vectorUB; b_i += 2) {
      __m128d r1;
      r = _mm_loadu_pd(&logSpacedFrequency_data[i + b_i]);
      r1 = _mm_loadu_pd(&logSpacedFrequency_data[b_i]);
      _mm_storeu_pd(&bwTemp_data[b_i],
                    _mm_div_pd(_mm_sub_pd(r, r1), _mm_set1_pd(2.0)));
    }
    for (b_i = scalarLB; b_i < m; b_i++) {
      bwTemp_data[b_i] =
          (logSpacedFrequency_data[i + b_i] - logSpacedFrequency_data[b_i]) /
          2.0;
    }
  } else {
    binary_expand_op_8(bwTemp, logSpacedFrequency, i, b_i, vectorUB);
    bwTemp_data = bwTemp->data;
  }
  loop_ub = bwTemp->size[0];
  if (bwTemp->size[0] < 1) {
    rtDynamicBoundsError(1, 1, bwTemp->size[0], &d_emlrtBCI);
  }
  if (bwTemp->size[0] < 1) {
    rtDynamicBoundsError(bwTemp->size[0], 1, bwTemp->size[0], &e_emlrtBCI);
  }
  i = costab->size[0] * costab->size[1];
  costab->size[0] = 1;
  b_loop_ub = logSpacedFrequency->size[0];
  costab->size[1] = logSpacedFrequency->size[0];
  emxEnsureCapacity_real_T(costab, i);
  costab_data = costab->data;
  for (i = 0; i < b_loop_ub; i++) {
    costab_data[i] = logSpacedFrequency_data[i];
  }
  createPitchEstimationFilter(costab, peaks, (double *)&numToPad_data,
                              numToPad_size);
  emxInit_real_T(&win, 1);
  hamming(y->size[0], win);
  emxInit_real_T(&b_bwTemp, 1);
  i = b_bwTemp->size[0];
  b_bwTemp->size[0] = bwTemp->size[0] + 2;
  emxEnsureCapacity_real_T(b_bwTemp, i);
  linSpacedFrequency_data = b_bwTemp->data;
  linSpacedFrequency_data[0] = bwTemp_data[0] / NFFT;
  scalarLB = (bwTemp->size[0] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    r = _mm_loadu_pd(&bwTemp_data[i]);
    _mm_storeu_pd(&linSpacedFrequency_data[i + 1],
                  _mm_div_pd(r, _mm_set1_pd(NFFT)));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    linSpacedFrequency_data[i + 1] = bwTemp_data[i] / NFFT;
  }
  linSpacedFrequency_data[bwTemp->size[0] + 1] =
      bwTemp_data[bwTemp->size[0] - 1] / NFFT;
  emxInit_real_T(&Z, 2);
  getZ(linSpacedFrequency, y, win, y->size[1], logSpacedFrequency, b_bwTemp,
       (double *)&numToPad_data, numToPad_size, NFFT, Z);
  emxFree_real_T(&b_bwTemp);
  emxFree_real_T(&win);
  emxFree_real_T(&linSpacedFrequency);
  m = (int)fmax(Z->size[0], peaks->size[0]);
  mxl = (int)fmin(wBandEdges[1], (double)m - 1.0);
  f = frexp(fabs(2.0 * (double)m - 1.0), &eint);
  if (f == 0.5) {
    eint--;
  }
  absn = fmin(rt_powd_snf(2.0, eint), NFFT * 4.0);
  emxInit_creal_T(&b_y, 1);
  if (!(absn == floor(absn))) {
    n_rtErrorWithMessageID(f_emlrtRTEI.fName, f_emlrtRTEI.lineNo);
  }
  if (!(absn <= 2.147483647E+9)) {
    o_rtErrorWithMessageID(g_emlrtRTEI.fName, g_emlrtRTEI.lineNo);
  }
  emxInit_real_T(&sintab, 2);
  emxInit_real_T(&sintabinv, 2);
  if ((peaks->size[0] == 0) || ((int)absn == 0)) {
    loop_ub = (int)absn;
    i = b_y->size[0];
    b_y->size[0] = (int)absn;
    emxEnsureCapacity_creal_T(b_y, i);
    y_data = b_y->data;
    for (i = 0; i < loop_ub; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  } else {
    useRadix2 = (((int)absn > 0) && (((int)absn & ((int)absn - 1)) == 0));
    m = c_FFTImplementationCallback_get((int)absn, useRadix2,
                                        &input_sizes_idx_0);
    f_FFTImplementationCallback_gen(input_sizes_idx_0, useRadix2, costab,
                                    sintab, sintabinv);
    costab_data = costab->data;
    if (useRadix2) {
      g_FFTImplementationCallback_r2b(peaks, (int)absn, costab, sintab, b_y);
      y_data = b_y->data;
    } else {
      e_FFTImplementationCallback_dob(peaks, m, (int)absn, costab, sintab,
                                      sintabinv, b_y);
      y_data = b_y->data;
    }
  }
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxInit_creal_T(&r2, 2);
  b_fft(Z, absn, r2);
  loop_ub = b_y->size[0];
  for (i = 0; i < loop_ub; i++) {
    y_data[i].im = -y_data[i].im;
  }
  emxInit_creal_T(&r3, 2);
  b_bsxfun(r2, b_y, r3);
  emxFree_creal_T(&b_y);
  b_ifft(r3, r2);
  y_data = r2->data;
  emxFree_creal_T(&r3);
  i = r2->size[0];
  b_i = Z->size[0] * Z->size[1];
  Z->size[0] = r2->size[0];
  loop_ub = r2->size[1];
  Z->size[1] = r2->size[1];
  emxEnsureCapacity_real_T(Z, b_i);
  Z_data = Z->data;
  scalarLB = r2->size[0] * r2->size[1];
  for (b_i = 0; b_i < scalarLB; b_i++) {
    Z_data[b_i] = y_data[b_i].re;
  }
  if (mxl + 1 < 1) {
    scalarLB = 0;
  } else {
    if (r2->size[0] < 1) {
      rtDynamicBoundsError(1, 1, r2->size[0], &j_emlrtBCI);
    }
    if ((mxl + 1 < 1) || (mxl + 1 > r2->size[0])) {
      rtDynamicBoundsError(mxl + 1, 1, r2->size[0], &k_emlrtBCI);
    }
    scalarLB = mxl + 1;
  }
  if (mxl < 1) {
    costab->size[0] = 1;
    costab->size[1] = 0;
  } else {
    b_i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = mxl;
    emxEnsureCapacity_real_T(costab, b_i);
    costab_data = costab->data;
    m = mxl - 1;
    for (b_i = 0; b_i <= m; b_i++) {
      costab_data[b_i] = (double)b_i + 1.0;
    }
  }
  absn -= (double)mxl;
  emxInit_real_T(&varargin_1, 2);
  m = costab->size[1];
  b_i = varargin_1->size[0] * varargin_1->size[1];
  varargin_1->size[0] = costab->size[1];
  varargin_1->size[1] = r2->size[1];
  emxEnsureCapacity_real_T(varargin_1, b_i);
  bwTemp_data = varargin_1->data;
  for (b_i = 0; b_i < loop_ub; b_i++) {
    for (vectorUB = 0; vectorUB < m; vectorUB++) {
      f = absn + costab_data[vectorUB];
      if (f != (int)floor(f)) {
        rtIntegerError(f, &e_emlrtDCI);
      }
      if (((int)f < 1) || ((int)f > i)) {
        rtDynamicBoundsError((int)f, 1, i, &c_emlrtBCI);
      }
      bwTemp_data[vectorUB + varargin_1->size[0] * b_i] =
          Z_data[((int)f + Z->size[0] * b_i) - 1];
    }
  }
  useRadix2 = ((costab->size[1] != 0) && (Z->size[1] != 0));
  if (useRadix2) {
    m = r2->size[1];
  } else if ((scalarLB != 0) && (Z->size[1] != 0)) {
    m = r2->size[1];
  } else {
    m = r2->size[1];
    if (Z->size[1] > r2->size[1]) {
      m = r2->size[1];
    }
  }
  emxFree_creal_T(&r2);
  if ((Z->size[1] != m) && ((costab->size[1] != 0) && (Z->size[1] != 0))) {
    t_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  if ((Z->size[1] != m) && ((scalarLB != 0) && (Z->size[1] != 0))) {
    t_rtErrorWithMessageID(l_emlrtRTEI.fName, l_emlrtRTEI.lineNo);
  }
  empty_non_axis_sizes = (m == 0);
  if (empty_non_axis_sizes || useRadix2) {
    input_sizes_idx_0 = costab->size[1];
  } else {
    input_sizes_idx_0 = 0;
  }
  emxFree_real_T(&costab);
  if (empty_non_axis_sizes || ((scalarLB != 0) && (Z->size[1] != 0))) {
    mxl = scalarLB;
  } else {
    mxl = 0;
  }
  for (i = 0; i < loop_ub; i++) {
    for (b_i = 0; b_i < scalarLB; b_i++) {
      Z_data[b_i + scalarLB * i] = Z_data[b_i + Z->size[0] * i];
    }
  }
  i = Z->size[0] * Z->size[1];
  Z->size[0] = scalarLB;
  emxEnsureCapacity_real_T(Z, i);
  Z_data = Z->data;
  emxInit_real_T(&R, 2);
  i = input_sizes_idx_0 + mxl;
  b_i = R->size[0] * R->size[1];
  R->size[0] = i;
  R->size[1] = m;
  emxEnsureCapacity_real_T(R, b_i);
  linSpacedFrequency_data = R->data;
  for (b_i = 0; b_i < m; b_i++) {
    for (vectorUB = 0; vectorUB < input_sizes_idx_0; vectorUB++) {
      linSpacedFrequency_data[vectorUB + R->size[0] * b_i] =
          bwTemp_data[vectorUB + input_sizes_idx_0 * b_i];
    }
    for (vectorUB = 0; vectorUB < mxl; vectorUB++) {
      linSpacedFrequency_data[(vectorUB + input_sizes_idx_0) +
                              R->size[0] * b_i] = Z_data[vectorUB + mxl * b_i];
    }
  }
  emxFree_real_T(&varargin_1);
  emxFree_real_T(&Z);
  if (wBandEdges[1] + 1.0 > R->size[0]) {
    b_i = -1;
    i = -1;
  } else {
    b_i = (int)wBandEdges[1];
    if ((b_i + 1 < 1.0) || (b_i + 1 > i)) {
      rtDynamicBoundsError((int)wBandEdges[1] + 1, 1, i, &h_emlrtBCI);
    }
    b_i--;
    if (i < 1) {
      rtDynamicBoundsError(i, 1, i, &i_emlrtBCI);
    }
    i--;
  }
  for (vectorUB = 0; vectorUB < loop_ub; vectorUB++) {
    m = i - b_i;
    for (input_sizes_idx_0 = 0; input_sizes_idx_0 < m; input_sizes_idx_0++) {
      linSpacedFrequency_data[input_sizes_idx_0 + m * vectorUB] =
          linSpacedFrequency_data[((b_i + input_sizes_idx_0) +
                                   R->size[0] * vectorUB) +
                                  1];
    }
  }
  vectorUB = R->size[0] * R->size[1];
  R->size[0] = i - b_i;
  emxEnsureCapacity_real_T(R, vectorUB);
  getCandidates(R, wBandEdges, peaks, bwTemp);
  bwTemp_data = bwTemp->data;
  linSpacedFrequency_data = peaks->data;
  emxFree_real_T(&R);
  loop_ub = bwTemp->size[0];
  i = f0->size[0];
  f0->size[0] = bwTemp->size[0];
  emxEnsureCapacity_real_T(f0, i);
  Z_data = f0->data;
  for (i = 0; i < loop_ub; i++) {
    b_i = (int)bwTemp_data[i];
    if ((b_i < 1) || (b_i > b_loop_ub)) {
      rtDynamicBoundsError(b_i, 1, b_loop_ub, &f_emlrtBCI);
    }
    Z_data[i] = logSpacedFrequency_data[b_i - 1];
  }
  emxFree_real_T(&logSpacedFrequency);
  m = peaks->size[0] - 1;
  for (b_i = 0; b_i <= m; b_i++) {
    if (linSpacedFrequency_data[b_i] < 0.0) {
      if (b_i > m) {
        rtDynamicBoundsError(b_i, 0, m, &g_emlrtBCI);
      }
      linSpacedFrequency_data[b_i] = 0.0;
    }
  }
  if (peaks->size[0] == 0) {
    bwTemp->size[0] = 0;
  } else {
    i = bwTemp->size[0];
    bwTemp->size[0] = peaks->size[0];
    emxEnsureCapacity_real_T(bwTemp, i);
    if (peaks->size[0] > 2147483646) {
      check_forloop_overflow_error();
    }
  }
  if (peaks->size[0] != bwTemp->size[0]) {
    r_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  emxFree_real_T(&peaks);
  emxFree_real_T(&bwTemp);
}

/*
 * File trailer for PEF.c
 *
 * [EOF]
 */
