/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: ifft.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef IFFT_H
#define IFFT_H

/* Include Files */
#include "analyse_periodecity_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_ifft(const emxArray_creal_T *x, emxArray_creal_T *y);

void ifft(const emxArray_real_T *x, emxArray_creal_T *y);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for ifft.h
 *
 * [EOF]
 */
