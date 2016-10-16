#include "xtime.h"

int xtime_comp(xtime *a, xtime *b) // returns (a - b)
{
  int a_value = a->year * 525949 + a->month * 43829 + a->day * 1440 + a->hour * 60 + a->minute;
  int b_value = b->year * 525949 + b->month * 43829 + b->day * 1440 + b->hour * 60 + b->minute;

  return a_value - b_value;
}

int xtime_validate(xtime *a)
{
  if (a->year < 0)
  {
    return 1;
  }
  else if (!(a->month >=1 && a->month <= 12))
  {
    return 1;
  }
  else if (((a->month == 1 || a->month == 3 || a->month == 5 || a->month == 7 || a->month == 8 ||
             a->month == 10 || a->month == 12) && (!(a->day >= 1 && a->day <= 31))))
  {
    return 1;
  }
  else if ((a->month == 4 || a->month == 6 || a->month == 9 || a->month == 11) && (!(a->day >= 1 && a->day <= 30)))
  {
    return 1;
  }
  else if (((!(a->year % 4)) && (a->year % 100) ) || (!(a->year % 400)))
  {
    if ((a->month == 2) && (!(a->day >= 1 && a->day <= 29)))
    {
      return 1;
    }
  }
  else if (a->month == 2 && (!(a->day >= 1 && a->day <= 28)))
  {
    return 1;
  }
  else if (!(a->hour >= 8 && a->hour <= 17))
  {
    return 1;
  }
  else if (!(a->minute >= 0 && a->minute <= 59))
  {
    return 1;
  }

  return 0;
}
