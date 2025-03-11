/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: analyse_periodecity_rtwutil.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "analyse_periodecity_rtwutil.h"
#include "analyse_periodecity_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : int numerator
 *                int denominator
 * Return Type  : int
 */
int div_s32(int numerator, int denominator)
{
  int quotient;
  if (denominator == 0) {
    rtDivisionByZeroErrorN();
  } else {
    unsigned int tempAbsQuotient;
    unsigned int u;
    if (numerator < 0) {
      tempAbsQuotient = ~(unsigned int)numerator + 1U;
    } else {
      tempAbsQuotient = (unsigned int)numerator;
    }
    if (denominator < 0) {
      u = ~(unsigned int)denominator + 1U;
    } else {
      u = (unsigned int)denominator;
    }
    tempAbsQuotient /= u;
    if ((numerator < 0) != (denominator < 0)) {
      quotient = -(int)tempAbsQuotient;
    } else {
      quotient = (int)tempAbsQuotient;
    }
  }
  return quotient;
}

/*
 * Arguments    : const int aDim1
 *                const int aDim2
 *                const rtEqualityCheckInfo *aInfo
 * Return Type  : void
 */
void emlrtDimSizeImpxCheckR2021b(const int aDim1, const int aDim2,
                                 const rtEqualityCheckInfo *aInfo)
{
  fprintf(stderr,
          "Size mismatch error on dimension %d: expected %d or a singleton, "
          "but actual size is %d.",
          aInfo->nDims, aDim1, aDim2);
  fprintf(stderr, "\n");
  rtReportErrorLocation(aInfo->fName, aInfo->lineNo);
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
void i_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Maximum variable size allowed by the program is exceeded.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
void k_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Argument must be integer-valued.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
void m_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Non-singleton dimensions of the two input arrays must match "
                  "each other.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
void n_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "FFT length must be a nonnegative integer scalar.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
void o_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr,
          "Requested array exceeds the maximum possible variable size.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
void p_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Assertion failed.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
void q_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "If the working dimension of MAX or MIN is variable in "
                  "length, it must not have zero length at runtime.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : char *aBuf
 *                const int aDim
 * Return Type  : void
 */
void rtAddSizeString(char *aBuf, const int aDim)
{
  char b_dimStr[1024];
  char dimStr[1024];
  snprintf(&dimStr[0], 1024U, "[%d]", aDim);
  if (strlen(&aBuf[0]) + strlen(&dimStr[0]) < 1024) {
    memcpy(&b_dimStr[0], &dimStr[0], 1024U * sizeof(char));
    strcat(aBuf, b_dimStr);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void rtDivisionByZeroErrorN(void)
{
  fprintf(
      stderr,
      "Division by zero detected.\nEarly termination due to division by zero.");
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : int aIndexValue
 *                int aLoBound
 *                int aHiBound
 *                const rtBoundsCheckInfo *aInfo
 * Return Type  : void
 */
void rtDynamicBoundsError(int aIndexValue, int aLoBound, int aHiBound,
                          const rtBoundsCheckInfo *aInfo)
{
  if (aLoBound == 0) {
    aIndexValue++;
    aLoBound = 1;
    aHiBound++;
  }
  if (rtIsNullOrEmptyString(aInfo->aName)) {
    fprintf(stderr,
            "Index exceeds array dimensions. Index value %d exceeds valid "
            "range [%d-%d].",
            aIndexValue, aLoBound, aHiBound);
    fprintf(stderr, "\n");
    rtReportErrorLocation(aInfo->fName, aInfo->lineNo);
    fflush(stderr);
    abort();
  } else {
    fprintf(stderr,
            "Index exceeds array dimensions. Index value %d exceeds valid "
            "range [%d-%d] for array \'%s\'.",
            aIndexValue, aLoBound, aHiBound, aInfo->aName);
    fprintf(stderr, "\n");
    rtReportErrorLocation(aInfo->fName, aInfo->lineNo);
    fflush(stderr);
    abort();
  }
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
void rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr,
          "The dimension to operate along was selected automatically, is "
          "variable-length, and has length 1 at run time. This is not support"
          "ed. Manually select the dimension to operate along by supplying the "
          "DIM argument.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const int aNDims
 *                const int *aDims
 *                char *aBuf
 * Return Type  : void
 */
void rtGenSizeString(const int aNDims, const int *aDims, char *aBuf)
{
  int i;
  aBuf[0] = '\x00';
  for (i = 0; i < aNDims; i++) {
    rtAddSizeString(aBuf, aDims[i]);
  }
}

/*
 * Arguments    : const double aInteger
 *                const rtDoubleCheckInfo *aInfo
 * Return Type  : void
 */
void rtIntegerError(const double aInteger, const rtDoubleCheckInfo *aInfo)
{
  fprintf(
      stderr,
      "Expected a value representable in the C type \'int\'. Found %g instead.",
      aInteger);
  fprintf(stderr, "\n");
  rtReportErrorLocation(aInfo->fName, aInfo->lineNo);
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aString
 * Return Type  : boolean_T
 */
boolean_T rtIsNullOrEmptyString(const char *aString)
{
  return (aString == NULL) || (*aString == '\x00');
}

/*
 * Arguments    : const double aPositive
 *                const rtDoubleCheckInfo *aInfo
 * Return Type  : void
 */
void rtNonNegativeError(const double aPositive, const rtDoubleCheckInfo *aInfo)
{
  fprintf(stderr,
          "Value %g is not greater than or equal to zero.\nExiting to prevent "
          "memory corruption.",
          aPositive);
  fprintf(stderr, "\n");
  rtReportErrorLocation(aInfo->fName, aInfo->lineNo);
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNo
 * Return Type  : void
 */
void rtReportErrorLocation(const char *aFcnName, int aLineNo)
{
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNo);
  fprintf(stderr, "\n");
}

/*
 * Arguments    : const int aDim1
 *                const int aDim2
 *                const rtEqualityCheckInfo *aInfo
 * Return Type  : void
 */
void rtSizeEq1DError(const int aDim1, const int aDim2,
                     const rtEqualityCheckInfo *aInfo)
{
  fprintf(stderr, "Sizes mismatch: %d ~= %d.", aDim1, aDim2);
  fprintf(stderr, "\n");
  rtReportErrorLocation(aInfo->fName, aInfo->lineNo);
  fflush(stderr);
  abort();
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
double rt_hypotd_snf(double u0, double u1)
{
  double a;
  double b;
  double y;
  a = fabs(u0);
  b = fabs(u1);
  if (a < b) {
    a /= b;
    y = b * sqrt(a * a + 1.0);
  } else if (a > b) {
    b /= a;
    y = a * sqrt(b * b + 1.0);
  } else if (rtIsNaN(b)) {
    y = rtNaN;
  } else {
    y = a * 1.4142135623730951;
  }
  return y;
}

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
double rt_powd_snf(double u0, double u1)
{
  double y;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else {
    double d;
    double d1;
    d = fabs(u0);
    d1 = fabs(u1);
    if (rtIsInf(u1)) {
      if (d == 1.0) {
        y = 1.0;
      } else if (d > 1.0) {
        if (u1 > 0.0) {
          y = rtInf;
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = rtInf;
      }
    } else if (d1 == 0.0) {
      y = 1.0;
    } else if (d1 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > floor(u1))) {
      y = rtNaN;
    } else {
      y = pow(u0, u1);
    }
  }
  return y;
}

/*
 * Arguments    : double u
 * Return Type  : double
 */
double rt_roundd_snf(double u)
{
  double y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }
  return y;
}

/*
 * Arguments    : const int i
 *                const char *r
 *                const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
void s_rtErrorWithMessageID(const int i, const char *r, const char *aFcnName,
                            int aLineNum)
{
  fprintf(stderr,
          "Domain error. To compute complex results from real x, use "
          "\'%.*s(complex(x))\'.",
          i, r);
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
void t_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr,
          "Dimensions of arrays being concatenated are not consistent.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
void u_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr,
          "The number of points N must be a positive integer and real.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * File trailer for analyse_periodecity_rtwutil.c
 *
 * [EOF]
 */
