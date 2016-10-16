#ifndef RESERVATION_HEADER
#define RESERVATION_HEADER

#include <stdlib.h>
#include <time.h>

#include "reservation_struct.h"
#include "pre_reservation.h"
#include "client.h"
#include "llist.h"
#include "xtime.h"
#include "colors.h"
#include "main.h"

/**
 * Lavagem.
 */
#define RESERVATION_TYPE_CLEANING 1

/**
 * Manutenção.
 */
#define RESERVATION_TYPE_CHECKING 2

/**
 * Reserva.
 */
#define RESERVA 3

/**
 * Pré-Reserva.
 */
#define PRE_RESERVA 4

/**
 * Allocates memory for and returns a new instance of a reservation.
 */
reservation *reservation_new(client*, int);

/**
 * Converts a reservation type as a character to the corresponding integer.
 */
int reservation_type_str_to_int(char*, int*);

/**
 * Prints the information of a given reservation.
 */
void reservation_print(reservation*);

/**
 * Recursive function to list each reservation.
 */
void reservation_listing(lnode*, int);

/**
 * Handles users asking to list all the reservations.
 */
int reservation_request_listing(llist*);

/**
 * Handles users asking to make a new reservation.
 */
int reservation_request_new(llist*, llist*, llist*);

/**
 * Handles users asking to cancel a reservation.
 */
int reservation_request_cancel(llist*);

/**
 * Writes reservations to file.
 */
void write_reservations(char*, llist*);

/**
 * Reads reservations from file.
 */
void read_reservation(char*, llist*, llist*);

/**
 * Recursive bubble sort function for reservations.
 */
lnode *_reservation_sort_rec(lnode*, int);

/**
 * Sorts a list of reservations.
 */
void reservation_sort(llist*, int);

/**
 * Function to check the reservation type input.
 */
int reservation_type_check(int*, char*);

/**
 * Function that checks the input of the order in which the reservations will be displayed.
 */
int reservation_request_check(int*, char*);

/**
 * Function that removes outdated reservations
 */
void reservation_remove_outdated(llist*);

/**
 * Returns the duration in minutes of a reservation according to its type in the statement.
 */
int reservation_get_duration_mins(reservation*);

/**
 * Finds out whether a given time collides with any reservation.
 */
reservation *reservation_any_collision(reservation*, llist*);

/**
 * Function to protect the input of the option pre-reservation/change date.
 */
int pre_reservation_request_check(char*);

/**
 * Updates pre reservations into the reservation list if possible. This function should be
 * called after any removal either from the reservation or the pre reservation list.
 */
void reservation_update_pre_reservations(llist*, llist*);

/**
 * Lists all reservations of a given client.
 */
void reservation_list_reservations_by_client(client*, llist*, int);

#endif
