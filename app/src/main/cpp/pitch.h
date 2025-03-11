/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: pitch.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef PITCH_H
#define PITCH_H

/* Include Files */
#include "analyse_periodecity_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void pitch(const double x[20000], const double fs_data[], const int fs_size[2],
           const double options_WindowLength_data[],
           const int options_WindowLength_size[2],
           const double options_OverlapLength_data[],
           const int options_OverlapLength_size[2],
           emxArray_real_T *varargout_1, emxArray_real_T *varargout_2);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for pitch.h
 *
 * [EOF]
 */
