#ifndef RESERVATION_STRUCT_HEADER
#define RESERVATION_STRUCT_HEADER

#include "client.h"

/**
 * The reservation structure that holds reservations.
 */
typedef struct reservation
{
  client *client;

  int type;
  int reservation_type;

  xtime register_time;
  xtime actual_time;
} reservation;

#endif
