/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: analyse_periodecity.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "analyse_periodecity.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "combineVectorElements.h"
#include "eml_int_forloop_overflow_check.h"
#include "pitch.h"
#include "rt_nonfinite.h"
#include "sum.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * SNR=snr(y);
 *
 *
 * Arguments    : const double y[20000]
 *                const double Fs_data[]
 *                const int Fs_size[2]
 *                double *jitt
 *                double *shim
 * Return Type  : void
 */
void analyse_periodecity(const double y[20000], const double Fs_data[],
                         const int Fs_size[2], double *jitt, double *shim)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,                    /* iFirst */
      -1,                    /* iLast */
      24,                    /* lineNo */
      30,                    /* colNo */
      "T0",                  /* aName */
      "analyse_periodecity", /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\analyse_periodecity.m", /* pName */
      0 /* checkKind */
  };
  static rtBoundsCheckInfo d_emlrtBCI = {
      -1,                    /* iFirst */
      -1,                    /* iLast */
      24,                    /* lineNo */
      38,                    /* colNo */
      "T0",                  /* aName */
      "analyse_periodecity", /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\analyse_periodecity.m", /* pName */
      0 /* checkKind */
  };
  static rtBoundsCheckInfo e_emlrtBCI = {
      -1,                    /* iFirst */
      -1,                    /* iLast */
      36,                    /* lineNo */
      36,                    /* colNo */
      "idx",                 /* aName */
      "analyse_periodecity", /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\analyse_periodecity.m", /* pName */
      0 /* checkKind */
  };
  static rtBoundsCheckInfo f_emlrtBCI = {
      1,                     /* iFirst */
      20000,                 /* iLast */
      36,                    /* lineNo */
      32,                    /* colNo */
      "y",                   /* aName */
      "analyse_periodecity", /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\analyse_periodecity.m", /* pName */
      0 /* checkKind */
  };
  static rtBoundsCheckInfo g_emlrtBCI = {
      -1,                    /* iFirst */
      -1,                    /* iLast */
      44,                    /* lineNo */
      27,                    /* colNo */
      "amplitude",           /* aName */
      "analyse_periodecity", /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\analyse_periodecity.m", /* pName */
      0 /* checkKind */
  };
  static rtBoundsCheckInfo h_emlrtBCI = {
      -1,                    /* iFirst */
      -1,                    /* iLast */
      44,                    /* lineNo */
      40,                    /* colNo */
      "amplitude",           /* aName */
      "analyse_periodecity", /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\analyse_periodecity.m", /* pName */
      0 /* checkKind */
  };
  static rtDoubleCheckInfo e_emlrtDCI = {
      36,                   /* lineNo */
      "analyse_periodecity" /* fName */
  };
  emxArray_real_T *T0;
  emxArray_real_T *amplitude;
  emxArray_real_T *b_y;
  emxArray_real_T *idx;
  emxArray_real_T *jitta;
  double overlapLength_data;
  double windowLength_data;
  double *T0_data;
  double *amplitude_data;
  double *idx_data;
  double *jitta_data;
  int overlapLength_size[2];
  int windowLength_size[2];
  int i;
  int k;
  int loop_ub_tmp;
  int vectorUB;
  windowLength_size[0] = Fs_size[0];
  windowLength_size[1] = Fs_size[1];
  loop_ub_tmp = Fs_size[0] * Fs_size[1];
  for (i = 0; i < loop_ub_tmp; i++) {
    windowLength_data = 0.05 * Fs_data[0];
  }
  overlapLength_size[0] = Fs_size[0];
  overlapLength_size[1] = Fs_size[1];
  for (k = 0; k < loop_ub_tmp; k++) {
    windowLength_data = rt_roundd_snf(windowLength_data);
    overlapLength_data = 0.04 * Fs_data[0];
  }
  for (k = 0; k < loop_ub_tmp; k++) {
    overlapLength_data = rt_roundd_snf(overlapLength_data);
  }
  emxInit_real_T(&T0, 1);
  emxInit_real_T(&idx, 1);
  pitch(y, Fs_data, Fs_size, (double *)&windowLength_data, windowLength_size,
        (double *)&overlapLength_data, overlapLength_size, T0, idx);
  idx_data = idx->data;
  T0_data = T0->data;
  loop_ub_tmp = T0->size[0];
  k = (T0->size[0] / 2) << 1;
  vectorUB = k - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    __m128d r;
    r = _mm_loadu_pd(&T0_data[i]);
    _mm_storeu_pd(&T0_data[i], _mm_div_pd(_mm_set1_pd(1.0), r));
  }
  for (i = k; i < loop_ub_tmp; i++) {
    T0_data[i] = 1.0 / T0_data[i];
  }
  /*   */
  /*  mean_pitch=mean(F0); */
  /*  max_pitch=max(F0); */
  /*  min_pitch=min(F0); */
  /*  Jitta absolute */
  emxInit_real_T(&jitta, 2);
  i = jitta->size[0] * jitta->size[1];
  jitta->size[0] = 1;
  jitta->size[1] = 1;
  emxEnsureCapacity_real_T(jitta, i);
  jitta_data = jitta->data;
  jitta_data[0] = 0.0;
  i = T0->size[0];
  for (vectorUB = 0; vectorUB <= i - 2; vectorUB++) {
    if (vectorUB + 1 > i) {
      rtDynamicBoundsError(vectorUB + 1, 1, i, &c_emlrtBCI);
    }
    if (vectorUB + 2 > i) {
      rtDynamicBoundsError(vectorUB + 2, 1, i, &d_emlrtBCI);
    }
    k = jitta->size[1];
    loop_ub_tmp = jitta->size[0] * jitta->size[1];
    jitta->size[0] = 1;
    jitta->size[1]++;
    emxEnsureCapacity_real_T(jitta, loop_ub_tmp);
    jitta_data = jitta->data;
    jitta_data[k] = fabs(T0_data[vectorUB] - T0_data[vectorUB + 1]);
  }
  windowLength_data = 1.0 / ((double)T0->size[0] - 1.0) * sum(jitta);
  /* jitter local */
  *jitt = 100.0 * windowLength_data /
          (1.0 / (double)T0->size[0] * combineVectorElements(T0));
  /* shimmer (amplitude) */
  emxInit_real_T(&amplitude, 1);
  i = amplitude->size[0];
  amplitude->size[0] = 1;
  emxEnsureCapacity_real_T(amplitude, i);
  amplitude_data = amplitude->data;
  amplitude_data[0] = 0.0;
  i = idx->size[0];
  for (vectorUB = 0; vectorUB < i; vectorUB++) {
    k = amplitude->size[0];
    loop_ub_tmp = amplitude->size[0];
    amplitude->size[0]++;
    emxEnsureCapacity_real_T(amplitude, loop_ub_tmp);
    amplitude_data = amplitude->data;
    if (vectorUB + 1 > i) {
      rtDynamicBoundsError(vectorUB + 1, 1, i, &e_emlrtBCI);
    }
    windowLength_data = idx_data[vectorUB];
    if (windowLength_data != (int)floor(windowLength_data)) {
      rtIntegerError(windowLength_data, &e_emlrtDCI);
    }
    if (((int)windowLength_data < 1) || ((int)windowLength_data > 20000)) {
      rtDynamicBoundsError((int)windowLength_data, 1, 20000, &f_emlrtBCI);
    }
    amplitude_data[k] = y[(int)windowLength_data - 1];
  }
  emxFree_real_T(&idx);
  /*  figure(2) */
  /*  plot(y); */
  /*   */
  /* shimmer local */
  i = jitta->size[0] * jitta->size[1];
  jitta->size[0] = 1;
  jitta->size[1] = 1;
  emxEnsureCapacity_real_T(jitta, i);
  jitta_data = jitta->data;
  jitta_data[0] = 0.0;
  i = amplitude->size[0];
  for (vectorUB = 0; vectorUB <= i - 2; vectorUB++) {
    if (vectorUB + 1 > i) {
      rtDynamicBoundsError(vectorUB + 1, 1, i, &g_emlrtBCI);
    }
    if (vectorUB + 2 > i) {
      rtDynamicBoundsError(vectorUB + 2, 1, i, &h_emlrtBCI);
    }
    k = jitta->size[1];
    loop_ub_tmp = jitta->size[0] * jitta->size[1];
    jitta->size[1]++;
    emxEnsureCapacity_real_T(jitta, loop_ub_tmp);
    jitta_data = jitta->data;
    jitta_data[k] =
        100.0 * (amplitude_data[vectorUB] - amplitude_data[vectorUB + 1]);
  }
  loop_ub_tmp = jitta->size[1];
  emxInit_real_T(&b_y, 2);
  k = b_y->size[0] * b_y->size[1];
  b_y->size[0] = 1;
  b_y->size[1] = jitta->size[1];
  emxEnsureCapacity_real_T(b_y, k);
  idx_data = b_y->data;
  if (jitta->size[1] > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < loop_ub_tmp; k++) {
    idx_data[k] = fabs(jitta_data[k]);
  }
  emxFree_real_T(&jitta);
  *shim = 0.0001 * sum(b_y) / ((double)amplitude->size[0] - 1.0);
  emxFree_real_T(&b_y);
  k = T0->size[0];
  T0->size[0] = amplitude->size[0];
  emxEnsureCapacity_real_T(T0, k);
  T0_data = T0->data;
  if (amplitude->size[0] > 2147483646) {
    check_forloop_overflow_error();
  }
  for (k = 0; k < i; k++) {
    T0_data[k] = fabs(amplitude_data[k]);
  }
  *shim /= combineVectorElements(T0) / (double)amplitude->size[0];
  emxFree_real_T(&amplitude);
  emxFree_real_T(&T0);
  /*  %shimmer local (in dB) */
  /*  %shimdb=zeros(1); */
  /*  [pks,locs] = findpeaks(amplitude); */
  /*   */
  /*  figure(2) */
  /*  plot(locs,pks,'rs', 'LineWidth', 1.5) */
  /*  hold on  */
  /*  plot(amplitude,'b','LineWidth', 1.5) */
  /*  xlabel("Shimmer (dB)") */
  /*  ylabel("Amplitude") */
  /*  title("Relative Peaks in Local Shimmer") */
  /*  for i=1:length(pks)-1 */
  /*      shdb=abs(20*log((pks(i+1)/pks(i)))); */
  /*      shimdb=[shimdb,shdb]; */
  /*  end */
  /*  shimdb(1)=(1/(length(y)-1))*(sum(shimdb)); */
}

/*
 * File trailer for analyse_periodecity.c
 *
 * [EOF]
 */
