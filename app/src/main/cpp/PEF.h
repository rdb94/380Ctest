/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: PEF.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef PEF_H
#define PEF_H

/* Include Files */
#include "analyse_periodecity_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void PEF(const emxArray_real_T *y, double fs, const double params_Range[2],
         double params_WindowLength, emxArray_real_T *f0);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for PEF.h
 *
 * [EOF]
 */
