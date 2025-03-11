/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: SRH.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef SRH_H
#define SRH_H

/* Include Files */
#include "analyse_periodecity_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void SRH(emxArray_real_T *y, double fs, double params_WindowLength,
         double params_OverlapLength, emxArray_real_T *f0);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for SRH.h
 *
 * [EOF]
 */
