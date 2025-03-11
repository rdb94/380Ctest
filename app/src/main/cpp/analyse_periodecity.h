/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: analyse_periodecity.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef ANALYSE_PERIODECITY_H
#define ANALYSE_PERIODECITY_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void analyse_periodecity(const double y[20000], const double Fs_data[],
                                const int Fs_size[2], double *jitt,
                                double *shim);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for analyse_periodecity.h
 *
 * [EOF]
 */
