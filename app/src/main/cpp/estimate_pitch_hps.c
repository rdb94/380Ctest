/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: estimate_pitch_hps.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "estimate_pitch_hps.h"
#include "FFTImplementationCallback.h"
#include "analyse_periodecity_data.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "indexShapeCheck.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Declarations */
static void times(emxArray_real_T *in1, const emxArray_real_T *in2);

/* Function Definitions */
/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 * Return Type  : void
 */
static void times(emxArray_real_T *in1, const emxArray_real_T *in2)
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
    b_in1_data[i] = in1_data[i * stride_0_0] * in2_data[i * stride_1_0];
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
 * Number of frequency bins
 *
 * Arguments    : const emxArray_real_T *segment
 *                double fs
 * Return Type  : double
 */
double b_estimate_pitch_hps(const emxArray_real_T *segment, double fs)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,                                                           /* iFirst */
      -1,                                                           /* iLast */
      9,                                                            /* lineNo */
      29,                                                           /* colNo */
      "fft_signal",                                                 /* aName */
      "estimate_pitch_hps",                                         /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\estimate_pitch_hps.m", /* pName */
      0 /* checkKind */
  };
  static rtBoundsCheckInfo d_emlrtBCI = {
      -1,                                                           /* iFirst */
      -1,                                                           /* iLast */
      9,                                                            /* lineNo */
      31,                                                           /* colNo */
      "fft_signal",                                                 /* aName */
      "estimate_pitch_hps",                                         /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\estimate_pitch_hps.m", /* pName */
      0 /* checkKind */
  };
  static rtBoundsCheckInfo e_emlrtBCI = {
      -1,                                                           /* iFirst */
      -1,                                                           /* iLast */
      14,                                                           /* lineNo */
      55,                                                           /* colNo */
      "fft_signal",                                                 /* aName */
      "estimate_pitch_hps",                                         /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\estimate_pitch_hps.m", /* pName */
      0 /* checkKind */
  };
  static rtEqualityCheckInfo emlrtECI = {
      1,                                                           /* nDims */
      15,                                                          /* lineNo */
      15,                                                          /* colNo */
      "estimate_pitch_hps",                                        /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\estimate_pitch_hps.m" /* pName */
  };
  emxArray_creal_T *y;
  emxArray_real_T *costab;
  emxArray_real_T *fft_signal;
  emxArray_real_T *hps;
  emxArray_real_T *shifted_signal;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  creal_T *y_data;
  double b_pitch;
  double *fft_signal_data;
  double *hps_data;
  double *shifted_signal_data;
  int iv[2];
  int b_y;
  int i;
  int j;
  int k;
  int last;
  int nRows;
  /*  Pitch estimation function using Harmonic Product Spectrum (HPS) */
  /*  Compute the FFT of the segment */
  if (segment->size[0] == 1) {
    rtErrorWithMessageID(e_emlrtRTEI.fName, e_emlrtRTEI.lineNo);
  }
  emxInit_creal_T(&y, 1);
  y_data = y->data;
  if (segment->size[0] == 0) {
    y->size[0] = 0;
  } else {
    boolean_T useRadix2;
    useRadix2 = ((segment->size[0] & (segment->size[0] - 1)) == 0);
    last = c_FFTImplementationCallback_get(segment->size[0], useRadix2, &nRows);
    emxInit_real_T(&costab, 2);
    emxInit_real_T(&sintab, 2);
    emxInit_real_T(&sintabinv, 2);
    f_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab,
                                    sintabinv);
    if (useRadix2) {
      g_FFTImplementationCallback_r2b(segment, segment->size[0], costab, sintab,
                                      y);
      y_data = y->data;
    } else {
      e_FFTImplementationCallback_dob(segment, last, segment->size[0], costab,
                                      sintab, sintabinv, y);
      y_data = y->data;
    }
    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
  }
  i = y->size[0];
  emxInit_real_T(&fft_signal, 1);
  k = fft_signal->size[0];
  fft_signal->size[0] = y->size[0];
  emxEnsureCapacity_real_T(fft_signal, k);
  fft_signal_data = fft_signal->data;
  for (k = 0; k < i; k++) {
    fft_signal_data[k] = rt_hypotd_snf(y_data[k].re, y_data[k].im);
  }
  /*  Ensure we are only working with the positive frequencies */
  b_y = (int)floor((double)segment->size[0] / 2.0);
  if (y->size[0] < 1) {
    rtDynamicBoundsError(1, 1, y->size[0], &c_emlrtBCI);
  }
  nRows = b_y + 1;
  if (b_y + 1 > y->size[0]) {
    rtDynamicBoundsError(b_y + 1, 1, y->size[0], &d_emlrtBCI);
  }
  emxFree_creal_T(&y);
  iv[0] = 1;
  iv[1] = b_y + 1;
  indexShapeCheck(fft_signal->size[0], iv);
  i = fft_signal->size[0];
  fft_signal->size[0] = b_y + 1;
  emxEnsureCapacity_real_T(fft_signal, i);
  fft_signal_data = fft_signal->data;
  /*  Apply Harmonic Product Spectrum (HPS) */
  emxInit_real_T(&hps, 1);
  i = hps->size[0];
  hps->size[0] = b_y + 1;
  emxEnsureCapacity_real_T(hps, i);
  hps_data = hps->data;
  for (i = 0; i < nRows; i++) {
    hps_data[i] = fft_signal_data[i];
  }
  /*  Initialize HPS with the first bin */
  iv[0] = 1;
  emxInit_real_T(&shifted_signal, 1);
  for (j = 0; j < 4; j++) {
    /*  Use up to the 5th harmonic */
    nRows = b_y - j;
    if (nRows < 1) {
      nRows = 0;
    } else if (nRows > b_y + 1) {
      rtDynamicBoundsError(nRows, 1, b_y + 1, &e_emlrtBCI);
    }
    iv[1] = nRows;
    indexShapeCheck(b_y + 1, iv);
    i = (j + nRows) + 1;
    k = shifted_signal->size[0];
    shifted_signal->size[0] = i;
    emxEnsureCapacity_real_T(shifted_signal, k);
    shifted_signal_data = shifted_signal->data;
    last = j + 1;
    for (k = 0; k < last; k++) {
      shifted_signal_data[k] = 0.0;
    }
    for (k = 0; k < nRows; k++) {
      shifted_signal_data[(k + j) + 1] = fft_signal_data[k];
    }
    /*  Shift the spectrum */
    nRows = hps->size[0];
    if ((hps->size[0] != i) && ((hps->size[0] != 1) && (i != 1))) {
      emlrtDimSizeImpxCheckR2021b(hps->size[0], i, &emlrtECI);
    }
    if (hps->size[0] == shifted_signal->size[0]) {
      last = (hps->size[0] / 2) << 1;
      k = last - 2;
      for (i = 0; i <= k; i += 2) {
        __m128d r;
        __m128d r1;
        r = _mm_loadu_pd(&hps_data[i]);
        r1 = _mm_loadu_pd(&shifted_signal_data[i]);
        _mm_storeu_pd(&hps_data[i], _mm_mul_pd(r, r1));
      }
      for (i = last; i < nRows; i++) {
        hps_data[i] *= shifted_signal_data[i];
      }
    } else {
      times(hps, shifted_signal);
      hps_data = hps->data;
    }
    /*  Multiply with the shifted versions */
  }
  emxFree_real_T(&shifted_signal);
  emxFree_real_T(&fft_signal);
  /*  Find the peak in the HPS */
  if (hps->size[0] < 1) {
    q_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  last = hps->size[0];
  if (hps->size[0] <= 2) {
    if (hps->size[0] == 1) {
      nRows = 1;
    } else if ((hps_data[0] < hps_data[1]) ||
               (rtIsNaN(hps_data[0]) && (!rtIsNaN(hps_data[1])))) {
      nRows = 2;
    } else {
      nRows = 1;
    }
  } else {
    if (!rtIsNaN(hps_data[0])) {
      nRows = 1;
    } else {
      boolean_T exitg1;
      nRows = 0;
      k = 2;
      exitg1 = false;
      while ((!exitg1) && (k <= last)) {
        if (!rtIsNaN(hps_data[k - 1])) {
          nRows = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (nRows == 0) {
      nRows = 1;
    } else {
      double ex;
      ex = hps_data[nRows - 1];
      i = nRows + 1;
      for (k = i; k <= last; k++) {
        double d;
        d = hps_data[k - 1];
        if (ex < d) {
          ex = d;
          nRows = k;
        }
      }
    }
  }
  emxFree_real_T(&hps);
  /*  Convert the peak index to the corresponding frequency */
  b_pitch = ((double)nRows - 1.0) * fs / (double)segment->size[0];
  /*  Convert index to frequency */
  /*  Reject invalid pitch values (e.g., outside human voice range) */
  if ((b_pitch < 50.0) || (b_pitch > 500.0)) {
    /*  Accept pitches in the range of 50-500 Hz */
    b_pitch = 0.0;
    /*  Return empty if no valid pitch is found */
  }
  return b_pitch;
}

/*
 * Number of frequency bins
 *
 * Arguments    : const double segment[120]
 *                const double fs_data[]
 *                const int fs_size[2]
 * Return Type  : double
 */
double estimate_pitch_hps(const double segment[120], const double fs_data[],
                          const int fs_size[2])
{
  static rtEqualityCheckInfo emlrtECI = {
      -1,                                                          /* nDims */
      23,                                                          /* lineNo */
      5,                                                           /* colNo */
      "estimate_pitch_hps",                                        /* fName */
      "C:\\Users\\Rachel\\Documents\\MATLAB\\estimate_pitch_hps.m" /* pName */
  };
  creal_T y[120];
  double fft_signal[120];
  double shifted_signal_data[64];
  double hps[61];
  double b_pitch;
  int i;
  int j;
  int k;
  int loop_ub;
  /*  Pitch estimation function using Harmonic Product Spectrum (HPS) */
  /*  Compute the FFT of the segment */
  h_FFTImplementationCallback_doH(segment, y);
  for (k = 0; k < 120; k++) {
    fft_signal[k] = rt_hypotd_snf(y[k].re, y[k].im);
  }
  /*  Ensure we are only working with the positive frequencies */
  /*  Apply Harmonic Product Spectrum (HPS) */
  memcpy(&hps[0], &fft_signal[0], 61U * sizeof(double));
  /*  Initialize HPS with the first bin */
  for (j = 0; j < 4; j++) {
    /*  Use up to the 5th harmonic */
    k = 59 - j;
    loop_ub = j + 1;
    memset(&shifted_signal_data[0], 0, (unsigned int)loop_ub * sizeof(double));
    memcpy(&shifted_signal_data[j + 1], &fft_signal[0],
           (unsigned int)(k + 1) * sizeof(double));
    /*  Shift the spectrum */
    for (i = 0; i <= 58; i += 2) {
      __m128d r;
      __m128d r1;
      r = _mm_loadu_pd(&hps[i]);
      r1 = _mm_loadu_pd(&shifted_signal_data[i]);
      _mm_storeu_pd(&hps[i], _mm_mul_pd(r, r1));
    }
    hps[60] *= shifted_signal_data[60];
    /*  Multiply with the shifted versions */
  }
  /*  Find the peak in the HPS */
  if (!rtIsNaN(hps[0])) {
    loop_ub = 1;
  } else {
    boolean_T exitg1;
    loop_ub = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 62)) {
      if (!rtIsNaN(hps[k - 1])) {
        loop_ub = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (loop_ub == 0) {
    loop_ub = 1;
  } else {
    double ex;
    ex = hps[loop_ub - 1];
    i = loop_ub + 1;
    for (k = i; k < 62; k++) {
      double d;
      d = hps[k - 1];
      if (ex < d) {
        ex = d;
        loop_ub = k;
      }
    }
  }
  /*  Convert the peak index to the corresponding frequency */
  k = fs_size[0] * fs_size[1];
  for (i = 0; i < k; i++) {
    b_pitch = ((double)loop_ub - 1.0) * fs_data[0] / 120.0;
  }
  if (k != 1) {
    rtSizeEq1DError(1, 0, &emlrtECI);
  }
  /*  Convert index to frequency */
  /*  Reject invalid pitch values (e.g., outside human voice range) */
  if ((b_pitch < 50.0) || (b_pitch > 500.0)) {
    /*  Accept pitches in the range of 50-500 Hz */
    b_pitch = 0.0;
    /*  Return empty if no valid pitch is found */
  }
  return b_pitch;
}

/*
 * File trailer for estimate_pitch_hps.c
 *
 * [EOF]
 */
