#include "pre_reservation.h"


int pre_reservation_request_new(llist *pre_reservation_list, reservation *request)
{
  /* reservation *request is the original reservation */

  llist_insert(pre_reservation_list, request);
  write_reservations("pre_reservations.txt", pre_reservation_list);
  return 0;
}
