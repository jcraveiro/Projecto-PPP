#ifndef PRE_RESERVATION_HEADER
#define PRE_RESERVATION_HEADER

#include "llist.h"
#include "reservation_struct.h"
#include "reservation.h"

int pre_reservation_request_new(llist*, reservation*);

/**
 * Writes the pre_reservations to a file.
 */
void write_pre_reservations(char*, llist*);

/**
 * Reads the pre_reservations from a file to the structs.
 */
void read_pre_reservation(char*, llist*, llist*);

#endif
