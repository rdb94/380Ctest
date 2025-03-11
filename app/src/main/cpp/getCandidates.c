/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: getCandidates.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "getCandidates.h"
#include "analyse_periodecity_data.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "colon.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *domain
 *                const double edge[2]
 *                emxArray_real_T *peaks
 *                emxArray_real_T *locs
 * Return Type  : void
 */
void getCandidates(const emxArray_real_T *domain, const double edge[2],
                   emxArray_real_T *peaks, emxArray_real_T *locs)
{
  static rtBoundsCheckInfo c_emlrtBCI = {
      -1,              /* iFirst */
      -1,              /* iLast */
      38,              /* lineNo */
      32,              /* colNo */
      "",              /* aName */
      "getCandidates", /* fName */
      "C:\\Program "
      "Files\\MATLAB\\R2024a\\toolbox\\audio\\audio\\+audio\\+internal\\+"
      "pitch\\getCandidates.m", /* pName */
      0                         /* checkKind */
  };
  static rtDoubleCheckInfo e_emlrtDCI = {
      38,             /* lineNo */
      "getCandidates" /* fName */
  };
  emxArray_int32_T *idx;
  emxArray_real_T *ex;
  emxArray_real_T *range;
  const double *domain_data;
  double a;
  double *ex_data;
  double *locs_data;
  double *peaks_data;
  double *range_data;
  int i;
  int loop_ub;
  int loop_ub_tmp;
  int n_tmp;
  int *idx_data;
  domain_data = domain->data;
  emxInit_real_T(&range, 2);
  range_data = range->data;
  if (rtIsNaN(edge[0]) || rtIsNaN(edge[1])) {
    i = range->size[0] * range->size[1];
    range->size[0] = 1;
    range->size[1] = 1;
    emxEnsureCapacity_real_T(range, i);
    range_data = range->data;
    range_data[0] = rtNaN;
  } else if (edge[1] < edge[0]) {
    range->size[0] = 1;
    range->size[1] = 0;
  } else if ((rtIsInf(edge[0]) || rtIsInf(edge[1])) && (edge[0] == edge[1])) {
    i = range->size[0] * range->size[1];
    range->size[0] = 1;
    range->size[1] = 1;
    emxEnsureCapacity_real_T(range, i);
    range_data = range->data;
    range_data[0] = rtNaN;
  } else if (floor(edge[0]) == edge[0]) {
    i = range->size[0] * range->size[1];
    range->size[0] = 1;
    loop_ub = (int)(edge[1] - edge[0]);
    range->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(range, i);
    range_data = range->data;
    for (i = 0; i <= loop_ub; i++) {
      range_data[i] = edge[0] + (double)i;
    }
  } else {
    eml_float_colon(edge[0], edge[1], range);
    range_data = range->data;
  }
  loop_ub_tmp = range->size[1];
  for (i = 0; i < loop_ub_tmp; i++) {
    if (range_data[i] != (int)floor(range_data[i])) {
      rtIntegerError(range_data[i], &e_emlrtDCI);
    }
    loop_ub = (int)range_data[i];
    if ((loop_ub < 1) || (loop_ub > domain->size[0])) {
      rtDynamicBoundsError(loop_ub, 1, domain->size[0], &c_emlrtBCI);
    }
  }
  if (range->size[1] < 1) {
    q_rtErrorWithMessageID(i_emlrtRTEI.fName, i_emlrtRTEI.lineNo);
  }
  n_tmp = domain->size[1];
  emxInit_real_T(&ex, 2);
  i = ex->size[0] * ex->size[1];
  ex->size[0] = 1;
  ex->size[1] = domain->size[1];
  emxEnsureCapacity_real_T(ex, i);
  ex_data = ex->data;
  emxInit_int32_T(&idx, 2);
  i = idx->size[0] * idx->size[1];
  idx->size[0] = 1;
  idx->size[1] = domain->size[1];
  emxEnsureCapacity_int32_T(idx, i);
  idx_data = idx->data;
  for (i = 0; i < n_tmp; i++) {
    idx_data[i] = 1;
  }
  if (domain->size[1] >= 1) {
    boolean_T overflow;
    if (domain->size[1] > 2147483646) {
      check_forloop_overflow_error();
    }
    overflow = (range->size[1] > 2147483646);
    for (loop_ub = 0; loop_ub < n_tmp; loop_ub++) {
      ex_data[loop_ub] =
          domain_data[((int)range_data[0] + domain->size[0] * loop_ub) - 1];
      if (overflow) {
        check_forloop_overflow_error();
      }
      for (i = 2; i <= loop_ub_tmp; i++) {
        double b_tmp;
        boolean_T p;
        a = ex_data[loop_ub];
        b_tmp =
            domain_data[((int)range_data[i - 1] + domain->size[0] * loop_ub) -
                        1];
        if (rtIsNaN(b_tmp)) {
          p = false;
        } else if (rtIsNaN(a)) {
          p = true;
        } else {
          p = (a < b_tmp);
        }
        if (p) {
          ex_data[loop_ub] = b_tmp;
          idx_data[loop_ub] = i;
        }
      }
    }
  }
  i = range->size[0] * range->size[1];
  range->size[0] = 1;
  range->size[1] = domain->size[1];
  emxEnsureCapacity_real_T(range, i);
  range_data = range->data;
  for (i = 0; i < n_tmp; i++) {
    range_data[i] = idx_data[i];
  }
  emxFree_int32_T(&idx);
  a = edge[0];
  i = locs->size[0];
  locs->size[0] = domain->size[1];
  emxEnsureCapacity_real_T(locs, i);
  locs_data = locs->data;
  i = peaks->size[0];
  peaks->size[0] = domain->size[1];
  emxEnsureCapacity_real_T(peaks, i);
  peaks_data = peaks->data;
  loop_ub = (range->size[1] / 2) << 1;
  loop_ub_tmp = loop_ub - 2;
  for (i = 0; i <= loop_ub_tmp; i += 2) {
    __m128d r;
    r = _mm_loadu_pd(&range_data[i]);
    _mm_storeu_pd(&locs_data[i],
                  _mm_sub_pd(_mm_add_pd(_mm_set1_pd(a), r), _mm_set1_pd(1.0)));
    r = _mm_loadu_pd(&ex_data[i]);
    _mm_storeu_pd(&peaks_data[i], r);
  }
  for (i = loop_ub; i < n_tmp; i++) {
    locs_data[i] = (a + range_data[i]) - 1.0;
    peaks_data[i] = ex_data[i];
  }
  emxFree_real_T(&ex);
  emxFree_real_T(&range);
}

/*
 * File trailer for getCandidates.c
 *
 * [EOF]
 */
