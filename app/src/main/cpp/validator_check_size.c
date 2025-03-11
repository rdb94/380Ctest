/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: validator_check_size.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "validator_check_size.h"
#include "analyse_periodecity_types.h"
#include "rt_nonfinite.h"
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static void e_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

static void gb_rtErrorWithMessageID(const long long i, const long long i1,
                                    const char *aFcnName, int aLineNum);

/* Function Definitions */
/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void e_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr,
          "Number of elements must not change. Use [] as one of the size "
          "inputs to automatically calculate the appropriate size for that di"
          "mension.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const long long i
 *                const long long i1
 *                const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void gb_rtErrorWithMessageID(const long long i, const long long i1,
                                    const char *aFcnName, int aLineNum)
{
  fprintf(stderr,
          "Validation size mismatch: input size %lld ~= allowed size %d for "
          "dimension %lld.",
          i, 1, i1);
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : const double in_data[]
 *                const int in_size[2]
 * Return Type  : double
 */
double validator_check_size(const double in_data[], const int in_size[2])
{
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      168,              /* lineNo */
      "expandOrReshape" /* fName */
  };
  static rtRunTimeErrorInfo o_emlrtRTEI = {
      223,              /* lineNo */
      "expandOrReshape" /* fName */
  };
  double out;
  if ((in_size[0] != 1) || (in_size[1] != 1)) {
    if (in_size[0] != 1) {
      gb_rtErrorWithMessageID(in_size[0], 1LL, n_emlrtRTEI.fName,
                              n_emlrtRTEI.lineNo);
    }
    if (in_size[1] != 1) {
      gb_rtErrorWithMessageID(in_size[1], 2LL, n_emlrtRTEI.fName,
                              n_emlrtRTEI.lineNo);
    }
  }
  if ((in_size[0] == 0) || (in_size[1] == 0)) {
    e_rtErrorWithMessageID(o_emlrtRTEI.fName, o_emlrtRTEI.lineNo);
  } else {
    out = in_data[0];
  }
  return out;
}

/*
 * File trailer for validator_check_size.c
 *
 * [EOF]
 */
