/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: SortedBuffer.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef SORTEDBUFFER_H
#define SORTEDBUFFER_H

/* Include Files */
#include "analyse_periodecity_internal_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void SortedBuffer_insert(coder_internal_SortedBuffer *obj, double x);

double SortedBuffer_median(const double obj_buf[3], int obj_nbuf,
                           int obj_nnans);

void SortedBuffer_remove(coder_internal_SortedBuffer *obj, double x);

void SortedBuffer_replace(coder_internal_SortedBuffer *obj, double xold,
                          double xnew);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for SortedBuffer.h
 *
 * [EOF]
 */
