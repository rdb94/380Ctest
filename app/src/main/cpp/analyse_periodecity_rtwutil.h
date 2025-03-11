/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: analyse_periodecity_rtwutil.h
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

#ifndef ANALYSE_PERIODECITY_RTWUTIL_H
#define ANALYSE_PERIODECITY_RTWUTIL_H

/* Include Files */
#include "analyse_periodecity_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern int div_s32(int numerator, int denominator);

extern void emlrtDimSizeImpxCheckR2021b(const int aDim1, const int aDim2,
                                        const rtEqualityCheckInfo *aInfo);

extern void i_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void k_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void m_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void n_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void p_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void q_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void rtAddSizeString(char *aBuf, const int aDim);

extern void rtDivisionByZeroErrorN(void);

extern void rtDynamicBoundsError(int aIndexValue, int aLoBound, int aHiBound,
                                 const rtBoundsCheckInfo *aInfo);

extern void rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void rtGenSizeString(const int aNDims, const int *aDims, char *aBuf);

extern void rtIntegerError(const double aInteger,
                           const rtDoubleCheckInfo *aInfo);

extern boolean_T rtIsNullOrEmptyString(const char *aString);

extern void rtNonNegativeError(const double aPositive,
                               const rtDoubleCheckInfo *aInfo);

extern void rtReportErrorLocation(const char *aFcnName, int aLineNo);

extern void rtSizeEq1DError(const int aDim1, const int aDim2,
                            const rtEqualityCheckInfo *aInfo);

extern double rt_hypotd_snf(double u0, double u1);

extern double rt_powd_snf(double u0, double u1);

extern double rt_roundd_snf(double u);

extern void s_rtErrorWithMessageID(const int i, const char *r,
                                   const char *aFcnName, int aLineNum);

extern void t_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

extern void u_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for analyse_periodecity_rtwutil.h
 *
 * [EOF]
 */
