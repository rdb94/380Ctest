/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: LHS.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "LHS.h"
#include "analyse_periodecity_emxutil.h"
#include "analyse_periodecity_types.h"
#include "getCandidates.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *in1
 *                const emxArray_real_T *in2
 *                emxArray_real_T *in3
 *                emxArray_real_T *in4
 * Return Type  : void
 */
void binary_expand_op(const emxArray_real_T *in1, const emxArray_real_T *in2,
                      emxArray_real_T *in3, emxArray_real_T *in4)
{
  emxArray_real_T *b_in1;
  const double *in1_data;
  const double *in2_data;
  double *b_in1_data;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 2);
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = 201;
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
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < 201; i1++) {
      b_in1_data[i1 + b_in1->size[0] * i] =
          in1_data[i1 + 201 * aux_0_1] +
          in2_data[5 * i1 + in2->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  double dv[2];
  dv[0] = 70.0;
  dv[1] = 200.0;
  getCandidates(b_in1, dv, in3, in4);
  emxFree_real_T(&b_in1);
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 * Return Type  : void
 */
void binary_expand_op_1(emxArray_real_T *in1, const emxArray_real_T *in2)
{
  emxArray_real_T *b_in1;
  const double *in2_data;
  double *b_in1_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 2);
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = 201;
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
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < 201; i1++) {
      b_in1_data[i1 + 201 * i] = in1_data[i1 + 201 * aux_0_1] +
                                 in2_data[(i1 << 2) + in2->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = 201;
  in1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < 201; i1++) {
      stride_0_1 = i1 + 201 * i;
      in1_data[stride_0_1] = b_in1_data[stride_0_1];
    }
  }
  emxFree_real_T(&b_in1);
}

/*
 * Arguments    : emxArray_real_T *in1
 *                const emxArray_real_T *in2
 * Return Type  : void
 */
void binary_expand_op_2(emxArray_real_T *in1, const emxArray_real_T *in2)
{
  emxArray_real_T *b_in1;
  const double *in2_data;
  double *b_in1_data;
  double *in1_data;
  int aux_0_1;
  int aux_1_1;
  int i;
  int i1;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  in2_data = in2->data;
  in1_data = in1->data;
  emxInit_real_T(&b_in1, 2);
  i = b_in1->size[0] * b_in1->size[1];
  b_in1->size[0] = 201;
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
  aux_0_1 = 0;
  aux_1_1 = 0;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < 201; i1++) {
      b_in1_data[i1 + 201 * i] = in1_data[i1 + 201 * aux_0_1] +
                                 in2_data[3 * i1 + in2->size[0] * aux_1_1];
    }
    aux_1_1 += stride_1_1;
    aux_0_1 += stride_0_1;
  }
  i = in1->size[0] * in1->size[1];
  in1->size[0] = 201;
  in1->size[1] = loop_ub;
  emxEnsureCapacity_real_T(in1, i);
  in1_data = in1->data;
  for (i = 0; i < loop_ub; i++) {
    for (i1 = 0; i1 < 201; i1++) {
      stride_0_1 = i1 + 201 * i;
      in1_data[stride_0_1] = b_in1_data[stride_0_1];
    }
  }
  emxFree_real_T(&b_in1);
}

/*
 * File trailer for LHS.c
 *
 * [EOF]
 */
