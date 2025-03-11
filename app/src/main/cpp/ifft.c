/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: ifft.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "ifft.h"
#include "FFTImplementationCallback.h"
#include "analyse_periodecity_data.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <string.h>

/* Variable Definitions */
static rtRunTimeErrorInfo h_emlrtRTEI = {
    56,    /* lineNo */
    "ifft" /* fName */
};

/* Function Definitions */
/*
 * Arguments    : const emxArray_creal_T *x
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void b_ifft(const emxArray_creal_T *x, emxArray_creal_T *y)
{
  emxArray_creal_T *fv;
  emxArray_creal_T *fy;
  emxArray_creal_T *r;
  emxArray_creal_T *wwc;
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  const creal_T *x_data;
  creal_T *fv_data;
  creal_T *fy_data;
  creal_T *r1;
  creal_T *wwc_data;
  creal_T *y_data;
  double *costab_data;
  double *sintab_data;
  int chan;
  int i;
  int iDelta2;
  int k;
  int nInt2;
  int nfft_tmp;
  int rt;
  x_data = x->data;
  if (x->size[0] == 1) {
    rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  nfft_tmp = x->size[0];
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    iDelta2 = y->size[0] * y->size[1];
    y->size[0] = x->size[0];
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, iDelta2);
    y_data = y->data;
    rt = x->size[0] * x->size[1];
    for (iDelta2 = 0; iDelta2 < rt; iDelta2++) {
      y_data[iDelta2].re = 0.0;
      y_data[iDelta2].im = 0.0;
    }
  } else {
    int iDelta;
    boolean_T useRadix2;
    useRadix2 = ((x->size[0] & (x->size[0] - 1)) == 0);
    iDelta = c_FFTImplementationCallback_get(x->size[0], useRadix2, &rt);
    emxInit_real_T(&costab, 2);
    emxInit_real_T(&sintab, 2);
    emxInit_real_T(&sintabinv, 2);
    d_FFTImplementationCallback_gen(rt, useRadix2, costab, sintab, sintabinv);
    sintab_data = sintab->data;
    costab_data = costab->data;
    emxInit_creal_T(&r, 1);
    if (useRadix2) {
      double re_tmp;
      int nChan_tmp;
      int nRowsD2;
      int nRowsD4;
      int nRowsM2;
      int u1;
      nChan_tmp = x->size[1];
      iDelta2 = y->size[0] * y->size[1];
      y->size[0] = x->size[0];
      y->size[1] = x->size[1];
      emxEnsureCapacity_creal_T(y, iDelta2);
      y_data = y->data;
      if (x->size[1] > 2147483646) {
        check_forloop_overflow_error();
      }
      rt = x->size[0];
      u1 = x->size[0];
      if (rt <= u1) {
        u1 = rt;
      }
      nRowsM2 = x->size[0] - 2;
      nRowsD2 = x->size[0] / 2;
      nRowsD4 = nRowsD2 / 2;
      for (chan = 0; chan < nChan_tmp; chan++) {
        double nt_im;
        double nt_re;
        double twid_re;
        int iheight;
        int minNrowsNx;
        minNrowsNx = chan * x->size[0];
        iDelta2 = r->size[0];
        r->size[0] = nfft_tmp;
        emxEnsureCapacity_creal_T(r, iDelta2);
        r1 = r->data;
        if (nfft_tmp > x->size[0]) {
          iDelta2 = r->size[0];
          r->size[0] = nfft_tmp;
          emxEnsureCapacity_creal_T(r, iDelta2);
          r1 = r->data;
          for (iDelta2 = 0; iDelta2 < nfft_tmp; iDelta2++) {
            r1[iDelta2].re = 0.0;
            r1[iDelta2].im = 0.0;
          }
        }
        rt = 0;
        nInt2 = 0;
        for (i = 0; i <= u1 - 2; i++) {
          r1[rt] = x_data[minNrowsNx + i];
          rt = nfft_tmp;
          useRadix2 = true;
          while (useRadix2) {
            rt >>= 1;
            nInt2 ^= rt;
            useRadix2 = ((nInt2 & rt) == 0);
          }
          rt = nInt2;
        }
        if (u1 - 2 >= 0) {
          minNrowsNx = (minNrowsNx + u1) - 1;
        }
        r1[rt] = x_data[minNrowsNx];
        if (nfft_tmp > 1) {
          for (i = 0; i <= nRowsM2; i += 2) {
            nt_im = r1[i + 1].re;
            re_tmp = r1[i + 1].im;
            nt_re = r1[i].re;
            twid_re = r1[i].im;
            r1[i + 1].re = nt_re - nt_im;
            r1[i + 1].im = twid_re - re_tmp;
            r1[i].re = nt_re + nt_im;
            r1[i].im = twid_re + re_tmp;
          }
        }
        iDelta = 2;
        iDelta2 = 4;
        k = nRowsD4;
        iheight = ((nRowsD4 - 1) << 2) + 1;
        while (k > 0) {
          for (i = 0; i < iheight; i += iDelta2) {
            int nt_re_tmp;
            nt_re_tmp = i + iDelta;
            nt_re = r1[nt_re_tmp].re;
            nt_im = r1[nt_re_tmp].im;
            r1[nt_re_tmp].re = r1[i].re - nt_re;
            r1[nt_re_tmp].im = r1[i].im - nt_im;
            r1[i].re += nt_re;
            r1[i].im += nt_im;
          }
          rt = 1;
          for (nInt2 = k; nInt2 < nRowsD2; nInt2 += k) {
            double twid_im;
            twid_re = costab_data[nInt2];
            twid_im = sintab_data[nInt2];
            i = rt;
            minNrowsNx = rt + iheight;
            while (i < minNrowsNx) {
              int nInt2m1;
              nInt2m1 = i + iDelta;
              nt_im = r1[nInt2m1].im;
              re_tmp = r1[nInt2m1].re;
              nt_re = twid_re * re_tmp - twid_im * nt_im;
              nt_im = twid_re * nt_im + twid_im * re_tmp;
              r1[nInt2m1].re = r1[i].re - nt_re;
              r1[nInt2m1].im = r1[i].im - nt_im;
              r1[i].re += nt_re;
              r1[i].im += nt_im;
              i += iDelta2;
            }
            rt++;
          }
          k /= 2;
          iDelta = iDelta2;
          iDelta2 += iDelta2;
          iheight -= iDelta;
        }
        for (iDelta2 = 0; iDelta2 < nfft_tmp; iDelta2++) {
          y_data[iDelta2 + y->size[0] * chan] = r1[iDelta2];
        }
      }
      if (y->size[0] > 1) {
        re_tmp = 1.0 / (double)y->size[0];
        rt = y->size[0] * y->size[1];
        for (iDelta2 = 0; iDelta2 < rt; iDelta2++) {
          y_data[iDelta2].re *= re_tmp;
          y_data[iDelta2].im *= re_tmp;
        }
      }
    } else {
      double nt_im;
      int minNrowsNx;
      int nChan_tmp;
      int nInt2m1;
      boolean_T b_overflow;
      boolean_T overflow;
      nChan_tmp = x->size[1];
      nInt2m1 = (x->size[0] + x->size[0]) - 1;
      emxInit_creal_T(&wwc, 1);
      if (nInt2m1 < 0) {
        rtNonNegativeError(nInt2m1, &d_emlrtDCI);
      }
      iDelta2 = wwc->size[0];
      wwc->size[0] = nInt2m1;
      emxEnsureCapacity_creal_T(wwc, iDelta2);
      wwc_data = wwc->data;
      rt = 0;
      wwc_data[x->size[0] - 1].re = 1.0;
      wwc_data[x->size[0] - 1].im = 0.0;
      nInt2 = x->size[0] << 1;
      for (k = 0; k <= nfft_tmp - 2; k++) {
        minNrowsNx = ((k + 1) << 1) - 1;
        if (nInt2 - rt <= minNrowsNx) {
          rt += minNrowsNx - nInt2;
        } else {
          rt += minNrowsNx;
        }
        nt_im = 3.1415926535897931 * (double)rt / (double)nfft_tmp;
        wwc_data[(x->size[0] - k) - 2].re = cos(nt_im);
        wwc_data[(x->size[0] - k) - 2].im = -sin(nt_im);
      }
      iDelta2 = nInt2m1 - 1;
      for (k = iDelta2; k >= nfft_tmp; k--) {
        wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
      }
      iDelta2 = y->size[0] * y->size[1];
      y->size[0] = x->size[0];
      y->size[1] = x->size[1];
      emxEnsureCapacity_creal_T(y, iDelta2);
      y_data = y->data;
      if (x->size[1] > 2147483646) {
        check_forloop_overflow_error();
      }
      rt = x->size[0];
      minNrowsNx = x->size[0];
      if (rt <= minNrowsNx) {
        minNrowsNx = rt;
      }
      useRadix2 = (minNrowsNx > 2147483646);
      nInt2 = minNrowsNx + 1;
      overflow = ((minNrowsNx + 1 <= x->size[0]) && (x->size[0] > 2147483646));
      b_overflow =
          ((x->size[0] <= wwc->size[0]) && (wwc->size[0] > 2147483646));
      emxInit_creal_T(&fy, 1);
      emxInit_creal_T(&fv, 1);
      for (chan = 0; chan < nChan_tmp; chan++) {
        double nt_re;
        double re_tmp;
        double twid_re;
        iDelta2 = r->size[0];
        r->size[0] = nfft_tmp;
        emxEnsureCapacity_creal_T(r, iDelta2);
        r1 = r->data;
        if (nfft_tmp > x->size[0]) {
          iDelta2 = r->size[0];
          r->size[0] = nfft_tmp;
          emxEnsureCapacity_creal_T(r, iDelta2);
          r1 = r->data;
          for (iDelta2 = 0; iDelta2 < nfft_tmp; iDelta2++) {
            r1[iDelta2].re = 0.0;
            r1[iDelta2].im = 0.0;
          }
        }
        rt = chan * x->size[0];
        if (useRadix2) {
          check_forloop_overflow_error();
        }
        for (k = 0; k < minNrowsNx; k++) {
          int nt_re_tmp;
          nt_re_tmp = (nfft_tmp + k) - 1;
          nt_re = wwc_data[nt_re_tmp].re;
          nt_im = wwc_data[nt_re_tmp].im;
          iDelta2 = rt + k;
          re_tmp = x_data[iDelta2].im;
          twid_re = x_data[iDelta2].re;
          r1[k].re = nt_re * twid_re + nt_im * re_tmp;
          r1[k].im = nt_re * re_tmp - nt_im * twid_re;
        }
        if (overflow) {
          check_forloop_overflow_error();
        }
        for (k = nInt2; k <= nfft_tmp; k++) {
          r1[k - 1].re = 0.0;
          r1[k - 1].im = 0.0;
        }
        e_FFTImplementationCallback_r2b(r, iDelta, costab, sintab, fy);
        fy_data = fy->data;
        e_FFTImplementationCallback_r2b(wwc, iDelta, costab, sintab, fv);
        fv_data = fv->data;
        rt = fy->size[0];
        for (iDelta2 = 0; iDelta2 < rt; iDelta2++) {
          nt_re = fy_data[iDelta2].re;
          re_tmp = fv_data[iDelta2].im;
          twid_re = fy_data[iDelta2].im;
          nt_im = fv_data[iDelta2].re;
          fy_data[iDelta2].re = nt_re * nt_im - twid_re * re_tmp;
          fy_data[iDelta2].im = nt_re * re_tmp + twid_re * nt_im;
        }
        e_FFTImplementationCallback_r2b(fy, iDelta, costab, sintabinv, fv);
        fv_data = fv->data;
        if (fv->size[0] > 1) {
          re_tmp = 1.0 / (double)fv->size[0];
          rt = fv->size[0];
          for (iDelta2 = 0; iDelta2 < rt; iDelta2++) {
            fv_data[iDelta2].re *= re_tmp;
            fv_data[iDelta2].im *= re_tmp;
          }
        }
        if (b_overflow) {
          check_forloop_overflow_error();
        }
        for (k = nfft_tmp; k <= nInt2m1; k++) {
          double twid_im;
          re_tmp = wwc_data[k - 1].re;
          twid_re = fv_data[k - 1].im;
          nt_im = wwc_data[k - 1].im;
          twid_im = fv_data[k - 1].re;
          nt_re = re_tmp * twid_im + nt_im * twid_re;
          re_tmp = re_tmp * twid_re - nt_im * twid_im;
          if (re_tmp == 0.0) {
            iDelta2 = k - nfft_tmp;
            r1[iDelta2].re = nt_re / (double)nfft_tmp;
            r1[iDelta2].im = 0.0;
          } else if (nt_re == 0.0) {
            iDelta2 = k - nfft_tmp;
            r1[iDelta2].re = 0.0;
            r1[iDelta2].im = re_tmp / (double)nfft_tmp;
          } else {
            iDelta2 = k - nfft_tmp;
            r1[iDelta2].re = nt_re / (double)nfft_tmp;
            r1[iDelta2].im = re_tmp / (double)nfft_tmp;
          }
        }
        for (iDelta2 = 0; iDelta2 < nfft_tmp; iDelta2++) {
          y_data[iDelta2 + y->size[0] * chan] = r1[iDelta2];
        }
      }
      emxFree_creal_T(&fv);
      emxFree_creal_T(&fy);
      emxFree_creal_T(&wwc);
    }
    emxFree_creal_T(&r);
    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void ifft(const emxArray_real_T *x, emxArray_creal_T *y)
{
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  creal_T *y_data;
  int nRows;
  if (x->size[0] == 1) {
    rtErrorWithMessageID(h_emlrtRTEI.fName, h_emlrtRTEI.lineNo);
  }
  if ((x->size[0] == 0) || (x->size[1] == 0)) {
    int N2blue;
    nRows = y->size[0] * y->size[1];
    y->size[0] = x->size[0];
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, nRows);
    y_data = y->data;
    N2blue = x->size[0] * x->size[1];
    for (nRows = 0; nRows < N2blue; nRows++) {
      y_data[nRows].re = 0.0;
      y_data[nRows].im = 0.0;
    }
  } else {
    int N2blue;
    boolean_T useRadix2;
    useRadix2 = ((x->size[0] & (x->size[0] - 1)) == 0);
    N2blue = c_FFTImplementationCallback_get(x->size[0], useRadix2, &nRows);
    emxInit_real_T(&costab, 2);
    emxInit_real_T(&sintab, 2);
    emxInit_real_T(&sintabinv, 2);
    d_FFTImplementationCallback_gen(nRows, useRadix2, costab, sintab,
                                    sintabinv);
    if (useRadix2) {
      f_FFTImplementationCallback_r2b(x, x->size[0], costab, sintab, y);
    } else {
      d_FFTImplementationCallback_dob(x, N2blue, x->size[0], costab, sintab,
                                      sintabinv, y);
    }
    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
  }
}

/*
 * File trailer for ifft.c
 *
 * [EOF]
 */
