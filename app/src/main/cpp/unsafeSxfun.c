/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: unsafeSxfun.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "unsafeSxfun.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : emxArray_real_T *in1
 *                const double in3[20000]
 *                int in4
 *                int in5
 *                const emxArray_real_T *in6
 * Return Type  : void
 */
void binary_expand_op_11(emxArray_real_T *in1, const double in3[20000], int in4,
                         int in5, const emxArray_real_T *in6)
{
  emxArray_real_T *b_in3;
  const double *in6_data;
  double *in1_data;
  double *in3_data;
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  in6_data = in6->data;
  emxInit_real_T(&b_in3, 1);
  i = in5 - in4;
  if (in6->size[0] == 1) {
    loop_ub = i;
  } else {
    loop_ub = in6->size[0];
  }
  stride_0_0 = b_in3->size[0];
  b_in3->size[0] = loop_ub;
  emxEnsureCapacity_real_T(b_in3, stride_0_0);
  in3_data = b_in3->data;
  stride_0_0 = (i != 1);
  stride_1_0 = (in6->size[0] != 1);
  for (i = 0; i < loop_ub; i++) {
    in3_data[i] = in3[in4 + i * stride_0_0] - in6_data[i * stride_1_0];
  }
  i = in1->size[0];
  in1->size[0] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  for (i = 0; i < loop_ub; i++) {
    double varargin_1;
    varargin_1 = in3_data[i];
    in1_data[i] = rt_powd_snf(varargin_1, 2.0);
  }
  emxFree_real_T(&b_in3);
}

/*
 * File trailer for unsafeSxfun.c
 *
 * [EOF]
 */
