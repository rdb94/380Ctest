/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: pitch.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "pitch.h"
#include "LHS.h"
#include "NCF.h"
#include "PEF.h"
#include "SRH.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "bsxfun.h"
#include "eml_int_forloop_overflow_check.h"
#include "fft.h"
#include "getCandidates.h"
#include "hamming.h"
#include "ifft.h"
#include "movmedian.h"
#include "rt_nonfinite.h"
#include "validator_check_size.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static void b_rtErrorWithMessageID(const int i, const char *r,
                                   const char *aFcnName, int aLineNum);

static void c_rtErrorWithMessageID(const int i, const char *r,
                                   const char *aFcnName, int aLineNum);

static void cb_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                    int aLineNum);

static void d_rtErrorWithMessageID(const int i, const char *r,
                                   const char *aFcnName, int aLineNum);

static void db_rtErrorWithMessageID(const char *r, const char *r1,
                                    const char *r2, const char *r3,
                                    const char *aFcnName, int aLineNum);

static void eb_rtErrorWithMessageID(const char *r, const char *r1,
                                    const char *aFcnName, int aLineNum);

static void f_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void fb_rtErrorWithMessageID(const char *r, const int i, const char *r1,
                                    const char *aFcnName, int aLineNum);

static void g_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void hb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void iDetectPitch(const double x[20000], double fs,
                         const double options_Range[2],
                         double options_WindowLength,
                         double options_OverlapLength,
                         const char options_Method[3], emxArray_real_T *f0);

/* Function Definitions */
/*
 * Arguments    : const int i
 *                const char *r
 *                const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void b_rtErrorWithMessageID(const int i, const char *r,
                                   const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Expected %.*s to be integer-valued.", i, r);
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const int i
 *                const char *r
 *                const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void c_rtErrorWithMessageID(const int i, const char *r,
                                   const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Expected %.*s to be finite.", i, r);
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *r
 *                const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void cb_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                    int aLineNum)
{
  fprintf(stderr, "Expected %.*s to be positive.", 2, r);
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const int i
 *                const char *r
 *                const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void d_rtErrorWithMessageID(const int i, const char *r,
                                   const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Expected %.*s to be non-NaN.", i, r);
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *r
 *                const char *r1
 *                const char *r2
 *                const char *r3
 *                const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void db_rtErrorWithMessageID(const char *r, const char *r1,
                                    const char *r2, const char *r3,
                                    const char *aFcnName, int aLineNum)
{
  fprintf(stderr,
          "Invalid window length. %.*s must be in the range %.*s, where %.*s "
          "is the audio input.\nThe default window length depends on the "
          "specified sample rate: %.*s.",
          12, r, 13, r1, 1, r2, 15, r3);
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *r
 *                const char *r1
 *                const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void eb_rtErrorWithMessageID(const char *r, const char *r1,
                                    const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Invalid overlap length. %.*s must be less than %.*s.", 13, r,
          12, r1);
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
static void f_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "To RESHAPE the number of elements must not change.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *r
 *                const int i
 *                const char *r1
 *                const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void fb_rtErrorWithMessageID(const char *r, const int i, const char *r1,
                                    const char *aFcnName, int aLineNum)
{
  fprintf(stderr,
          "Invalid specifications. To use the %.*s method, specify a valid "
          "combination of input arguments:\n\n     %.*s\n\nValid combinatio"
          "ns rely on Name-Value pair arguments. Consult the documentation for "
          "default optional Name-Value pair arguments.",
          3, r, i, r1);
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
static void g_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Size vector elements should be nonnegative.");
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
static void h_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr,
          "To RESHAPE the number of elements must not change, and if the input "
          "is empty, the maximum dimension length cannot be increased u"
          "nless the output size is fixed.");
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
static void hb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Size argument must be an integer in the range: %d to %d.",
          MIN_int32_T, MAX_int32_T);
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const double x[20000]
 *                double fs
 *                const double options_Range[2]
 *                double options_WindowLength
 *                double options_OverlapLength
 *                const char options_Method[3]
 *                emxArray_real_T *f0
 * Return Type  : void
 */
static void iDetectPitch(const double x[20000], double fs,
                         const double options_Range[2],
                         double options_WindowLength,
                         double options_OverlapLength,
                         const char options_Method[3], emxArray_real_T *f0)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,       /* iFirst */
      -1,       /* iLast */
      28,       /* lineNo */
      50,       /* colNo */
      "",       /* aName */
      "buffer", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "spectraldescriptors\\buffer.m", /* pName */
      0                                /* checkKind */
  };
  static rtBoundsCheckInfo d_emlrtBCI = {
      -1,       /* iFirst */
      -1,       /* iLast */
      28,       /* lineNo */
      19,       /* colNo */
      "",       /* aName */
      "buffer", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "spectraldescriptors\\buffer.m", /* pName */
      0                                /* checkKind */
  };
  static rtBoundsCheckInfo e_emlrtBCI = {
      -1,       /* iFirst */
      -1,       /* iLast */
      28,       /* lineNo */
      21,       /* colNo */
      "",       /* aName */
      "buffer", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\signal\\signal\\+signal\\+internal\\+"
      "spectraldescriptors\\buffer.m", /* pName */
      0                                /* checkKind */
  };
  static rtBoundsCheckInfo f_emlrtBCI = {
      -1,                   /* iFirst */
      -1,                   /* iLast */
      48,                   /* lineNo */
      15,                   /* colNo */
      "",                   /* aName */
      "getTrimmedSpectrum", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\LHS.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo g_emlrtBCI = {
      -1,                   /* iFirst */
      -1,                   /* iLast */
      48,                   /* lineNo */
      17,                   /* colNo */
      "",                   /* aName */
      "getTrimmedSpectrum", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\LHS.m", /* pName */
      0               /* checkKind */
  };
  static rtBoundsCheckInfo h_emlrtBCI = {
      -1,      /* iFirst */
      -1,      /* iLast */
      191,     /* lineNo */
      7,       /* colNo */
      "",      /* aName */
      "iClip", /* fName */
      "C:\\Program Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\pitch.m", /* pName
                                                                            */
      0 /* checkKind */
  };
  static rtBoundsCheckInfo i_emlrtBCI = {
      -1,      /* iFirst */
      -1,      /* iLast */
      192,     /* lineNo */
      7,       /* colNo */
      "",      /* aName */
      "iClip", /* fName */
      "C:\\Program Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\pitch.m", /* pName
                                                                            */
      0 /* checkKind */
  };
  static rtDoubleCheckInfo e_emlrtDCI = {
      159,           /* lineNo */
      "iDetectPitch" /* fName */
  };
  static rtDoubleCheckInfo f_emlrtDCI = {
      159,           /* lineNo */
      "iDetectPitch" /* fName */
  };
  static rtDoubleCheckInfo g_emlrtDCI = {
      24,      /* lineNo */
      "buffer" /* fName */
  };
  static rtDoubleCheckInfo h_emlrtDCI = {
      24,      /* lineNo */
      "buffer" /* fName */
  };
  static rtDoubleCheckInfo i_emlrtDCI = {
      24,      /* lineNo */
      "buffer" /* fName */
  };
  static rtDoubleCheckInfo j_emlrtDCI = {
      24,      /* lineNo */
      "buffer" /* fName */
  };
  static rtDoubleCheckInfo k_emlrtDCI = {
      159,           /* lineNo */
      "iDetectPitch" /* fName */
  };
  static rtDoubleCheckInfo l_emlrtDCI = {
      28,      /* lineNo */
      "buffer" /* fName */
  };
  static rtDoubleCheckInfo m_emlrtDCI = {
      28,      /* lineNo */
      "buffer" /* fName */
  };
  static rtEqualityCheckInfo emlrtECI = {
      2,     /* nDims */
      23,    /* lineNo */
      5,     /* colNo */
      "LHS", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\LHS.m" /* pName */
  };
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      58,                  /* lineNo */
      "assertValidSizeArg" /* fName */
  };
  static rtRunTimeErrorInfo o_emlrtRTEI = {
      64,                  /* lineNo */
      "assertValidSizeArg" /* fName */
  };
  static rtRunTimeErrorInfo p_emlrtRTEI = {
      74,                 /* lineNo */
      "reshapeSizeChecks" /* fName */
  };
  static rtRunTimeErrorInfo q_emlrtRTEI = {
      79,                 /* lineNo */
      "reshapeSizeChecks" /* fName */
  };
  static rtRunTimeErrorInfo r_emlrtRTEI = {
      81,                 /* lineNo */
      "reshapeSizeChecks" /* fName */
  };
  static const char a[3] = {'P', 'E', 'F'};
  static const char b[3] = {'S', 'R', 'H'};
  static const char b_a[3] = {'C', 'E', 'P'};
  static const char c_a[3] = {'L', 'H', 'S'};
  emxArray_creal_T *Yfull;
  emxArray_real_T *c_y;
  emxArray_real_T *hammingWindow;
  emxArray_real_T *r;
  emxArray_real_T *yw;
  creal_T *Yfull_data;
  double edge[2];
  double N;
  double b_y;
  double d;
  double hopLength;
  double numToPad;
  double y;
  double *hammingWindow_data;
  double *y_data;
  int eint;
  int i;
  int k;
  int loop_ub;
  int ret;
  int vectorUB;
  hopLength = options_WindowLength - options_OverlapLength;
  y = ceil((20000.0 - options_WindowLength) / hopLength);
  ret = memcmp(&options_Method[0], &b[0], 3);
  if (ret == 0) {
    N = rt_roundd_snf(0.025 * fs);
    hopLength = rt_roundd_snf(0.005 * fs);
  } else {
    N = options_WindowLength;
  }
  numToPad =
      ((N + (ceil((20000.0 - N) / hopLength) + 1.0) * hopLength) - 20000.0) -
      1.0;
  emxInit_real_T(&hammingWindow, 1);
  if (!(numToPad >= 0.0)) {
    rtNonNegativeError(numToPad, &e_emlrtDCI);
  }
  k = (int)floor(numToPad);
  if (numToPad != k) {
    rtIntegerError(numToPad, &f_emlrtDCI);
  }
  i = hammingWindow->size[0];
  loop_ub = (int)numToPad;
  hammingWindow->size[0] = loop_ub + 20000;
  emxEnsureCapacity_real_T(hammingWindow, i);
  hammingWindow_data = hammingWindow->data;
  for (i = 0; i < 20000; i++) {
    hammingWindow_data[i] = x[i];
  }
  if (loop_ub != k) {
    rtIntegerError(numToPad, &f_emlrtDCI);
  }
  for (k = 0; k < loop_ub; k++) {
    hammingWindow_data[k + 20000] = 0.0;
  }
  b_y = floor(((double)hammingWindow->size[0] - N) / hopLength);
  emxInit_real_T(&c_y, 2);
  if (!(N >= 0.0)) {
    rtNonNegativeError(N, &g_emlrtDCI);
  }
  k = (int)floor(N);
  if (N != k) {
    rtIntegerError(N, &h_emlrtDCI);
  }
  if (!(b_y + 1.0 >= 0.0)) {
    rtNonNegativeError(b_y + 1.0, &i_emlrtDCI);
  }
  if (b_y + 1.0 != (int)(b_y + 1.0)) {
    rtIntegerError(b_y + 1.0, &j_emlrtDCI);
  }
  i = (int)N;
  ret = c_y->size[0] * c_y->size[1];
  c_y->size[0] = i;
  vectorUB = (int)(b_y + 1.0);
  c_y->size[1] = (int)(b_y + 1.0);
  emxEnsureCapacity_real_T(c_y, ret);
  y_data = c_y->data;
  if (i != k) {
    rtIntegerError(N, &k_emlrtDCI);
  }
  if (b_y + 1.0 != (int)(b_y + 1.0)) {
    rtIntegerError(b_y + 1.0, &k_emlrtDCI);
  }
  ret = i * (int)(b_y + 1.0);
  for (k = 0; k < ret; k++) {
    y_data[k] = 0.0;
  }
  for (ret = 0; ret < vectorUB; ret++) {
    for (k = 0; k < i; k++) {
      double d1;
      d = ((double)k + 1.0) + hopLength * (((double)ret + 1.0) - 1.0);
      if (d != (int)floor(d)) {
        rtIntegerError(d, &l_emlrtDCI);
      }
      if (((int)d < 1) || ((int)d > loop_ub + 20000)) {
        rtDynamicBoundsError((int)d, 1, (int)numToPad + 20000, &c_emlrtBCI);
      }
      if ((int)((unsigned int)k + 1U) > i) {
        rtDynamicBoundsError((int)((unsigned int)k + 1U), 1, (int)N,
                             &d_emlrtBCI);
      }
      d1 = ((double)ret + 1.0) + 0.0 * (b_y + 1.0);
      if (d1 != (int)d1) {
        rtIntegerError(d1, &m_emlrtDCI);
      }
      if (((int)d1 < 1) || ((int)d1 > (int)(b_y + 1.0))) {
        rtDynamicBoundsError((int)d1, 1, (int)(b_y + 1.0), &e_emlrtBCI);
      }
      y_data[k + c_y->size[0] * ((int)d1 - 1)] = hammingWindow_data[(int)d - 1];
    }
  }
  ret = memcmp(&b[0], &options_Method[0], 3);
  if (ret == 0) {
    ret = 0;
  } else {
    ret = memcmp(&a[0], &options_Method[0], 3);
    if (ret == 0) {
      ret = 1;
    } else {
      ret = memcmp(&b_a[0], &options_Method[0], 3);
      if (ret == 0) {
        ret = 2;
      } else {
        ret = memcmp(&c_a[0], &options_Method[0], 3);
        if (ret == 0) {
          ret = 3;
        } else {
          ret = -1;
        }
      }
    }
  }
  emxInit_real_T(&yw, 2);
  emxInit_creal_T(&Yfull, 2);
  switch (ret) {
  case 0:
    SRH(c_y, fs, options_WindowLength, options_OverlapLength, f0);
    hammingWindow_data = f0->data;
    break;
  case 1:
    PEF(c_y, fs, options_Range, options_WindowLength, f0);
    hammingWindow_data = f0->data;
    break;
  case 2: {
    edge[0] = rt_roundd_snf(fs / 200.0);
    edge[1] = rt_roundd_snf(fs / 70.0);
    hamming(c_y->size[0], hammingWindow);
    bsxfun(c_y, hammingWindow, yw);
    hopLength = fabs(2.0 * options_WindowLength - 1.0);
    if ((!rtIsInf(hopLength)) && (!rtIsNaN(hopLength))) {
      N = frexp(hopLength, &eint);
      hopLength = eint;
      if (N == 0.5) {
        hopLength = (double)eint - 1.0;
      }
    }
    fft(yw, rt_powd_snf(2.0, hopLength), Yfull);
    Yfull_data = Yfull->data;
    ret = Yfull->size[0] * Yfull->size[1];
    k = c_y->size[0] * c_y->size[1];
    c_y->size[0] = Yfull->size[0];
    c_y->size[1] = Yfull->size[1];
    emxEnsureCapacity_real_T(c_y, k);
    y_data = c_y->data;
    if (ret > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < ret; k++) {
      y_data[k] = rt_hypotd_snf(Yfull_data[k].re, Yfull_data[k].im);
    }
    k = yw->size[0] * yw->size[1];
    yw->size[0] = c_y->size[0];
    yw->size[1] = c_y->size[1];
    emxEnsureCapacity_real_T(yw, k);
    hammingWindow_data = yw->data;
    ret = c_y->size[0] * c_y->size[1];
    for (k = 0; k < ret; k++) {
      hopLength = y_data[k];
      hammingWindow_data[k] = hopLength * hopLength;
    }
    if (ret > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < ret; k++) {
      hammingWindow_data[k] = log(hammingWindow_data[k]);
    }
    ifft(yw, Yfull);
    Yfull_data = Yfull->data;
    k = yw->size[0] * yw->size[1];
    yw->size[0] = Yfull->size[0];
    yw->size[1] = Yfull->size[1];
    emxEnsureCapacity_real_T(yw, k);
    hammingWindow_data = yw->data;
    loop_ub = Yfull->size[0] * Yfull->size[1];
    for (k = 0; k < loop_ub; k++) {
      hammingWindow_data[k] = Yfull_data[k].re;
    }
    getCandidates(yw, edge, hammingWindow, f0);
    hammingWindow_data = f0->data;
    loop_ub = f0->size[0];
    ret = (f0->size[0] / 2) << 1;
    vectorUB = ret - 2;
    for (k = 0; k <= vectorUB; k += 2) {
      __m128d r1;
      r1 = _mm_loadu_pd(&hammingWindow_data[k]);
      _mm_storeu_pd(&hammingWindow_data[k], _mm_div_pd(_mm_set1_pd(fs), r1));
    }
    for (k = ret; k < loop_ub; k++) {
      hammingWindow_data[k] = fs / hammingWindow_data[k];
    }
  } break;
  case 3:
    hamming(c_y->size[0], hammingWindow);
    bsxfun(c_y, hammingWindow, yw);
    fft(yw, rt_roundd_snf(fs), Yfull);
    Yfull_data = Yfull->data;
    if (Yfull->size[0] < 1) {
      rtDynamicBoundsError(1, 1, Yfull->size[0], &f_emlrtBCI);
    }
    if (Yfull->size[0] < 1005) {
      rtDynamicBoundsError(1005, 1, Yfull->size[0], &g_emlrtBCI);
    }
    vectorUB = 1005 * Yfull->size[1];
    k = c_y->size[0] * c_y->size[1];
    c_y->size[0] = 1005;
    loop_ub = Yfull->size[1];
    c_y->size[1] = Yfull->size[1];
    emxEnsureCapacity_real_T(c_y, k);
    y_data = c_y->data;
    if (vectorUB > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < vectorUB; k++) {
      ret = k % 1005;
      y_data[k] =
          rt_hypotd_snf(Yfull_data[ret + Yfull->size[0] * (k / 1005)].re,
                        Yfull_data[ret + Yfull->size[0] * (k / 1005)].im);
    }
    for (k = 0; k < vectorUB; k++) {
      y_data[k] = log(y_data[k]);
    }
    emxInit_real_T(&r, 2);
    k = r->size[0] * r->size[1];
    r->size[0] = 201;
    r->size[1] = Yfull->size[1];
    emxEnsureCapacity_real_T(r, k);
    hammingWindow_data = r->data;
    for (k = 0; k < loop_ub; k++) {
      for (i = 0; i < 201; i++) {
        hammingWindow_data[i + 201 * k] =
            y_data[i + c_y->size[0] * k] + y_data[(i << 1) + c_y->size[0] * k];
      }
    }
    if (r->size[1] == c_y->size[1]) {
      k = r->size[0] * r->size[1];
      r->size[0] = 201;
      emxEnsureCapacity_real_T(r, k);
      hammingWindow_data = r->data;
      for (k = 0; k < loop_ub; k++) {
        for (i = 0; i < 201; i++) {
          ret = i + 201 * k;
          hammingWindow_data[ret] += y_data[3 * i + c_y->size[0] * k];
        }
      }
    } else {
      binary_expand_op_2(r, c_y);
    }
    loop_ub = r->size[1];
    if ((r->size[1] != c_y->size[1]) &&
        ((r->size[1] != 1) && (c_y->size[1] != 1))) {
      emlrtDimSizeImpxCheckR2021b(r->size[1], c_y->size[1], &emlrtECI);
    }
    if (r->size[1] == c_y->size[1]) {
      k = r->size[0] * r->size[1];
      r->size[0] = 201;
      emxEnsureCapacity_real_T(r, k);
      hammingWindow_data = r->data;
      for (k = 0; k < loop_ub; k++) {
        for (i = 0; i < 201; i++) {
          ret = i + 201 * k;
          hammingWindow_data[ret] += y_data[(i << 2) + c_y->size[0] * k];
        }
      }
    } else {
      binary_expand_op_1(r, c_y);
      hammingWindow_data = r->data;
    }
    loop_ub = r->size[1];
    if ((r->size[1] != c_y->size[1]) &&
        ((r->size[1] != 1) && (c_y->size[1] != 1))) {
      emlrtDimSizeImpxCheckR2021b(r->size[1], c_y->size[1], &emlrtECI);
    }
    if (r->size[1] == c_y->size[1]) {
      for (k = 0; k < loop_ub; k++) {
        for (i = 0; i < 201; i++) {
          ret = i + 201 * k;
          y_data[ret] =
              hammingWindow_data[ret] + y_data[5 * i + c_y->size[0] * k];
        }
      }
      k = c_y->size[0] * c_y->size[1];
      c_y->size[0] = 201;
      c_y->size[1] = r->size[1];
      emxEnsureCapacity_real_T(c_y, k);
      edge[0] = 70.0;
      edge[1] = 200.0;
      getCandidates(c_y, edge, hammingWindow, f0);
      hammingWindow_data = f0->data;
    } else {
      binary_expand_op(r, c_y, hammingWindow, f0);
      hammingWindow_data = f0->data;
    }
    emxFree_real_T(&r);
    break;
  default:
    NCF(c_y, fs, f0);
    hammingWindow_data = f0->data;
    break;
  }
  emxFree_creal_T(&Yfull);
  emxFree_real_T(&yw);
  emxFree_real_T(&hammingWindow);
  emxFree_real_T(&c_y);
  ret = f0->size[0] - 1;
  for (vectorUB = 0; vectorUB <= ret; vectorUB++) {
    if (hammingWindow_data[vectorUB] < 70.0) {
      if (vectorUB > ret) {
        rtDynamicBoundsError(vectorUB, 0, ret, &h_emlrtBCI);
      }
      hammingWindow_data[vectorUB] = 70.0;
    }
  }
  for (vectorUB = 0; vectorUB <= ret; vectorUB++) {
    if (hammingWindow_data[vectorUB] > 200.0) {
      if (vectorUB > ret) {
        rtDynamicBoundsError(vectorUB, 0, ret, &i_emlrtBCI);
      }
      hammingWindow_data[vectorUB] = 200.0;
    }
  }
  if ((y + 1.0 != y + 1.0) || rtIsInf(y + 1.0) || (y + 1.0 < -2.147483648E+9) ||
      (y + 1.0 > 2.147483647E+9)) {
    hb_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  if (y + 1.0 <= 0.0) {
    d = 0.0;
  } else {
    d = y + 1.0;
  }
  if (!(d <= 2.147483647E+9)) {
    i_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
  ret = f0->size[0];
  if (f0->size[0] < 1) {
    ret = 1;
  }
  vectorUB = f0->size[0];
  if (vectorUB >= ret) {
    ret = vectorUB;
  }
  if ((int)(y + 1.0) > ret) {
    h_rtErrorWithMessageID(p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
  }
  if ((int)(y + 1.0) < 0) {
    g_rtErrorWithMessageID(q_emlrtRTEI.fName, q_emlrtRTEI.lineNo);
  }
  if ((int)(y + 1.0) != f0->size[0]) {
    f_rtErrorWithMessageID(r_emlrtRTEI.fName, r_emlrtRTEI.lineNo);
  }
  k = f0->size[0];
  f0->size[0] = (int)(y + 1.0);
  emxEnsureCapacity_real_T(f0, k);
}

/*
 * Arguments    : const double x[20000]
 *                const double fs_data[]
 *                const int fs_size[2]
 *                const double options_WindowLength_data[]
 *                const int options_WindowLength_size[2]
 *                const double options_OverlapLength_data[]
 *                const int options_OverlapLength_size[2]
 *                emxArray_real_T *varargout_1
 *                emxArray_real_T *varargout_2
 * Return Type  : void
 */
void pitch(const double x[20000], const double fs_data[], const int fs_size[2],
           const double options_WindowLength_data[],
           const int options_WindowLength_size[2],
           const double options_OverlapLength_data[],
           const int options_OverlapLength_size[2],
           emxArray_real_T *varargout_1, emxArray_real_T *varargout_2)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,      /* iFirst */
      -1,      /* iLast */
      116,     /* lineNo */
      13,      /* colNo */
      "",      /* aName */
      "pitch", /* fName */
      "C:\\Program Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\pitch.m", /* pName
                                                                            */
      0 /* checkKind */
  };
  static rtBoundsCheckInfo d_emlrtBCI = {
      -1,      /* iFirst */
      -1,      /* iLast */
      116,     /* lineNo */
      16,      /* colNo */
      "",      /* aName */
      "pitch", /* fName */
      "C:\\Program Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\pitch.m", /* pName
                                                                            */
      0 /* checkKind */
  };
  static rtDoubleCheckInfo e_emlrtDCI = {
      116,    /* lineNo */
      "pitch" /* fName */
  };
  static rtRunTimeErrorInfo ab_emlrtRTEI = {
      218,                    /* lineNo */
      "iCrossValidateOptions" /* fName */
  };
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      14,              /* lineNo */
      "validatenonnan" /* fName */
  };
  static rtRunTimeErrorInfo o_emlrtRTEI = {
      14,              /* lineNo */
      "validatefinite" /* fName */
  };
  static rtRunTimeErrorInfo p_emlrtRTEI = {
      14,                /* lineNo */
      "validatepositive" /* fName */
  };
  static rtRunTimeErrorInfo q_emlrtRTEI = {
      13,               /* lineNo */
      "validateinteger" /* fName */
  };
  static rtRunTimeErrorInfo r_emlrtRTEI = {
      204,                        /* lineNo */
      "iValidateWindowAndOverlap" /* fName */
  };
  static rtRunTimeErrorInfo s_emlrtRTEI = {
      207,                        /* lineNo */
      "iValidateWindowAndOverlap" /* fName */
  };
  static rtRunTimeErrorInfo t_emlrtRTEI = {
      237,                    /* lineNo */
      "iCrossValidateOptions" /* fName */
  };
  static rtRunTimeErrorInfo u_emlrtRTEI = {
      233,                    /* lineNo */
      "iCrossValidateOptions" /* fName */
  };
  static rtRunTimeErrorInfo v_emlrtRTEI = {
      226,                    /* lineNo */
      "iCrossValidateOptions" /* fName */
  };
  static rtRunTimeErrorInfo w_emlrtRTEI = {
      229,                    /* lineNo */
      "iCrossValidateOptions" /* fName */
  };
  static rtRunTimeErrorInfo x_emlrtRTEI = {
      222,                    /* lineNo */
      "iCrossValidateOptions" /* fName */
  };
  static rtRunTimeErrorInfo y_emlrtRTEI = {
      215,                    /* lineNo */
      "iCrossValidateOptions" /* fName */
  };
  static const char a[3] = {'N', 'C', 'F'};
  static const char b_a[3] = {'P', 'E', 'F'};
  static const char c_a[3] = {'C', 'E', 'P'};
  static const char d_a[3] = {'L', 'H', 'S'};
  static const char e_a[3] = {'S', 'R', 'H'};
  emxArray_real_T *b_varargout_1;
  emxArray_real_T *y;
  double t0_Range[2];
  double hopLength;
  double numHops;
  double options_WindowLength;
  double *b_varargout_1_data;
  double *varargout_1_data;
  int eint;
  int i;
  int ret;
  int vectorUB;
  boolean_T exitg1;
  boolean_T p;
  p = true;
  ret = 0;
  exitg1 = false;
  while ((!exitg1) && (ret < 20000)) {
    if (!rtIsNaN(x[ret])) {
      ret++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    d_rtErrorWithMessageID(7, "audioIn", n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  p = true;
  ret = 0;
  exitg1 = false;
  while ((!exitg1) && (ret < 20000)) {
    if ((!rtIsInf(x[ret])) && (!rtIsNaN(x[ret]))) {
      ret++;
    } else {
      p = false;
      exitg1 = true;
    }
  }
  if (!p) {
    c_rtErrorWithMessageID(7, "audioIn", o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
  hopLength = validator_check_size(fs_data, fs_size);
  if (hopLength <= 0.0) {
    cb_rtErrorWithMessageID("fs", p_emlrtRTEI.fName, p_emlrtRTEI.lineNo);
  }
  if (rtIsNaN(hopLength)) {
    d_rtErrorWithMessageID(2, "fs", n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  if (rtIsInf(hopLength)) {
    c_rtErrorWithMessageID(2, "fs", o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  }
  options_WindowLength = validator_check_size(options_WindowLength_data,
                                              options_WindowLength_size);
  if (rtIsInf(options_WindowLength) || rtIsNaN(options_WindowLength) ||
      (!(floor(options_WindowLength) == options_WindowLength))) {
    b_rtErrorWithMessageID(12, "WindowLength", q_emlrtRTEI.fName,
                           q_emlrtRTEI.lineNo);
  }
  numHops = validator_check_size(options_OverlapLength_data,
                                 options_OverlapLength_size);
  if (rtIsInf(numHops) || rtIsNaN(numHops) || (!(floor(numHops) == numHops))) {
    b_rtErrorWithMessageID(13, "OverlapLength", q_emlrtRTEI.fName,
                           q_emlrtRTEI.lineNo);
  }
  if ((options_WindowLength > 20000.0) || (options_WindowLength < 1.0)) {
    db_rtErrorWithMessageID("WINDOWLENGTH", "[1,size(x,1)]", "x",
                            "round(fs*0.052)", r_emlrtRTEI.fName,
                            r_emlrtRTEI.lineNo);
  }
  if (numHops >= options_WindowLength) {
    eb_rtErrorWithMessageID("OVERLAPLENGTH", "WINDOWLENGTH", s_emlrtRTEI.fName,
                            s_emlrtRTEI.lineNo);
  }
  ret = memcmp(&a[0], &a[0], 3);
  if (ret == 0) {
    ret = 0;
  } else {
    ret = memcmp(&b_a[0], &a[0], 3);
    if (ret == 0) {
      ret = 1;
    } else {
      ret = memcmp(&c_a[0], &a[0], 3);
      if (ret == 0) {
        ret = 2;
      } else {
        ret = memcmp(&d_a[0], &a[0], 3);
        if (ret == 0) {
          ret = 3;
        } else {
          ret = memcmp(&e_a[0], &a[0], 3);
          if (ret == 0) {
            ret = 4;
          } else {
            ret = -1;
          }
        }
      }
    }
  }
  switch (ret) {
  case 0:
    if (hopLength / 70.0 >= options_WindowLength) {
      fb_rtErrorWithMessageID("NCF", 26, "fs/RANGE(1) < WINDOWLENGTH",
                              y_emlrtRTEI.fName, y_emlrtRTEI.lineNo);
    }
    if (hopLength / 2.0 < 200.0) {
      fb_rtErrorWithMessageID("NCF", 16, "fs/2 >= RANGE(2)", ab_emlrtRTEI.fName,
                              ab_emlrtRTEI.lineNo);
    }
    break;
  case 1:
    if (fmin(4000.0, hopLength / 2.0) <= 200.0) {
      fb_rtErrorWithMessageID("PEF", 42,
                              "RANGE(1) > 10 && RANGE(2) < min(4000,fs/2)",
                              x_emlrtRTEI.fName, x_emlrtRTEI.lineNo);
    }
    break;
  case 2: {
    double f;
    if (hopLength / 2.0 <= 200.0) {
      fb_rtErrorWithMessageID(a, 15, "RANGE(2) < fs/2", v_emlrtRTEI.fName,
                              v_emlrtRTEI.lineNo);
    }
    f = frexp(2 * (int)options_WindowLength - 1, &eint);
    if (f == 0.5) {
      eint--;
    }
    if (rt_roundd_snf(hopLength / 70.0) > rt_powd_snf(2.0, eint)) {
      fb_rtErrorWithMessageID(
          a, 50, "round(fs/RANGE(1)) <= 2^nextpow2(2*WINDOWLENGTH-1)",
          w_emlrtRTEI.fName, w_emlrtRTEI.lineNo);
    }
  } break;
  case 3:
    if (hopLength <= 1005.0) {
      fb_rtErrorWithMessageID(a, 19, "(RANGE(2)+1)*5 < fs", u_emlrtRTEI.fName,
                              u_emlrtRTEI.lineNo);
    }
    break;
  case 4:
    if (hopLength <= 1005.0) {
      fb_rtErrorWithMessageID(a, 19, "(RANGE(2)+1)*5 < fs", t_emlrtRTEI.fName,
                              t_emlrtRTEI.lineNo);
    }
    break;
  }
  t0_Range[0] = 70.0;
  t0_Range[1] = 200.0;
  iDetectPitch(x, hopLength, t0_Range, options_WindowLength, numHops, a,
               varargout_1);
  varargout_1_data = varargout_1->data;
  hopLength = options_WindowLength - numHops;
  numHops = floor((20000.0 - options_WindowLength) / hopLength);
  emxInit_real_T(&b_varargout_1, 1);
  i = b_varargout_1->size[0];
  b_varargout_1->size[0] = varargout_1->size[0];
  emxEnsureCapacity_real_T(b_varargout_1, i);
  b_varargout_1_data = b_varargout_1->data;
  ret = varargout_1->size[0] - 1;
  for (i = 0; i <= ret; i++) {
    b_varargout_1_data[i] = varargout_1_data[i];
  }
  movmedian(b_varargout_1, varargout_1);
  emxFree_real_T(&b_varargout_1);
  if (numHops + 1.0 < 1.0) {
    i = 0;
  } else {
    if (varargout_1->size[0] < 1) {
      rtDynamicBoundsError(1, 1, varargout_1->size[0], &c_emlrtBCI);
    }
    if (numHops + 1.0 != (int)(numHops + 1.0)) {
      rtIntegerError(numHops + 1.0, &e_emlrtDCI);
    }
    if (((int)(numHops + 1.0) < 1) ||
        ((int)(numHops + 1.0) > varargout_1->size[0])) {
      rtDynamicBoundsError((int)(numHops + 1.0), 1, varargout_1->size[0],
                           &d_emlrtBCI);
    }
    i = (int)(numHops + 1.0);
  }
  ret = varargout_1->size[0];
  varargout_1->size[0] = i;
  emxEnsureCapacity_real_T(varargout_1, ret);
  emxInit_real_T(&y, 2);
  varargout_1_data = y->data;
  if (rtIsNaN(numHops)) {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = 1;
    emxEnsureCapacity_real_T(y, i);
    varargout_1_data = y->data;
    varargout_1_data[0] = rtNaN;
  } else if (numHops < 0.0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    i = y->size[0] * y->size[1];
    y->size[0] = 1;
    y->size[1] = (int)numHops + 1;
    emxEnsureCapacity_real_T(y, i);
    varargout_1_data = y->data;
    ret = (int)numHops;
    for (i = 0; i <= ret; i++) {
      varargout_1_data[i] = i;
    }
  }
  ret = y->size[1];
  i = varargout_2->size[0];
  varargout_2->size[0] = y->size[1];
  emxEnsureCapacity_real_T(varargout_2, i);
  b_varargout_1_data = varargout_2->data;
  eint = (y->size[1] / 2) << 1;
  vectorUB = eint - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    __m128d r;
    r = _mm_loadu_pd(&varargout_1_data[i]);
    _mm_storeu_pd(&b_varargout_1_data[i],
                  _mm_add_pd(_mm_mul_pd(r, _mm_set1_pd(hopLength)),
                             _mm_set1_pd(options_WindowLength)));
  }
  for (i = eint; i < ret; i++) {
    b_varargout_1_data[i] =
        varargout_1_data[i] * hopLength + options_WindowLength;
  }
  emxFree_real_T(&y);
}

/*
 * File trailer for pitch.c
 *
 * [EOF]
 */
