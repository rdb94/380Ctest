/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: FFTImplementationCallback.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
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
static rtDoubleCheckInfo emlrtDCI = {
    1149,                                            /* lineNo */
    "FFTImplementationCallback/make_1q_cosine_table" /* fName */
};

static rtDoubleCheckInfo b_emlrtDCI = {
    1174,                                          /* lineNo */
    "FFTImplementationCallback/make_twiddle_table" /* fName */
};

static rtDoubleCheckInfo c_emlrtDCI = {
    19,              /* lineNo */
    "allocFftOutput" /* fName */
};

/* Function Declarations */
static void c_FFTImplementationCallback_doH(const emxArray_real_T *x,
                                            int xoffInit, emxArray_creal_T *y,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab);

static void d_FFTImplementationCallback_doH(
    const emxArray_real_T *x, int xoffInit, emxArray_creal_T *y, int nrowsx,
    int nRows, int nfft, const emxArray_creal_T *wwc,
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv);

static void d_FFTImplementationCallback_get(int nRowsM1, int nfftLen,
                                            emxArray_int32_T *bitrevIndex);

static void d_FFTImplementationCallback_r2b(const emxArray_real_T *x,
                                            int xoffInit, int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y);

static void e_FFTImplementationCallback_doH(
    const emxArray_real_T *x, int xoffInit, emxArray_creal_T *y, int nrowsx,
    int nRows, int nfft, const emxArray_creal_T *wwc,
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv);

static void e_FFTImplementationCallback_gen(int nRows, emxArray_real_T *costab,
                                            emxArray_real_T *sintab,
                                            emxArray_real_T *sintabinv);

static void e_FFTImplementationCallback_get(
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv,
    emxArray_real_T *hcostab, emxArray_real_T *hsintab,
    emxArray_real_T *hcostabinv, emxArray_real_T *hsintabinv);

static void f_FFTImplementationCallback_doH(const emxArray_real_T *x,
                                            emxArray_creal_T *y,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab);

static void f_FFTImplementationCallback_get(emxArray_creal_T *y,
                                            const emxArray_creal_T *reconVar1,
                                            const emxArray_creal_T *reconVar2,
                                            const emxArray_int32_T *wrapIndex,
                                            int hnRows);

static void g_FFTImplementationCallback_doH(
    const emxArray_real_T *x, emxArray_creal_T *y, int nrowsx, int nRows,
    int nfft, const emxArray_creal_T *wwc, const emxArray_real_T *costab,
    const emxArray_real_T *sintab, const emxArray_real_T *costabinv,
    const emxArray_real_T *sintabinv);

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                int xoffInit
 *                emxArray_creal_T *y
 *                int unsigned_nRows
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 * Return Type  : void
 */
static void c_FFTImplementationCallback_doH(const emxArray_real_T *x,
                                            int xoffInit, emxArray_creal_T *y,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab)
{
  static rtDoubleCheckInfo e_emlrtDCI = {
      1006,                                               /* lineNo */
      "FFTImplementationCallback/get_reconstruct_factors" /* fName */
  };
  emxArray_creal_T *reconVar1;
  emxArray_creal_T *reconVar2;
  emxArray_int32_T *bitrevIndex;
  emxArray_int32_T *wrapIndex;
  emxArray_real_T *hcostab;
  emxArray_real_T *hsintab;
  creal_T *reconVar1_data;
  creal_T *reconVar2_data;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  const double *x_data;
  double im;
  double re;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  double *hcostab_data;
  double *hsintab_data;
  int hszCostab;
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int ihi;
  int k;
  int minXBy2;
  int nRowsD2;
  int nRowsM2;
  int nRows_tmp;
  int *wrapIndex_data;
  boolean_T nxeven;
  sintab_data = sintab->data;
  costab_data = costab->data;
  y_data = y->data;
  x_data = x->data;
  nRows_tmp = unsigned_nRows / 2;
  nRowsM2 = nRows_tmp - 2;
  nRowsD2 = nRows_tmp / 2;
  k = nRowsD2 / 2;
  hszCostab = (int)((unsigned int)costab->size[1] >> 1);
  emxInit_real_T(&hcostab, 2);
  ihi = hcostab->size[0] * hcostab->size[1];
  hcostab->size[0] = 1;
  hcostab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hcostab, ihi);
  hcostab_data = hcostab->data;
  emxInit_real_T(&hsintab, 2);
  ihi = hsintab->size[0] * hsintab->size[1];
  hsintab->size[0] = 1;
  hsintab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hsintab, ihi);
  hsintab_data = hsintab->data;
  for (i = 0; i < hszCostab; i++) {
    minXBy2 = ((i + 1) << 1) - 2;
    hcostab_data[i] = costab_data[minXBy2];
    hsintab_data[i] = sintab_data[minXBy2];
  }
  emxInit_creal_T(&reconVar1, 1);
  if (nRows_tmp < 0) {
    rtNonNegativeError(nRows_tmp, &e_emlrtDCI);
  }
  ihi = reconVar1->size[0];
  reconVar1->size[0] = nRows_tmp;
  emxEnsureCapacity_creal_T(reconVar1, ihi);
  reconVar1_data = reconVar1->data;
  emxInit_creal_T(&reconVar2, 1);
  ihi = reconVar2->size[0];
  reconVar2->size[0] = nRows_tmp;
  emxEnsureCapacity_creal_T(reconVar2, ihi);
  reconVar2_data = reconVar2->data;
  emxInit_int32_T(&wrapIndex, 2);
  ihi = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[0] = 1;
  wrapIndex->size[1] = nRows_tmp;
  emxEnsureCapacity_int32_T(wrapIndex, ihi);
  wrapIndex_data = wrapIndex->data;
  for (i = 0; i < nRows_tmp; i++) {
    re = sintab_data[i];
    im = costab_data[i];
    reconVar1_data[i].re = re + 1.0;
    reconVar1_data[i].im = -im;
    reconVar2_data[i].re = 1.0 - re;
    reconVar2_data[i].im = im;
    if (i + 1 != 1) {
      wrapIndex_data[i] = (nRows_tmp - i) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
  }
  emxInit_int32_T(&bitrevIndex, 1);
  minXBy2 = y->size[0];
  if (minXBy2 > nRows_tmp) {
    minXBy2 = nRows_tmp;
  }
  d_FFTImplementationCallback_get(minXBy2 - 1, nRows_tmp, bitrevIndex);
  wrapIndex_data = bitrevIndex->data;
  if ((x->size[0] & 1) == 0) {
    nxeven = true;
    minXBy2 = x->size[0];
  } else if (x->size[0] >= unsigned_nRows) {
    nxeven = true;
    minXBy2 = unsigned_nRows;
  } else {
    nxeven = false;
    minXBy2 = x->size[0] - 1;
  }
  if (minXBy2 > unsigned_nRows) {
    minXBy2 = unsigned_nRows;
  }
  minXBy2 /= 2;
  for (i = 0; i < minXBy2; i++) {
    ihi = xoffInit + (i << 1);
    y_data[wrapIndex_data[i] - 1].re = x_data[ihi];
    y_data[wrapIndex_data[i] - 1].im = x_data[ihi + 1];
  }
  if (!nxeven) {
    if (minXBy2 - 1 < 0) {
      hszCostab = xoffInit;
    } else {
      hszCostab = xoffInit + (minXBy2 << 1);
    }
    y_data[wrapIndex_data[minXBy2] - 1].re = x_data[hszCostab];
    y_data[wrapIndex_data[minXBy2] - 1].im = 0.0;
  }
  emxFree_int32_T(&bitrevIndex);
  if (nRows_tmp > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      re = y_data[i + 1].re;
      im = y_data[i + 1].im;
      temp_re = re;
      temp_im = im;
      twid_re = y_data[i].re;
      twid_im = y_data[i].im;
      re = twid_re - re;
      im = twid_im - im;
      y_data[i + 1].re = re;
      y_data[i + 1].im = im;
      twid_re += temp_re;
      twid_im += temp_im;
      y_data[i].re = twid_re;
      y_data[i].im = twid_im;
    }
  }
  iDelta = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      minXBy2 = i + iDelta;
      temp_re = y_data[minXBy2].re;
      temp_im = y_data[minXBy2].im;
      y_data[minXBy2].re = y_data[i].re - temp_re;
      y_data[minXBy2].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }
    minXBy2 = 1;
    for (hszCostab = k; hszCostab < nRowsD2; hszCostab += k) {
      twid_re = hcostab_data[hszCostab];
      twid_im = hsintab_data[hszCostab];
      i = minXBy2;
      ihi = minXBy2 + iheight;
      while (i < ihi) {
        nRowsM2 = i + iDelta;
        re = y_data[nRowsM2].im;
        im = y_data[nRowsM2].re;
        temp_re = twid_re * im - twid_im * re;
        temp_im = twid_re * re + twid_im * im;
        y_data[nRowsM2].re = y_data[i].re - temp_re;
        y_data[nRowsM2].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += iDelta2;
      }
      minXBy2++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
  emxFree_real_T(&hsintab);
  emxFree_real_T(&hcostab);
  f_FFTImplementationCallback_get(y, reconVar1, reconVar2, wrapIndex,
                                  nRows_tmp);
  emxFree_creal_T(&reconVar2);
  emxFree_creal_T(&reconVar1);
  emxFree_int32_T(&wrapIndex);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int xoffInit
 *                emxArray_creal_T *y
 *                int nrowsx
 *                int nRows
 *                int nfft
 *                const emxArray_creal_T *wwc
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *costabinv
 *                const emxArray_real_T *sintabinv
 * Return Type  : void
 */
static void d_FFTImplementationCallback_doH(
    const emxArray_real_T *x, int xoffInit, emxArray_creal_T *y, int nrowsx,
    int nRows, int nfft, const emxArray_creal_T *wwc,
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv)
{
  emxArray_creal_T *fv;
  emxArray_creal_T *fy;
  emxArray_creal_T *reconVar1;
  emxArray_creal_T *reconVar2;
  emxArray_creal_T *ytmp;
  emxArray_int32_T *wrapIndex;
  emxArray_real_T *b_costab;
  emxArray_real_T *b_sintab;
  emxArray_real_T *costab1q;
  emxArray_real_T *hcostabinv;
  emxArray_real_T *hsintab;
  emxArray_real_T *hsintabinv;
  const creal_T *wwc_data;
  creal_T *fv_data;
  creal_T *fy_data;
  creal_T *reconVar1_data;
  creal_T *reconVar2_data;
  creal_T *y_data;
  creal_T *ytmp_data;
  const double *x_data;
  double a_im;
  double b_im;
  double b_re;
  double e;
  double *costab1q_data;
  double *costab_data;
  double *sintab_data;
  int hnRows;
  int i;
  int k;
  int n;
  int n2;
  int nd2;
  int u0;
  int *wrapIndex_data;
  boolean_T nxeven;
  wwc_data = wwc->data;
  y_data = y->data;
  x_data = x->data;
  hnRows = nRows / 2;
  if (hnRows < 0) {
    rtNonNegativeError(hnRows, &c_emlrtDCI);
  }
  emxInit_creal_T(&ytmp, 1);
  i = ytmp->size[0];
  ytmp->size[0] = hnRows;
  emxEnsureCapacity_creal_T(ytmp, i);
  ytmp_data = ytmp->data;
  if (hnRows > nrowsx) {
    i = ytmp->size[0];
    ytmp->size[0] = hnRows;
    emxEnsureCapacity_creal_T(ytmp, i);
    ytmp_data = ytmp->data;
    for (i = 0; i < hnRows; i++) {
      ytmp_data[i].re = 0.0;
      ytmp_data[i].im = 0.0;
    }
  }
  if ((x->size[0] & 1) == 0) {
    nxeven = true;
    u0 = x->size[0];
  } else if (x->size[0] >= nRows) {
    nxeven = true;
    u0 = nRows;
  } else {
    nxeven = false;
    u0 = x->size[0] - 1;
  }
  nd2 = nRows << 1;
  e = 6.2831853071795862 / (double)nd2;
  n = nd2 / 2 / 2;
  emxInit_real_T(&costab1q, 2);
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  emxEnsureCapacity_real_T(costab1q, i);
  if (n + 1 < 0) {
    rtNonNegativeError((double)n + 1.0, &emlrtDCI);
  }
  i = n + 1;
  nd2 = costab1q->size[0] * costab1q->size[1];
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, nd2);
  costab1q_data = costab1q->data;
  costab1q_data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(e * ((double)k + 1.0));
  }
  nd2 += 2;
  n2 = n - 1;
  for (k = nd2; k <= n2; k++) {
    costab1q_data[k] = sin(e * (double)(n - k));
  }
  costab1q_data[n] = 0.0;
  n = costab1q->size[1] - 1;
  n2 = (costab1q->size[1] - 1) << 1;
  emxInit_real_T(&b_costab, 2);
  nd2 = b_costab->size[0] * b_costab->size[1];
  b_costab->size[0] = 1;
  emxEnsureCapacity_real_T(b_costab, nd2);
  if (n2 + 1 < 0) {
    rtNonNegativeError(-1.0, &b_emlrtDCI);
  }
  nd2 = b_costab->size[0] * b_costab->size[1];
  b_costab->size[1] = n2 + 1;
  emxEnsureCapacity_real_T(b_costab, nd2);
  costab_data = b_costab->data;
  emxInit_real_T(&b_sintab, 2);
  nd2 = b_sintab->size[0] * b_sintab->size[1];
  b_sintab->size[0] = 1;
  b_sintab->size[1] = n2 + 1;
  emxEnsureCapacity_real_T(b_sintab, nd2);
  sintab_data = b_sintab->data;
  costab_data[0] = 1.0;
  sintab_data[0] = 0.0;
  for (k = 0; k < n; k++) {
    costab_data[k + 1] = costab1q_data[k + 1];
    sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
  }
  for (k = i; k <= n2; k++) {
    costab_data[k] = -costab1q_data[n2 - k];
    sintab_data[k] = -costab1q_data[k - n];
  }
  emxInit_real_T(&hsintab, 2);
  emxInit_real_T(&hcostabinv, 2);
  emxInit_real_T(&hsintabinv, 2);
  e_FFTImplementationCallback_get(costab, sintab, costabinv, sintabinv,
                                  costab1q, hsintab, hcostabinv, hsintabinv);
  emxInit_creal_T(&reconVar1, 1);
  i = reconVar1->size[0];
  reconVar1->size[0] = hnRows;
  emxEnsureCapacity_creal_T(reconVar1, i);
  reconVar1_data = reconVar1->data;
  emxInit_creal_T(&reconVar2, 1);
  i = reconVar2->size[0];
  reconVar2->size[0] = hnRows;
  emxEnsureCapacity_creal_T(reconVar2, i);
  reconVar2_data = reconVar2->data;
  emxInit_int32_T(&wrapIndex, 2);
  i = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[0] = 1;
  wrapIndex->size[1] = hnRows;
  emxEnsureCapacity_int32_T(wrapIndex, i);
  wrapIndex_data = wrapIndex->data;
  for (nd2 = 0; nd2 < hnRows; nd2++) {
    i = nd2 << 1;
    e = sintab_data[i];
    a_im = costab_data[i];
    reconVar1_data[nd2].re = e + 1.0;
    reconVar1_data[nd2].im = -a_im;
    reconVar2_data[nd2].re = 1.0 - e;
    reconVar2_data[nd2].im = a_im;
    if (nd2 + 1 != 1) {
      wrapIndex_data[nd2] = (hnRows - nd2) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
  }
  emxFree_real_T(&b_sintab);
  emxFree_real_T(&b_costab);
  if (u0 > nRows) {
    u0 = nRows;
  }
  n2 = u0 / 2 - 1;
  for (n = 0; n <= n2; n++) {
    nd2 = (hnRows + n) - 1;
    e = wwc_data[nd2].re;
    a_im = wwc_data[nd2].im;
    nd2 = xoffInit + (n << 1);
    b_re = x_data[nd2];
    b_im = x_data[nd2 + 1];
    ytmp_data[n].re = e * b_re + a_im * b_im;
    ytmp_data[n].im = e * b_im - a_im * b_re;
  }
  if (!nxeven) {
    nd2 = hnRows + n2;
    e = wwc_data[nd2].re;
    a_im = wwc_data[nd2].im;
    if (n2 < 0) {
      i = xoffInit;
    } else {
      i = xoffInit + ((n2 + 1) << 1);
    }
    b_re = x_data[i];
    ytmp_data[n2 + 1].re = e * b_re + a_im * 0.0;
    ytmp_data[n2 + 1].im = e * 0.0 - a_im * b_re;
    if (n2 + 3 <= hnRows) {
      i = n2 + 3;
      for (nd2 = i; nd2 <= hnRows; nd2++) {
        ytmp_data[nd2 - 1].re = 0.0;
        ytmp_data[nd2 - 1].im = 0.0;
      }
    }
  } else if (n2 + 2 <= hnRows) {
    i = n2 + 2;
    for (nd2 = i; nd2 <= hnRows; nd2++) {
      ytmp_data[nd2 - 1].re = 0.0;
      ytmp_data[nd2 - 1].im = 0.0;
    }
  }
  nd2 = nfft / 2;
  emxInit_creal_T(&fy, 1);
  e_FFTImplementationCallback_r2b(ytmp, nd2, costab1q, hsintab, fy);
  fy_data = fy->data;
  emxInit_creal_T(&fv, 1);
  e_FFTImplementationCallback_r2b(wwc, nd2, costab1q, hsintab, fv);
  fv_data = fv->data;
  emxFree_real_T(&costab1q);
  emxFree_real_T(&hsintab);
  n2 = fy->size[0];
  for (i = 0; i < n2; i++) {
    e = fy_data[i].re;
    a_im = fv_data[i].im;
    b_re = fy_data[i].im;
    b_im = fv_data[i].re;
    fy_data[i].re = e * b_im - b_re * a_im;
    fy_data[i].im = e * a_im + b_re * b_im;
  }
  e_FFTImplementationCallback_r2b(fy, nd2, hcostabinv, hsintabinv, fv);
  fv_data = fv->data;
  emxFree_creal_T(&fy);
  emxFree_real_T(&hsintabinv);
  emxFree_real_T(&hcostabinv);
  if (fv->size[0] > 1) {
    e = 1.0 / (double)fv->size[0];
    n2 = fv->size[0];
    for (i = 0; i < n2; i++) {
      fv_data[i].re *= e;
      fv_data[i].im *= e;
    }
  }
  nd2 = wwc->size[0];
  if ((hnRows <= wwc->size[0]) && (wwc->size[0] > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (k = hnRows; k <= nd2; k++) {
    e = wwc_data[k - 1].re;
    a_im = fv_data[k - 1].im;
    b_re = wwc_data[k - 1].im;
    b_im = fv_data[k - 1].re;
    i = k - hnRows;
    ytmp_data[i].re = e * b_im + b_re * a_im;
    ytmp_data[i].im = e * a_im - b_re * b_im;
  }
  emxFree_creal_T(&fv);
  for (nd2 = 0; nd2 < hnRows; nd2++) {
    double b_ytmp_re_tmp;
    double c_ytmp_re_tmp;
    double ytmp_im_tmp;
    double ytmp_re_tmp;
    i = wrapIndex_data[nd2];
    e = ytmp_data[nd2].re;
    a_im = reconVar1_data[nd2].im;
    b_re = ytmp_data[nd2].im;
    b_im = reconVar1_data[nd2].re;
    ytmp_re_tmp = ytmp_data[i - 1].re;
    ytmp_im_tmp = -ytmp_data[i - 1].im;
    b_ytmp_re_tmp = reconVar2_data[nd2].im;
    c_ytmp_re_tmp = reconVar2_data[nd2].re;
    y_data[nd2].re =
        0.5 * ((e * b_im - b_re * a_im) +
               (ytmp_re_tmp * c_ytmp_re_tmp - ytmp_im_tmp * b_ytmp_re_tmp));
    y_data[nd2].im =
        0.5 * ((e * a_im + b_re * b_im) +
               (ytmp_re_tmp * b_ytmp_re_tmp + ytmp_im_tmp * c_ytmp_re_tmp));
    i = hnRows + nd2;
    y_data[i].re = 0.5 * ((e * c_ytmp_re_tmp - b_re * b_ytmp_re_tmp) +
                          (ytmp_re_tmp * b_im - ytmp_im_tmp * a_im));
    y_data[i].im = 0.5 * ((e * b_ytmp_re_tmp + b_re * c_ytmp_re_tmp) +
                          (ytmp_re_tmp * a_im + ytmp_im_tmp * b_im));
  }
  emxFree_creal_T(&reconVar2);
  emxFree_creal_T(&reconVar1);
  emxFree_int32_T(&wrapIndex);
  emxFree_creal_T(&ytmp);
}

/*
 * Arguments    : int nRowsM1
 *                int nfftLen
 *                emxArray_int32_T *bitrevIndex
 * Return Type  : void
 */
static void d_FFTImplementationCallback_get(int nRowsM1, int nfftLen,
                                            emxArray_int32_T *bitrevIndex)
{
  static rtDoubleCheckInfo e_emlrtDCI = {
      844,                                        /* lineNo */
      "FFTImplementationCallback/get_bitrevIndex" /* fName */
  };
  int b_j1;
  int iy;
  int ju;
  int *bitrevIndex_data;
  ju = 0;
  iy = 1;
  if (nfftLen < 0) {
    rtNonNegativeError(nfftLen, &e_emlrtDCI);
  }
  b_j1 = bitrevIndex->size[0];
  bitrevIndex->size[0] = nfftLen;
  emxEnsureCapacity_int32_T(bitrevIndex, b_j1);
  bitrevIndex_data = bitrevIndex->data;
  for (b_j1 = 0; b_j1 < nfftLen; b_j1++) {
    bitrevIndex_data[b_j1] = 0;
  }
  if (nRowsM1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (b_j1 = 0; b_j1 < nRowsM1; b_j1++) {
    boolean_T tst;
    bitrevIndex_data[b_j1] = iy;
    iy = nfftLen;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju + 1;
  }
  bitrevIndex_data[nRowsM1] = iy;
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int xoffInit
 *                int unsigned_nRows
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
static void d_FFTImplementationCallback_r2b(const emxArray_real_T *x,
                                            int xoffInit, int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab,
                                            emxArray_creal_T *y)
{
  creal_T *y_data;
  const double *x_data;
  int i;
  x_data = x->data;
  if (unsigned_nRows < 0) {
    rtNonNegativeError(unsigned_nRows, &c_emlrtDCI);
  }
  i = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (unsigned_nRows > x->size[0]) {
    i = y->size[0];
    y->size[0] = unsigned_nRows;
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    for (i = 0; i < unsigned_nRows; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  if (unsigned_nRows != 1) {
    c_FFTImplementationCallback_doH(x, xoffInit, y, unsigned_nRows, costab,
                                    sintab);
  } else {
    y_data[0].re = x_data[xoffInit];
    y_data[0].im = 0.0;
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int xoffInit
 *                emxArray_creal_T *y
 *                int nrowsx
 *                int nRows
 *                int nfft
 *                const emxArray_creal_T *wwc
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *costabinv
 *                const emxArray_real_T *sintabinv
 * Return Type  : void
 */
static void e_FFTImplementationCallback_doH(
    const emxArray_real_T *x, int xoffInit, emxArray_creal_T *y, int nrowsx,
    int nRows, int nfft, const emxArray_creal_T *wwc,
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv)
{
  emxArray_creal_T *fv;
  emxArray_creal_T *fy;
  emxArray_creal_T *reconVar1;
  emxArray_creal_T *reconVar2;
  emxArray_creal_T *ytmp;
  emxArray_int32_T *wrapIndex;
  emxArray_real_T *a__1;
  emxArray_real_T *costable;
  emxArray_real_T *hcostabinv;
  emxArray_real_T *hsintab;
  emxArray_real_T *hsintabinv;
  emxArray_real_T *sintable;
  const creal_T *wwc_data;
  creal_T *fv_data;
  creal_T *fy_data;
  creal_T *reconVar1_data;
  creal_T *reconVar2_data;
  creal_T *y_data;
  creal_T *ytmp_data;
  const double *x_data;
  double a_im;
  double a_re;
  double ar;
  double b_im;
  double b_re;
  double *costable_data;
  double *sintable_data;
  int hnRows;
  int k1;
  int minHnrowsNxBy2;
  int u0;
  int *wrapIndex_data;
  boolean_T nxeven;
  wwc_data = wwc->data;
  y_data = y->data;
  x_data = x->data;
  hnRows = nRows / 2;
  if (hnRows < 0) {
    rtNonNegativeError(hnRows, &c_emlrtDCI);
  }
  emxInit_creal_T(&ytmp, 1);
  k1 = ytmp->size[0];
  ytmp->size[0] = hnRows;
  emxEnsureCapacity_creal_T(ytmp, k1);
  ytmp_data = ytmp->data;
  if (hnRows > nrowsx) {
    k1 = ytmp->size[0];
    ytmp->size[0] = hnRows;
    emxEnsureCapacity_creal_T(ytmp, k1);
    ytmp_data = ytmp->data;
    for (k1 = 0; k1 < hnRows; k1++) {
      ytmp_data[k1].re = 0.0;
      ytmp_data[k1].im = 0.0;
    }
  }
  if ((x->size[0] & 1) == 0) {
    nxeven = true;
    u0 = x->size[0];
  } else if (x->size[0] >= nRows) {
    nxeven = true;
    u0 = nRows;
  } else {
    nxeven = false;
    u0 = x->size[0] - 1;
  }
  emxInit_real_T(&a__1, 2);
  emxInit_real_T(&costable, 2);
  emxInit_real_T(&sintable, 2);
  e_FFTImplementationCallback_gen(nRows << 1, costable, sintable, a__1);
  sintable_data = sintable->data;
  costable_data = costable->data;
  emxInit_real_T(&hsintab, 2);
  emxInit_real_T(&hcostabinv, 2);
  emxInit_real_T(&hsintabinv, 2);
  e_FFTImplementationCallback_get(costab, sintab, costabinv, sintabinv, a__1,
                                  hsintab, hcostabinv, hsintabinv);
  emxInit_creal_T(&reconVar1, 1);
  k1 = reconVar1->size[0];
  reconVar1->size[0] = hnRows;
  emxEnsureCapacity_creal_T(reconVar1, k1);
  reconVar1_data = reconVar1->data;
  emxInit_creal_T(&reconVar2, 1);
  k1 = reconVar2->size[0];
  reconVar2->size[0] = hnRows;
  emxEnsureCapacity_creal_T(reconVar2, k1);
  reconVar2_data = reconVar2->data;
  for (minHnrowsNxBy2 = 0; minHnrowsNxBy2 < hnRows; minHnrowsNxBy2++) {
    k1 = minHnrowsNxBy2 << 1;
    a_re = sintable_data[k1];
    a_im = costable_data[k1];
    reconVar1_data[minHnrowsNxBy2].re = 1.0 - a_re;
    reconVar1_data[minHnrowsNxBy2].im = -a_im;
    reconVar2_data[minHnrowsNxBy2].re = a_re + 1.0;
    reconVar2_data[minHnrowsNxBy2].im = a_im;
  }
  emxFree_real_T(&sintable);
  emxFree_real_T(&costable);
  emxInit_int32_T(&wrapIndex, 2);
  k1 = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[0] = 1;
  emxEnsureCapacity_int32_T(wrapIndex, k1);
  k1 = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[1] = hnRows;
  emxEnsureCapacity_int32_T(wrapIndex, k1);
  wrapIndex_data = wrapIndex->data;
  for (minHnrowsNxBy2 = 0; minHnrowsNxBy2 < hnRows; minHnrowsNxBy2++) {
    if (minHnrowsNxBy2 + 1 != 1) {
      wrapIndex_data[minHnrowsNxBy2] = (hnRows - minHnrowsNxBy2) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
  }
  if (u0 > nRows) {
    u0 = nRows;
  }
  minHnrowsNxBy2 = u0 / 2 - 1;
  for (k1 = 0; k1 <= minHnrowsNxBy2; k1++) {
    u0 = (hnRows + k1) - 1;
    a_re = wwc_data[u0].re;
    a_im = wwc_data[u0].im;
    u0 = xoffInit + (k1 << 1);
    b_re = x_data[u0];
    b_im = x_data[u0 + 1];
    ytmp_data[k1].re = a_re * b_re + a_im * b_im;
    ytmp_data[k1].im = a_re * b_im - a_im * b_re;
  }
  if (!nxeven) {
    u0 = hnRows + minHnrowsNxBy2;
    a_re = wwc_data[u0].re;
    a_im = wwc_data[u0].im;
    if (minHnrowsNxBy2 < 0) {
      u0 = xoffInit;
    } else {
      u0 = xoffInit + ((minHnrowsNxBy2 + 1) << 1);
    }
    b_re = x_data[u0];
    ytmp_data[minHnrowsNxBy2 + 1].re = a_re * b_re + a_im * 0.0;
    ytmp_data[minHnrowsNxBy2 + 1].im = a_re * 0.0 - a_im * b_re;
    if (minHnrowsNxBy2 + 3 <= hnRows) {
      k1 = minHnrowsNxBy2 + 3;
      for (minHnrowsNxBy2 = k1; minHnrowsNxBy2 <= hnRows; minHnrowsNxBy2++) {
        ytmp_data[minHnrowsNxBy2 - 1].re = 0.0;
        ytmp_data[minHnrowsNxBy2 - 1].im = 0.0;
      }
    }
  } else if (minHnrowsNxBy2 + 2 <= hnRows) {
    k1 = minHnrowsNxBy2 + 2;
    for (minHnrowsNxBy2 = k1; minHnrowsNxBy2 <= hnRows; minHnrowsNxBy2++) {
      ytmp_data[minHnrowsNxBy2 - 1].re = 0.0;
      ytmp_data[minHnrowsNxBy2 - 1].im = 0.0;
    }
  }
  u0 = nfft / 2;
  emxInit_creal_T(&fy, 1);
  e_FFTImplementationCallback_r2b(ytmp, u0, a__1, hsintab, fy);
  fy_data = fy->data;
  emxInit_creal_T(&fv, 1);
  e_FFTImplementationCallback_r2b(wwc, u0, a__1, hsintab, fv);
  fv_data = fv->data;
  emxFree_real_T(&hsintab);
  emxFree_real_T(&a__1);
  minHnrowsNxBy2 = fy->size[0];
  for (k1 = 0; k1 < minHnrowsNxBy2; k1++) {
    a_re = fy_data[k1].re;
    a_im = fv_data[k1].im;
    b_re = fy_data[k1].im;
    b_im = fv_data[k1].re;
    fy_data[k1].re = a_re * b_im - b_re * a_im;
    fy_data[k1].im = a_re * a_im + b_re * b_im;
  }
  e_FFTImplementationCallback_r2b(fy, u0, hcostabinv, hsintabinv, fv);
  fv_data = fv->data;
  emxFree_creal_T(&fy);
  emxFree_real_T(&hsintabinv);
  emxFree_real_T(&hcostabinv);
  if (fv->size[0] > 1) {
    a_re = 1.0 / (double)fv->size[0];
    minHnrowsNxBy2 = fv->size[0];
    for (k1 = 0; k1 < minHnrowsNxBy2; k1++) {
      fv_data[k1].re *= a_re;
      fv_data[k1].im *= a_re;
    }
  }
  u0 = wwc->size[0];
  if ((hnRows <= wwc->size[0]) && (wwc->size[0] > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (minHnrowsNxBy2 = hnRows; minHnrowsNxBy2 <= u0; minHnrowsNxBy2++) {
    a_re = wwc_data[minHnrowsNxBy2 - 1].re;
    a_im = fv_data[minHnrowsNxBy2 - 1].im;
    b_re = wwc_data[minHnrowsNxBy2 - 1].im;
    b_im = fv_data[minHnrowsNxBy2 - 1].re;
    ar = a_re * b_im + b_re * a_im;
    a_re = a_re * a_im - b_re * b_im;
    if (a_re == 0.0) {
      k1 = minHnrowsNxBy2 - hnRows;
      ytmp_data[k1].re = ar / (double)hnRows;
      ytmp_data[k1].im = 0.0;
    } else if (ar == 0.0) {
      k1 = minHnrowsNxBy2 - hnRows;
      ytmp_data[k1].re = 0.0;
      ytmp_data[k1].im = a_re / (double)hnRows;
    } else {
      k1 = minHnrowsNxBy2 - hnRows;
      ytmp_data[k1].re = ar / (double)hnRows;
      ytmp_data[k1].im = a_re / (double)hnRows;
    }
  }
  emxFree_creal_T(&fv);
  for (minHnrowsNxBy2 = 0; minHnrowsNxBy2 < hnRows; minHnrowsNxBy2++) {
    double b_ytmp_re_tmp;
    double ytmp_im_tmp;
    double ytmp_re_tmp;
    k1 = wrapIndex_data[minHnrowsNxBy2];
    a_re = ytmp_data[minHnrowsNxBy2].re;
    a_im = reconVar1_data[minHnrowsNxBy2].im;
    b_re = ytmp_data[minHnrowsNxBy2].im;
    b_im = reconVar1_data[minHnrowsNxBy2].re;
    ar = ytmp_data[k1 - 1].re;
    ytmp_im_tmp = -ytmp_data[k1 - 1].im;
    ytmp_re_tmp = reconVar2_data[minHnrowsNxBy2].im;
    b_ytmp_re_tmp = reconVar2_data[minHnrowsNxBy2].re;
    y_data[minHnrowsNxBy2].re =
        0.5 * ((a_re * b_im - b_re * a_im) +
               (ar * b_ytmp_re_tmp - ytmp_im_tmp * ytmp_re_tmp));
    y_data[minHnrowsNxBy2].im =
        0.5 * ((a_re * a_im + b_re * b_im) +
               (ar * ytmp_re_tmp + ytmp_im_tmp * b_ytmp_re_tmp));
    k1 = hnRows + minHnrowsNxBy2;
    y_data[k1].re = 0.5 * ((a_re * b_ytmp_re_tmp - b_re * ytmp_re_tmp) +
                           (ar * b_im - ytmp_im_tmp * a_im));
    y_data[k1].im = 0.5 * ((a_re * ytmp_re_tmp + b_re * b_ytmp_re_tmp) +
                           (ar * a_im + ytmp_im_tmp * b_im));
  }
  emxFree_creal_T(&reconVar2);
  emxFree_creal_T(&reconVar1);
  emxFree_int32_T(&wrapIndex);
  emxFree_creal_T(&ytmp);
  minHnrowsNxBy2 = y->size[0];
  for (k1 = 0; k1 < minHnrowsNxBy2; k1++) {
    ar = y_data[k1].re;
    a_re = y_data[k1].im;
    if (a_re == 0.0) {
      a_im = ar / 2.0;
      a_re = 0.0;
    } else if (ar == 0.0) {
      a_im = 0.0;
      a_re /= 2.0;
    } else {
      a_im = ar / 2.0;
      a_re /= 2.0;
    }
    y_data[k1].re = a_im;
    y_data[k1].im = a_re;
  }
}

/*
 * Arguments    : int nRows
 *                emxArray_real_T *costab
 *                emxArray_real_T *sintab
 *                emxArray_real_T *sintabinv
 * Return Type  : void
 */
static void e_FFTImplementationCallback_gen(int nRows, emxArray_real_T *costab,
                                            emxArray_real_T *sintab,
                                            emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  double *costab1q_data;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
  int i;
  int k;
  int n;
  int nd2;
  e = 6.2831853071795862 / (double)nRows;
  n = nRows / 2 / 2;
  emxInit_real_T(&costab1q, 2);
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i);
  costab1q_data = costab1q->data;
  costab1q_data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(e * ((double)k + 1.0));
  }
  i = nd2 + 2;
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab1q_data[k] = sin(e * (double)(n - k));
  }
  costab1q_data[n] = 0.0;
  n = costab1q->size[1] - 1;
  nd2 = (costab1q->size[1] - 1) << 1;
  i = costab->size[0] * costab->size[1];
  costab->size[0] = 1;
  emxEnsureCapacity_real_T(costab, i);
  if (nd2 + 1 < 0) {
    rtNonNegativeError(-1.0, &b_emlrtDCI);
  }
  i = costab->size[0] * costab->size[1];
  costab->size[1] = nd2 + 1;
  emxEnsureCapacity_real_T(costab, i);
  costab_data = costab->data;
  i = sintab->size[0] * sintab->size[1];
  sintab->size[0] = 1;
  sintab->size[1] = nd2 + 1;
  emxEnsureCapacity_real_T(sintab, i);
  sintab_data = sintab->data;
  costab_data[0] = 1.0;
  sintab_data[0] = 0.0;
  i = sintabinv->size[0] * sintabinv->size[1];
  sintabinv->size[0] = 1;
  sintabinv->size[1] = nd2 + 1;
  emxEnsureCapacity_real_T(sintabinv, i);
  sintabinv_data = sintabinv->data;
  for (k = 0; k < n; k++) {
    sintabinv_data[k + 1] = costab1q_data[(n - k) - 1];
  }
  i = costab1q->size[1];
  for (k = i; k <= nd2; k++) {
    sintabinv_data[k] = costab1q_data[k - n];
  }
  for (k = 0; k < n; k++) {
    costab_data[k + 1] = costab1q_data[k + 1];
    sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
  }
  for (k = i; k <= nd2; k++) {
    costab_data[k] = -costab1q_data[nd2 - k];
    sintab_data[k] = -costab1q_data[k - n];
  }
  emxFree_real_T(&costab1q);
}

/*
 * Arguments    : const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *costabinv
 *                const emxArray_real_T *sintabinv
 *                emxArray_real_T *hcostab
 *                emxArray_real_T *hsintab
 *                emxArray_real_T *hcostabinv
 *                emxArray_real_T *hsintabinv
 * Return Type  : void
 */
static void e_FFTImplementationCallback_get(
    const emxArray_real_T *costab, const emxArray_real_T *sintab,
    const emxArray_real_T *costabinv, const emxArray_real_T *sintabinv,
    emxArray_real_T *hcostab, emxArray_real_T *hsintab,
    emxArray_real_T *hcostabinv, emxArray_real_T *hsintabinv)
{
  const double *costab_data;
  const double *costabinv_data;
  const double *sintab_data;
  const double *sintabinv_data;
  double *hcostab_data;
  double *hcostabinv_data;
  double *hsintab_data;
  double *hsintabinv_data;
  int hcostab_tmp;
  int hszCostab;
  int i;
  sintabinv_data = sintabinv->data;
  costabinv_data = costabinv->data;
  sintab_data = sintab->data;
  costab_data = costab->data;
  hszCostab = (int)((unsigned int)costab->size[1] >> 1);
  hcostab_tmp = hcostab->size[0] * hcostab->size[1];
  hcostab->size[0] = 1;
  hcostab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hcostab, hcostab_tmp);
  hcostab_data = hcostab->data;
  hcostab_tmp = hsintab->size[0] * hsintab->size[1];
  hsintab->size[0] = 1;
  hsintab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hsintab, hcostab_tmp);
  hsintab_data = hsintab->data;
  hcostab_tmp = hcostabinv->size[0] * hcostabinv->size[1];
  hcostabinv->size[0] = 1;
  hcostabinv->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hcostabinv, hcostab_tmp);
  hcostabinv_data = hcostabinv->data;
  hcostab_tmp = hsintabinv->size[0] * hsintabinv->size[1];
  hsintabinv->size[0] = 1;
  hsintabinv->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hsintabinv, hcostab_tmp);
  hsintabinv_data = hsintabinv->data;
  for (i = 0; i < hszCostab; i++) {
    hcostab_tmp = ((i + 1) << 1) - 2;
    hcostab_data[i] = costab_data[hcostab_tmp];
    hsintab_data[i] = sintab_data[hcostab_tmp];
    hcostabinv_data[i] = costabinv_data[hcostab_tmp];
    hsintabinv_data[i] = sintabinv_data[hcostab_tmp];
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_creal_T *y
 *                int unsigned_nRows
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 * Return Type  : void
 */
static void f_FFTImplementationCallback_doH(const emxArray_real_T *x,
                                            emxArray_creal_T *y,
                                            int unsigned_nRows,
                                            const emxArray_real_T *costab,
                                            const emxArray_real_T *sintab)
{
  static rtDoubleCheckInfo e_emlrtDCI = {
      900,                                            /* lineNo */
      "FFTImplementationCallback/calculate_wrapIndex" /* fName */
  };
  emxArray_creal_T *reconVar1;
  emxArray_creal_T *reconVar2;
  emxArray_int32_T *bitrevIndex;
  emxArray_int32_T *wrapIndex;
  emxArray_real_T *hcostab;
  emxArray_real_T *hsintab;
  creal_T *reconVar1_data;
  creal_T *reconVar2_data;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  const double *x_data;
  double im;
  double re;
  double temp_im;
  double temp_re;
  double twid_im;
  double twid_re;
  double *hcostab_data;
  double *hsintab_data;
  int hszCostab;
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int ihi;
  int k;
  int minXBy2;
  int nRowsD2;
  int nRowsM2;
  int nRows_tmp;
  int *wrapIndex_data;
  boolean_T nxeven;
  sintab_data = sintab->data;
  costab_data = costab->data;
  y_data = y->data;
  x_data = x->data;
  nRows_tmp = unsigned_nRows / 2;
  nRowsM2 = nRows_tmp - 2;
  nRowsD2 = nRows_tmp / 2;
  k = nRowsD2 / 2;
  hszCostab = (int)((unsigned int)costab->size[1] >> 1);
  emxInit_real_T(&hcostab, 2);
  ihi = hcostab->size[0] * hcostab->size[1];
  hcostab->size[0] = 1;
  hcostab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hcostab, ihi);
  hcostab_data = hcostab->data;
  emxInit_real_T(&hsintab, 2);
  ihi = hsintab->size[0] * hsintab->size[1];
  hsintab->size[0] = 1;
  hsintab->size[1] = hszCostab;
  emxEnsureCapacity_real_T(hsintab, ihi);
  hsintab_data = hsintab->data;
  for (i = 0; i < hszCostab; i++) {
    minXBy2 = ((i + 1) << 1) - 2;
    hcostab_data[i] = costab_data[minXBy2];
    hsintab_data[i] = sintab_data[minXBy2];
  }
  emxInit_creal_T(&reconVar1, 1);
  ihi = reconVar1->size[0];
  reconVar1->size[0] = nRows_tmp;
  emxEnsureCapacity_creal_T(reconVar1, ihi);
  reconVar1_data = reconVar1->data;
  emxInit_creal_T(&reconVar2, 1);
  ihi = reconVar2->size[0];
  reconVar2->size[0] = nRows_tmp;
  emxEnsureCapacity_creal_T(reconVar2, ihi);
  reconVar2_data = reconVar2->data;
  for (i = 0; i < nRows_tmp; i++) {
    re = sintab_data[i];
    im = costab_data[i];
    reconVar1_data[i].re = re + 1.0;
    reconVar1_data[i].im = -im;
    reconVar2_data[i].re = 1.0 - re;
    reconVar2_data[i].im = im;
  }
  emxInit_int32_T(&wrapIndex, 2);
  ihi = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[0] = 1;
  emxEnsureCapacity_int32_T(wrapIndex, ihi);
  if (nRows_tmp < 0) {
    rtNonNegativeError(nRows_tmp, &e_emlrtDCI);
  }
  ihi = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[1] = nRows_tmp;
  emxEnsureCapacity_int32_T(wrapIndex, ihi);
  wrapIndex_data = wrapIndex->data;
  for (i = 0; i < nRows_tmp; i++) {
    if (i + 1 != 1) {
      wrapIndex_data[i] = (nRows_tmp - i) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
  }
  emxInit_int32_T(&bitrevIndex, 1);
  minXBy2 = y->size[0];
  if (minXBy2 > nRows_tmp) {
    minXBy2 = nRows_tmp;
  }
  d_FFTImplementationCallback_get(minXBy2 - 1, nRows_tmp, bitrevIndex);
  wrapIndex_data = bitrevIndex->data;
  if ((x->size[0] & 1) == 0) {
    nxeven = true;
    minXBy2 = x->size[0];
  } else if (x->size[0] >= unsigned_nRows) {
    nxeven = true;
    minXBy2 = unsigned_nRows;
  } else {
    nxeven = false;
    minXBy2 = x->size[0] - 1;
  }
  if (minXBy2 > unsigned_nRows) {
    minXBy2 = unsigned_nRows;
  }
  minXBy2 /= 2;
  for (i = 0; i < minXBy2; i++) {
    ihi = i << 1;
    y_data[wrapIndex_data[i] - 1].re = x_data[ihi];
    y_data[wrapIndex_data[i] - 1].im = x_data[ihi + 1];
  }
  if (!nxeven) {
    if (minXBy2 - 1 < 0) {
      hszCostab = 0;
    } else {
      hszCostab = minXBy2 << 1;
    }
    y_data[wrapIndex_data[minXBy2] - 1].re = x_data[hszCostab];
    y_data[wrapIndex_data[minXBy2] - 1].im = 0.0;
  }
  emxFree_int32_T(&bitrevIndex);
  if (nRows_tmp > 1) {
    for (i = 0; i <= nRowsM2; i += 2) {
      re = y_data[i + 1].re;
      im = y_data[i + 1].im;
      temp_re = re;
      temp_im = im;
      twid_re = y_data[i].re;
      twid_im = y_data[i].im;
      re = twid_re - re;
      im = twid_im - im;
      y_data[i + 1].re = re;
      y_data[i + 1].im = im;
      twid_re += temp_re;
      twid_im += temp_im;
      y_data[i].re = twid_re;
      y_data[i].im = twid_im;
    }
  }
  iDelta = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      minXBy2 = i + iDelta;
      temp_re = y_data[minXBy2].re;
      temp_im = y_data[minXBy2].im;
      y_data[minXBy2].re = y_data[i].re - temp_re;
      y_data[minXBy2].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }
    minXBy2 = 1;
    for (hszCostab = k; hszCostab < nRowsD2; hszCostab += k) {
      twid_re = hcostab_data[hszCostab];
      twid_im = hsintab_data[hszCostab];
      i = minXBy2;
      ihi = minXBy2 + iheight;
      while (i < ihi) {
        nRowsM2 = i + iDelta;
        re = y_data[nRowsM2].im;
        im = y_data[nRowsM2].re;
        temp_re = twid_re * im - twid_im * re;
        temp_im = twid_re * re + twid_im * im;
        y_data[nRowsM2].re = y_data[i].re - temp_re;
        y_data[nRowsM2].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += iDelta2;
      }
      minXBy2++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
  emxFree_real_T(&hsintab);
  emxFree_real_T(&hcostab);
  f_FFTImplementationCallback_get(y, reconVar1, reconVar2, wrapIndex,
                                  nRows_tmp);
  emxFree_creal_T(&reconVar2);
  emxFree_creal_T(&reconVar1);
  emxFree_int32_T(&wrapIndex);
}

/*
 * Arguments    : emxArray_creal_T *y
 *                const emxArray_creal_T *reconVar1
 *                const emxArray_creal_T *reconVar2
 *                const emxArray_int32_T *wrapIndex
 *                int hnRows
 * Return Type  : void
 */
static void f_FFTImplementationCallback_get(emxArray_creal_T *y,
                                            const emxArray_creal_T *reconVar1,
                                            const emxArray_creal_T *reconVar2,
                                            const emxArray_int32_T *wrapIndex,
                                            int hnRows)
{
  const creal_T *reconVar1_data;
  const creal_T *reconVar2_data;
  creal_T *y_data;
  double b_temp1_re_tmp;
  double b_temp2_re_tmp;
  double b_y_re_tmp;
  double c_y_re_tmp;
  double d_y_re_tmp;
  double temp1_im_tmp;
  double temp1_re_tmp;
  double temp1_re_tmp_tmp;
  double y_im_tmp;
  double y_re_tmp;
  const int *wrapIndex_data;
  int b_i;
  int i;
  int iterVar;
  wrapIndex_data = wrapIndex->data;
  reconVar2_data = reconVar2->data;
  reconVar1_data = reconVar1->data;
  y_data = y->data;
  iterVar = hnRows / 2;
  temp1_re_tmp_tmp = y_data[0].re;
  temp1_im_tmp = y_data[0].im;
  y_re_tmp = temp1_re_tmp_tmp * reconVar1_data[0].re;
  y_im_tmp = temp1_re_tmp_tmp * reconVar1_data[0].im;
  b_y_re_tmp = temp1_re_tmp_tmp * reconVar2_data[0].re;
  temp1_re_tmp_tmp *= reconVar2_data[0].im;
  y_data[0].re = 0.5 * ((y_re_tmp - temp1_im_tmp * reconVar1_data[0].im) +
                        (b_y_re_tmp - -temp1_im_tmp * reconVar2_data[0].im));
  y_data[0].im =
      0.5 * ((y_im_tmp + temp1_im_tmp * reconVar1_data[0].re) +
             (temp1_re_tmp_tmp + -temp1_im_tmp * reconVar2_data[0].re));
  y_data[hnRows].re =
      0.5 * ((b_y_re_tmp - temp1_im_tmp * reconVar2_data[0].im) +
             (y_re_tmp - -temp1_im_tmp * reconVar1_data[0].im));
  y_data[hnRows].im =
      0.5 * ((temp1_re_tmp_tmp + temp1_im_tmp * reconVar2_data[0].re) +
             (y_im_tmp + -temp1_im_tmp * reconVar1_data[0].re));
  for (i = 2; i <= iterVar; i++) {
    double temp2_im_tmp;
    double temp2_re_tmp;
    int i1;
    temp1_re_tmp = y_data[i - 1].re;
    temp1_im_tmp = y_data[i - 1].im;
    b_i = wrapIndex_data[i - 1];
    temp2_re_tmp = y_data[b_i - 1].re;
    temp2_im_tmp = y_data[b_i - 1].im;
    y_re_tmp = reconVar1_data[i - 1].im;
    b_y_re_tmp = reconVar1_data[i - 1].re;
    c_y_re_tmp = reconVar2_data[i - 1].im;
    d_y_re_tmp = reconVar2_data[i - 1].re;
    y_data[i - 1].re =
        0.5 * ((temp1_re_tmp * b_y_re_tmp - temp1_im_tmp * y_re_tmp) +
               (temp2_re_tmp * d_y_re_tmp - -temp2_im_tmp * c_y_re_tmp));
    y_data[i - 1].im =
        0.5 * ((temp1_re_tmp * y_re_tmp + temp1_im_tmp * b_y_re_tmp) +
               (temp2_re_tmp * c_y_re_tmp + -temp2_im_tmp * d_y_re_tmp));
    i1 = (hnRows + i) - 1;
    y_data[i1].re =
        0.5 * ((temp1_re_tmp * d_y_re_tmp - temp1_im_tmp * c_y_re_tmp) +
               (temp2_re_tmp * b_y_re_tmp - -temp2_im_tmp * y_re_tmp));
    y_data[i1].im =
        0.5 * ((temp1_re_tmp * c_y_re_tmp + temp1_im_tmp * d_y_re_tmp) +
               (temp2_re_tmp * y_re_tmp + -temp2_im_tmp * b_y_re_tmp));
    temp1_re_tmp_tmp = reconVar1_data[b_i - 1].im;
    b_temp2_re_tmp = reconVar1_data[b_i - 1].re;
    b_temp1_re_tmp = reconVar2_data[b_i - 1].im;
    y_im_tmp = reconVar2_data[b_i - 1].re;
    y_data[b_i - 1].re =
        0.5 *
        ((temp2_re_tmp * b_temp2_re_tmp - temp2_im_tmp * temp1_re_tmp_tmp) +
         (temp1_re_tmp * y_im_tmp - -temp1_im_tmp * b_temp1_re_tmp));
    y_data[b_i - 1].im =
        0.5 *
        ((temp2_re_tmp * temp1_re_tmp_tmp + temp2_im_tmp * b_temp2_re_tmp) +
         (temp1_re_tmp * b_temp1_re_tmp + -temp1_im_tmp * y_im_tmp));
    b_i = (b_i + hnRows) - 1;
    y_data[b_i].re =
        0.5 *
        ((temp2_re_tmp * y_im_tmp - temp2_im_tmp * b_temp1_re_tmp) +
         (temp1_re_tmp * b_temp2_re_tmp - -temp1_im_tmp * temp1_re_tmp_tmp));
    y_data[b_i].im =
        0.5 *
        ((temp2_re_tmp * b_temp1_re_tmp + temp2_im_tmp * y_im_tmp) +
         (temp1_re_tmp * temp1_re_tmp_tmp + -temp1_im_tmp * b_temp2_re_tmp));
  }
  if (iterVar != 0) {
    temp1_re_tmp = y_data[iterVar].re;
    temp1_im_tmp = y_data[iterVar].im;
    y_re_tmp = reconVar1_data[iterVar].im;
    b_y_re_tmp = reconVar1_data[iterVar].re;
    c_y_re_tmp = temp1_re_tmp * b_y_re_tmp;
    y_im_tmp = temp1_re_tmp * y_re_tmp;
    d_y_re_tmp = reconVar2_data[iterVar].im;
    b_temp2_re_tmp = reconVar2_data[iterVar].re;
    b_temp1_re_tmp = temp1_re_tmp * b_temp2_re_tmp;
    temp1_re_tmp_tmp = temp1_re_tmp * d_y_re_tmp;
    y_data[iterVar].re = 0.5 * ((c_y_re_tmp - temp1_im_tmp * y_re_tmp) +
                                (b_temp1_re_tmp - -temp1_im_tmp * d_y_re_tmp));
    y_data[iterVar].im =
        0.5 * ((y_im_tmp + temp1_im_tmp * b_y_re_tmp) +
               (temp1_re_tmp_tmp + -temp1_im_tmp * b_temp2_re_tmp));
    b_i = hnRows + iterVar;
    y_data[b_i].re = 0.5 * ((b_temp1_re_tmp - temp1_im_tmp * d_y_re_tmp) +
                            (c_y_re_tmp - -temp1_im_tmp * y_re_tmp));
    y_data[b_i].im = 0.5 * ((temp1_re_tmp_tmp + temp1_im_tmp * b_temp2_re_tmp) +
                            (y_im_tmp + -temp1_im_tmp * b_y_re_tmp));
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_creal_T *y
 *                int nrowsx
 *                int nRows
 *                int nfft
 *                const emxArray_creal_T *wwc
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *costabinv
 *                const emxArray_real_T *sintabinv
 * Return Type  : void
 */
static void g_FFTImplementationCallback_doH(
    const emxArray_real_T *x, emxArray_creal_T *y, int nrowsx, int nRows,
    int nfft, const emxArray_creal_T *wwc, const emxArray_real_T *costab,
    const emxArray_real_T *sintab, const emxArray_real_T *costabinv,
    const emxArray_real_T *sintabinv)
{
  emxArray_creal_T *fv;
  emxArray_creal_T *fy;
  emxArray_creal_T *reconVar1;
  emxArray_creal_T *reconVar2;
  emxArray_creal_T *ytmp;
  emxArray_int32_T *wrapIndex;
  emxArray_real_T *a__1;
  emxArray_real_T *costable;
  emxArray_real_T *hcostabinv;
  emxArray_real_T *hsintab;
  emxArray_real_T *hsintabinv;
  emxArray_real_T *sintable;
  const creal_T *wwc_data;
  creal_T *fv_data;
  creal_T *fy_data;
  creal_T *reconVar1_data;
  creal_T *reconVar2_data;
  creal_T *y_data;
  creal_T *ytmp_data;
  const double *x_data;
  double a_im;
  double a_re;
  double b_im;
  double b_re;
  double *costable_data;
  double *sintable_data;
  int hnRows;
  int k1;
  int minHnrowsNxBy2;
  int u0;
  int *wrapIndex_data;
  boolean_T nxeven;
  wwc_data = wwc->data;
  y_data = y->data;
  x_data = x->data;
  hnRows = nRows / 2;
  if (hnRows < 0) {
    rtNonNegativeError(hnRows, &c_emlrtDCI);
  }
  emxInit_creal_T(&ytmp, 1);
  k1 = ytmp->size[0];
  ytmp->size[0] = hnRows;
  emxEnsureCapacity_creal_T(ytmp, k1);
  ytmp_data = ytmp->data;
  if (hnRows > nrowsx) {
    k1 = ytmp->size[0];
    ytmp->size[0] = hnRows;
    emxEnsureCapacity_creal_T(ytmp, k1);
    ytmp_data = ytmp->data;
    for (k1 = 0; k1 < hnRows; k1++) {
      ytmp_data[k1].re = 0.0;
      ytmp_data[k1].im = 0.0;
    }
  }
  if ((x->size[0] & 1) == 0) {
    nxeven = true;
    u0 = x->size[0];
  } else if (x->size[0] >= nRows) {
    nxeven = true;
    u0 = nRows;
  } else {
    nxeven = false;
    u0 = x->size[0] - 1;
  }
  emxInit_real_T(&a__1, 2);
  emxInit_real_T(&costable, 2);
  emxInit_real_T(&sintable, 2);
  e_FFTImplementationCallback_gen(nRows << 1, costable, sintable, a__1);
  sintable_data = sintable->data;
  costable_data = costable->data;
  emxInit_real_T(&hsintab, 2);
  emxInit_real_T(&hcostabinv, 2);
  emxInit_real_T(&hsintabinv, 2);
  e_FFTImplementationCallback_get(costab, sintab, costabinv, sintabinv, a__1,
                                  hsintab, hcostabinv, hsintabinv);
  emxInit_creal_T(&reconVar1, 1);
  k1 = reconVar1->size[0];
  reconVar1->size[0] = hnRows;
  emxEnsureCapacity_creal_T(reconVar1, k1);
  reconVar1_data = reconVar1->data;
  emxInit_creal_T(&reconVar2, 1);
  k1 = reconVar2->size[0];
  reconVar2->size[0] = hnRows;
  emxEnsureCapacity_creal_T(reconVar2, k1);
  reconVar2_data = reconVar2->data;
  for (minHnrowsNxBy2 = 0; minHnrowsNxBy2 < hnRows; minHnrowsNxBy2++) {
    k1 = minHnrowsNxBy2 << 1;
    a_re = sintable_data[k1];
    a_im = costable_data[k1];
    reconVar1_data[minHnrowsNxBy2].re = a_re + 1.0;
    reconVar1_data[minHnrowsNxBy2].im = -a_im;
    reconVar2_data[minHnrowsNxBy2].re = 1.0 - a_re;
    reconVar2_data[minHnrowsNxBy2].im = a_im;
  }
  emxFree_real_T(&sintable);
  emxFree_real_T(&costable);
  emxInit_int32_T(&wrapIndex, 2);
  k1 = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[0] = 1;
  emxEnsureCapacity_int32_T(wrapIndex, k1);
  k1 = wrapIndex->size[0] * wrapIndex->size[1];
  wrapIndex->size[1] = hnRows;
  emxEnsureCapacity_int32_T(wrapIndex, k1);
  wrapIndex_data = wrapIndex->data;
  for (minHnrowsNxBy2 = 0; minHnrowsNxBy2 < hnRows; minHnrowsNxBy2++) {
    if (minHnrowsNxBy2 + 1 != 1) {
      wrapIndex_data[minHnrowsNxBy2] = (hnRows - minHnrowsNxBy2) + 1;
    } else {
      wrapIndex_data[0] = 1;
    }
  }
  if (u0 > nRows) {
    u0 = nRows;
  }
  minHnrowsNxBy2 = u0 / 2 - 1;
  for (k1 = 0; k1 <= minHnrowsNxBy2; k1++) {
    u0 = (hnRows + k1) - 1;
    a_re = wwc_data[u0].re;
    a_im = wwc_data[u0].im;
    u0 = k1 << 1;
    b_re = x_data[u0];
    b_im = x_data[u0 + 1];
    ytmp_data[k1].re = a_re * b_re + a_im * b_im;
    ytmp_data[k1].im = a_re * b_im - a_im * b_re;
  }
  if (!nxeven) {
    u0 = hnRows + minHnrowsNxBy2;
    a_re = wwc_data[u0].re;
    a_im = wwc_data[u0].im;
    if (minHnrowsNxBy2 < 0) {
      u0 = 0;
    } else {
      u0 = (minHnrowsNxBy2 + 1) << 1;
    }
    b_re = x_data[u0];
    ytmp_data[minHnrowsNxBy2 + 1].re = a_re * b_re + a_im * 0.0;
    ytmp_data[minHnrowsNxBy2 + 1].im = a_re * 0.0 - a_im * b_re;
    if (minHnrowsNxBy2 + 3 <= hnRows) {
      k1 = minHnrowsNxBy2 + 3;
      for (minHnrowsNxBy2 = k1; minHnrowsNxBy2 <= hnRows; minHnrowsNxBy2++) {
        ytmp_data[minHnrowsNxBy2 - 1].re = 0.0;
        ytmp_data[minHnrowsNxBy2 - 1].im = 0.0;
      }
    }
  } else if (minHnrowsNxBy2 + 2 <= hnRows) {
    k1 = minHnrowsNxBy2 + 2;
    for (minHnrowsNxBy2 = k1; minHnrowsNxBy2 <= hnRows; minHnrowsNxBy2++) {
      ytmp_data[minHnrowsNxBy2 - 1].re = 0.0;
      ytmp_data[minHnrowsNxBy2 - 1].im = 0.0;
    }
  }
  u0 = nfft / 2;
  emxInit_creal_T(&fy, 1);
  e_FFTImplementationCallback_r2b(ytmp, u0, a__1, hsintab, fy);
  fy_data = fy->data;
  emxInit_creal_T(&fv, 1);
  e_FFTImplementationCallback_r2b(wwc, u0, a__1, hsintab, fv);
  fv_data = fv->data;
  emxFree_real_T(&hsintab);
  emxFree_real_T(&a__1);
  minHnrowsNxBy2 = fy->size[0];
  for (k1 = 0; k1 < minHnrowsNxBy2; k1++) {
    a_re = fy_data[k1].re;
    a_im = fv_data[k1].im;
    b_re = fy_data[k1].im;
    b_im = fv_data[k1].re;
    fy_data[k1].re = a_re * b_im - b_re * a_im;
    fy_data[k1].im = a_re * a_im + b_re * b_im;
  }
  e_FFTImplementationCallback_r2b(fy, u0, hcostabinv, hsintabinv, fv);
  fv_data = fv->data;
  emxFree_creal_T(&fy);
  emxFree_real_T(&hsintabinv);
  emxFree_real_T(&hcostabinv);
  if (fv->size[0] > 1) {
    a_re = 1.0 / (double)fv->size[0];
    minHnrowsNxBy2 = fv->size[0];
    for (k1 = 0; k1 < minHnrowsNxBy2; k1++) {
      fv_data[k1].re *= a_re;
      fv_data[k1].im *= a_re;
    }
  }
  u0 = wwc->size[0];
  if ((hnRows <= wwc->size[0]) && (wwc->size[0] > 2147483646)) {
    check_forloop_overflow_error();
  }
  for (minHnrowsNxBy2 = hnRows; minHnrowsNxBy2 <= u0; minHnrowsNxBy2++) {
    a_re = wwc_data[minHnrowsNxBy2 - 1].re;
    a_im = fv_data[minHnrowsNxBy2 - 1].im;
    b_re = wwc_data[minHnrowsNxBy2 - 1].im;
    b_im = fv_data[minHnrowsNxBy2 - 1].re;
    k1 = minHnrowsNxBy2 - hnRows;
    ytmp_data[k1].re = a_re * b_im + b_re * a_im;
    ytmp_data[k1].im = a_re * a_im - b_re * b_im;
  }
  emxFree_creal_T(&fv);
  for (minHnrowsNxBy2 = 0; minHnrowsNxBy2 < hnRows; minHnrowsNxBy2++) {
    double b_ytmp_re_tmp;
    double c_ytmp_re_tmp;
    double ytmp_im_tmp;
    double ytmp_re_tmp;
    k1 = wrapIndex_data[minHnrowsNxBy2];
    a_re = ytmp_data[minHnrowsNxBy2].re;
    a_im = reconVar1_data[minHnrowsNxBy2].im;
    b_re = ytmp_data[minHnrowsNxBy2].im;
    b_im = reconVar1_data[minHnrowsNxBy2].re;
    ytmp_re_tmp = ytmp_data[k1 - 1].re;
    ytmp_im_tmp = -ytmp_data[k1 - 1].im;
    b_ytmp_re_tmp = reconVar2_data[minHnrowsNxBy2].im;
    c_ytmp_re_tmp = reconVar2_data[minHnrowsNxBy2].re;
    y_data[minHnrowsNxBy2].re =
        0.5 * ((a_re * b_im - b_re * a_im) +
               (ytmp_re_tmp * c_ytmp_re_tmp - ytmp_im_tmp * b_ytmp_re_tmp));
    y_data[minHnrowsNxBy2].im =
        0.5 * ((a_re * a_im + b_re * b_im) +
               (ytmp_re_tmp * b_ytmp_re_tmp + ytmp_im_tmp * c_ytmp_re_tmp));
    k1 = hnRows + minHnrowsNxBy2;
    y_data[k1].re = 0.5 * ((a_re * c_ytmp_re_tmp - b_re * b_ytmp_re_tmp) +
                           (ytmp_re_tmp * b_im - ytmp_im_tmp * a_im));
    y_data[k1].im = 0.5 * ((a_re * b_ytmp_re_tmp + b_re * c_ytmp_re_tmp) +
                           (ytmp_re_tmp * a_im + ytmp_im_tmp * b_im));
  }
  emxFree_creal_T(&reconVar2);
  emxFree_creal_T(&reconVar1);
  emxFree_int32_T(&wrapIndex);
  emxFree_creal_T(&ytmp);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int n2blue
 *                int nfft
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *sintabinv
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void c_FFTImplementationCallback_dob(const emxArray_real_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *fv;
  emxArray_creal_T *fy;
  emxArray_creal_T *r;
  emxArray_creal_T *wwc;
  creal_T *fv_data;
  creal_T *fy_data;
  creal_T *r1;
  creal_T *wwc_data;
  creal_T *y_data;
  const double *x_data;
  double nt_im;
  int b_y;
  int i;
  int k;
  int nChan_tmp;
  int nInt2;
  int nInt2m1;
  int rt;
  boolean_T ishalflength;
  x_data = x->data;
  nChan_tmp = x->size[1];
  emxInit_creal_T(&wwc, 1);
  if ((nfft != 1) && ((nfft & 1) == 0)) {
    int nRows;
    nRows = nfft / 2;
    nInt2m1 = (nRows + nRows) - 1;
    if (nInt2m1 < 0) {
      rtNonNegativeError(nInt2m1, &d_emlrtDCI);
    }
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, i);
    wwc_data = wwc->data;
    rt = 0;
    wwc_data[nRows - 1].re = 1.0;
    wwc_data[nRows - 1].im = 0.0;
    nInt2 = nRows << 1;
    for (k = 0; k <= nRows - 2; k++) {
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }
      nt_im = -3.1415926535897931 * (double)rt / (double)nRows;
      i = (nRows - k) - 2;
      wwc_data[i].re = cos(nt_im);
      wwc_data[i].im = -sin(nt_im);
    }
    i = nInt2m1 - 1;
    for (k = i; k >= nRows; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  } else {
    nInt2m1 = (nfft + nfft) - 1;
    if (nInt2m1 < 0) {
      rtNonNegativeError(nInt2m1, &d_emlrtDCI);
    }
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, i);
    wwc_data = wwc->data;
    rt = 0;
    wwc_data[nfft - 1].re = 1.0;
    wwc_data[nfft - 1].im = 0.0;
    nInt2 = nfft << 1;
    if (nfft - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k <= nfft - 2; k++) {
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }
      nt_im = -3.1415926535897931 * (double)rt / (double)nfft;
      i = (nfft - k) - 2;
      wwc_data[i].re = cos(nt_im);
      wwc_data[i].im = -sin(nt_im);
    }
    i = nInt2m1 - 1;
    for (k = i; k >= nfft; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  }
  if (nfft < 0) {
    rtNonNegativeError(nfft, &c_emlrtDCI);
  }
  i = y->size[0] * y->size[1];
  y->size[0] = nfft;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (nfft > x->size[0]) {
    i = y->size[0] * y->size[1];
    y->size[0] = nfft;
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    b_y = nfft * x->size[1];
    for (i = 0; i < b_y; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  if (x->size[1] > 2147483646) {
    check_forloop_overflow_error();
  }
  if (x->size[1] - 1 >= 0) {
    if ((n2blue != 1) && ((nfft & 1) == 0)) {
      ishalflength = true;
    } else {
      ishalflength = false;
    }
  }
  emxInit_creal_T(&r, 1);
  emxInit_creal_T(&fy, 1);
  emxInit_creal_T(&fv, 1);
  for (nInt2 = 0; nInt2 < nChan_tmp; nInt2++) {
    nInt2m1 = nInt2 * x->size[0];
    i = r->size[0];
    r->size[0] = nfft;
    emxEnsureCapacity_creal_T(r, i);
    r1 = r->data;
    if (nfft > x->size[0]) {
      i = r->size[0];
      r->size[0] = nfft;
      emxEnsureCapacity_creal_T(r, i);
      r1 = r->data;
      for (i = 0; i < nfft; i++) {
        r1[i].re = 0.0;
        r1[i].im = 0.0;
      }
    }
    if (ishalflength) {
      d_FFTImplementationCallback_doH(x, nInt2m1, r, x->size[0], nfft, n2blue,
                                      wwc, costab, sintab, costab, sintabinv);
      r1 = r->data;
    } else {
      double b_re_tmp;
      double c_re_tmp;
      double re_tmp;
      rt = x->size[0];
      if (nfft <= rt) {
        rt = nfft;
      }
      if (rt > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 0; k < rt; k++) {
        b_y = (nfft + k) - 1;
        nt_im = x_data[nInt2m1 + k];
        r1[k].re = wwc_data[b_y].re * nt_im;
        r1[k].im = wwc_data[b_y].im * -nt_im;
      }
      b_y = rt + 1;
      if ((rt + 1 <= nfft) && (nfft > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (k = b_y; k <= nfft; k++) {
        r1[k - 1].re = 0.0;
        r1[k - 1].im = 0.0;
      }
      e_FFTImplementationCallback_r2b(r, n2blue, costab, sintab, fy);
      fy_data = fy->data;
      e_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, fv);
      fv_data = fv->data;
      b_y = fy->size[0];
      for (i = 0; i < b_y; i++) {
        nt_im = fy_data[i].re;
        re_tmp = fv_data[i].im;
        b_re_tmp = fy_data[i].im;
        c_re_tmp = fv_data[i].re;
        fy_data[i].re = nt_im * c_re_tmp - b_re_tmp * re_tmp;
        fy_data[i].im = nt_im * re_tmp + b_re_tmp * c_re_tmp;
      }
      e_FFTImplementationCallback_r2b(fy, n2blue, costab, sintabinv, fv);
      fv_data = fv->data;
      if (fv->size[0] > 1) {
        nt_im = 1.0 / (double)fv->size[0];
        b_y = fv->size[0];
        for (i = 0; i < b_y; i++) {
          fv_data[i].re *= nt_im;
          fv_data[i].im *= nt_im;
        }
      }
      b_y = wwc->size[0];
      if ((nfft <= wwc->size[0]) && (wwc->size[0] > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (k = nfft; k <= b_y; k++) {
        nt_im = wwc_data[k - 1].re;
        re_tmp = fv_data[k - 1].im;
        b_re_tmp = wwc_data[k - 1].im;
        c_re_tmp = fv_data[k - 1].re;
        i = k - nfft;
        r1[i].re = nt_im * c_re_tmp + b_re_tmp * re_tmp;
        r1[i].im = nt_im * re_tmp - b_re_tmp * c_re_tmp;
      }
    }
    b_y = y->size[0];
    for (i = 0; i < b_y; i++) {
      y_data[i + y->size[0] * nInt2] = r1[i];
    }
  }
  emxFree_creal_T(&fv);
  emxFree_creal_T(&fy);
  emxFree_creal_T(&r);
  emxFree_creal_T(&wwc);
}

/*
 * Arguments    : int nRows
 *                boolean_T useRadix2
 *                emxArray_real_T *costab
 *                emxArray_real_T *sintab
 *                emxArray_real_T *sintabinv
 * Return Type  : void
 */
void c_FFTImplementationCallback_gen(int nRows, boolean_T useRadix2,
                                     emxArray_real_T *costab,
                                     emxArray_real_T *sintab,
                                     emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  double *costab1q_data;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
  int i;
  int i1;
  int k;
  int n;
  int nd2;
  e = 6.2831853071795862 / (double)nRows;
  n = nRows / 2 / 2;
  emxInit_real_T(&costab1q, 2);
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  emxEnsureCapacity_real_T(costab1q, i);
  if (n + 1 < 0) {
    rtNonNegativeError((double)n + 1.0, &emlrtDCI);
  }
  i = n + 1;
  i1 = costab1q->size[0] * costab1q->size[1];
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i1);
  costab1q_data = costab1q->data;
  costab1q_data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(e * ((double)k + 1.0));
  }
  i1 = nd2 + 2;
  nd2 = n - 1;
  for (k = i1; k <= nd2; k++) {
    costab1q_data[k] = sin(e * (double)(n - k));
  }
  costab1q_data[n] = 0.0;
  if (!useRadix2) {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i1 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    emxEnsureCapacity_real_T(costab, i1);
    if (nd2 + 1 < 0) {
      rtNonNegativeError(-1.0, &b_emlrtDCI);
    }
    i1 = costab->size[0] * costab->size[1];
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i1);
    costab_data = costab->data;
    i1 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i1);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    i1 = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintabinv, i1);
    sintabinv_data = sintabinv->data;
    for (k = 0; k < n; k++) {
      sintabinv_data[k + 1] = costab1q_data[(n - k) - 1];
    }
    for (k = i; k <= nd2; k++) {
      sintabinv_data[k] = costab1q_data[k - n];
    }
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    for (k = i; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i1 = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    emxEnsureCapacity_real_T(costab, i1);
    if (nd2 + 1 < 0) {
      rtNonNegativeError(-1.0, &b_emlrtDCI);
    }
    i1 = costab->size[0] * costab->size[1];
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i1);
    costab_data = costab->data;
    i1 = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i1);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    for (k = i; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }
  emxFree_real_T(&costab1q);
}

/*
 * Arguments    : int nfft
 *                boolean_T useRadix2
 *                int *nRows
 * Return Type  : int
 */
int c_FFTImplementationCallback_get(int nfft, boolean_T useRadix2, int *nRows)
{
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      792,                                       /* lineNo */
      "FFTImplementationCallback/get_algo_sizes" /* fName */
  };
  int n2blue;
  n2blue = 1;
  if (useRadix2) {
    *nRows = nfft;
  } else {
    int n;
    if (nfft > 0) {
      int pmax;
      n = (nfft + nfft) - 1;
      pmax = 31;
      if (n <= 1) {
        pmax = 0;
      } else {
        int pmin;
        boolean_T exitg1;
        pmin = 0;
        exitg1 = false;
        while ((!exitg1) && (pmax - pmin > 1)) {
          int k;
          int pow2p;
          k = (pmin + pmax) >> 1;
          pow2p = 1 << k;
          if (pow2p == n) {
            pmax = k;
            exitg1 = true;
          } else if (pow2p > n) {
            pmax = k;
          } else {
            pmin = k;
          }
        }
      }
      n2blue = 1 << pmax;
    }
    n = nfft << 2;
    if (n < 1) {
      n = 1;
    }
    if (n2blue > n) {
      p_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
    }
    *nRows = n2blue;
  }
  return n2blue;
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int n1_unsigned
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void c_FFTImplementationCallback_r2b(const emxArray_real_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *r;
  creal_T *r1;
  creal_T *y_data;
  int chan;
  int i;
  int loop_ub;
  int nChan_tmp;
  nChan_tmp = x->size[1];
  if (n1_unsigned < 0) {
    rtNonNegativeError(n1_unsigned, &c_emlrtDCI);
  }
  i = y->size[0] * y->size[1];
  y->size[0] = n1_unsigned;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    i = y->size[0] * y->size[1];
    y->size[0] = n1_unsigned;
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    loop_ub = n1_unsigned * x->size[1];
    for (i = 0; i < loop_ub; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  if (x->size[1] > 2147483646) {
    check_forloop_overflow_error();
  }
  emxInit_creal_T(&r, 1);
  for (chan = 0; chan < nChan_tmp; chan++) {
    d_FFTImplementationCallback_r2b(x, chan * x->size[0], n1_unsigned, costab,
                                    sintab, r);
    r1 = r->data;
    loop_ub = y->size[0];
    for (i = 0; i < loop_ub; i++) {
      y_data[i + y->size[0] * chan] = r1[i];
    }
  }
  emxFree_creal_T(&r);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int n2blue
 *                int nfft
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *sintabinv
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void d_FFTImplementationCallback_dob(const emxArray_real_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *fv;
  emxArray_creal_T *fy;
  emxArray_creal_T *r;
  emxArray_creal_T *wwc;
  creal_T *fv_data;
  creal_T *fy_data;
  creal_T *r1;
  creal_T *wwc_data;
  creal_T *y_data;
  const double *x_data;
  double nt_im;
  int b_y;
  int i;
  int k;
  int nChan_tmp;
  int nInt2;
  int nInt2m1;
  int rt;
  boolean_T ishalflength;
  x_data = x->data;
  nChan_tmp = x->size[1];
  emxInit_creal_T(&wwc, 1);
  if ((nfft != 1) && ((nfft & 1) == 0)) {
    int nRows;
    nRows = nfft / 2;
    nInt2m1 = (nRows + nRows) - 1;
    if (nInt2m1 < 0) {
      rtNonNegativeError(nInt2m1, &d_emlrtDCI);
    }
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, i);
    wwc_data = wwc->data;
    rt = 0;
    wwc_data[nRows - 1].re = 1.0;
    wwc_data[nRows - 1].im = 0.0;
    nInt2 = nRows << 1;
    for (k = 0; k <= nRows - 2; k++) {
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }
      nt_im = 3.1415926535897931 * (double)rt / (double)nRows;
      i = (nRows - k) - 2;
      wwc_data[i].re = cos(nt_im);
      wwc_data[i].im = -sin(nt_im);
    }
    i = nInt2m1 - 1;
    for (k = i; k >= nRows; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  } else {
    nInt2m1 = (nfft + nfft) - 1;
    if (nInt2m1 < 0) {
      rtNonNegativeError(nInt2m1, &d_emlrtDCI);
    }
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, i);
    wwc_data = wwc->data;
    rt = 0;
    wwc_data[nfft - 1].re = 1.0;
    wwc_data[nfft - 1].im = 0.0;
    nInt2 = nfft << 1;
    if (nfft - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k <= nfft - 2; k++) {
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }
      nt_im = 3.1415926535897931 * (double)rt / (double)nfft;
      i = (nfft - k) - 2;
      wwc_data[i].re = cos(nt_im);
      wwc_data[i].im = -sin(nt_im);
    }
    i = nInt2m1 - 1;
    for (k = i; k >= nfft; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  }
  if (nfft < 0) {
    rtNonNegativeError(nfft, &c_emlrtDCI);
  }
  i = y->size[0] * y->size[1];
  y->size[0] = nfft;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (nfft > x->size[0]) {
    i = y->size[0] * y->size[1];
    y->size[0] = nfft;
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    b_y = nfft * x->size[1];
    for (i = 0; i < b_y; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  if (x->size[1] > 2147483646) {
    check_forloop_overflow_error();
  }
  if (x->size[1] - 1 >= 0) {
    if ((n2blue != 1) && ((nfft & 1) == 0)) {
      ishalflength = true;
    } else {
      ishalflength = false;
    }
  }
  emxInit_creal_T(&r, 1);
  emxInit_creal_T(&fy, 1);
  emxInit_creal_T(&fv, 1);
  for (nInt2 = 0; nInt2 < nChan_tmp; nInt2++) {
    nInt2m1 = nInt2 * x->size[0];
    i = r->size[0];
    r->size[0] = nfft;
    emxEnsureCapacity_creal_T(r, i);
    r1 = r->data;
    if (nfft > x->size[0]) {
      i = r->size[0];
      r->size[0] = nfft;
      emxEnsureCapacity_creal_T(r, i);
      r1 = r->data;
      for (i = 0; i < nfft; i++) {
        r1[i].re = 0.0;
        r1[i].im = 0.0;
      }
    }
    if (ishalflength) {
      e_FFTImplementationCallback_doH(x, nInt2m1, r, x->size[0], nfft, n2blue,
                                      wwc, costab, sintab, costab, sintabinv);
      r1 = r->data;
    } else {
      double b_re_tmp;
      double c_re_tmp;
      double re_tmp;
      rt = x->size[0];
      if (nfft <= rt) {
        rt = nfft;
      }
      if (rt > 2147483646) {
        check_forloop_overflow_error();
      }
      for (k = 0; k < rt; k++) {
        b_y = (nfft + k) - 1;
        nt_im = x_data[nInt2m1 + k];
        r1[k].re = wwc_data[b_y].re * nt_im;
        r1[k].im = wwc_data[b_y].im * -nt_im;
      }
      b_y = rt + 1;
      if ((rt + 1 <= nfft) && (nfft > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (k = b_y; k <= nfft; k++) {
        r1[k - 1].re = 0.0;
        r1[k - 1].im = 0.0;
      }
      e_FFTImplementationCallback_r2b(r, n2blue, costab, sintab, fy);
      fy_data = fy->data;
      e_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, fv);
      fv_data = fv->data;
      b_y = fy->size[0];
      for (i = 0; i < b_y; i++) {
        nt_im = fy_data[i].re;
        re_tmp = fv_data[i].im;
        b_re_tmp = fy_data[i].im;
        c_re_tmp = fv_data[i].re;
        fy_data[i].re = nt_im * c_re_tmp - b_re_tmp * re_tmp;
        fy_data[i].im = nt_im * re_tmp + b_re_tmp * c_re_tmp;
      }
      e_FFTImplementationCallback_r2b(fy, n2blue, costab, sintabinv, fv);
      fv_data = fv->data;
      if (fv->size[0] > 1) {
        nt_im = 1.0 / (double)fv->size[0];
        b_y = fv->size[0];
        for (i = 0; i < b_y; i++) {
          fv_data[i].re *= nt_im;
          fv_data[i].im *= nt_im;
        }
      }
      b_y = wwc->size[0];
      if ((nfft <= wwc->size[0]) && (wwc->size[0] > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (k = nfft; k <= b_y; k++) {
        double ar;
        nt_im = wwc_data[k - 1].re;
        re_tmp = fv_data[k - 1].im;
        b_re_tmp = wwc_data[k - 1].im;
        c_re_tmp = fv_data[k - 1].re;
        ar = nt_im * c_re_tmp + b_re_tmp * re_tmp;
        nt_im = nt_im * re_tmp - b_re_tmp * c_re_tmp;
        if (nt_im == 0.0) {
          i = k - nfft;
          r1[i].re = ar / (double)nfft;
          r1[i].im = 0.0;
        } else if (ar == 0.0) {
          i = k - nfft;
          r1[i].re = 0.0;
          r1[i].im = nt_im / (double)nfft;
        } else {
          i = k - nfft;
          r1[i].re = ar / (double)nfft;
          r1[i].im = nt_im / (double)nfft;
        }
      }
    }
    b_y = y->size[0];
    for (i = 0; i < b_y; i++) {
      y_data[i + y->size[0] * nInt2] = r1[i];
    }
  }
  emxFree_creal_T(&fv);
  emxFree_creal_T(&fy);
  emxFree_creal_T(&r);
  emxFree_creal_T(&wwc);
}

/*
 * Arguments    : int nRows
 *                boolean_T useRadix2
 *                emxArray_real_T *costab
 *                emxArray_real_T *sintab
 *                emxArray_real_T *sintabinv
 * Return Type  : void
 */
void d_FFTImplementationCallback_gen(int nRows, boolean_T useRadix2,
                                     emxArray_real_T *costab,
                                     emxArray_real_T *sintab,
                                     emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  double *costab1q_data;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
  int i;
  int k;
  int n;
  int nd2;
  e = 6.2831853071795862 / (double)nRows;
  n = nRows / 2 / 2;
  emxInit_real_T(&costab1q, 2);
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i);
  costab1q_data = costab1q->data;
  costab1q_data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(e * ((double)k + 1.0));
  }
  i = nd2 + 2;
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab1q_data[k] = sin(e * (double)(n - k));
  }
  costab1q_data[n] = 0.0;
  if (!useRadix2) {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    emxEnsureCapacity_real_T(costab, i);
    if (nd2 + 1 < 0) {
      rtNonNegativeError(-1.0, &b_emlrtDCI);
    }
    i = costab->size[0] * costab->size[1];
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    costab_data = costab->data;
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    i = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintabinv, i);
    sintabinv_data = sintabinv->data;
    for (k = 0; k < n; k++) {
      sintabinv_data[k + 1] = costab1q_data[(n - k) - 1];
    }
    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      sintabinv_data[k] = costab1q_data[k - n];
    }
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    for (k = i; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    costab_data = costab->data;
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = costab1q_data[(n - k) - 1];
    }
    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = costab1q_data[k - n];
    }
    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }
  emxFree_real_T(&costab1q);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int n2blue
 *                int nfft
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                const emxArray_real_T *sintabinv
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void e_FFTImplementationCallback_dob(const emxArray_real_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *fv;
  emxArray_creal_T *fy;
  emxArray_creal_T *wwc;
  creal_T *fv_data;
  creal_T *fy_data;
  creal_T *wwc_data;
  creal_T *y_data;
  const double *x_data;
  double nt_im;
  int b_y;
  int i;
  int k;
  int nInt2m1;
  x_data = x->data;
  emxInit_creal_T(&wwc, 1);
  if ((nfft != 1) && ((nfft & 1) == 0)) {
    int nInt2;
    int nRows;
    int rt;
    nRows = nfft / 2;
    nInt2m1 = (nRows + nRows) - 1;
    if (nInt2m1 < 0) {
      rtNonNegativeError(nInt2m1, &d_emlrtDCI);
    }
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, i);
    wwc_data = wwc->data;
    rt = 0;
    wwc_data[nRows - 1].re = 1.0;
    wwc_data[nRows - 1].im = 0.0;
    nInt2 = nRows << 1;
    for (k = 0; k <= nRows - 2; k++) {
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }
      nt_im = -3.1415926535897931 * (double)rt / (double)nRows;
      i = (nRows - k) - 2;
      wwc_data[i].re = cos(nt_im);
      wwc_data[i].im = -sin(nt_im);
    }
    i = nInt2m1 - 1;
    for (k = i; k >= nRows; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  } else {
    int nInt2;
    int rt;
    nInt2m1 = (nfft + nfft) - 1;
    if (nInt2m1 < 0) {
      rtNonNegativeError(nInt2m1, &d_emlrtDCI);
    }
    i = wwc->size[0];
    wwc->size[0] = nInt2m1;
    emxEnsureCapacity_creal_T(wwc, i);
    wwc_data = wwc->data;
    rt = 0;
    wwc_data[nfft - 1].re = 1.0;
    wwc_data[nfft - 1].im = 0.0;
    nInt2 = nfft << 1;
    if (nfft - 1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k <= nfft - 2; k++) {
      b_y = ((k + 1) << 1) - 1;
      if (nInt2 - rt <= b_y) {
        rt += b_y - nInt2;
      } else {
        rt += b_y;
      }
      nt_im = -3.1415926535897931 * (double)rt / (double)nfft;
      i = (nfft - k) - 2;
      wwc_data[i].re = cos(nt_im);
      wwc_data[i].im = -sin(nt_im);
    }
    i = nInt2m1 - 1;
    for (k = i; k >= nfft; k--) {
      wwc_data[k] = wwc_data[(nInt2m1 - k) - 1];
    }
  }
  if (nfft < 0) {
    rtNonNegativeError(nfft, &c_emlrtDCI);
  }
  i = y->size[0];
  y->size[0] = nfft;
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (nfft > x->size[0]) {
    i = y->size[0];
    y->size[0] = nfft;
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    for (i = 0; i < nfft; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  emxInit_creal_T(&fy, 1);
  emxInit_creal_T(&fv, 1);
  if ((n2blue != 1) && ((nfft & 1) == 0)) {
    g_FFTImplementationCallback_doH(x, y, x->size[0], nfft, n2blue, wwc, costab,
                                    sintab, costab, sintabinv);
  } else {
    double b_re_tmp;
    double c_re_tmp;
    double re_tmp;
    nInt2m1 = x->size[0];
    if (nfft <= nInt2m1) {
      nInt2m1 = nfft;
    }
    if (nInt2m1 > 2147483646) {
      check_forloop_overflow_error();
    }
    for (k = 0; k < nInt2m1; k++) {
      b_y = (nfft + k) - 1;
      y_data[k].re = wwc_data[b_y].re * x_data[k];
      y_data[k].im = wwc_data[b_y].im * -x_data[k];
    }
    b_y = nInt2m1 + 1;
    if ((nInt2m1 + 1 <= nfft) && (nfft > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (k = b_y; k <= nfft; k++) {
      y_data[k - 1].re = 0.0;
      y_data[k - 1].im = 0.0;
    }
    e_FFTImplementationCallback_r2b(y, n2blue, costab, sintab, fy);
    fy_data = fy->data;
    e_FFTImplementationCallback_r2b(wwc, n2blue, costab, sintab, fv);
    fv_data = fv->data;
    b_y = fy->size[0];
    for (i = 0; i < b_y; i++) {
      nt_im = fy_data[i].re;
      re_tmp = fv_data[i].im;
      b_re_tmp = fy_data[i].im;
      c_re_tmp = fv_data[i].re;
      fy_data[i].re = nt_im * c_re_tmp - b_re_tmp * re_tmp;
      fy_data[i].im = nt_im * re_tmp + b_re_tmp * c_re_tmp;
    }
    e_FFTImplementationCallback_r2b(fy, n2blue, costab, sintabinv, fv);
    fv_data = fv->data;
    if (fv->size[0] > 1) {
      nt_im = 1.0 / (double)fv->size[0];
      b_y = fv->size[0];
      for (i = 0; i < b_y; i++) {
        fv_data[i].re *= nt_im;
        fv_data[i].im *= nt_im;
      }
    }
    b_y = wwc->size[0];
    if ((nfft <= wwc->size[0]) && (wwc->size[0] > 2147483646)) {
      check_forloop_overflow_error();
    }
    for (k = nfft; k <= b_y; k++) {
      nt_im = wwc_data[k - 1].re;
      re_tmp = fv_data[k - 1].im;
      b_re_tmp = wwc_data[k - 1].im;
      c_re_tmp = fv_data[k - 1].re;
      i = k - nfft;
      y_data[i].re = nt_im * c_re_tmp + b_re_tmp * re_tmp;
      y_data[i].im = nt_im * re_tmp - b_re_tmp * c_re_tmp;
    }
  }
  emxFree_creal_T(&fv);
  emxFree_creal_T(&fy);
  emxFree_creal_T(&wwc);
}

/*
 * Arguments    : const emxArray_creal_T *x
 *                int unsigned_nRows
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void e_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                     int unsigned_nRows,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y)
{
  const creal_T *x_data;
  creal_T *y_data;
  const double *costab_data;
  const double *sintab_data;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_re;
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int ihi;
  int iy;
  int j;
  int ju;
  int k;
  int nRowsD2;
  sintab_data = sintab->data;
  costab_data = costab->data;
  x_data = x->data;
  iy = y->size[0];
  y->size[0] = unsigned_nRows;
  emxEnsureCapacity_creal_T(y, iy);
  y_data = y->data;
  if (unsigned_nRows > x->size[0]) {
    iy = y->size[0];
    y->size[0] = unsigned_nRows;
    emxEnsureCapacity_creal_T(y, iy);
    y_data = y->data;
    for (iy = 0; iy < unsigned_nRows; iy++) {
      y_data[iy].re = 0.0;
      y_data[iy].im = 0.0;
    }
  }
  j = x->size[0];
  if (j > unsigned_nRows) {
    j = unsigned_nRows;
  }
  ihi = unsigned_nRows - 2;
  nRowsD2 = unsigned_nRows / 2;
  k = nRowsD2 / 2;
  iy = 0;
  ju = 0;
  if (j - 1 > 2147483646) {
    check_forloop_overflow_error();
  }
  for (i = 0; i <= j - 2; i++) {
    boolean_T tst;
    y_data[iy] = x_data[i];
    iy = unsigned_nRows;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }
    iy = ju;
  }
  if (j - 2 < 0) {
    j = 0;
  } else {
    j--;
  }
  y_data[iy] = x_data[j];
  if (unsigned_nRows > 1) {
    for (i = 0; i <= ihi; i += 2) {
      temp_re_tmp = y_data[i + 1].re;
      temp_im = y_data[i + 1].im;
      temp_re = y_data[i].re;
      twid_re = y_data[i].im;
      y_data[i + 1].re = temp_re - temp_re_tmp;
      y_data[i + 1].im = twid_re - temp_im;
      y_data[i].re = temp_re + temp_re_tmp;
      y_data[i].im = twid_re + temp_im;
    }
  }
  iDelta = 2;
  iDelta2 = 4;
  iheight = ((k - 1) << 2) + 1;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      iy = i + iDelta;
      temp_re = y_data[iy].re;
      temp_im = y_data[iy].im;
      y_data[iy].re = y_data[i].re - temp_re;
      y_data[iy].im = y_data[i].im - temp_im;
      y_data[i].re += temp_re;
      y_data[i].im += temp_im;
    }
    iy = 1;
    for (j = k; j < nRowsD2; j += k) {
      double twid_im;
      twid_re = costab_data[j];
      twid_im = sintab_data[j];
      i = iy;
      ihi = iy + iheight;
      while (i < ihi) {
        ju = i + iDelta;
        temp_re_tmp = y_data[ju].im;
        temp_im = y_data[ju].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        y_data[ju].re = y_data[i].re - temp_re;
        y_data[ju].im = y_data[i].im - temp_im;
        y_data[i].re += temp_re;
        y_data[i].im += temp_im;
        i += iDelta2;
      }
      iy++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
}

/*
 * Arguments    : int nRows
 *                boolean_T useRadix2
 *                emxArray_real_T *costab
 *                emxArray_real_T *sintab
 *                emxArray_real_T *sintabinv
 * Return Type  : void
 */
void f_FFTImplementationCallback_gen(int nRows, boolean_T useRadix2,
                                     emxArray_real_T *costab,
                                     emxArray_real_T *sintab,
                                     emxArray_real_T *sintabinv)
{
  emxArray_real_T *costab1q;
  double e;
  double *costab1q_data;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
  int i;
  int k;
  int n;
  int nd2;
  e = 6.2831853071795862 / (double)nRows;
  n = nRows / 2 / 2;
  emxInit_real_T(&costab1q, 2);
  i = costab1q->size[0] * costab1q->size[1];
  costab1q->size[0] = 1;
  costab1q->size[1] = n + 1;
  emxEnsureCapacity_real_T(costab1q, i);
  costab1q_data = costab1q->data;
  costab1q_data[0] = 1.0;
  nd2 = n / 2 - 1;
  for (k = 0; k <= nd2; k++) {
    costab1q_data[k + 1] = cos(e * ((double)k + 1.0));
  }
  i = nd2 + 2;
  nd2 = n - 1;
  for (k = i; k <= nd2; k++) {
    costab1q_data[k] = sin(e * (double)(n - k));
  }
  costab1q_data[n] = 0.0;
  if (!useRadix2) {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    emxEnsureCapacity_real_T(costab, i);
    if (nd2 + 1 < 0) {
      rtNonNegativeError(-1.0, &b_emlrtDCI);
    }
    i = costab->size[0] * costab->size[1];
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    costab_data = costab->data;
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    i = sintabinv->size[0] * sintabinv->size[1];
    sintabinv->size[0] = 1;
    sintabinv->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintabinv, i);
    sintabinv_data = sintabinv->data;
    for (k = 0; k < n; k++) {
      sintabinv_data[k + 1] = costab1q_data[(n - k) - 1];
    }
    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      sintabinv_data[k] = costab1q_data[k - n];
    }
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    for (k = i; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
  } else {
    n = costab1q->size[1] - 1;
    nd2 = (costab1q->size[1] - 1) << 1;
    i = costab->size[0] * costab->size[1];
    costab->size[0] = 1;
    emxEnsureCapacity_real_T(costab, i);
    if (nd2 + 1 < 0) {
      rtNonNegativeError(-1.0, &b_emlrtDCI);
    }
    i = costab->size[0] * costab->size[1];
    costab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(costab, i);
    costab_data = costab->data;
    i = sintab->size[0] * sintab->size[1];
    sintab->size[0] = 1;
    sintab->size[1] = nd2 + 1;
    emxEnsureCapacity_real_T(sintab, i);
    sintab_data = sintab->data;
    costab_data[0] = 1.0;
    sintab_data[0] = 0.0;
    for (k = 0; k < n; k++) {
      costab_data[k + 1] = costab1q_data[k + 1];
      sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
    }
    i = costab1q->size[1];
    for (k = i; k <= nd2; k++) {
      costab_data[k] = -costab1q_data[nd2 - k];
      sintab_data[k] = -costab1q_data[k - n];
    }
    sintabinv->size[0] = 1;
    sintabinv->size[1] = 0;
  }
  emxFree_real_T(&costab1q);
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int n1_unsigned
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void f_FFTImplementationCallback_r2b(const emxArray_real_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y)
{
  emxArray_creal_T *r;
  creal_T *r1;
  creal_T *y_data;
  int chan;
  int i;
  int loop_ub;
  int nChan_tmp;
  nChan_tmp = x->size[1];
  if (n1_unsigned < 0) {
    rtNonNegativeError(n1_unsigned, &c_emlrtDCI);
  }
  i = y->size[0] * y->size[1];
  y->size[0] = n1_unsigned;
  y->size[1] = x->size[1];
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    i = y->size[0] * y->size[1];
    y->size[0] = n1_unsigned;
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    loop_ub = n1_unsigned * x->size[1];
    for (i = 0; i < loop_ub; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  if (x->size[1] > 2147483646) {
    check_forloop_overflow_error();
  }
  emxInit_creal_T(&r, 1);
  for (chan = 0; chan < nChan_tmp; chan++) {
    d_FFTImplementationCallback_r2b(x, chan * x->size[0], n1_unsigned, costab,
                                    sintab, r);
    r1 = r->data;
    loop_ub = y->size[0];
    for (i = 0; i < loop_ub; i++) {
      y_data[i + y->size[0] * chan] = r1[i];
    }
  }
  emxFree_creal_T(&r);
  if (y->size[0] > 1) {
    double b;
    b = 1.0 / (double)y->size[0];
    loop_ub = y->size[0] * y->size[1];
    for (i = 0; i < loop_ub; i++) {
      y_data[i].re *= b;
      y_data[i].im *= b;
    }
  }
}

/*
 * Arguments    : const emxArray_real_T *x
 *                int n1_unsigned
 *                const emxArray_real_T *costab
 *                const emxArray_real_T *sintab
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void g_FFTImplementationCallback_r2b(const emxArray_real_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y)
{
  creal_T *y_data;
  const double *x_data;
  int i;
  x_data = x->data;
  if (n1_unsigned < 0) {
    rtNonNegativeError(n1_unsigned, &c_emlrtDCI);
  }
  i = y->size[0];
  y->size[0] = n1_unsigned;
  emxEnsureCapacity_creal_T(y, i);
  y_data = y->data;
  if (n1_unsigned > x->size[0]) {
    i = y->size[0];
    y->size[0] = n1_unsigned;
    emxEnsureCapacity_creal_T(y, i);
    y_data = y->data;
    for (i = 0; i < n1_unsigned; i++) {
      y_data[i].re = 0.0;
      y_data[i].im = 0.0;
    }
  }
  if (n1_unsigned != 1) {
    f_FFTImplementationCallback_doH(x, y, n1_unsigned, costab, sintab);
  } else {
    y_data[0].re = x_data[0];
    y_data[0].im = 0.0;
  }
}

/*
 * Arguments    : const double x[120]
 *                creal_T y[120]
 * Return Type  : void
 */
void h_FFTImplementationCallback_doH(const double x[120], creal_T y[120])
{
  static const creal_T b_fv[128] = {{
                                        9.9544511501033188, /* re */
                                        10.954451150103331  /* im */
                                    },
                                    {
                                        -0.9847449818695061, /* re */
                                        -0.542454889828055   /* im */
                                    },
                                    {
                                        4.4867559600345466, /* re */
                                        12.971100696432089  /* im */
                                    },
                                    {
                                        0.16211829815030954, /* re */
                                        -3.0663334951204231  /* im */
                                    },
                                    {
                                        1.4626484990555526, /* re */
                                        10.924028181659278  /* im */
                                    },
                                    {
                                        3.6928435001467568, /* re */
                                        -5.874050851678291  /* im */
                                    },
                                    {
                                        1.8788461357929469, /* re */
                                        8.0912261350045611  /* im */
                                    },
                                    {
                                        8.4491757720058089, /* re */
                                        -7.3935764266268329 /* im */
                                    },
                                    {
                                        3.9481421938301615, /* re */
                                        6.3371404117062431  /* im */
                                    },
                                    {
                                        12.170499515241486, /* re */
                                        -7.8298450486603475 /* im */
                                    },
                                    {
                                        5.38735538208306,  /* re */
                                        5.3579331868766911 /* im */
                                    },
                                    {
                                        13.154052477490035, /* re */
                                        -8.665690761523873  /* im */
                                    },
                                    {
                                        4.9411721784018443, /* re */
                                        3.9203383425957807  /* im */
                                    },
                                    {
                                        10.865132549604477, /* re */
                                        -11.059833233364511 /* im */
                                    },
                                    {
                                        2.6155939293429293, /* re */
                                        1.534073067224853   /* im */
                                    },
                                    {
                                        5.6880431781414158, /* re */
                                        -14.493929728851587 /* im */
                                    },
                                    {
                                        -0.70710678118654757, /* re */
                                        -0.70710678118654757  /* im */
                                    },
                                    {
                                        -1.3245338484037734, /* re */
                                        -16.578315345582581  /* im */
                                    },
                                    {
                                        -3.4818987875568905, /* re */
                                        -0.72988831193093606 /* im */
                                    },
                                    {
                                        -8.2149550404786034, /* re */
                                        -14.370513349783046  /* im */
                                    },
                                    {
                                        -3.5635904282706212, /* re */
                                        2.55705493799564     /* im */
                                    },
                                    {
                                        -11.992360374477162, /* re */
                                        -6.8608960229009472  /* im */
                                    },
                                    {
                                        0.85380960647066,  /* re */
                                        7.0542234835999267 /* im */
                                    },
                                    {
                                        -9.9794700446710358, /* re */
                                        2.8995190057331355   /* im */
                                    },
                                    {
                                        8.6708690085819615, /* re */
                                        7.4441379002809711  /* im */
                                    },
                                    {
                                        -2.8403283222781184, /* re */
                                        8.7066753341928056   /* im */
                                    },
                                    {
                                        13.729604380986014,  /* re */
                                        -0.28031741182797631 /* im */
                                    },
                                    {
                                        3.8903818937725658, /* re */
                                        6.5656219446504673  /* im */
                                    },
                                    {
                                        8.24829146445924,   /* re */
                                        -11.765781491838291 /* im */
                                    },
                                    {
                                        4.376230178461741,  /* re */
                                        0.24802895761511934 /* im */
                                    },
                                    {
                                        -6.6713533844242221, /* re */
                                        -14.211901360004456  /* im */
                                    },
                                    {
                                        0.65079320174724142, /* re */
                                        -2.0289037889284014  /* im */
                                    },
                                    {
                                        -15.491933384829665, /* re */
                                        -0.99999999999999867 /* im */
                                    },
                                    {
                                        1.1324785631997358, /* re */
                                        0.1200645071411941  /* im */
                                    },
                                    {
                                        -4.5788032544276138, /* re */
                                        13.16360787969937    /* im */
                                    },
                                    {
                                        5.1590971396900773, /* re */
                                        -2.3123865042646345 /* im */
                                    },
                                    {
                                        12.856494234373717, /* re */
                                        7.3625353762799257  /* im */
                                    },
                                    {
                                        0.45686505305231728, /* re */
                                        -7.7026722346630869  /* im */
                                    },
                                    {
                                        9.9680840119698075, /* re */
                                        -9.4334926682616267 /* im */
                                    },
                                    {
                                        -8.9470394457190583, /* re */
                                        -0.14552315461046339 /* im */
                                    },
                                    {
                                        -6.7316654247055752, /* re */
                                        -7.8849446529590237  /* im */
                                    },
                                    {
                                        -0.24269943085274992, /* re */
                                        12.195091186801561    /* im */
                                    },
                                    {
                                        -6.1290475563851317, /* re */
                                        6.0342819349381305   /* im */
                                    },
                                    {
                                        13.638452219349087,  /* re */
                                        -0.32546033515069039 /* im */
                                    },
                                    {
                                        4.4842753163841946, /* re */
                                        3.49075540049986    /* im */
                                    },
                                    {
                                        -2.5766681164910454, /* re */
                                        -15.144140381688114  /* im */
                                    },
                                    {
                                        1.6541576407213698, /* re */
                                        -3.3706769978361311 /* im */
                                    },
                                    {
                                        -13.559701198953295, /* re */
                                        5.6436359976373662   /* im */
                                    },
                                    {
                                        0.70710678118654757, /* re */
                                        -0.70710678118654757 /* im */
                                    },
                                    {
                                        11.66315054390402, /* re */
                                        10.498148260582045 /* im */
                                    },
                                    {
                                        0.43319236703500219, /* re */
                                        -3.2777588615585911  /* im */
                                    },
                                    {
                                        6.2742568561978658, /* re */
                                        -13.915012036582228 /* im */
                                    },
                                    {
                                        -3.7238732394345666, /* re */
                                        3.8782255531606498   /* im */
                                    },
                                    {
                                        -12.764665323179791, /* re */
                                        2.5727390530870604   /* im */
                                    },
                                    {
                                        8.6426229795541474, /* re */
                                        3.1092712675309655  /* im */
                                    },
                                    {
                                        8.7134628071878311, /* re */
                                        8.8041329422603     /* im */
                                    },
                                    {
                                        -3.609457387828686, /* re */
                                        -10.132665132291196 /* im */
                                    },
                                    {
                                        0.73133749645939616, /* re */
                                        -9.8263471230895583  /* im */
                                    },
                                    {
                                        -5.7990174214971875, /* re */
                                        11.24357027979736    /* im */
                                    },
                                    {
                                        -5.289555315704856, /* re */
                                        4.4410650983684272  /* im */
                                    },
                                    {
                                        13.64514450866004,  /* re */
                                        -5.8436372229331628 /* im */
                                    },
                                    {
                                        5.0768811909548983,  /* re */
                                        -0.77487420379333571 /* im */
                                    },
                                    {
                                        -13.929048090344653, /* re */
                                        -4.1633352689021494  /* im */
                                    },
                                    {
                                        -0.3645509537477189, /* re */
                                        -1.0026445191813593  /* im */
                                    },
                                    {
                                        11.954451150103322, /* re */
                                        10.954451150103321  /* im */
                                    },
                                    {
                                        0.151138116489978,  /* re */
                                        -1.0561016520518534 /* im */
                                    },
                                    {
                                        -4.2768777313744426, /* re */
                                        -13.894605360905071  /* im */
                                    },
                                    {
                                        1.2687643488377416, /* re */
                                        4.9764836667967014  /* im */
                                    },
                                    {
                                        0.17704608999736415, /* re */
                                        14.842732879678252   /* im */
                                    },
                                    {
                                        1.2714996797417941, /* re */
                                        -6.7886481135984784 /* im */
                                    },
                                    {
                                        3.4940791813097016, /* re */
                                        -12.158860405741507 /* im */
                                    },
                                    {
                                        -3.5522843526117756, /* re */
                                        9.1909318458667428   /* im */
                                    },
                                    {
                                        -4.6126044311980436, /* re */
                                        9.7171480218731361   /* im */
                                    },
                                    {
                                        5.8956451948442865, /* re */
                                        -10.893968913749847 /* im */
                                    },
                                    {
                                        4.7356195921202744, /* re */
                                        -7.8699686696033044 /* im */
                                    },
                                    {
                                        -6.1090637738109859, /* re */
                                        11.499348105678784   /* im */
                                    },
                                    {
                                        -1.9562776014105816, /* re */
                                        5.0080778039867138   /* im */
                                    },
                                    {
                                        7.6079542819836359, /* re */
                                        -13.23302273552876  /* im */
                                    },
                                    {
                                        2.181211543969189, /* re */
                                        -2.484688105545406 /* im */
                                    },
                                    {
                                        -3.7605690797822904, /* re */
                                        15.234773306718939   /* im */
                                    },
                                    {
                                        0.70710678118654757, /* re */
                                        0.70710678118654757  /* im */
                                    },
                                    {
                                        1.4147563029639183, /* re */
                                        -14.618980418686784 /* im */
                                    },
                                    {
                                        0.49726599290374285, /* re */
                                        3.7216162424946413   /* im */
                                    },
                                    {
                                        4.0486460881975948, /* re */
                                        14.818659566078857  /* im */
                                    },
                                    {
                                        -2.8070759247426738, /* re */
                                        -4.9410953372690116  /* im */
                                    },
                                    {
                                        -8.9037267355682523, /* re */
                                        -10.336196282363813  /* im */
                                    },
                                    {
                                        7.1140527610177831, /* re */
                                        4.8340496203707417  /* im */
                                    },
                                    {
                                        11.599522728627853, /* re */
                                        3.7722969840916756  /* im */
                                    },
                                    {
                                        -10.335504103876266, /* re */
                                        -0.81549156289960179 /* im */
                                    },
                                    {
                                        -8.60402607296486, /* re */
                                        2.4579314814537536 /* im */
                                    },
                                    {
                                        11.616933195150711, /* re */
                                        -7.3075540320437895 /* im */
                                    },
                                    {
                                        5.2396849975696052, /* re */
                                        -5.6644140347960219 /* im */
                                    },
                                    {
                                        -1.8821283997431895, /* re */
                                        14.695372191691442   /* im */
                                    },
                                    {
                                        1.7955717828922413, /* re */
                                        5.3609081893224708  /* im */
                                    },
                                    {
                                        -8.4012931492231,   /* re */
                                        -11.120444463871808 /* im */
                                    },
                                    {
                                        -1.0553549431795002, /* re */
                                        0.4279592572764287   /* im */
                                    },
                                    {
                                        15.491933384829665, /* re */
                                        0.99999999999999867 /* im */
                                    },
                                    {
                                        -1.5303669887489935, /* re */
                                        1.4825516031207115   /* im */
                                    },
                                    {
                                        -8.1103587595442423, /* re */
                                        13.442736962309759   /* im */
                                    },
                                    {
                                        -0.18211093712575055, /* re */
                                        -4.3794685231514245   /* im */
                                    },
                                    {
                                        -7.713680215542575, /* re */
                                        -12.122997307955764 /* im */
                                    },
                                    {
                                        7.1724923395030249, /* re */
                                        2.6072622498014315  /* im */
                                    },
                                    {
                                        13.411106668490547, /* re */
                                        -2.9534441312022142 /* im */
                                    },
                                    {
                                        -5.2454391776560714, /* re */
                                        7.5072650270845926   /* im */
                                    },
                                    {
                                        0.86742988537211962, /* re */
                                        11.395030664125041   /* im */
                                    },
                                    {
                                        -5.6715539318960948, /* re */
                                        -8.7080714762045961  /* im */
                                    },
                                    {
                                        -7.0852485484564305, /* re */
                                        -0.53880683669594687 /* im */
                                    },
                                    {
                                        12.911417227975797, /* re */
                                        -4.9177135696904877 /* im */
                                    },
                                    {
                                        2.3137856985140841, /* re */
                                        -3.7261377373550717 /* im */
                                    },
                                    {
                                        6.7668411629695768, /* re */
                                        15.106521801146616  /* im */
                                    },
                                    {
                                        2.4895888154288759, /* re */
                                        2.541319272499027   /* im */
                                    },
                                    {
                                        -13.996387896388807, /* re */
                                        8.9830983222364367   /* im */
                                    },
                                    {
                                        -0.70710678118654757, /* re */
                                        0.70710678118654757   /* im */
                                    },
                                    {
                                        -10.101179838743764, /* re */
                                        -11.848797409300463  /* im */
                                    },
                                    {
                                        3.0270722017988643,  /* re */
                                        -0.17761099036048389 /* im */
                                    },
                                    {
                                        9.7287607405790943, /* re */
                                        -12.071546335199804 /* im */
                                    },
                                    {
                                        3.0647993092626526, /* re */
                                        5.5128250843811664  /* im */
                                    },
                                    {
                                        15.04351209552269, /* re */
                                        4.6707640474321082 /* im */
                                    },
                                    {
                                        -4.2039611067667231, /* re */
                                        6.3291197698168613   /* im */
                                    },
                                    {
                                        3.959785025788741, /* re */
                                        13.919325935046693 /* im */
                                    },
                                    {
                                        -7.2727930767948337, /* re */
                                        -1.6892768401027549  /* im */
                                    },
                                    {
                                        -5.9391151531641126, /* re */
                                        9.5278777700009556   /* im */
                                    },
                                    {
                                        -0.2642247219448608, /* re */
                                        -8.3023001912769985  /* im */
                                    },
                                    {
                                        -6.58106503938653, /* re */
                                        2.1979875959711306 /* im */
                                    },
                                    {
                                        9.5327547016492691, /* re */
                                        -5.5317556113461226 /* im */
                                    },
                                    {
                                        -3.0356778892474305, /* re */
                                        -0.46189089472172717 /* im */
                                    },
                                    {
                                        13.277784121418145, /* re */
                                        3.4757561978514397  /* im */
                                    },
                                    {
                                        -1.1241790044113065,  /* re */
                                        -0.014196931230045728 /* im */
                                    }};
  static const creal_T wwc[119] = {{
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       0.97814760073380569, /* re */
                                       0.20791169081775931  /* im */
                                   },
                                   {
                                       0.8910065241883679, /* re */
                                       0.45399049973954675 /* im */
                                   },
                                   {
                                       0.66913060635885824, /* re */
                                       0.74314482547739424  /* im */
                                   },
                                   {
                                       0.25881904510252074, /* re */
                                       0.96592582628906831  /* im */
                                   },
                                   {
                                       -0.30901699437494734, /* re */
                                       0.95105651629515364   /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       -0.97814760073380569, /* re */
                                       -0.20791169081775907  /* im */
                                   },
                                   {
                                       -0.45399049973954692, /* re */
                                       -0.89100652418836779  /* im */
                                   },
                                   {
                                       0.50000000000000011, /* re */
                                       -0.8660254037844386  /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       0.30901699437494745, /* re */
                                       0.95105651629515353  /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       -0.66913060635885846, /* re */
                                       -0.743144825477394    /* im */
                                   },
                                   {
                                       0.70710678118654735, /* re */
                                       -0.70710678118654768 /* im */
                                   },
                                   {
                                       0.66913060635885824, /* re */
                                       0.74314482547739424  /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       -0.30901699437494756, /* re */
                                       -0.95105651629515353  /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       -0.49999999999999978, /* re */
                                       0.86602540378443871   /* im */
                                   },
                                   {
                                       -0.45399049973954692, /* re */
                                       -0.89100652418836779  /* im */
                                   },
                                   {
                                       0.97814760073380569, /* re */
                                       0.20791169081775931  /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       0.30901699437494723, /* re */
                                       -0.95105651629515364 /* im */
                                   },
                                   {
                                       0.25881904510252074, /* re */
                                       0.96592582628906831  /* im */
                                   },
                                   {
                                       -0.66913060635885846, /* re */
                                       -0.743144825477394    /* im */
                                   },
                                   {
                                       0.8910065241883679, /* re */
                                       0.45399049973954675 /* im */
                                   },
                                   {
                                       -0.97814760073380569, /* re */
                                       -0.20791169081775907  /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       -1.0,                /* re */
                                       5.66553889764798E-16 /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       -0.97814760073380569, /* re */
                                       -0.20791169081775907  /* im */
                                   },
                                   {
                                       0.8910065241883679, /* re */
                                       0.45399049973954675 /* im */
                                   },
                                   {
                                       -0.66913060635885846, /* re */
                                       -0.743144825477394    /* im */
                                   },
                                   {
                                       0.25881904510252074, /* re */
                                       0.96592582628906831  /* im */
                                   },
                                   {
                                       0.30901699437494723, /* re */
                                       -0.95105651629515364 /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       0.97814760073380569, /* re */
                                       0.20791169081775931  /* im */
                                   },
                                   {
                                       -0.45399049973954692, /* re */
                                       -0.89100652418836779  /* im */
                                   },
                                   {
                                       -0.49999999999999978, /* re */
                                       0.86602540378443871   /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       -0.30901699437494756, /* re */
                                       -0.95105651629515353  /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       0.66913060635885824, /* re */
                                       0.74314482547739424  /* im */
                                   },
                                   {
                                       0.70710678118654735, /* re */
                                       -0.70710678118654768 /* im */
                                   },
                                   {
                                       -0.66913060635885846, /* re */
                                       -0.743144825477394    /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       0.30901699437494745, /* re */
                                       0.95105651629515353  /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       0.50000000000000011, /* re */
                                       -0.8660254037844386  /* im */
                                   },
                                   {
                                       -0.45399049973954692, /* re */
                                       -0.89100652418836779  /* im */
                                   },
                                   {
                                       -0.97814760073380569, /* re */
                                       -0.20791169081775907  /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       -0.30901699437494734, /* re */
                                       0.95105651629515364   /* im */
                                   },
                                   {
                                       0.25881904510252074, /* re */
                                       0.96592582628906831  /* im */
                                   },
                                   {
                                       0.66913060635885824, /* re */
                                       0.74314482547739424  /* im */
                                   },
                                   {
                                       0.8910065241883679, /* re */
                                       0.45399049973954675 /* im */
                                   },
                                   {
                                       0.97814760073380569, /* re */
                                       0.20791169081775931  /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       1.0, /* re */
                                       0.0  /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       0.97814760073380569, /* re */
                                       0.20791169081775931  /* im */
                                   },
                                   {
                                       0.8910065241883679, /* re */
                                       0.45399049973954675 /* im */
                                   },
                                   {
                                       0.66913060635885824, /* re */
                                       0.74314482547739424  /* im */
                                   },
                                   {
                                       0.25881904510252074, /* re */
                                       0.96592582628906831  /* im */
                                   },
                                   {
                                       -0.30901699437494734, /* re */
                                       0.95105651629515364   /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       -0.97814760073380569, /* re */
                                       -0.20791169081775907  /* im */
                                   },
                                   {
                                       -0.45399049973954692, /* re */
                                       -0.89100652418836779  /* im */
                                   },
                                   {
                                       0.50000000000000011, /* re */
                                       -0.8660254037844386  /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       0.30901699437494745, /* re */
                                       0.95105651629515353  /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       -0.66913060635885846, /* re */
                                       -0.743144825477394    /* im */
                                   },
                                   {
                                       0.70710678118654735, /* re */
                                       -0.70710678118654768 /* im */
                                   },
                                   {
                                       0.66913060635885824, /* re */
                                       0.74314482547739424  /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       -0.30901699437494756, /* re */
                                       -0.95105651629515353  /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       -0.49999999999999978, /* re */
                                       0.86602540378443871   /* im */
                                   },
                                   {
                                       -0.45399049973954692, /* re */
                                       -0.89100652418836779  /* im */
                                   },
                                   {
                                       0.97814760073380569, /* re */
                                       0.20791169081775931  /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       0.30901699437494723, /* re */
                                       -0.95105651629515364 /* im */
                                   },
                                   {
                                       0.25881904510252074, /* re */
                                       0.96592582628906831  /* im */
                                   },
                                   {
                                       -0.66913060635885846, /* re */
                                       -0.743144825477394    /* im */
                                   },
                                   {
                                       0.8910065241883679, /* re */
                                       0.45399049973954675 /* im */
                                   },
                                   {
                                       -0.97814760073380569, /* re */
                                       -0.20791169081775907  /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       -1.0,                /* re */
                                       5.66553889764798E-16 /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       -0.97814760073380569, /* re */
                                       -0.20791169081775907  /* im */
                                   },
                                   {
                                       0.8910065241883679, /* re */
                                       0.45399049973954675 /* im */
                                   },
                                   {
                                       -0.66913060635885846, /* re */
                                       -0.743144825477394    /* im */
                                   },
                                   {
                                       0.25881904510252074, /* re */
                                       0.96592582628906831  /* im */
                                   },
                                   {
                                       0.30901699437494723, /* re */
                                       -0.95105651629515364 /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       0.97814760073380569, /* re */
                                       0.20791169081775931  /* im */
                                   },
                                   {
                                       -0.45399049973954692, /* re */
                                       -0.89100652418836779  /* im */
                                   },
                                   {
                                       -0.49999999999999978, /* re */
                                       0.86602540378443871   /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       -0.30901699437494756, /* re */
                                       -0.95105651629515353  /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       0.66913060635885824, /* re */
                                       0.74314482547739424  /* im */
                                   },
                                   {
                                       0.70710678118654735, /* re */
                                       -0.70710678118654768 /* im */
                                   },
                                   {
                                       -0.66913060635885846, /* re */
                                       -0.743144825477394    /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       0.30901699437494745, /* re */
                                       0.95105651629515353  /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   },
                                   {
                                       0.50000000000000011, /* re */
                                       -0.8660254037844386  /* im */
                                   },
                                   {
                                       -0.45399049973954692, /* re */
                                       -0.89100652418836779  /* im */
                                   },
                                   {
                                       -0.97814760073380569, /* re */
                                       -0.20791169081775907  /* im */
                                   },
                                   {
                                       -0.83867056794542394, /* re */
                                       0.54463903501502731   /* im */
                                   },
                                   {
                                       -0.30901699437494734, /* re */
                                       0.95105651629515364   /* im */
                                   },
                                   {
                                       0.25881904510252074, /* re */
                                       0.96592582628906831  /* im */
                                   },
                                   {
                                       0.66913060635885824, /* re */
                                       0.74314482547739424  /* im */
                                   },
                                   {
                                       0.8910065241883679, /* re */
                                       0.45399049973954675 /* im */
                                   },
                                   {
                                       0.97814760073380569, /* re */
                                       0.20791169081775931  /* im */
                                   },
                                   {
                                       0.99862953475457383, /* re */
                                       0.052335956242943828 /* im */
                                   }};
  static const creal_T reconVar1[60] = {{
                                            1.0, /* re */
                                            -1.0 /* im */
                                        },
                                        {
                                            0.94766404375705615, /* re */
                                            -0.99862953475457383 /* im */
                                        },
                                        {
                                            0.89547153673234658, /* re */
                                            -0.99452189536827329 /* im */
                                        },
                                        {
                                            0.84356553495976916, /* re */
                                            -0.98768834059513777 /* im */
                                        },
                                        {
                                            0.79208830918224071, /* re */
                                            -0.97814760073380569 /* im */
                                        },
                                        {
                                            0.74118095489747926, /* re */
                                            -0.96592582628906831 /* im */
                                        },
                                        {
                                            0.69098300562505255, /* re */
                                            -0.95105651629515353 /* im */
                                        },
                                        {
                                            0.64163205045469973, /* re */
                                            -0.93358042649720174 /* im */
                                        },
                                        {
                                            0.59326335692419985, /* re */
                                            -0.91354545764260087 /* im */
                                        },
                                        {
                                            0.54600950026045325, /* re */
                                            -0.8910065241883679  /* im */
                                        },
                                        {
                                            0.5,                 /* re */
                                            -0.86602540378443871 /* im */
                                        },
                                        {
                                            0.455360964984973, /* re */
                                            -0.838670567945424 /* im */
                                        },
                                        {
                                            0.41221474770752686, /* re */
                                            -0.80901699437494745 /* im */
                                        },
                                        {
                                            0.37067960895016261, /* re */
                                            -0.7771459614569709  /* im */
                                        },
                                        {
                                            0.33086939364114187, /* re */
                                            -0.74314482547739424 /* im */
                                        },
                                        {
                                            0.29289321881345243, /* re */
                                            -0.70710678118654757 /* im */
                                        },
                                        {
                                            0.25685517452260576, /* re */
                                            -0.66913060635885813 /* im */
                                        },
                                        {
                                            0.2228540385430291,  /* re */
                                            -0.62932039104983739 /* im */
                                        },
                                        {
                                            0.19098300562505255, /* re */
                                            -0.58778525229247314 /* im */
                                        },
                                        {
                                            0.16132943205457595, /* re */
                                            -0.544639035015027   /* im */
                                        },
                                        {
                                            0.13397459621556129, /* re */
                                            -0.49999999999999994 /* im */
                                        },
                                        {
                                            0.1089934758116321,  /* re */
                                            -0.45399049973954675 /* im */
                                        },
                                        {
                                            0.086454542357399133, /* re */
                                            -0.40673664307580015  /* im */
                                        },
                                        {
                                            0.066419573502798257, /* re */
                                            -0.35836794954530021  /* im */
                                        },
                                        {
                                            0.048943483704846469, /* re */
                                            -0.3090169943749474   /* im */
                                        },
                                        {
                                            0.034074173710931688, /* re */
                                            -0.25881904510252074  /* im */
                                        },
                                        {
                                            0.021852399266194311, /* re */
                                            -0.20791169081775931  /* im */
                                        },
                                        {
                                            0.01231165940486223, /* re */
                                            -0.15643446504023087 /* im */
                                        },
                                        {
                                            0.00547810463172671, /* re */
                                            -0.10452846326765346 /* im */
                                        },
                                        {
                                            0.0013704652454261668, /* re */
                                            -0.052335956242943828  /* im */
                                        },
                                        {
                                            0.0, /* re */
                                            -0.0 /* im */
                                        },
                                        {
                                            0.0013704652454261668, /* re */
                                            0.052335956242943828   /* im */
                                        },
                                        {
                                            0.00547810463172671, /* re */
                                            0.10452846326765346  /* im */
                                        },
                                        {
                                            0.01231165940486223, /* re */
                                            0.15643446504023087  /* im */
                                        },
                                        {
                                            0.021852399266194311, /* re */
                                            0.20791169081775931   /* im */
                                        },
                                        {
                                            0.034074173710931688, /* re */
                                            0.25881904510252074   /* im */
                                        },
                                        {
                                            0.048943483704846469, /* re */
                                            0.3090169943749474    /* im */
                                        },
                                        {
                                            0.066419573502798257, /* re */
                                            0.35836794954530021   /* im */
                                        },
                                        {
                                            0.086454542357399133, /* re */
                                            0.40673664307580015   /* im */
                                        },
                                        {
                                            0.1089934758116321, /* re */
                                            0.45399049973954675 /* im */
                                        },
                                        {
                                            0.13397459621556129, /* re */
                                            0.49999999999999994  /* im */
                                        },
                                        {
                                            0.16132943205457595, /* re */
                                            0.544639035015027    /* im */
                                        },
                                        {
                                            0.19098300562505255, /* re */
                                            0.58778525229247314  /* im */
                                        },
                                        {
                                            0.2228540385430291, /* re */
                                            0.62932039104983739 /* im */
                                        },
                                        {
                                            0.25685517452260576, /* re */
                                            0.66913060635885813  /* im */
                                        },
                                        {
                                            0.29289321881345243, /* re */
                                            0.70710678118654757  /* im */
                                        },
                                        {
                                            0.33086939364114187, /* re */
                                            0.74314482547739424  /* im */
                                        },
                                        {
                                            0.37067960895016261, /* re */
                                            0.7771459614569709   /* im */
                                        },
                                        {
                                            0.41221474770752686, /* re */
                                            0.80901699437494745  /* im */
                                        },
                                        {
                                            0.455360964984973, /* re */
                                            0.838670567945424  /* im */
                                        },
                                        {
                                            0.5,                /* re */
                                            0.86602540378443871 /* im */
                                        },
                                        {
                                            0.54600950026045325, /* re */
                                            0.8910065241883679   /* im */
                                        },
                                        {
                                            0.59326335692419985, /* re */
                                            0.91354545764260087  /* im */
                                        },
                                        {
                                            0.64163205045469973, /* re */
                                            0.93358042649720174  /* im */
                                        },
                                        {
                                            0.69098300562505255, /* re */
                                            0.95105651629515353  /* im */
                                        },
                                        {
                                            0.74118095489747926, /* re */
                                            0.96592582628906831  /* im */
                                        },
                                        {
                                            0.79208830918224071, /* re */
                                            0.97814760073380569  /* im */
                                        },
                                        {
                                            0.84356553495976916, /* re */
                                            0.98768834059513777  /* im */
                                        },
                                        {
                                            0.89547153673234658, /* re */
                                            0.99452189536827329  /* im */
                                        },
                                        {
                                            0.94766404375705615, /* re */
                                            0.99862953475457383  /* im */
                                        }};
  static const creal_T reconVar2[60] = {{
                                            1.0, /* re */
                                            1.0  /* im */
                                        },
                                        {
                                            1.0523359562429437, /* re */
                                            0.99862953475457383 /* im */
                                        },
                                        {
                                            1.1045284632676535, /* re */
                                            0.99452189536827329 /* im */
                                        },
                                        {
                                            1.156434465040231,  /* re */
                                            0.98768834059513777 /* im */
                                        },
                                        {
                                            1.2079116908177594, /* re */
                                            0.97814760073380569 /* im */
                                        },
                                        {
                                            1.2588190451025207, /* re */
                                            0.96592582628906831 /* im */
                                        },
                                        {
                                            1.3090169943749475, /* re */
                                            0.95105651629515353 /* im */
                                        },
                                        {
                                            1.3583679495453003, /* re */
                                            0.93358042649720174 /* im */
                                        },
                                        {
                                            1.4067366430758002, /* re */
                                            0.91354545764260087 /* im */
                                        },
                                        {
                                            1.4539904997395467, /* re */
                                            0.8910065241883679  /* im */
                                        },
                                        {
                                            1.5,                /* re */
                                            0.86602540378443871 /* im */
                                        },
                                        {
                                            1.544639035015027, /* re */
                                            0.838670567945424  /* im */
                                        },
                                        {
                                            1.5877852522924731, /* re */
                                            0.80901699437494745 /* im */
                                        },
                                        {
                                            1.6293203910498373, /* re */
                                            0.7771459614569709  /* im */
                                        },
                                        {
                                            1.6691306063588582, /* re */
                                            0.74314482547739424 /* im */
                                        },
                                        {
                                            1.7071067811865475, /* re */
                                            0.70710678118654757 /* im */
                                        },
                                        {
                                            1.7431448254773942, /* re */
                                            0.66913060635885813 /* im */
                                        },
                                        {
                                            1.7771459614569709, /* re */
                                            0.62932039104983739 /* im */
                                        },
                                        {
                                            1.8090169943749475, /* re */
                                            0.58778525229247314 /* im */
                                        },
                                        {
                                            1.8386705679454241, /* re */
                                            0.544639035015027   /* im */
                                        },
                                        {
                                            1.8660254037844388, /* re */
                                            0.49999999999999994 /* im */
                                        },
                                        {
                                            1.8910065241883678, /* re */
                                            0.45399049973954675 /* im */
                                        },
                                        {
                                            1.9135454576426008, /* re */
                                            0.40673664307580015 /* im */
                                        },
                                        {
                                            1.9335804264972016, /* re */
                                            0.35836794954530021 /* im */
                                        },
                                        {
                                            1.9510565162951536, /* re */
                                            0.3090169943749474  /* im */
                                        },
                                        {
                                            1.9659258262890682, /* re */
                                            0.25881904510252074 /* im */
                                        },
                                        {
                                            1.9781476007338057, /* re */
                                            0.20791169081775931 /* im */
                                        },
                                        {
                                            1.9876883405951378, /* re */
                                            0.15643446504023087 /* im */
                                        },
                                        {
                                            1.9945218953682733, /* re */
                                            0.10452846326765346 /* im */
                                        },
                                        {
                                            1.9986295347545737,  /* re */
                                            0.052335956242943828 /* im */
                                        },
                                        {
                                            2.0, /* re */
                                            0.0  /* im */
                                        },
                                        {
                                            1.9986295347545737,   /* re */
                                            -0.052335956242943828 /* im */
                                        },
                                        {
                                            1.9945218953682733,  /* re */
                                            -0.10452846326765346 /* im */
                                        },
                                        {
                                            1.9876883405951378,  /* re */
                                            -0.15643446504023087 /* im */
                                        },
                                        {
                                            1.9781476007338057,  /* re */
                                            -0.20791169081775931 /* im */
                                        },
                                        {
                                            1.9659258262890682,  /* re */
                                            -0.25881904510252074 /* im */
                                        },
                                        {
                                            1.9510565162951536, /* re */
                                            -0.3090169943749474 /* im */
                                        },
                                        {
                                            1.9335804264972016,  /* re */
                                            -0.35836794954530021 /* im */
                                        },
                                        {
                                            1.9135454576426008,  /* re */
                                            -0.40673664307580015 /* im */
                                        },
                                        {
                                            1.8910065241883678,  /* re */
                                            -0.45399049973954675 /* im */
                                        },
                                        {
                                            1.8660254037844388,  /* re */
                                            -0.49999999999999994 /* im */
                                        },
                                        {
                                            1.8386705679454241, /* re */
                                            -0.544639035015027  /* im */
                                        },
                                        {
                                            1.8090169943749475,  /* re */
                                            -0.58778525229247314 /* im */
                                        },
                                        {
                                            1.7771459614569709,  /* re */
                                            -0.62932039104983739 /* im */
                                        },
                                        {
                                            1.7431448254773942,  /* re */
                                            -0.66913060635885813 /* im */
                                        },
                                        {
                                            1.7071067811865475,  /* re */
                                            -0.70710678118654757 /* im */
                                        },
                                        {
                                            1.6691306063588582,  /* re */
                                            -0.74314482547739424 /* im */
                                        },
                                        {
                                            1.6293203910498373, /* re */
                                            -0.7771459614569709 /* im */
                                        },
                                        {
                                            1.5877852522924731,  /* re */
                                            -0.80901699437494745 /* im */
                                        },
                                        {
                                            1.544639035015027, /* re */
                                            -0.838670567945424 /* im */
                                        },
                                        {
                                            1.5,                 /* re */
                                            -0.86602540378443871 /* im */
                                        },
                                        {
                                            1.4539904997395467, /* re */
                                            -0.8910065241883679 /* im */
                                        },
                                        {
                                            1.4067366430758002,  /* re */
                                            -0.91354545764260087 /* im */
                                        },
                                        {
                                            1.3583679495453003,  /* re */
                                            -0.93358042649720174 /* im */
                                        },
                                        {
                                            1.3090169943749475,  /* re */
                                            -0.95105651629515353 /* im */
                                        },
                                        {
                                            1.2588190451025207,  /* re */
                                            -0.96592582628906831 /* im */
                                        },
                                        {
                                            1.2079116908177594,  /* re */
                                            -0.97814760073380569 /* im */
                                        },
                                        {
                                            1.156434465040231,   /* re */
                                            -0.98768834059513777 /* im */
                                        },
                                        {
                                            1.1045284632676535,  /* re */
                                            -0.99452189536827329 /* im */
                                        },
                                        {
                                            1.0523359562429437,  /* re */
                                            -0.99862953475457383 /* im */
                                        }};
  static const double dv[64] = {1.0,
                                0.99879545620517241,
                                0.99518472667219693,
                                0.989176509964781,
                                0.98078528040323043,
                                0.970031253194544,
                                0.95694033573220882,
                                0.94154406518302081,
                                0.92387953251128674,
                                0.90398929312344334,
                                0.881921264348355,
                                0.85772861000027212,
                                0.83146961230254524,
                                0.80320753148064494,
                                0.773010453362737,
                                0.74095112535495922,
                                0.70710678118654757,
                                0.67155895484701833,
                                0.63439328416364549,
                                0.59569930449243336,
                                0.55557023301960218,
                                0.51410274419322166,
                                0.47139673682599764,
                                0.42755509343028208,
                                0.38268343236508978,
                                0.33688985339222005,
                                0.29028467725446233,
                                0.24298017990326387,
                                0.19509032201612825,
                                0.14673047445536175,
                                0.0980171403295606,
                                0.049067674327418015,
                                0.0,
                                -0.049067674327418015,
                                -0.0980171403295606,
                                -0.14673047445536175,
                                -0.19509032201612825,
                                -0.24298017990326387,
                                -0.29028467725446233,
                                -0.33688985339222005,
                                -0.38268343236508978,
                                -0.42755509343028208,
                                -0.47139673682599764,
                                -0.51410274419322166,
                                -0.55557023301960218,
                                -0.59569930449243336,
                                -0.63439328416364549,
                                -0.67155895484701833,
                                -0.70710678118654757,
                                -0.74095112535495922,
                                -0.773010453362737,
                                -0.80320753148064494,
                                -0.83146961230254524,
                                -0.85772861000027212,
                                -0.881921264348355,
                                -0.90398929312344334,
                                -0.92387953251128674,
                                -0.94154406518302081,
                                -0.95694033573220882,
                                -0.970031253194544,
                                -0.98078528040323043,
                                -0.989176509964781,
                                -0.99518472667219693,
                                -0.99879545620517241};
  static const double dv1[64] = {0.0,
                                 -0.049067674327418015,
                                 -0.0980171403295606,
                                 -0.14673047445536175,
                                 -0.19509032201612825,
                                 -0.24298017990326387,
                                 -0.29028467725446233,
                                 -0.33688985339222005,
                                 -0.38268343236508978,
                                 -0.42755509343028208,
                                 -0.47139673682599764,
                                 -0.51410274419322166,
                                 -0.55557023301960218,
                                 -0.59569930449243336,
                                 -0.63439328416364549,
                                 -0.67155895484701833,
                                 -0.70710678118654757,
                                 -0.74095112535495922,
                                 -0.773010453362737,
                                 -0.80320753148064494,
                                 -0.83146961230254524,
                                 -0.85772861000027212,
                                 -0.881921264348355,
                                 -0.90398929312344334,
                                 -0.92387953251128674,
                                 -0.94154406518302081,
                                 -0.95694033573220882,
                                 -0.970031253194544,
                                 -0.98078528040323043,
                                 -0.989176509964781,
                                 -0.99518472667219693,
                                 -0.99879545620517241,
                                 -1.0,
                                 -0.99879545620517241,
                                 -0.99518472667219693,
                                 -0.989176509964781,
                                 -0.98078528040323043,
                                 -0.970031253194544,
                                 -0.95694033573220882,
                                 -0.94154406518302081,
                                 -0.92387953251128674,
                                 -0.90398929312344334,
                                 -0.881921264348355,
                                 -0.85772861000027212,
                                 -0.83146961230254524,
                                 -0.80320753148064494,
                                 -0.773010453362737,
                                 -0.74095112535495922,
                                 -0.70710678118654757,
                                 -0.67155895484701833,
                                 -0.63439328416364549,
                                 -0.59569930449243336,
                                 -0.55557023301960218,
                                 -0.51410274419322166,
                                 -0.47139673682599764,
                                 -0.42755509343028208,
                                 -0.38268343236508978,
                                 -0.33688985339222005,
                                 -0.29028467725446233,
                                 -0.24298017990326387,
                                 -0.19509032201612825,
                                 -0.14673047445536175,
                                 -0.0980171403295606,
                                 -0.049067674327418015};
  static const double dv2[64] = {0.0,
                                 0.049067674327418015,
                                 0.0980171403295606,
                                 0.14673047445536175,
                                 0.19509032201612825,
                                 0.24298017990326387,
                                 0.29028467725446233,
                                 0.33688985339222005,
                                 0.38268343236508978,
                                 0.42755509343028208,
                                 0.47139673682599764,
                                 0.51410274419322166,
                                 0.55557023301960218,
                                 0.59569930449243336,
                                 0.63439328416364549,
                                 0.67155895484701833,
                                 0.70710678118654757,
                                 0.74095112535495922,
                                 0.773010453362737,
                                 0.80320753148064494,
                                 0.83146961230254524,
                                 0.85772861000027212,
                                 0.881921264348355,
                                 0.90398929312344334,
                                 0.92387953251128674,
                                 0.94154406518302081,
                                 0.95694033573220882,
                                 0.970031253194544,
                                 0.98078528040323043,
                                 0.989176509964781,
                                 0.99518472667219693,
                                 0.99879545620517241,
                                 1.0,
                                 0.99879545620517241,
                                 0.99518472667219693,
                                 0.989176509964781,
                                 0.98078528040323043,
                                 0.970031253194544,
                                 0.95694033573220882,
                                 0.94154406518302081,
                                 0.92387953251128674,
                                 0.90398929312344334,
                                 0.881921264348355,
                                 0.85772861000027212,
                                 0.83146961230254524,
                                 0.80320753148064494,
                                 0.773010453362737,
                                 0.74095112535495922,
                                 0.70710678118654757,
                                 0.67155895484701833,
                                 0.63439328416364549,
                                 0.59569930449243336,
                                 0.55557023301960218,
                                 0.51410274419322166,
                                 0.47139673682599764,
                                 0.42755509343028208,
                                 0.38268343236508978,
                                 0.33688985339222005,
                                 0.29028467725446233,
                                 0.24298017990326387,
                                 0.19509032201612825,
                                 0.14673047445536175,
                                 0.0980171403295606,
                                 0.049067674327418015};
  static const signed char iv[60] = {
      1,  60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47,
      46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32,
      31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17,
      16, 15, 14, 13, 12, 11, 10, 9,  8,  7,  6,  5,  4,  3,  2};
  creal_T fv[128];
  creal_T fy[128];
  creal_T ytmp[60];
  double re_tmp;
  double temp_im;
  double temp_re;
  double temp_re_tmp;
  double twid_im;
  double twid_re;
  int i;
  int iDelta;
  int iDelta2;
  int iheight;
  int istart;
  int iy;
  int ju;
  int k;
  int temp_re_tmp_tmp;
  boolean_T tst;
  for (istart = 0; istart < 60; istart++) {
    iy = istart << 1;
    twid_re = x[iy];
    twid_im = x[iy + 1];
    temp_re_tmp = wwc[istart + 59].re;
    re_tmp = wwc[istart + 59].im;
    ytmp[istart].re = temp_re_tmp * twid_re + re_tmp * twid_im;
    ytmp[istart].im = temp_re_tmp * twid_im - re_tmp * twid_re;
  }
  memset(&fy[0], 0, 128U * sizeof(creal_T));
  iy = 0;
  ju = 0;
  for (i = 0; i < 59; i++) {
    fy[iy] = ytmp[i];
    istart = 128;
    tst = true;
    while (tst) {
      istart >>= 1;
      ju ^= istart;
      tst = ((ju & istart) == 0);
    }
    iy = ju;
  }
  fy[iy] = ytmp[59];
  for (i = 0; i <= 126; i += 2) {
    temp_re_tmp = fy[i + 1].re;
    temp_im = fy[i + 1].im;
    re_tmp = fy[i].re;
    temp_re = fy[i].im;
    fy[i + 1].re = re_tmp - temp_re_tmp;
    fy[i + 1].im = temp_re - temp_im;
    fy[i].re = re_tmp + temp_re_tmp;
    fy[i].im = temp_re + temp_im;
  }
  iDelta = 2;
  iDelta2 = 4;
  k = 32;
  iheight = 125;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      istart = i + iDelta;
      temp_re = fy[istart].re;
      temp_im = fy[istart].im;
      fy[istart].re = fy[i].re - temp_re;
      fy[istart].im = fy[i].im - temp_im;
      fy[i].re += temp_re;
      fy[i].im += temp_im;
    }
    istart = 1;
    for (iy = k; iy < 64; iy += k) {
      twid_re = dv[iy];
      twid_im = dv1[iy];
      i = istart;
      ju = istart + iheight;
      while (i < ju) {
        temp_re_tmp_tmp = i + iDelta;
        temp_re_tmp = fy[temp_re_tmp_tmp].im;
        temp_im = fy[temp_re_tmp_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        fy[temp_re_tmp_tmp].re = fy[i].re - temp_re;
        fy[temp_re_tmp_tmp].im = fy[i].im - temp_im;
        fy[i].re += temp_re;
        fy[i].im += temp_im;
        i += iDelta2;
      }
      istart++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
  for (iy = 0; iy < 128; iy++) {
    re_tmp = fy[iy].re;
    temp_im = b_fv[iy].im;
    temp_re = fy[iy].im;
    temp_re_tmp = b_fv[iy].re;
    fy[iy].re = re_tmp * temp_re_tmp - temp_re * temp_im;
    fy[iy].im = re_tmp * temp_im + temp_re * temp_re_tmp;
  }
  iy = 0;
  ju = 0;
  for (i = 0; i < 127; i++) {
    fv[iy] = fy[i];
    istart = 128;
    tst = true;
    while (tst) {
      istart >>= 1;
      ju ^= istart;
      tst = ((ju & istart) == 0);
    }
    iy = ju;
  }
  fv[iy] = fy[127];
  for (i = 0; i <= 126; i += 2) {
    temp_re_tmp = fv[i + 1].re;
    temp_im = fv[i + 1].im;
    re_tmp = fv[i].re;
    temp_re = fv[i].im;
    fv[i + 1].re = re_tmp - temp_re_tmp;
    fv[i + 1].im = temp_re - temp_im;
    fv[i].re = re_tmp + temp_re_tmp;
    fv[i].im = temp_re + temp_im;
  }
  iDelta = 2;
  iDelta2 = 4;
  k = 32;
  iheight = 125;
  while (k > 0) {
    for (i = 0; i < iheight; i += iDelta2) {
      istart = i + iDelta;
      temp_re = fv[istart].re;
      temp_im = fv[istart].im;
      fv[istart].re = fv[i].re - temp_re;
      fv[istart].im = fv[i].im - temp_im;
      fv[i].re += temp_re;
      fv[i].im += temp_im;
    }
    istart = 1;
    for (iy = k; iy < 64; iy += k) {
      twid_re = dv[iy];
      twid_im = dv2[iy];
      i = istart;
      ju = istart + iheight;
      while (i < ju) {
        temp_re_tmp_tmp = i + iDelta;
        temp_re_tmp = fv[temp_re_tmp_tmp].im;
        temp_im = fv[temp_re_tmp_tmp].re;
        temp_re = twid_re * temp_im - twid_im * temp_re_tmp;
        temp_im = twid_re * temp_re_tmp + twid_im * temp_im;
        fv[temp_re_tmp_tmp].re = fv[i].re - temp_re;
        fv[temp_re_tmp_tmp].im = fv[i].im - temp_im;
        fv[i].re += temp_re;
        fv[i].im += temp_im;
        i += iDelta2;
      }
      istart++;
    }
    k /= 2;
    iDelta = iDelta2;
    iDelta2 += iDelta2;
    iheight -= iDelta;
  }
  for (iy = 0; iy < 128; iy++) {
    fv[iy].re *= 0.0078125;
    fv[iy].im *= 0.0078125;
  }
  for (k = 0; k < 60; k++) {
    temp_re_tmp = wwc[k + 59].re;
    re_tmp = fv[k + 59].im;
    temp_im = wwc[k + 59].im;
    temp_re = fv[k + 59].re;
    ytmp[k].re = temp_re_tmp * temp_re + temp_im * re_tmp;
    ytmp[k].im = temp_re_tmp * re_tmp - temp_im * temp_re;
  }
  for (i = 0; i < 60; i++) {
    double b_ytmp_re_tmp;
    double ytmp_re_tmp;
    temp_im = ytmp[i].re;
    temp_re = reconVar1[i].im;
    re_tmp = ytmp[i].im;
    twid_re = reconVar1[i].re;
    iy = iv[i] - 1;
    twid_im = ytmp[iy].re;
    temp_re_tmp = -ytmp[iy].im;
    ytmp_re_tmp = reconVar2[i].im;
    b_ytmp_re_tmp = reconVar2[i].re;
    y[i].re = 0.5 * ((temp_im * twid_re - re_tmp * temp_re) +
                     (twid_im * b_ytmp_re_tmp - temp_re_tmp * ytmp_re_tmp));
    y[i].im = 0.5 * ((temp_im * temp_re + re_tmp * twid_re) +
                     (twid_im * ytmp_re_tmp + temp_re_tmp * b_ytmp_re_tmp));
    y[i + 60].re = 0.5 * ((temp_im * b_ytmp_re_tmp - re_tmp * ytmp_re_tmp) +
                          (twid_im * twid_re - temp_re_tmp * temp_re));
    y[i + 60].im = 0.5 * ((temp_im * ytmp_re_tmp + re_tmp * b_ytmp_re_tmp) +
                          (twid_im * temp_re + temp_re_tmp * twid_re));
  }
}

/*
 * File trailer for FFTImplementationCallback.c
 *
 * [EOF]
 */
