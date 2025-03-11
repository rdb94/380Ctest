/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: main.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "../../../../../../AndroidStudioProjects/380Ctest/app/src/main/cpp/analyse_periodecity.h"
#include "../../../../../../AndroidStudioProjects/380Ctest/app/src/main/cpp/analyse_periodecity_terminate.h"
#include "../../../../../../AndroidStudioProjects/380Ctest/app/src/main/cpp/analyse_periodecity_types.h"
#include "../../../../../../AndroidStudioProjects/380Ctest/app/src/main/cpp/calculate_HNR.h"
#include "../../../../../../AndroidStudioProjects/380Ctest/app/src/main/cpp/estimate_pitch_hps.h"
#include "../../../../../../AndroidStudioProjects/380Ctest/app/src/main/cpp/rt_nonfinite.h"
#include <stdio.h>
#include <string.h>

/* Function Declarations */
static void argInit_120x1_real_T(double result[120]);

static void argInit_20000x1_real_T(double result[20000]);

static void argInit_d1xd1_real_T(double result_data[], int result_size[2]);

static double argInit_real_T(void);

static void bb_rtErrorWithMessageID(const char *aFcnName, int aLineNum);

/* Function Definitions */
/*
 * Arguments    : double result[120]
 * Return Type  : void
 */
static void argInit_120x1_real_T(double result[120])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 120; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[20000]
 * Return Type  : void
 */
static void argInit_20000x1_real_T(double result[20000])
{
  int idx0;
  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 20000; idx0++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : double result_data[]
 *                int result_size[2]
 * Return Type  : void
 */
static void argInit_d1xd1_real_T(double result_data[], int result_size[2])
{
  /* Set the size of the array.
Change this size to the value that the application requires. */
  result_size[0] = 1;
  result_size[1] = 1;
  /* Loop over the array to initialize each element. */
  result_data[0] = argInit_real_T();
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : const char *aFcnName
 *                int aLineNum
 * Return Type  : void
 */
static void bb_rtErrorWithMessageID(const char *aFcnName, int aLineNum)
{
  fprintf(stderr, "Example main does not support command line arguments.");
  fprintf(stderr, "\n");
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNum);
  fprintf(stderr, "\n");
  fflush(stderr);
  abort();
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  static rtRunTimeErrorInfo n_emlrtRTEI = {
      1,                    /* lineNo */
      "analyse_periodecity" /* fName */
  };
  (void)argv;
  if (argc > 1) {
    bb_rtErrorWithMessageID(n_emlrtRTEI.fName, n_emlrtRTEI.lineNo);
  }
  /* The initialize function is being called automatically from your entry-point
   * function. So, a call to initialize is not included here. */
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_analyse_periodecity();
  main_calculate_HNR();
  main_estimate_pitch_hps();
  /* Terminate the application.
You do not need to do this more than one time. */
  analyse_periodecity_terminate();
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void main_analyse_periodecity(void)
{
  static double dv[20000];
  double Fs_data;
  double jitt;
  double shim;
  int Fs_size[2];
  /* Initialize function 'analyse_periodecity' input arguments. */
  /* Initialize function input argument 'y'. */
  /* Initialize function input argument 'Fs'. */
  argInit_d1xd1_real_T((double *)&Fs_data, Fs_size);
  /* Call the entry-point 'analyse_periodecity'. */
  argInit_20000x1_real_T(dv);
  analyse_periodecity(dv, (double *)&Fs_data, Fs_size, &jitt, &shim);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void main_calculate_HNR(void)
{
  static double dv[20000];
  double hnr;
  /* Initialize function 'calculate_HNR' input arguments. */
  /* Initialize function input argument 'signal'. */
  /* Call the entry-point 'calculate_HNR'. */
  argInit_20000x1_real_T(dv);
  hnr = calculate_HNR(dv, argInit_real_T());
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void main_estimate_pitch_hps(void)
{
  double dv[120];
  double fs_data;
  int fs_size[2];
  /* Initialize function 'estimate_pitch_hps' input arguments. */
  /* Initialize function input argument 'segment'. */
  /* Initialize function input argument 'fs'. */
  argInit_d1xd1_real_T((double *)&fs_data, fs_size);
  /* Call the entry-point 'estimate_pitch_hps'. */
  argInit_120x1_real_T(dv);
  fs_data = estimate_pitch_hps(dv, (double *)&fs_data, fs_size);
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
