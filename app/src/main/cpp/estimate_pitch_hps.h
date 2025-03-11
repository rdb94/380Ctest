/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: estimate_pitch_hps.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef ESTIMATE_PITCH_HPS_H
#define ESTIMATE_PITCH_HPS_H

/* Include Files */
#include "analyse_periodecity_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
double b_estimate_pitch_hps(const emxArray_real_T *segment, double fs);

extern double estimate_pitch_hps(const double segment[120],
                                 const double fs_data[], const int fs_size[2]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for estimate_pitch_hps.h
 *
 * [EOF]
 */
