#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <stdio.h>
#include <string.h>

#include "menu.h"
#include "client.h"
#include "reservation.h"
#include "llist.h"

/**
 * The list of clients.
 */
llist *client_list;

/**
 * The list of reservations.
 */
llist *reservation_list;

/**
 * The list of pre-reservations.
 */
llist *pre_reservation_list;

/**
 * The main loop that runs the application's core.
 */
void main_loop();

#endif
