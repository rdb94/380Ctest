/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: FFTImplementationCallback.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

/* Include Files */
#include "analyse_periodecity_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void c_FFTImplementationCallback_dob(const emxArray_real_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y);

void c_FFTImplementationCallback_gen(int nRows, boolean_T useRadix2,
                                     emxArray_real_T *costab,
                                     emxArray_real_T *sintab,
                                     emxArray_real_T *sintabinv);

int c_FFTImplementationCallback_get(int nfft, boolean_T useRadix2, int *nRows);

void c_FFTImplementationCallback_r2b(const emxArray_real_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y);

void d_FFTImplementationCallback_dob(const emxArray_real_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y);

void d_FFTImplementationCallback_gen(int nRows, boolean_T useRadix2,
                                     emxArray_real_T *costab,
                                     emxArray_real_T *sintab,
                                     emxArray_real_T *sintabinv);

void e_FFTImplementationCallback_dob(const emxArray_real_T *x, int n2blue,
                                     int nfft, const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     const emxArray_real_T *sintabinv,
                                     emxArray_creal_T *y);

void e_FFTImplementationCallback_r2b(const emxArray_creal_T *x,
                                     int unsigned_nRows,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y);

void f_FFTImplementationCallback_gen(int nRows, boolean_T useRadix2,
                                     emxArray_real_T *costab,
                                     emxArray_real_T *sintab,
                                     emxArray_real_T *sintabinv);

void f_FFTImplementationCallback_r2b(const emxArray_real_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y);

void g_FFTImplementationCallback_r2b(const emxArray_real_T *x, int n1_unsigned,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab,
                                     emxArray_creal_T *y);

void h_FFTImplementationCallback_doH(const double x[120], creal_T y[120]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for FFTImplementationCallback.h
 *
 * [EOF]
 */
