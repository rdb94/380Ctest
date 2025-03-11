/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: indexShapeCheck.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "indexShapeCheck.h"
#include "analyse_periodecity_types.h"
#include "rt_nonfinite.h"
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static void l_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

/* Function Definitions */
/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void l_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr,
          "Invalid vector size. Expected to index a variable-size vector by a "
          "vector, but received a scalar indexed by a vector. To perform"
          " this index operation, vector orientations must match at code "
          "generation time or data array must not be a scalar at run time.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : int matrixSize
 *                const int indexSize[2]
 * Return Type  : void
 */
void indexShapeCheck(int matrixSize, const int indexSize[2])
{
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      122,          /* lineNo */
      "errOrWarnIf" /* fName */
  };
  if ((matrixSize == 1) && (indexSize[1] != 1)) {
    l_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
}

/*
 * File trailer for indexShapeCheck.c
 *
 * [EOF]
 */
