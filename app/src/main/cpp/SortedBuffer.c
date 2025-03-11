/*
 * Prerelease License - for engineering feedback and testing purposes
 * only. Not for sale.
 * File: SortedBuffer.c
 *
 * MATLAB Coder version            : 24.1
 * C/C++ source code generated on  : 10-Mar-2025 15:14:10
 */

/* Include Files */
#include "SortedBuffer.h"
#include "analyse_periodecity_internal_types.h"
#include "eml_int_forloop_overflow_check.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <string.h>

/* Function Declarations */
static int SortedBuffer_locateElement(const double obj_buf[3], int obj_nbuf,
                                      double x);

/* Function Definitions */
/*
 * Arguments    : const double obj_buf[3]
 *                int obj_nbuf
 *                double x
 * Return Type  : int
 */
static int SortedBuffer_locateElement(const double obj_buf[3], int obj_nbuf,
                                      double x)
{
  int i;
  if ((obj_nbuf == 0) || (x < obj_buf[0])) {
    i = 0;
  } else if (x < obj_buf[obj_nbuf - 1]) {
    int ip1;
    int upper;
    i = 1;
    ip1 = 2;
    upper = obj_nbuf;
    while (upper > ip1) {
      int m;
      m = (i + upper) >> 1;
      if (x < obj_buf[m - 1]) {
        upper = m;
      } else {
        i = m;
        ip1 = m + 1;
      }
    }
  } else {
    i = obj_nbuf;
  }
  return i;
}

/*
 * Arguments    : coder_internal_SortedBuffer *obj
 *                double x
 * Return Type  : void
 */
void SortedBuffer_insert(coder_internal_SortedBuffer *obj, double x)
{
  int k;
  if (obj->nbuf < 3) {
    if (rtIsNaN(x)) {
      obj->nnans++;
    } else if (obj->nbuf == 0) {
      obj->buf[0] = x;
      obj->nbuf = 1;
    } else {
      int i;
      i = SortedBuffer_locateElement(obj->buf, obj->nbuf, x);
      if (i == 0) {
        int b_i;
        b_i = obj->nbuf;
        for (k = b_i; k >= 1; k--) {
          obj->buf[k] = obj->buf[k - 1];
        }
        obj->buf[0] = x;
        obj->nbuf++;
      } else if (i >= obj->nbuf) {
        obj->nbuf++;
        obj->buf[obj->nbuf - 1] = x;
      } else {
        int b_i;
        int i1;
        b_i = obj->nbuf;
        i1 = i + 1;
        for (k = b_i; k >= i1; k--) {
          obj->buf[k] = obj->buf[k - 1];
        }
        obj->buf[i] = x;
        obj->nbuf++;
      }
    }
  }
}

/*
 * Arguments    : const double obj_buf[3]
 *                int obj_nbuf
 *                int obj_nnans
 * Return Type  : double
 */
double SortedBuffer_median(const double obj_buf[3], int obj_nbuf, int obj_nnans)
{
  double m;
  if (obj_nnans > 0) {
    m = rtNaN;
  } else if (obj_nbuf == 0) {
    m = rtNaN;
  } else {
    int mid;
    mid = obj_nbuf >> 1;
    if ((obj_nbuf & 1) == 1) {
      m = obj_buf[mid];
    } else {
      double d;
      d = obj_buf[mid - 1];
      if (((d < 0.0) != (obj_buf[mid] < 0.0)) || rtIsInf(d)) {
        m = (d + obj_buf[mid]) / 2.0;
      } else {
        m = d + (obj_buf[mid] - d) / 2.0;
      }
    }
  }
  return m;
}

/*
 * Arguments    : coder_internal_SortedBuffer *obj
 *                double x
 * Return Type  : void
 */
void SortedBuffer_remove(coder_internal_SortedBuffer *obj, double x)
{
  int i;
  if (rtIsNaN(x)) {
    if (obj->nnans >= 1) {
      obj->nnans--;
    }
  } else if (obj->nbuf == 1) {
    if (x == obj->buf[0]) {
      obj->nbuf = 0;
    }
  } else {
    i = SortedBuffer_locateElement(obj->buf, obj->nbuf, x);
    if ((i > 0) && (x == obj->buf[i - 1])) {
      int a;
      int b;
      a = i + 1;
      b = obj->nbuf;
      if ((i + 1 <= obj->nbuf) && (obj->nbuf > 2147483646)) {
        check_forloop_overflow_error();
      }
      for (i = a; i <= b; i++) {
        obj->buf[i - 2] = obj->buf[i - 1];
      }
      obj->nbuf--;
    }
  }
}

/*
 * Arguments    : coder_internal_SortedBuffer *obj
 *                double xold
 *                double xnew
 * Return Type  : void
 */
void SortedBuffer_replace(coder_internal_SortedBuffer *obj, double xold,
                          double xnew)
{
  int k;
  if (rtIsNaN(xold)) {
    if (obj->nnans > 0) {
      obj->nnans--;
    }
    SortedBuffer_insert(obj, xnew);
  } else if (rtIsNaN(xnew)) {
    SortedBuffer_remove(obj, xold);
    obj->nnans++;
  } else {
    int iold;
    iold = SortedBuffer_locateElement(obj->buf, obj->nbuf, xold);
    if ((iold > 0) && (obj->buf[iold - 1] == xold)) {
      int inew;
      inew = SortedBuffer_locateElement(obj->buf, obj->nbuf, xnew);
      if (iold <= inew) {
        int i;
        i = inew - 1;
        for (k = iold; k <= i; k++) {
          obj->buf[k - 1] = obj->buf[k];
        }
        obj->buf[inew - 1] = xnew;
      } else if (iold == inew + 1) {
        obj->buf[iold - 1] = xnew;
      } else {
        int i;
        i = inew + 2;
        for (k = iold; k >= i; k--) {
          obj->buf[k - 1] = obj->buf[k - 2];
        }
        obj->buf[inew] = xnew;
      }
    } else {
      SortedBuffer_insert(obj, xnew);
    }
  }
}

/*
 * File trailer for SortedBuffer.c
 *
 * [EOF]
 */
