/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: eml_int_forloop_overflow_check.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "eml_int_forloop_overflow_check.h"
#include "analyse_periodecity_types.h"
#include "rt_nonfinite.h"
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static void jb_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                    int aLineNum);

/* Function Definitions */
/*
 * Arguments    : const char *r
 *                const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void jb_rtErrorWithMessageID(const char *r, const char *aFcnName,
                                    int aLineNum)
{
  fprintf(stderr,
          "The loop variable of class %.*s might overflow on the last "
          "iteration of the for loop. This could lead to an infinite loop.",
          5, r);
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void check_forloop_overflow_error(void)
{
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      87,                            /* lineNo */
      "check_forloop_overflow_error" /* fName */
  };
  jb_rtErrorWithMessageID("int32", n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
}

/*
 * File trailer for eml_int_forloop_overflow_check.c
 *
 * [EOF]
 */
