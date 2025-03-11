/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: calculate_HNR.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "calculate_HNR.h"
#include "analyse_periodecity_data.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "combineVectorElements.h"
#include "estimate_pitch_hps.h"
#include "rt_nonfinite.h"
#include "unsafeSxfun.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Declarations */
static void plus(emxArray_real_T *in1, const emxArray_real_T *in2);

/* Function Definitions */
/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 * Return Type  : void
 */
static void plus(emxArray_real_T *in1, const emxArray_real_T *in2)
{
  emxArray_real_T *b_in1;
  const double *in2_data;
  double *b_in1_data;
  double *in1_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 1);
  if (in2->size[0] == 1) {
    loop_ub = in1->size[0];
  } else {
    loop_ub = in2->size[0];
  }
  i = b_in1->size[0];
  b_in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(b_in1, i);
  b_in1_data = b_in1->data;
  stride_0_0 = (in1->size[0] != 1);
  stride_1_0 = (in2->size[0] != 1);
  for (i = 0; i < loop_ub; i++) {
    b_in1_data[i] = in1_data[i * stride_0_0] + in2_data[i * stride_1_0];
  }
  i = in1->size[0];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  for (i = 0; i < loop_ub; i++) {
    in1_data[i] = b_in1_data[i];
  }
  emxFree_real_T(&b_in1);
}

/*
 * Load the audio signal
 * [signal, fs] = audioread(filename);  % fs is the sampling frequency
 *
 * Arguments    : double b_signal[20000]
 *                double fs
 * Return Type  : double
 */
double calculate_HNR(double b_signal[20000], double fs)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,                                                      /* iFirst */
      -1,                                                      /* iLast */
      56,                                                      /* lineNo */
      24,                                                      /* colNo */
      "hnr_values",                                            /* aName */
      "calculate_HNR",                                         /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\calculate_HNR.m", /* pName */
      0                                                        /* checkKind */
  };
  static rtBoundsCheckInfo d_emlrtBCI = {
      -1,                                                      /* iFirst */
      -1,                                                      /* iLast */
      54,                                                      /* lineNo */
      24,                                                      /* colNo */
      "hnr_values",                                            /* aName */
      "calculate_HNR",                                         /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\calculate_HNR.m", /* pName */
      0                                                        /* checkKind */
  };
  static rtBoundsCheckInfo e_emlrtBCI = {
      1,                                                       /* iFirst */
      20000,                                                   /* iLast */
      29,                                                      /* lineNo */
      26,                                                      /* colNo */
      "signal",                                                /* aName */
      "calculate_HNR",                                         /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\calculate_HNR.m", /* pName */
      0                                                        /* checkKind */
  };
  static rtBoundsCheckInfo f_emlrtBCI = {
      1,                                                       /* iFirst */
      20000,                                                   /* iLast */
      29,                                                      /* lineNo */
      36,                                                      /* colNo */
      "signal",                                                /* aName */
      "calculate_HNR",                                         /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\calculate_HNR.m", /* pName */
      0                                                        /* checkKind */
  };
  static rtDoubleCheckInfo e_emlrtDCI = {
      23,             /* lineNo */
      "calculate_HNR" /* fName */
  };
  static rtDoubleCheckInfo f_emlrtDCI = {
      23,             /* lineNo */
      "calculate_HNR" /* fName */
  };
  static rtDoubleCheckInfo g_emlrtDCI = {
      29,             /* lineNo */
      "calculate_HNR" /* fName */
  };
  static rtDoubleCheckInfo h_emlrtDCI = {
      29,             /* lineNo */
      "calculate_HNR" /* fName */
  };
  static rtEqualityCheckInfo b_emlrtECI = {
      1,                                                      /* nDims */
      46,                                                     /* lineNo */
      17,                                                     /* colNo */
      "calculate_HNR",                                        /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\calculate_HNR.m" /* pName */
  };
  static rtEqualityCheckInfo emlrtECI = {
      1,                                                      /* nDims */
      42,                                                     /* lineNo */
      25,                                                     /* colNo */
      "calculate_HNR",                                        /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\calculate_HNR.m" /* pName */
  };
  __m128d r;
  emxArray_int16_T *y;
  emxArray_real_T *harmonic_signal;
  emxArray_real_T *harmonics;
  emxArray_real_T *hnr_values;
  double varargin_1[20000];
  double end_idx;
  double hnr;
  double hop_size;
  double num_frames;
  double start_idx;
  double win_length;
  double *harmonic_signal_data;
  double *harmonics_data;
  double *hnr_values_data;
  int b_i;
  int i;
  int i1;
  int i2;
  int i3;
  int idx;
  int j;
  int k;
  short *y_data;
  /*  If the signal is stereo, convert to mono by averaging channels */
  /*  Normalize the signal to avoid clipping */
  for (k = 0; k < 20000; k++) {
    varargin_1[k] = fabs(b_signal[k]);
  }
  if (!rtIsNaN(varargin_1[0])) {
    idx = 1;
  } else {
    boolean_T exitg1;
    idx = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k <= 20000)) {
      if (!rtIsNaN(varargin_1[k - 1])) {
        idx = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (idx == 0) {
    start_idx = varargin_1[0];
  } else {
    start_idx = varargin_1[idx - 1];
    i = idx + 1;
    for (k = i; k < 20001; k++) {
      end_idx = varargin_1[k - 1];
      if (start_idx < end_idx) {
        start_idx = end_idx;
      }
    }
  }
  for (i = 0; i <= 19998; i += 2) {
    r = _mm_loadu_pd(&b_signal[i]);
    _mm_storeu_pd(&b_signal[i], _mm_div_pd(r, _mm_set1_pd(start_idx)));
  }
  /*  Window parameters for short-time analysis */
  win_length = rt_roundd_snf(0.03 * fs);
  /*  30 ms window length */
  hop_size = rt_roundd_snf(0.01 * fs);
  /*  10 ms hop size */
  num_frames = floor((20000.0 - win_length) / hop_size);
  /* num_frames = num_frames; */
  /*  Initialize HNR values over time */
  if (!(num_frames >= 0.0)) {
    rtNonNegativeError(num_frames, &e_emlrtDCI);
  }
  if (num_frames != (int)num_frames) {
    rtIntegerError(num_frames, &f_emlrtDCI);
  }
  i = (int)num_frames;
  emxInit_real_T(&hnr_values, 1);
  i1 = hnr_values->size[0];
  hnr_values->size[0] = (int)num_frames;
  emxEnsureCapacity_real_T(hnr_values, i1);
  hnr_values_data = hnr_values->data;
  emxInit_real_T(&harmonics, 1);
  emxInit_real_T(&harmonic_signal, 1);
  emxInit_int16_T(&y, 2);
  y_data = y->data;
  for (b_i = 0; b_i < i; b_i++) {
    int loop_ub;
    int loop_ub_tmp;
    /*  Extract a windowed segment */
    start_idx = (((double)b_i + 1.0) - 1.0) * hop_size + 1.0;
    end_idx = (start_idx + win_length) - 1.0;
    if (start_idx > end_idx) {
      i1 = 0;
      i2 = 0;
    } else {
      if (start_idx != (int)start_idx) {
        rtIntegerError(start_idx, &g_emlrtDCI);
      }
      if (((int)start_idx < 1) || ((int)start_idx > 20000)) {
        rtDynamicBoundsError((int)start_idx, 1, 20000, &e_emlrtBCI);
      }
      i1 = (int)start_idx - 1;
      if (end_idx != (int)end_idx) {
        rtIntegerError(end_idx, &h_emlrtDCI);
      }
      if (((int)end_idx < 1) || ((int)end_idx > 20000)) {
        rtDynamicBoundsError((int)end_idx, 1, 20000, &f_emlrtBCI);
      }
      i2 = (int)end_idx;
    }
    /*  Pitch detection using Harmonic Product Spectrum (HPS) */
    loop_ub = i2 - i1;
    i3 = harmonics->size[0];
    harmonics->size[0] = loop_ub;
    emxEnsureCapacity_real_T(harmonics, i3);
    harmonics_data = harmonics->data;
    for (i3 = 0; i3 < loop_ub; i3++) {
      harmonics_data[i3] = b_signal[i1 + i3];
    }
    start_idx = b_estimate_pitch_hps(harmonics, fs);
    /*  Using HPS for pitch estimation */
    /*  Harmonic synthesis: Create harmonic components (sine waves) */
    i3 = harmonics->size[0];
    harmonics->size[0] = loop_ub;
    emxEnsureCapacity_real_T(harmonics, i3);
    harmonics_data = harmonics->data;
    for (i3 = 0; i3 < loop_ub; i3++) {
      harmonics_data[i3] = 0.0;
    }
    if (loop_ub < 1) {
      y->size[0] = 1;
      y->size[1] = 0;
    } else {
      i3 = y->size[0] * y->size[1];
      y->size[0] = 1;
      y->size[1] = (short)loop_ub;
      emxEnsureCapacity_int16_T(y, i3);
      y_data = y->data;
      idx = (short)loop_ub - 1;
      for (i3 = 0; i3 <= idx; i3++) {
        y_data[i3] = (short)(i3 + 1);
      }
    }
    loop_ub_tmp = y->size[1];
    for (j = 0; j < 5; j++) {
      /*  Let's assume the first 5 harmonics (F0, 2F0, 3F0, etc.) */
      end_idx = 6.2831853071795862 * start_idx * ((double)j + 1.0);
      i3 = harmonic_signal->size[0];
      harmonic_signal->size[0] = loop_ub_tmp;
      emxEnsureCapacity_real_T(harmonic_signal, i3);
      harmonic_signal_data = harmonic_signal->data;
      for (i3 = 0; i3 < loop_ub_tmp; i3++) {
        harmonic_signal_data[i3] = end_idx * (double)y_data[i3] / fs;
      }
      for (k = 0; k < loop_ub_tmp; k++) {
        harmonic_signal_data[k] = sin(harmonic_signal_data[k]);
      }
      idx = harmonics->size[0];
      if ((harmonics->size[0] != loop_ub_tmp) &&
          ((harmonics->size[0] != 1) && (loop_ub_tmp != 1))) {
        emlrtDimSizeImpxCheckR2021b(harmonics->size[0], loop_ub_tmp, &emlrtECI);
      }
      if (harmonics->size[0] == harmonic_signal->size[0]) {
        int vectorUB;
        k = (harmonics->size[0] / 2) << 1;
        vectorUB = k - 2;
        for (i3 = 0; i3 <= vectorUB; i3 += 2) {
          __m128d r1;
          r = _mm_loadu_pd(&harmonics_data[i3]);
          r1 = _mm_loadu_pd(&harmonic_signal_data[i3]);
          _mm_storeu_pd(&harmonics_data[i3], _mm_add_pd(r, r1));
        }
        for (i3 = k; i3 < idx; i3++) {
          harmonics_data[i3] += harmonic_signal_data[i3];
        }
      } else {
        plus(harmonics, harmonic_signal);
        harmonics_data = harmonics->data;
      }
    }
    /*  Noise estimation: Subtract harmonic components from the original signal
     */
    if ((loop_ub != harmonics->size[0]) &&
        ((loop_ub != 1) && (harmonics->size[0] != 1))) {
      emlrtDimSizeImpxCheckR2021b(loop_ub, harmonics->size[0], &b_emlrtECI);
    }
    /*  Calculate energy of harmonics and noise (sum of squares) */
    if (loop_ub == harmonics->size[0]) {
      i2 = harmonic_signal->size[0];
      harmonic_signal->size[0] = loop_ub;
      emxEnsureCapacity_real_T(harmonic_signal, i2);
      harmonic_signal_data = harmonic_signal->data;
      for (i2 = 0; i2 < loop_ub; i2++) {
        start_idx = b_signal[i1 + i2] - harmonics_data[i2];
        harmonic_signal_data[i2] = rt_powd_snf(start_idx, 2.0);
      }
    } else {
      binary_expand_op_11(harmonic_signal, b_signal, i1, i2, harmonics);
    }
    end_idx = combineVectorElements(harmonic_signal);
    /*  Calculate Harmonics-to-Noise Ratio (HNR) in dB */
    if (end_idx == 0.0) {
      if (((int)((unsigned int)b_i + 1U) < 1) ||
          ((int)((unsigned int)b_i + 1U) > (int)num_frames)) {
        rtDynamicBoundsError((int)((unsigned int)b_i + 1U), 1, (int)num_frames,
                             &d_emlrtBCI);
      }
      hnr_values_data[b_i] = rtInf;
      /*  Avoid division by zero (perfect harmonic signal) */
    } else {
      loop_ub = harmonics->size[0];
      for (i1 = 0; i1 < loop_ub; i1++) {
        start_idx = harmonics_data[i1];
        harmonics_data[i1] = rt_powd_snf(start_idx, 2.0);
      }
      start_idx = combineVectorElements(harmonics) / end_idx;
      if (start_idx < 0.0) {
        s_rtErrorWithMessageID(5, "log10", k_emlrtRTEI.fName,
                               k_emlrtRTEI.lineNo);
      }
      start_idx = log10(start_idx);
      if (((int)((unsigned int)b_i + 1U) < 1) ||
          ((int)((unsigned int)b_i + 1U) > (int)num_frames)) {
        rtDynamicBoundsError((int)((unsigned int)b_i + 1U), 1, (int)num_frames,
                             &c_emlrtBCI);
      }
      hnr_values_data[b_i] = 10.0 * start_idx;
      /*  HNR in dB */
    }
  }
  emxFree_int16_T(&y);
  emxFree_real_T(&harmonic_signal);
  emxFree_real_T(&harmonics);
  /*  Return the average HNR value over time */
  hnr = combineVectorElements(hnr_values) / (double)hnr_values->size[0];
  emxFree_real_T(&hnr_values);
  return hnr;
}

/*
 * File trailer for calculate_HNR.c
 *
 * [EOF]
 */
