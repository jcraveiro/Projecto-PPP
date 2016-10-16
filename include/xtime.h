#ifndef XTIME_HEADER
#define XTIME_HEADER

#include <stdio.h>

/**
 * The xtime structure, used for all kinds of dates.
 */
typedef struct xtime
{
  int year, month, day;
  int hour, minute;
} xtime;

/**
 * Comparison function for two xtime instances.
 */
int xtime_comp(xtime*, xtime*);

/**
 * Validate a given xtime.
 */
int xtime_validate(xtime*);

#endif
