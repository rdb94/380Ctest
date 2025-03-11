/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: gencoswin.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef GENCOSWIN_H
#define GENCOSWIN_H

/* Include Files */
#include "analyse_periodecity_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void b_calc_window(double m, double n, emxArray_real_T *w);

void c_calc_window(double m, double n, emxArray_real_T *w);

void calc_window(double m, double n, emxArray_real_T *w);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for gencoswin.h
 *
 * [EOF]
 */
