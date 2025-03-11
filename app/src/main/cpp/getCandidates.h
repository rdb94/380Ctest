/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: getCandidates.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef GETCANDIDATES_H
#define GETCANDIDATES_H

/* Include Files */
#include "analyse_periodecity_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void getCandidates(const emxArray_real_T *domain, const double edge[2],
                   emxArray_real_T *peaks, emxArray_real_T *locs);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for getCandidates.h
 *
 * [EOF]
 */
