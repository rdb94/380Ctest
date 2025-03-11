/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: SRH.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "SRH.h"
#include "analyse_periodecity_data.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "bsxfun.h"
#include "eml_int_forloop_overflow_check.h"
#include "fft.h"
#include "gencoswin.h"
#include "getCandidates.h"
#include "ifft.h"
#include "indexShapeCheck.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static void binary_expand_op_3(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3);

static void binary_expand_op_4(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3);

static void binary_expand_op_5(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3);

static void binary_expand_op_6(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3);

static void binary_expand_op_7(emxArray_real_T *in1, const double in2[20000],
                               const emxArray_real_T *in3,
                               const emxArray_real_T *in4, int in5, int in6);

static void computeResidual(const emxArray_real_T *y, double fs,
                            double params_WindowLength,
                            double params_OverlapLength,
                            emxArray_real_T *residualBuff);

static void j_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void minus(emxArray_real_T *in1, const emxArray_real_T *in2);

static void rtSubAssignSizeCheck(const int *aDims1, const int aNDims1,
                                 const int *aDims2, const int aNDims2,
                                 const rtEqualityCheckInfo *aInfo);

/* Function Definitions */
/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_real_T *in3
 * Return Type  : void
 */
static void binary_expand_op_3(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3)
{
  const double *in2_data;
  const double *in3_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in3_data = in3->data;
  in2_data = in2->data;
  loop_ub = in2->size[0];
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  if (in3->size[1] == 1) {
    b_loop_ub = in2->size[1];
  } else {
    b_loop_ub = in3->size[1];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_1 = (in2->size[1] != 1);
  stride_1_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          in2_data[i1 + in2->size[0] * aux_0_1] +
          in3_data[(5 * (i1 + 70) + in3->size[0] * aux_1_1) - 1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_real_T *in3
 * Return Type  : void
 */
static void binary_expand_op_4(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3)
{
  const double *in2_data;
  const double *in3_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in3_data = in3->data;
  in2_data = in2->data;
  loop_ub = in2->size[0];
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  if (in3->size[1] == 1) {
    b_loop_ub = in2->size[1];
  } else {
    b_loop_ub = in3->size[1];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_1 = (in2->size[1] != 1);
  stride_1_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          in2_data[i1 + in2->size[0] * aux_0_1] +
          in3_data[(((i1 + 70) << 2) + in3->size[0] * aux_1_1) - 1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_real_T *in3
 * Return Type  : void
 */
static void binary_expand_op_5(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3)
{
  const double *in2_data;
  const double *in3_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in3_data = in3->data;
  in2_data = in2->data;
  loop_ub = in2->size[0];
  i = in1->size[0] * in1->size[1];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  if (in3->size[1] == 1) {
    b_loop_ub = in2->size[1];
  } else {
    b_loop_ub = in3->size[1];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_1 = (in2->size[1] != 1);
  stride_1_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          in2_data[i1 + in2->size[0] * aux_0_1] +
          in3_data[(3 * (i1 + 70) + in3->size[0] * aux_1_1) - 1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                const emxArray_real_T *in3
 * Return Type  : void
 */
static void binary_expand_op_6(emxArray_real_T *in1, const emxArray_real_T *in2,
                               const emxArray_real_T *in3)
{
  const double *in2_data;
  const double *in3_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in3_data = in3->data;
  in2_data = in2->data;
  i = in1->size[0] * in1->size[1];
  in1->size[0] = 131;
  emxEnsureCapacity_real_T(in1, i);
  if (in3->size[1] == 1) {
    loop_ub = in2->size[1];
  } else {
    loop_ub = in3->size[1];
  }
  i = in1->size[0] * in1->size[1];
  in1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_1 = (in2->size[1] != 1);
  stride_1_1 = (in3->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < 131; i1++) {
      in1_data[i1 + in1->size[0] * i] =
          (in2_data[(i1 + in2->size[0] * aux_0_1) + 69] +
           in2_data[(((i1 + 70) << 1) + in2->size[0] * aux_0_1) - 1]) -
          in3_data[i1 + in3->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const double in2[20000]
 *                const emxArray_real_T *in3
 *                const emxArray_real_T *in4
 *                int in5
 *                int in6
 * Return Type  : void
 */
static void binary_expand_op_7(emxArray_real_T *in1, const double in2[20000],
                               const emxArray_real_T *in3,
                               const emxArray_real_T *in4, int in5, int in6)
{
  const double *in3_data;
  const double *in4_data;
  double *in1_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  in4_data = in4->data;
  in3_data = in3->data;
  if (in5 == 1) {
    loop_ub = in3->size[0];
  } else {
    loop_ub = in5;
  }
  i = in1->size[0];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  stride_0_0 = (in3->size[0] != 1);
  stride_1_0 = (in5 != 1);
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = in2[(int)in3_data[i * stride_0_0] - 1] +
                  in4_data[i * stride_1_0 + in4->size[0] * in6];
  }
}

/*
 * Arguments    : const emxArray_real_T *y
 *                double fs
 *                double params_WindowLength
 *                double params_OverlapLength
 *                emxArray_real_T *residualBuff
 * Return Type  : void
 */
static void computeResidual(const emxArray_real_T *y, double fs,
                            double params_WindowLength,
                            double params_OverlapLength,
                            emxArray_real_T *residualBuff)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,           /* iFirst */
      -1,           /* iLast */
      106,          /* lineNo */
      26,           /* colNo */
      "",           /* aName */
      "computeLPC", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo d_emlrtBCI = {
      -1,           /* iFirst */
      -1,           /* iLast */
      106,          /* lineNo */
      15,           /* colNo */
      "",           /* aName */
      "computeLPC", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo e_emlrtBCI = {
      1,              /* iFirst */
      11,             /* iLast */
      40,             /* lineNo */
      43,             /* colNo */
      "",             /* aName */
      "levinsonImpl", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "levinson\\levinsonImpl.m", /* pName */
      0                           /* checkKind */
  };
  static rtBoundsCheckInfo f_emlrtBCI = {
      1,              /* iFirst */
      11,             /* iLast */
      48,             /* lineNo */
      74,             /* colNo */
      "",             /* aName */
      "levinsonImpl", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "levinson\\levinsonImpl.m", /* pName */
      0                           /* checkKind */
  };
  static rtBoundsCheckInfo g_emlrtBCI = {
      -1,           /* iFirst */
      -1,           /* iLast */
      107,          /* lineNo */
      7,            /* colNo */
      "",           /* aName */
      "computeLPC", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo h_emlrtBCI = {
      -1,                /* iFirst */
      -1,                /* iLast */
      53,                /* lineNo */
      11,                /* colNo */
      "",                /* aName */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo i_emlrtBCI = {
      1,                 /* iFirst */
      20000,             /* iLast */
      60,                /* lineNo */
      37,                /* colNo */
      "",                /* aName */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo j_emlrtBCI = {
      -1,                /* iFirst */
      -1,                /* iLast */
      60,                /* lineNo */
      85,                /* colNo */
      "",                /* aName */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo k_emlrtBCI = {
      -1,                /* iFirst */
      -1,                /* iLast */
      60,                /* lineNo */
      51,                /* colNo */
      "",                /* aName */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo l_emlrtBCI = {
      -1,                /* iFirst */
      -1,                /* iLast */
      60,                /* lineNo */
      53,                /* colNo */
      "",                /* aName */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo m_emlrtBCI = {
      -1,                /* iFirst */
      -1,                /* iLast */
      74,                /* lineNo */
      54,                /* colNo */
      "",                /* aName */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo n_emlrtBCI = {
      -1,                /* iFirst */
      -1,                /* iLast */
      74,                /* lineNo */
      22,                /* colNo */
      "",                /* aName */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo o_emlrtBCI = {
      -1,                /* iFirst */
      -1,                /* iLast */
      74,                /* lineNo */
      24,                /* colNo */
      "",                /* aName */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo p_emlrtBCI = {
      1,                 /* iFirst */
      20000,             /* iLast */
      73,                /* lineNo */
      25,                /* colNo */
      "",                /* aName */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo q_emlrtBCI = {
      1,                 /* iFirst */
      20000,             /* iLast */
      73,                /* lineNo */
      45,                /* colNo */
      "",                /* aName */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtDoubleCheckInfo e_emlrtDCI = {
      60,               /* lineNo */
      "computeResidual" /* fName */
  };
  static rtDoubleCheckInfo f_emlrtDCI = {
      70,               /* lineNo */
      "computeResidual" /* fName */
  };
  static rtDoubleCheckInfo g_emlrtDCI = {
      70,               /* lineNo */
      "computeResidual" /* fName */
  };
  static rtDoubleCheckInfo h_emlrtDCI = {
      70,               /* lineNo */
      "computeResidual" /* fName */
  };
  static rtDoubleCheckInfo i_emlrtDCI = {
      70,               /* lineNo */
      "computeResidual" /* fName */
  };
  static rtDoubleCheckInfo j_emlrtDCI = {
      70,               /* lineNo */
      "computeResidual" /* fName */
  };
  static rtDoubleCheckInfo k_emlrtDCI = {
      74,               /* lineNo */
      "computeResidual" /* fName */
  };
  static rtDoubleCheckInfo l_emlrtDCI = {
      73,               /* lineNo */
      "computeResidual" /* fName */
  };
  static rtDoubleCheckInfo m_emlrtDCI = {
      73,               /* lineNo */
      "computeResidual" /* fName */
  };
  static rtEqualityCheckInfo b_emlrtECI = {
      1,                 /* nDims */
      60,                /* lineNo */
      28,                /* colNo */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m" /* pName */
  };
  static rtEqualityCheckInfo c_emlrtECI = {
      -1,                /* nDims */
      60,                /* lineNo */
      9,                 /* colNo */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m" /* pName */
  };
  static rtEqualityCheckInfo d_emlrtECI = {
      -1,                /* nDims */
      74,                /* lineNo */
      9,                 /* colNo */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m" /* pName */
  };
  static rtEqualityCheckInfo emlrtECI = {
      -1,                /* nDims */
      53,                /* lineNo */
      5,                 /* colNo */
      "computeResidual", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m" /* pName */
  };
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      34,      /* lineNo */
      "filter" /* fName */
  };
  emxArray_creal_T *R;
  emxArray_int16_T *r1;
  emxArray_real_T *A;
  emxArray_real_T *b_w;
  emxArray_real_T *idx;
  emxArray_real_T *inv;
  emxArray_real_T *r;
  emxArray_real_T *w;
  creal_T temp_a[11];
  creal_T temp_auf[11];
  creal_T *R_data;
  double residual[20000];
  const double *y_data;
  double b_temp_a_re_tmp;
  double im;
  double resHopLength;
  double temp_a_re_tmp;
  double *A_data;
  double *idx_data;
  double *inv_data;
  double *w_data;
  int b_nx;
  int i;
  int i1;
  int ii;
  int j;
  int k;
  int loop_ub;
  int naxpy;
  int nx;
  int nx_m_nb;
  int resWindowLength_tmp;
  short *r3;
  signed char b_w_data;
  boolean_T b;
  y_data = y->data;
  emxInit_real_T(&A, 2);
  i = y->size[1];
  i1 = A->size[0] * A->size[1];
  A->size[0] = y->size[1];
  A->size[1] = 12;
  emxEnsureCapacity_real_T(A, i1);
  A_data = A->data;
  nx = y->size[1] * 12;
  for (i1 = 0; i1 < nx; i1++) {
    A_data[i1] = 0.0;
  }
  emxInit_real_T(&inv, 2);
  resHopLength = frexp(fabs(2.0 * (double)y->size[0] - 1.0), &nx_m_nb);
  if (resHopLength == 0.5) {
    nx_m_nb--;
  }
  emxInit_creal_T(&R, 2);
  fft(y, rt_powd_snf(2.0, nx_m_nb), R);
  R_data = R->data;
  nx = R->size[0] * R->size[1];
  i1 = inv->size[0] * inv->size[1];
  inv->size[0] = R->size[0];
  inv->size[1] = R->size[1];
  emxEnsureCapacity_real_T(inv, i1);
  inv_data = inv->data;
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < nx; k++) {
    inv_data[k] = rt_hypotd_snf(R_data[k].re, R_data[k].im);
  }
  emxInit_real_T(&r, 2);
  i1 = r->size[0] * r->size[1];
  r->size[0] = inv->size[0];
  r->size[1] = inv->size[1];
  emxEnsureCapacity_real_T(r, i1);
  idx_data = r->data;
  nx = inv->size[0] * inv->size[1];
  for (i1 = 0; i1 < nx; i1++) {
    resHopLength = inv_data[i1];
    idx_data[i1] = resHopLength * resHopLength;
  }
  ifft(r, R);
  R_data = R->data;
  emxFree_real_T(&r);
  for (ii = 0; ii < i; ii++) {
    creal_T Rtemp[12];
    double temp_J_im;
    double temp_J_re;
    if (ii + 1 > R->size[1]) {
      rtDynamicBoundsError(ii + 1, 1, R->size[1], &c_emlrtBCI);
    }
    for (i1 = 0; i1 < 12; i1++) {
      if (i1 + 1 > R->size[0]) {
        rtDynamicBoundsError(i1 + 1, 1, R->size[0], &d_emlrtBCI);
      }
      Rtemp[i1].re = R_data[i1 + R->size[0] * ii].re;
      if (i1 + 1 > R->size[0]) {
        rtDynamicBoundsError(i1 + 1, 1, R->size[0], &d_emlrtBCI);
      }
      Rtemp[i1].im = R_data[i1 + R->size[0] * ii].im;
    }
    memset(&temp_a[0], 0, 11U * sizeof(creal_T));
    memset(&temp_auf[0], 0, 11U * sizeof(creal_T));
    temp_a[0].re = -Rtemp[0].re;
    temp_a[0].im = -Rtemp[0].im;
    temp_J_re = Rtemp[0].re;
    temp_J_im = 0.0;
    for (nx_m_nb = 0; nx_m_nb < 11; nx_m_nb++) {
      double ar;
      double re;
      double temp_kprod_im;
      double temp_kprod_re;
      temp_kprod_re = 0.0;
      temp_kprod_im = 0.0;
      for (j = 0; j < nx_m_nb; j++) {
        temp_auf[j] = temp_a[j];
        i1 = nx_m_nb - j;
        if (i1 < 1) {
          rtDynamicBoundsError(i1, 1, 11, &e_emlrtBCI);
        }
        resHopLength = temp_a[j].re;
        im = Rtemp[i1].im;
        temp_a_re_tmp = temp_a[j].im;
        b_temp_a_re_tmp = Rtemp[i1].re;
        temp_kprod_re += resHopLength * b_temp_a_re_tmp - temp_a_re_tmp * im;
        temp_kprod_im += resHopLength * im + temp_a_re_tmp * b_temp_a_re_tmp;
      }
      ar = -(Rtemp[nx_m_nb + 1].re + temp_kprod_re);
      temp_kprod_re = -(Rtemp[nx_m_nb + 1].im + temp_kprod_im);
      if (temp_J_im == 0.0) {
        if (temp_kprod_re == 0.0) {
          re = ar / temp_J_re;
          im = 0.0;
        } else if (ar == 0.0) {
          re = 0.0;
          im = temp_kprod_re / temp_J_re;
        } else {
          re = ar / temp_J_re;
          im = temp_kprod_re / temp_J_re;
        }
      } else if (temp_J_re == 0.0) {
        if (ar == 0.0) {
          re = temp_kprod_re / temp_J_im;
          im = 0.0;
        } else if (temp_kprod_re == 0.0) {
          re = 0.0;
          im = -(ar / temp_J_im);
        } else {
          re = temp_kprod_re / temp_J_im;
          im = -(ar / temp_J_im);
        }
      } else {
        temp_a_re_tmp = fabs(temp_J_re);
        resHopLength = fabs(temp_J_im);
        if (temp_a_re_tmp > resHopLength) {
          resHopLength = temp_J_im / temp_J_re;
          b_temp_a_re_tmp = temp_J_re + resHopLength * temp_J_im;
          re = (ar + resHopLength * temp_kprod_re) / b_temp_a_re_tmp;
          im = (temp_kprod_re - resHopLength * ar) / b_temp_a_re_tmp;
        } else if (resHopLength == temp_a_re_tmp) {
          if (temp_J_re > 0.0) {
            resHopLength = 0.5;
          } else {
            resHopLength = -0.5;
          }
          if (temp_J_im > 0.0) {
            im = 0.5;
          } else {
            im = -0.5;
          }
          re = (ar * resHopLength + temp_kprod_re * im) / temp_a_re_tmp;
          im = (temp_kprod_re * resHopLength - ar * im) / temp_a_re_tmp;
        } else {
          resHopLength = temp_J_re / temp_J_im;
          b_temp_a_re_tmp = temp_J_im + resHopLength * temp_J_re;
          re = (resHopLength * ar + temp_kprod_re) / b_temp_a_re_tmp;
          im = (resHopLength * temp_kprod_re - ar) / b_temp_a_re_tmp;
        }
      }
      temp_kprod_re = re * re - im * -im;
      temp_kprod_im = re * -im + im * re;
      resHopLength =
          (1.0 - temp_kprod_re) * temp_J_re - (0.0 - temp_kprod_im) * temp_J_im;
      temp_J_im =
          (1.0 - temp_kprod_re) * temp_J_im + (0.0 - temp_kprod_im) * temp_J_re;
      temp_J_re = resHopLength;
      for (nx = 0; nx < nx_m_nb; nx++) {
        i1 = nx_m_nb - nx;
        if (i1 < 1) {
          rtDynamicBoundsError(i1, 1, 11, &f_emlrtBCI);
        }
        resHopLength = temp_auf[i1 - 1].re;
        temp_a_re_tmp = -temp_auf[i1 - 1].im;
        temp_a[nx].re =
            temp_auf[nx].re + (re * resHopLength - im * temp_a_re_tmp);
        temp_a[nx].im =
            temp_auf[nx].im + (re * temp_a_re_tmp + im * resHopLength);
      }
      temp_a[nx_m_nb].re = re;
      temp_a[nx_m_nb].im = im;
    }
    if (ii + 1 > i) {
      rtDynamicBoundsError(ii + 1, 1, i, &g_emlrtBCI);
    }
    A_data[ii] = 1.0;
    for (i1 = 0; i1 < 11; i1++) {
      A_data[ii + A->size[0] * (i1 + 1)] = temp_a[i1].re;
    }
  }
  emxFree_creal_T(&R);
  resWindowLength_tmp = y->size[0];
  resHopLength = rt_roundd_snf(0.005 * fs);
  i1 = inv->size[0] * inv->size[1];
  inv->size[0] = y->size[0];
  inv->size[1] = y->size[1];
  emxEnsureCapacity_real_T(inv, i1);
  inv_data = inv->data;
  nx = y->size[0] * y->size[1];
  for (i1 = 0; i1 < nx; i1++) {
    inv_data[i1] = 0.0;
  }
  memset(&residual[0], 0, 20000U * sizeof(double));
  if (y->size[1] - 1 >= 0) {
    b = true;
    b_nx = y->size[0];
    loop_ub = y->size[0];
  }
  emxInit_real_T(&w, 1);
  for (ii = 0; ii < i; ii++) {
    if (ii + 1 > i) {
      rtDynamicBoundsError(ii + 1, 1, i, &h_emlrtBCI);
    }
    if (!b) {
      rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    i1 = w->size[0];
    w->size[0] = resWindowLength_tmp;
    emxEnsureCapacity_real_T(w, i1);
    w_data = w->data;
    for (i1 = 0; i1 < loop_ub; i1++) {
      w_data[i1] = 0.0;
    }
    if (y->size[0] >= 24) {
      for (k = 0; k < 12; k++) {
        nx = k + 1;
        if (b_nx > 2147483646) {
          check_forloop_overflow_error();
        }
        nx_m_nb = ((((b_nx - k) / 2) << 1) + k) + 1;
        naxpy = nx_m_nb - 2;
        for (j = nx; j <= naxpy; j += 2) {
          __m128d r2;
          r2 = _mm_loadu_pd(&w_data[j - 1]);
          _mm_storeu_pd(
              &w_data[j - 1],
              _mm_add_pd(
                  r2,
                  _mm_mul_pd(
                      _mm_set1_pd(A_data[ii + A->size[0] * k]),
                      _mm_loadu_pd(&y_data[((j - k) + y->size[0] * ii) - 1]))));
        }
        for (j = nx_m_nb; j <= b_nx; j++) {
          w_data[j - 1] += A_data[ii + A->size[0] * k] *
                           y_data[((j - k) + y->size[0] * ii) - 1];
        }
      }
    } else {
      if (y->size[0] > 12) {
        nx_m_nb = y->size[0] - 13;
      } else {
        nx_m_nb = -1;
      }
      for (k = 0; k <= nx_m_nb; k++) {
        for (j = 0; j < 12; j++) {
          nx = k + j;
          w_data[nx] +=
              y_data[k + y->size[0] * ii] * A_data[ii + A->size[0] * j];
        }
      }
      naxpy = (y->size[0] - nx_m_nb) - 1;
      i1 = nx_m_nb + 2;
      for (k = i1; k <= b_nx; k++) {
        if (naxpy > 2147483646) {
          check_forloop_overflow_error();
        }
        for (j = 0; j < naxpy; j++) {
          nx = (k + j) - 1;
          w_data[nx] +=
              y_data[(k + y->size[0] * ii) - 1] * A_data[ii + A->size[0] * j];
        }
        naxpy--;
      }
    }
    rtSubAssignSizeCheck(&resWindowLength_tmp, 1, &w->size[0], 1, &emlrtECI);
    for (i1 = 0; i1 < resWindowLength_tmp; i1++) {
      inv_data[i1 + inv->size[0] * ii] = w_data[i1];
    }
  }
  emxFree_real_T(&A);
  emxInit_real_T(&idx, 2);
  idx_data = idx->data;
  emxInit_int16_T(&r1, 1);
  emxInit_real_T(&b_w, 1);
  for (naxpy = 0; naxpy < i; naxpy++) {
    temp_a_re_tmp = resHopLength * (((double)naxpy + 1.0) - 1.0);
    b_temp_a_re_tmp =
        fmin((double)resWindowLength_tmp + temp_a_re_tmp, 20000.0);
    if (rtIsNaN(temp_a_re_tmp + 1.0)) {
      i1 = idx->size[0] * idx->size[1];
      idx->size[0] = 1;
      idx->size[1] = 1;
      emxEnsureCapacity_real_T(idx, i1);
      idx_data = idx->data;
      idx_data[0] = rtNaN;
    } else if (b_temp_a_re_tmp < temp_a_re_tmp + 1.0) {
      idx->size[0] = 1;
      idx->size[1] = 0;
    } else if ((rtIsInf(temp_a_re_tmp + 1.0) || rtIsInf(b_temp_a_re_tmp)) &&
               (temp_a_re_tmp + 1.0 == b_temp_a_re_tmp)) {
      i1 = idx->size[0] * idx->size[1];
      idx->size[0] = 1;
      idx->size[1] = 1;
      emxEnsureCapacity_real_T(idx, i1);
      idx_data = idx->data;
      idx_data[0] = rtNaN;
    } else {
      i1 = idx->size[0] * idx->size[1];
      idx->size[0] = 1;
      nx = (int)(b_temp_a_re_tmp - (temp_a_re_tmp + 1.0));
      idx->size[1] = nx + 1;
      emxEnsureCapacity_real_T(idx, i1);
      idx_data = idx->data;
      for (i1 = 0; i1 <= nx; i1++) {
        idx_data[i1] = (temp_a_re_tmp + 1.0) + (double)i1;
      }
    }
    i1 = (int)fmin(idx->size[1], resWindowLength_tmp);
    if (i1 < 1) {
      i1 = 0;
    } else {
      if (inv->size[0] < 1) {
        rtDynamicBoundsError(1, 1, inv->size[0], &k_emlrtBCI);
      }
      if (i1 > inv->size[0]) {
        rtDynamicBoundsError(i1, 1, inv->size[0], &l_emlrtBCI);
      }
    }
    nx = idx->size[1];
    b_nx = w->size[0];
    w->size[0] = idx->size[1];
    emxEnsureCapacity_real_T(w, b_nx);
    w_data = w->data;
    for (b_nx = 0; b_nx < nx; b_nx++) {
      w_data[b_nx] = idx_data[b_nx];
    }
    for (b_nx = 0; b_nx < nx; b_nx++) {
      nx_m_nb = (int)w_data[b_nx];
      if (w_data[b_nx] != nx_m_nb) {
        rtIntegerError(w_data[b_nx], &e_emlrtDCI);
      }
      if ((nx_m_nb < 1) || (nx_m_nb > 20000)) {
        rtDynamicBoundsError(nx_m_nb, 1, 20000, &i_emlrtBCI);
      }
    }
    if (naxpy + 1 > inv->size[1]) {
      rtDynamicBoundsError(naxpy + 1, 1, inv->size[1], &j_emlrtBCI);
    }
    if ((idx->size[1] != i1) && ((idx->size[1] != 1) && (i1 != 1))) {
      emlrtDimSizeImpxCheckR2021b(idx->size[1], i1, &b_emlrtECI);
    }
    b_nx = r1->size[0];
    r1->size[0] = idx->size[1];
    emxEnsureCapacity_int16_T(r1, b_nx);
    r3 = r1->data;
    for (b_nx = 0; b_nx < nx; b_nx++) {
      r3[b_nx] = (short)((short)w_data[b_nx] - 1);
    }
    if (w->size[0] == i1) {
      i1 = b_w->size[0];
      b_w->size[0] = idx->size[1];
      emxEnsureCapacity_real_T(b_w, i1);
      A_data = b_w->data;
      for (i1 = 0; i1 < nx; i1++) {
        A_data[i1] =
            residual[(int)w_data[i1] - 1] + inv_data[i1 + inv->size[0] * naxpy];
      }
    } else {
      binary_expand_op_7(b_w, residual, w, inv, i1, naxpy);
      A_data = b_w->data;
    }
    rtSubAssignSizeCheck(&idx->size[1], 1, &b_w->size[0], 1, &c_emlrtECI);
    for (i1 = 0; i1 < nx; i1++) {
      residual[r3[i1]] = A_data[i1];
    }
  }
  emxFree_int16_T(&r1);
  emxFree_real_T(&idx);
  resHopLength = params_WindowLength - params_OverlapLength;
  temp_a_re_tmp = ceil((20000.0 - params_WindowLength) / resHopLength);
  if (!(params_WindowLength >= 0.0)) {
    rtNonNegativeError(params_WindowLength, &f_emlrtDCI);
  }
  i = (int)floor(params_WindowLength);
  if (params_WindowLength != i) {
    rtIntegerError(params_WindowLength, &g_emlrtDCI);
  }
  if (!(temp_a_re_tmp + 1.0 >= 0.0)) {
    rtNonNegativeError(temp_a_re_tmp + 1.0, &h_emlrtDCI);
  }
  if (temp_a_re_tmp + 1.0 != (int)(temp_a_re_tmp + 1.0)) {
    rtIntegerError(temp_a_re_tmp + 1.0, &i_emlrtDCI);
  }
  i1 = residualBuff->size[0] * residualBuff->size[1];
  b_nx = (int)params_WindowLength;
  residualBuff->size[0] = b_nx;
  nx_m_nb = (int)(temp_a_re_tmp + 1.0);
  residualBuff->size[1] = (int)(temp_a_re_tmp + 1.0);
  emxEnsureCapacity_real_T(residualBuff, i1);
  idx_data = residualBuff->data;
  if (b_nx != i) {
    rtIntegerError(params_WindowLength, &j_emlrtDCI);
  }
  if (temp_a_re_tmp + 1.0 != (int)(temp_a_re_tmp + 1.0)) {
    rtIntegerError(temp_a_re_tmp + 1.0, &j_emlrtDCI);
  }
  nx = b_nx * (int)(temp_a_re_tmp + 1.0);
  for (i = 0; i < nx; i++) {
    idx_data[i] = 0.0;
  }
  for (naxpy = 0; naxpy < nx_m_nb; naxpy++) {
    b_temp_a_re_tmp = resHopLength * (((double)naxpy + 1.0) - 1.0);
    im = fmin(params_WindowLength + b_temp_a_re_tmp, 20000.0);
    if (b_temp_a_re_tmp + 1.0 > im) {
      i = 1;
      i1 = 0;
    } else {
      if (b_temp_a_re_tmp + 1.0 != (int)floor(b_temp_a_re_tmp + 1.0)) {
        rtIntegerError(b_temp_a_re_tmp + 1.0, &l_emlrtDCI);
      }
      if (((int)(b_temp_a_re_tmp + 1.0) < 1) ||
          ((int)(b_temp_a_re_tmp + 1.0) > 20000)) {
        rtDynamicBoundsError((int)(b_temp_a_re_tmp + 1.0), 1, 20000,
                             &p_emlrtBCI);
      }
      i = (int)(b_temp_a_re_tmp + 1.0);
      if (im != (int)floor(im)) {
        rtIntegerError(im, &m_emlrtDCI);
      }
      if (((int)im < 1) || ((int)im > 20000)) {
        rtDynamicBoundsError((int)im, 1, 20000, &q_emlrtBCI);
      }
      i1 = (int)im;
    }
    i1 -= i;
    nx = (int)fmin(params_WindowLength, (double)i1 + 1.0);
    if (nx < 1) {
      nx = 0;
    } else {
      if (params_WindowLength < 1.0) {
        rtDynamicBoundsError(1, 1, (int)params_WindowLength, &n_emlrtBCI);
      }
      if (nx > b_nx) {
        rtDynamicBoundsError(nx, 1, (int)params_WindowLength, &o_emlrtBCI);
      }
    }
    b_temp_a_re_tmp = ((double)naxpy + 1.0) + 0.0 * (temp_a_re_tmp + 1.0);
    if (b_temp_a_re_tmp != (int)b_temp_a_re_tmp) {
      rtIntegerError(b_temp_a_re_tmp, &k_emlrtDCI);
    }
    if (((int)b_temp_a_re_tmp < 1) ||
        ((int)b_temp_a_re_tmp > (int)(temp_a_re_tmp + 1.0))) {
      rtDynamicBoundsError((int)b_temp_a_re_tmp, 1, (int)(temp_a_re_tmp + 1.0),
                           &m_emlrtBCI);
    }
    i1++;
    rtSubAssignSizeCheck(&nx, 1, &i1, 1, &d_emlrtECI);
    for (i1 = 0; i1 < nx; i1++) {
      idx_data[i1 + residualBuff->size[0] * ((int)b_temp_a_re_tmp - 1)] =
          residual[(i + i1) - 1];
    }
  }
  nx_m_nb = 1;
  b_w_data = 0;
  nx = 0;
  if (residualBuff->size[0] == 0) {
    nx_m_nb = 0;
    nx = 1;
  } else if (residualBuff->size[0] == 1) {
    b_w_data = 1;
    nx = 1;
  }
  i = w->size[0];
  w->size[0] = nx_m_nb;
  emxEnsureCapacity_real_T(w, i);
  w_data = w->data;
  for (i = 0; i < nx_m_nb; i++) {
    w_data[0] = b_w_data;
  }
  if (nx == 0) {
    resHopLength = (double)residualBuff->size[0] + 1.0;
    if (resHopLength - resHopLength != 0.0) {
      k_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
    }
    nx_m_nb = (int)fmod(resHopLength, 2.0);
    if (nx_m_nb == 0) {
      nx_m_nb = 0;
    }
    if (nx_m_nb == 0) {
      int iv[2];
      b_calc_window(((double)residualBuff->size[0] + 1.0) / 2.0,
                    (double)residualBuff->size[0] + 1.0, w);
      w_data = w->data;
      if (w->size[0] < 2) {
        i = 0;
        i1 = 1;
        b_nx = -1;
      } else {
        i = w->size[0] - 1;
        i1 = -1;
        b_nx = 1;
      }
      iv[0] = 1;
      nx = div_s32(b_nx - i, i1);
      iv[1] = nx + 1;
      indexShapeCheck(w->size[0], iv);
      loop_ub = (w->size[0] + nx) + 1;
      b_nx = b_w->size[0];
      b_w->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_w, b_nx);
      A_data = b_w->data;
      nx_m_nb = w->size[0];
      for (b_nx = 0; b_nx < nx_m_nb; b_nx++) {
        A_data[b_nx] = w_data[b_nx];
      }
      for (b_nx = 0; b_nx <= nx; b_nx++) {
        A_data[b_nx + w->size[0]] = w_data[i + i1 * b_nx];
      }
      i = w->size[0];
      w->size[0] = loop_ub;
      emxEnsureCapacity_real_T(w, i);
      w_data = w->data;
      for (i = 0; i < loop_ub; i++) {
        w_data[i] = A_data[i];
      }
    } else {
      int iv[2];
      b_calc_window((((double)residualBuff->size[0] + 1.0) + 1.0) / 2.0,
                    (double)residualBuff->size[0] + 1.0, w);
      w_data = w->data;
      if (w->size[0] - 1 < 2) {
        i = 0;
        i1 = 1;
        b_nx = -1;
      } else {
        if ((w->size[0] - 1 < 1) || (w->size[0] - 1 > w->size[0])) {
          rtDynamicBoundsError(w->size[0] - 1, 1, w->size[0], &b_emlrtBCI);
        }
        i = w->size[0] - 2;
        i1 = -1;
        if (w->size[0] < 2) {
          rtDynamicBoundsError(2, 1, w->size[0], &emlrtBCI);
        }
        b_nx = 1;
      }
      iv[0] = 1;
      nx = div_s32(b_nx - i, i1);
      iv[1] = nx + 1;
      indexShapeCheck(w->size[0], iv);
      loop_ub = (w->size[0] + nx) + 1;
      b_nx = b_w->size[0];
      b_w->size[0] = loop_ub;
      emxEnsureCapacity_real_T(b_w, b_nx);
      A_data = b_w->data;
      nx_m_nb = w->size[0];
      for (b_nx = 0; b_nx < nx_m_nb; b_nx++) {
        A_data[b_nx] = w_data[b_nx];
      }
      for (b_nx = 0; b_nx <= nx; b_nx++) {
        A_data[b_nx + w->size[0]] = w_data[i + i1 * b_nx];
      }
      i = w->size[0];
      w->size[0] = loop_ub;
      emxEnsureCapacity_real_T(w, i);
      w_data = w->data;
      for (i = 0; i < loop_ub; i++) {
        w_data[i] = A_data[i];
      }
    }
  }
  emxFree_real_T(&b_w);
  i = inv->size[0] * inv->size[1];
  inv->size[0] = residualBuff->size[0];
  inv->size[1] = residualBuff->size[1];
  emxEnsureCapacity_real_T(inv, i);
  inv_data = inv->data;
  nx = residualBuff->size[0] * residualBuff->size[1] - 1;
  for (i = 0; i <= nx; i++) {
    inv_data[i] = idx_data[i];
  }
  bsxfun(inv, w, residualBuff);
  emxFree_real_T(&w);
  emxFree_real_T(&inv);
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void j_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Arrays have incompatible sizes for this operation.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 * Return Type  : void
 */
static void minus(emxArray_real_T *in1, const emxArray_real_T *in2)
{
  emxArray_real_T *b_in1;
  const double *in2_data;
  double *b_in1_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 2);
  loop_ub = in1->size[0];
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = loop_ub;
  if (in2->size[1] == 1) {
    b_loop_ub = in1->size[1];
  } else {
    b_loop_ub = in2->size[1];
  }
  b_in1->size[1] = b_loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_1 = (in1->size[1] != 1);
  stride_1_1 = (in2->size[1] != 1);
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < b_loop_ub; i++) {
    int scalarLB;
    int vectorUB;
    scalarLB = (loop_ub / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i1 = 0; i1 <= vectorUB; i1 += 2) {
      __m128d r;
      __m128d r1;
      r = _mm_loadu_pd(&in1_data[i1 + in1->size[0] * aux_0_1]);
      r1 = _mm_loadu_pd(&in2_data[i1 + in2->size[0] * aux_1_1]);
      _mm_storeu_pd(&b_in1_data[i1 + b_in1->size[0] * i], _mm_sub_pd(r, r1));
    }
    for (i1 = scalarLB; i1 < loop_ub; i1++) {
      b_in1_data[i1 + b_in1->size[0] * i] =
          in1_data[i1 + in1->size[0] * aux_0_1] -
          in2_data[i1 + in2->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  loop_ub = b_in1->size[0];
  i = in1->size[0] * in1->size[1];
  in1->size[0] = b_in1->size[0];
  emxEnsureCapacity_real_T(in1, i);
  b_loop_ub = b_in1->size[1];
  i = in1->size[0] * in1->size[1];
  in1->size[1] = b_in1->size[1];
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  for (i = 0; i < b_loop_ub; i++) {
    for (i1 = 0; i1 < loop_ub; i1++) {
      in1_data[i1 + in1->size[0] * i] = b_in1_data[i1 + b_in1->size[0] * i];
    }
  }
  emxFree_real_T(&b_in1);
}

/*
 * Arguments    : const int *aDims1
 *                const int aNDims1
 *                const int *aDims2
 *                const int aNDims2
 *                const rtEqualityCheckInfo *aInfo
 * Return Type  : void
 */
static void rtSubAssignSizeCheck(const int *aDims1, const int aNDims1,
                                 const int *aDims2, const int aNDims2,
                                 const rtEqualityCheckInfo *aInfo)
{
  int i;
  int j;
  char b_dims2Str[1024];
  char dims1Str[1024];
  char dims2Str[1024];
  i = 0;
  j = 0;
  while ((i < aNDims1) && (j < aNDims2)) {
    while ((i < aNDims1) && (aDims1[i] == 1)) {
      i++;
    }
    while ((j < aNDims2) && (aDims2[j] == 1)) {
      j++;
    }
    if (((i < aNDims1) || (j < aNDims2)) &&
        ((i == aNDims1) || ((j == aNDims2) || ((aDims1[i] != -1) &&
                                               ((aDims2[j] != -1) &&
                                                (aDims1[i] != aDims2[j])))))) {
      rtGenSizeString(aNDims1, aDims1, dims1Str);
      rtGenSizeString(aNDims1, aDims2, dims2Str);
      memcpy(&b_dims2Str[0], &dims2Str[0], 1024U * sizeof(char));
      fprintf(stderr, "Subscripted assignment dimension mismatch: %s ~= %s.",
              dims1Str, b_dims2Str);
      fprintf(stderr, "\n");
      rtReportErrorLocation(aInfo->fName, aInfo->lineNo);
      fflush(stderr);
      abort();
    }
    i++;
    j++;
  }
}

/*
 * Arguments    : emxArray_real_T *y
 *                double fs
 *                double params_WindowLength
 *                double params_OverlapLength
 *                emxArray_real_T *f0
 * Return Type  : void
 */
void SRH(emxArray_real_T *y, double fs, double params_WindowLength,
         double params_OverlapLength, emxArray_real_T *f0)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,                                    /* iFirst */
      -1,                                    /* iLast */
      88,                                    /* lineNo */
      13,                                    /* colNo */
      "",                                    /* aName */
      "computeHarmonicSummationOfResiduals", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo d_emlrtBCI = {
      -1,                                    /* iFirst */
      -1,                                    /* iLast */
      88,                                    /* lineNo */
      15,                                    /* colNo */
      "",                                    /* aName */
      "computeHarmonicSummationOfResiduals", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m", /* pName */
      0               /* checkKind */
  };
  static rtEqualityCheckInfo b_emlrtECI = {
      -1,                                    /* nDims */
      92,                                    /* lineNo */
      1,                                     /* colNo */
      "computeHarmonicSummationOfResiduals", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m" /* pName */
  };
  static rtEqualityCheckInfo emlrtECI = {
      2,                                     /* nDims */
      93,                                    /* lineNo */
      5,                                     /* colNo */
      "computeHarmonicSummationOfResiduals", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\SRH.m" /* pName */
  };
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      13,                    /* lineNo */
      "assertCompatibleDims" /* fName */
  };
  __m128d r2;
  __m128d r3;
  emxArray_creal_T *b_x;
  emxArray_creal_T *res;
  emxArray_real_T *b_r;
  emxArray_real_T *b_w;
  emxArray_real_T *b_y;
  emxArray_real_T *domain;
  emxArray_real_T *r;
  emxArray_real_T *r1;
  emxArray_real_T *w;
  creal_T *res_data;
  creal_T *x_data;
  double *b_w_data;
  double *domain_data;
  double *r_data;
  double *y_data;
  int iv[2];
  int b_loop_ub;
  int i;
  int i1;
  int loop_ub;
  int nx;
  int trivialwin;
  short b_x_data[131];
  signed char w_data;
  y_data = y->data;
  emxInit_real_T(&w, 1);
  nx = 1;
  w_data = 0;
  trivialwin = 0;
  if (y->size[0] == 0) {
    nx = 0;
    trivialwin = 1;
  } else if (y->size[0] == 1) {
    w_data = 1;
    trivialwin = 1;
  }
  i = w->size[0];
  w->size[0] = nx;
  emxEnsureCapacity_real_T(w, i);
  domain_data = w->data;
  for (i = 0; i < nx; i++) {
    domain_data[0] = w_data;
  }
  emxInit_real_T(&b_w, 1);
  if (trivialwin == 0) {
    double x;
    x = (double)y->size[0] + 1.0;
    if (x - x != 0.0) {
      k_rtErrorWithMessageID(c_emlrtRTEI.fName, c_emlrtRTEI.lineNo);
    }
    nx = (int)fmod(x, 2.0);
    if (nx == 0) {
      nx = 0;
    }
    if (nx == 0) {
      calc_window(((double)y->size[0] + 1.0) / 2.0, (double)y->size[0] + 1.0,
                  w);
      domain_data = w->data;
      if (w->size[0] < 2) {
        i = 0;
        nx = 1;
        i1 = -1;
      } else {
        i = w->size[0] - 1;
        nx = -1;
        i1 = 1;
      }
      iv[0] = 1;
      loop_ub = div_s32(i1 - i, nx);
      iv[1] = loop_ub + 1;
      indexShapeCheck(w->size[0], iv);
      b_loop_ub = (w->size[0] + loop_ub) + 1;
      i1 = b_w->size[0];
      b_w->size[0] = b_loop_ub;
      emxEnsureCapacity_real_T(b_w, i1);
      b_w_data = b_w->data;
      trivialwin = w->size[0];
      for (i1 = 0; i1 < trivialwin; i1++) {
        b_w_data[i1] = domain_data[i1];
      }
      for (i1 = 0; i1 <= loop_ub; i1++) {
        b_w_data[i1 + w->size[0]] = domain_data[i + nx * i1];
      }
      i = w->size[0];
      w->size[0] = b_loop_ub;
      emxEnsureCapacity_real_T(w, i);
      domain_data = w->data;
      for (i = 0; i < b_loop_ub; i++) {
        domain_data[i] = b_w_data[i];
      }
    } else {
      calc_window((((double)y->size[0] + 1.0) + 1.0) / 2.0,
                  (double)y->size[0] + 1.0, w);
      domain_data = w->data;
      if (w->size[0] - 1 < 2) {
        i = 0;
        nx = 1;
        i1 = -1;
      } else {
        if ((w->size[0] - 1 < 1) || (w->size[0] - 1 > w->size[0])) {
          rtDynamicBoundsError(w->size[0] - 1, 1, w->size[0], &b_emlrtBCI);
        }
        i = w->size[0] - 2;
        nx = -1;
        if (w->size[0] < 2) {
          rtDynamicBoundsError(2, 1, w->size[0], &emlrtBCI);
        }
        i1 = 1;
      }
      iv[0] = 1;
      loop_ub = div_s32(i1 - i, nx);
      iv[1] = loop_ub + 1;
      indexShapeCheck(w->size[0], iv);
      b_loop_ub = (w->size[0] + loop_ub) + 1;
      i1 = b_w->size[0];
      b_w->size[0] = b_loop_ub;
      emxEnsureCapacity_real_T(b_w, i1);
      b_w_data = b_w->data;
      trivialwin = w->size[0];
      for (i1 = 0; i1 < trivialwin; i1++) {
        b_w_data[i1] = domain_data[i1];
      }
      for (i1 = 0; i1 <= loop_ub; i1++) {
        b_w_data[i1 + w->size[0]] = domain_data[i + nx * i1];
      }
      i = w->size[0];
      w->size[0] = b_loop_ub;
      emxEnsureCapacity_real_T(w, i);
      domain_data = w->data;
      for (i = 0; i < b_loop_ub; i++) {
        domain_data[i] = b_w_data[i];
      }
    }
  }
  emxInit_real_T(&r, 2);
  i = r->size[0] * r->size[1];
  r->size[0] = y->size[0];
  r->size[1] = y->size[1];
  emxEnsureCapacity_real_T(r, i);
  r_data = r->data;
  loop_ub = y->size[0] * y->size[1] - 1;
  for (i = 0; i <= loop_ub; i++) {
    r_data[i] = y_data[i];
  }
  bsxfun(r, w, y);
  computeResidual(y, fs, params_WindowLength, params_OverlapLength, r);
  emxInit_creal_T(&res, 2);
  fft(r, rt_roundd_snf(fs), res);
  res_data = res->data;
  if (res->size[0] < 1) {
    rtDynamicBoundsError(1, 1, res->size[0], &c_emlrtBCI);
  }
  if (res->size[0] < 1000) {
    rtDynamicBoundsError(1000, 1, res->size[0], &d_emlrtBCI);
  }
  emxInit_creal_T(&b_x, 2);
  i = b_x->size[0] * b_x->size[1];
  b_x->size[0] = 1000;
  loop_ub = res->size[1];
  b_x->size[1] = res->size[1];
  emxEnsureCapacity_creal_T(b_x, i);
  x_data = b_x->data;
  for (i = 0; i < loop_ub; i++) {
    for (nx = 0; nx < 1000; nx++) {
      x_data[nx + b_x->size[0] * i] = res_data[nx + res->size[0] * i];
    }
  }
  nx = 1000 * res->size[1];
  i = r->size[0] * r->size[1];
  r->size[0] = 1000;
  r->size[1] = res->size[1];
  emxEnsureCapacity_real_T(r, i);
  r_data = r->data;
  if (nx > 2147483646) {
    check_forloop_overflow_error();
  }
  for (trivialwin = 0; trivialwin < nx; trivialwin++) {
    r_data[trivialwin] =
        rt_hypotd_snf(x_data[trivialwin].re, x_data[trivialwin].im);
  }
  emxFree_creal_T(&b_x);
  emxInit_real_T(&domain, 2);
  i = domain->size[0] * domain->size[1];
  domain->size[0] = 200;
  domain->size[1] = res->size[1];
  emxEnsureCapacity_real_T(domain, i);
  domain_data = domain->data;
  b_loop_ub = 200 * r->size[1];
  for (i = 0; i < b_loop_ub; i++) {
    domain_data[i] = 0.0;
  }
  for (trivialwin = 0; trivialwin < 131; trivialwin++) {
    b_x_data[trivialwin] =
        (short)rt_roundd_snf(1.5 * ((double)trivialwin + 70.0));
  }
  emxInit_real_T(&b_r, 2);
  i = b_r->size[0] * b_r->size[1];
  b_r->size[0] = 131;
  b_r->size[1] = res->size[1];
  emxEnsureCapacity_real_T(b_r, i);
  b_w_data = b_r->data;
  for (i = 0; i < loop_ub; i++) {
    for (nx = 0; nx < 131; nx++) {
      b_w_data[nx + b_r->size[0] * i] =
          r_data[(b_x_data[nx] + r->size[0] * i) - 1];
    }
  }
  emxInit_real_T(&r1, 2);
  if (r->size[1] == b_r->size[1]) {
    i = r1->size[0] * r1->size[1];
    r1->size[0] = 131;
    r1->size[1] = res->size[1];
    emxEnsureCapacity_real_T(r1, i);
    y_data = r1->data;
    for (i = 0; i < loop_ub; i++) {
      for (nx = 0; nx < 131; nx++) {
        y_data[nx + r1->size[0] * i] =
            (r_data[(nx + r->size[0] * i) + 69] +
             r_data[(((nx + 70) << 1) + r->size[0] * i) - 1]) -
            b_w_data[nx + b_r->size[0] * i];
      }
    }
  } else {
    binary_expand_op_6(r1, r, b_r);
    y_data = r1->data;
  }
  emxFree_creal_T(&res);
  loop_ub = r1->size[1];
  if ((r1->size[1] != r->size[1]) &&
      ((r1->size[1] != 1) && (r->size[1] != 1))) {
    emlrtDimSizeImpxCheckR2021b(r1->size[1], r->size[1], &emlrtECI);
  }
  if (r1->size[1] == r->size[1]) {
    b_loop_ub = r1->size[0];
    i = b_r->size[0] * b_r->size[1];
    b_r->size[0] = r1->size[0];
    b_r->size[1] = r1->size[1];
    emxEnsureCapacity_real_T(b_r, i);
    b_w_data = b_r->data;
    for (i = 0; i < loop_ub; i++) {
      for (nx = 0; nx < b_loop_ub; nx++) {
        b_w_data[nx + b_r->size[0] * i] =
            y_data[nx + r1->size[0] * i] +
            r_data[(3 * (nx + 70) + r->size[0] * i) - 1];
      }
    }
  } else {
    binary_expand_op_5(b_r, r1, r);
    b_w_data = b_r->data;
  }
  for (trivialwin = 0; trivialwin < 131; trivialwin++) {
    b_x_data[trivialwin] =
        (short)rt_roundd_snf(2.5 * ((double)trivialwin + 70.0));
  }
  i = r1->size[0] * r1->size[1];
  r1->size[0] = 131;
  loop_ub = r->size[1];
  r1->size[1] = r->size[1];
  emxEnsureCapacity_real_T(r1, i);
  y_data = r1->data;
  for (i = 0; i < loop_ub; i++) {
    for (nx = 0; nx < 131; nx++) {
      y_data[nx + r1->size[0] * i] =
          r_data[(b_x_data[nx] + r->size[0] * i) - 1];
    }
  }
  if ((b_r->size[1] != r->size[1]) &&
      ((b_r->size[1] != 1) && (r->size[1] != 1))) {
    emlrtDimSizeImpxCheckR2021b(b_r->size[1], r->size[1], &emlrtECI);
  }
  if (b_r->size[1] == r1->size[1]) {
    loop_ub = b_r->size[0] * b_r->size[1];
    trivialwin = (loop_ub / 2) << 1;
    nx = trivialwin - 2;
    for (i = 0; i <= nx; i += 2) {
      r2 = _mm_loadu_pd(&b_w_data[i]);
      r3 = _mm_loadu_pd(&y_data[i]);
      _mm_storeu_pd(&b_w_data[i], _mm_sub_pd(r2, r3));
    }
    for (i = trivialwin; i < loop_ub; i++) {
      b_w_data[i] -= y_data[i];
    }
  } else {
    minus(b_r, r1);
    b_w_data = b_r->data;
  }
  loop_ub = b_r->size[1];
  if ((b_r->size[1] != r->size[1]) &&
      ((b_r->size[1] != 1) && (r->size[1] != 1))) {
    emlrtDimSizeImpxCheckR2021b(b_r->size[1], r->size[1], &emlrtECI);
  }
  if (b_r->size[1] == r->size[1]) {
    b_loop_ub = b_r->size[0];
    i = r1->size[0] * r1->size[1];
    r1->size[0] = b_r->size[0];
    r1->size[1] = b_r->size[1];
    emxEnsureCapacity_real_T(r1, i);
    y_data = r1->data;
    for (i = 0; i < loop_ub; i++) {
      for (nx = 0; nx < b_loop_ub; nx++) {
        y_data[nx + r1->size[0] * i] =
            b_w_data[nx + b_r->size[0] * i] +
            r_data[(((nx + 70) << 2) + r->size[0] * i) - 1];
      }
    }
  } else {
    binary_expand_op_4(r1, b_r, r);
    y_data = r1->data;
  }
  for (trivialwin = 0; trivialwin < 131; trivialwin++) {
    b_x_data[trivialwin] =
        (short)rt_roundd_snf(3.5 * ((double)trivialwin + 70.0));
  }
  i = b_r->size[0] * b_r->size[1];
  b_r->size[0] = 131;
  loop_ub = r->size[1];
  b_r->size[1] = r->size[1];
  emxEnsureCapacity_real_T(b_r, i);
  b_w_data = b_r->data;
  for (i = 0; i < loop_ub; i++) {
    for (nx = 0; nx < 131; nx++) {
      b_w_data[nx + b_r->size[0] * i] =
          r_data[(b_x_data[nx] + r->size[0] * i) - 1];
    }
  }
  if ((r1->size[1] != r->size[1]) &&
      ((r1->size[1] != 1) && (r->size[1] != 1))) {
    emlrtDimSizeImpxCheckR2021b(r1->size[1], r->size[1], &emlrtECI);
  }
  if (r1->size[1] == b_r->size[1]) {
    loop_ub = r1->size[0] * r1->size[1];
    trivialwin = (loop_ub / 2) << 1;
    nx = trivialwin - 2;
    for (i = 0; i <= nx; i += 2) {
      r2 = _mm_loadu_pd(&y_data[i]);
      r3 = _mm_loadu_pd(&b_w_data[i]);
      _mm_storeu_pd(&y_data[i], _mm_sub_pd(r2, r3));
    }
    for (i = trivialwin; i < loop_ub; i++) {
      y_data[i] -= b_w_data[i];
    }
  } else {
    minus(r1, b_r);
    y_data = r1->data;
  }
  loop_ub = r1->size[1];
  if ((r1->size[1] != r->size[1]) &&
      ((r1->size[1] != 1) && (r->size[1] != 1))) {
    emlrtDimSizeImpxCheckR2021b(r1->size[1], r->size[1], &emlrtECI);
  }
  if (r1->size[1] == r->size[1]) {
    b_loop_ub = r1->size[0];
    i = b_r->size[0] * b_r->size[1];
    b_r->size[0] = r1->size[0];
    b_r->size[1] = r1->size[1];
    emxEnsureCapacity_real_T(b_r, i);
    b_w_data = b_r->data;
    for (i = 0; i < loop_ub; i++) {
      for (nx = 0; nx < b_loop_ub; nx++) {
        b_w_data[nx + b_r->size[0] * i] =
            y_data[nx + r1->size[0] * i] +
            r_data[(5 * (nx + 70) + r->size[0] * i) - 1];
      }
    }
  } else {
    binary_expand_op_3(b_r, r1, r);
    b_w_data = b_r->data;
  }
  for (trivialwin = 0; trivialwin < 131; trivialwin++) {
    b_x_data[trivialwin] =
        (short)rt_roundd_snf(4.5 * ((double)trivialwin + 70.0));
  }
  i = r1->size[0] * r1->size[1];
  r1->size[0] = 131;
  loop_ub = r->size[1];
  r1->size[1] = r->size[1];
  emxEnsureCapacity_real_T(r1, i);
  y_data = r1->data;
  for (i = 0; i < loop_ub; i++) {
    for (nx = 0; nx < 131; nx++) {
      y_data[nx + r1->size[0] * i] =
          r_data[(b_x_data[nx] + r->size[0] * i) - 1];
    }
  }
  if ((b_r->size[1] != r->size[1]) &&
      ((b_r->size[1] != 1) && (r->size[1] != 1))) {
    emlrtDimSizeImpxCheckR2021b(b_r->size[1], r->size[1], &emlrtECI);
  }
  if (b_r->size[1] == r1->size[1]) {
    b_loop_ub = b_r->size[0] * b_r->size[1];
    trivialwin = (b_loop_ub / 2) << 1;
    nx = trivialwin - 2;
    for (i = 0; i <= nx; i += 2) {
      r2 = _mm_loadu_pd(&b_w_data[i]);
      r3 = _mm_loadu_pd(&y_data[i]);
      _mm_storeu_pd(&b_w_data[i], _mm_sub_pd(r2, r3));
    }
    for (i = trivialwin; i < b_loop_ub; i++) {
      b_w_data[i] -= y_data[i];
    }
  } else {
    minus(b_r, r1);
    b_w_data = b_r->data;
  }
  emxFree_real_T(&r1);
  iv[0] = 131;
  iv[1] = r->size[1];
  rtSubAssignSizeCheck(&iv[0], 2, &b_r->size[0], 2, &b_emlrtECI);
  emxFree_real_T(&r);
  for (i = 0; i < loop_ub; i++) {
    for (nx = 0; nx < 131; nx++) {
      domain_data[(nx + 200 * i) + 69] = b_w_data[nx + 131 * i];
    }
  }
  double dv[2];
  emxFree_real_T(&b_r);
  dv[0] = 70.0;
  dv[1] = 200.0;
  getCandidates(domain, dv, w, f0);
  domain_data = w->data;
  emxFree_real_T(&domain);
  nx = w->size[0];
  i = b_w->size[0];
  b_w->size[0] = w->size[0];
  emxEnsureCapacity_real_T(b_w, i);
  b_w_data = b_w->data;
  if (w->size[0] > 2147483646) {
    check_forloop_overflow_error();
  }
  for (trivialwin = 0; trivialwin < nx; trivialwin++) {
    b_w_data[trivialwin] = fabs(domain_data[trivialwin]);
  }
  emxInit_real_T(&b_y, 1);
  if (b_w->size[0] == 0) {
    b_y->size[0] = 0;
  } else {
    i = b_y->size[0];
    b_y->size[0] = w->size[0];
    emxEnsureCapacity_real_T(b_y, i);
    if (b_w->size[0] > 2147483646) {
      check_forloop_overflow_error();
    }
  }
  emxFree_real_T(&b_w);
  if ((w->size[0] != 1) && (b_y->size[0] != 1) &&
      (w->size[0] != b_y->size[0])) {
    j_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  emxFree_real_T(&b_y);
  emxFree_real_T(&w);
}

/*
 * File trailer for SRH.c
 *
 * [EOF]
 */
