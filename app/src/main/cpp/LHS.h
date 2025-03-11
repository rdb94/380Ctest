/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: LHS.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef LHS_H
#define LHS_H

/* Include Files */
#include "analyse_periodecity_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void binary_expand_op(const emxArray_real_T *in1, const emxArray_real_T *in2,
                      emxArray_real_T *in3, emxArray_real_T *in4);

void binary_expand_op_1(emxArray_real_T *in1, const emxArray_real_T *in2);

void binary_expand_op_2(emxArray_real_T *in1, const emxArray_real_T *in2);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for LHS.h
 *
 * [EOF]
 */
