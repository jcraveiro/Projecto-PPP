#include "reservation.h"

reservation *reservation_new(client *client, int type)
{
  reservation *new_reservation = (reservation*) malloc(sizeof(reservation));
  new_reservation->client = client;
  new_reservation->type = type;
  return new_reservation;
}

int reservation_type_str_to_int(char *str, int *integer)
{
  if (!strcmp(str, "L"))
  {
    *integer = RESERVATION_TYPE_CLEANING;
    return 0;
  }
  else if (!strcmp(str, "M"))
  {
    *integer = RESERVATION_TYPE_CHECKING;
    return 0;
  }
  else
  {
    return 1;
  }
}

void reservation_print(reservation *which)
{
  printf("%sCliente: ", COLOR_CYAN);
  reset_color();
  printf("%s\n", which->client->name);

  char register_time_str[MAX_TIME_CHARS];
  time_to_str(&(which->register_time), register_time_str);

  printf("%sRegistada em: ", COLOR_CYAN);
  reset_color();
  printf("%s\n", register_time_str);

  char actual_time_str[MAX_TIME_CHARS];
  time_to_str(&(which->actual_time), actual_time_str);

  printf("%sData marcada: ", COLOR_CYAN);
  reset_color();
  printf("%s\n", actual_time_str);

  printf("%sTrata-se de uma: ", COLOR_CYAN);
  reset_color();

  if (which->type == RESERVATION_TYPE_CLEANING)
  {
    printf("lavagem.\n");
  }
  else if (which->type == RESERVATION_TYPE_CHECKING)
  {
    printf("manutenção.\n");
  }
  else
  {
    printf("ERRO.\n");
  }
}

void reservation_listing(lnode *where, int index)
{
  if (where == NULL)
  {
    return;
  }

  reservation *aux = where->value;

  if (aux->reservation_type == RESERVA)
  {
    printf("%sListando reserva número %d\n", COLOR_CYAN, index);
    reset_color();
  }
  else if (aux->reservation_type == PRE_RESERVA)
  {
    printf("%sListando pré-reserva número %d\n", COLOR_CYAN, index);
    reset_color();
  }

  reservation_print((reservation*) where->value);

  printf("\n");

  reservation_listing(where->next, index + 1);
}

int reservation_request_listing(llist *reservation_list)
{
  char which_order_str[MAX_CHAR];
  int reservation_sort_order = -1;

  /* Pre reservations are always listed in descendent order */
  if (((reservation*) reservation_list->root->value)->reservation_type == PRE_RESERVA)
  {
    clear_screen();
    reservation_listing(reservation_list->root, 1);
    return 0;
  }

  do
  {
    if (get_str_input("Deseja ordenar por mais recentes [R] ou mais antigas [A]?: ",
                      which_order_str, MAX_CHAR) == 2)
    {
      return 2;
    }
  } while (reservation_request_check(&reservation_sort_order, which_order_str));

  clear_screen();
  reservation_sort(reservation_list, reservation_sort_order);

  reservation_listing(reservation_list->root, 1);
  return 0;
}

int reservation_request_new(llist *reservation_list, llist *client_list, llist *pre_reservation_list)
{
  char request_client_name[MAX_NAME_SIZE];
  int aux;

  do
  {
    aux = get_str_input("Insira o nome do cliente: ", request_client_name, MAX_NAME_SIZE);

    if (aux == 2)
    {
      return 2;
    }
  } while (aux == 1);

  client *request_client;
  request_client = client_find_by_name(client_list, request_client_name);

  if (request_client == NULL)
  {
    request_client = client_new(request_client_name);
    llist_insert(client_list, request_client);
    write_client("clients.txt", client_list);
  }

  /* Asks the user for what type of a reservation it is. */
  int request_reservation_type = -1;
  char request_reservation_type_str[MAX_CHAR];

  do
  {
    if (get_str_input("Que tipo de serviço deseja, lavagem [L] ou manutenção [M]: ",
                      request_reservation_type_str, MAX_CHAR) == 2)
    {
      return 2;
    }
  } while (reservation_type_check(&request_reservation_type,
                                  request_reservation_type_str));

  reservation *request_reservation = reservation_new(request_client, request_reservation_type);

  /* Here i set the reservation type as reserva */
  request_reservation->reservation_type = 3;

  /* Get the current date for the registration date */
  time_t current_time = time(NULL);
  time_t_to_xtime(&(request_reservation->register_time), &current_time);

  /* Ask for desired date for the reservation */
  int date_aux;
  do
  {
    date_aux = ask_date(&(request_reservation->actual_time));

    if (date_aux == 2)
    {
      return 2;
    }
  } while (xtime_validate(&(request_reservation->actual_time)));


  if (xtime_comp(&(request_reservation->actual_time), &(request_reservation->register_time)) < 0)
  {
    clear_screen();
    printf("Não pode reservar para o passado.\n\n");
    return 1;
  }

  reservation *find_collision = reservation_any_collision(request_reservation, reservation_list);

  if (find_collision)
  {
    char collision_date[MAX_TIME_CHARS];
    char pre_reservation_decision_str[MAX_CHAR];
    time_to_str(&(find_collision->actual_time), collision_date);
    printf("Foi encontrada uma reserva que colide com a sua a começar às: %s\n", collision_date);

    do
    {
      get_str_input("Deseja [G]uardar a sua reserva na lista de pré-reservas ou [M]udar a data para outra que também lhe convenha: ",
                    pre_reservation_decision_str, MAX_CHAR);
    } while ((pre_reservation_request_check(pre_reservation_decision_str)));

    if (!strcmp(pre_reservation_decision_str, "G"))
    {
      request_reservation->reservation_type = PRE_RESERVA;
      pre_reservation_request_new(pre_reservation_list, request_reservation);
    }
    else if (!strcmp(pre_reservation_decision_str, "M"))
    {
      reservation_request_new(reservation_list, client_list, pre_reservation_list);
    }

    return 0;
  }

  llist_insert(reservation_list, request_reservation);
  write_reservations("reservations.txt", reservation_list);

  return 0;
}

int reservation_request_cancel(llist *reservation_list)
{
  printf("Listando todas as reservas.\n\n");

  if (reservation_request_listing(reservation_list) == 2)
  {
    return 2;
  }

  int which_reservation;
  if (get_int_input("Insira o número da reserva que deseja cancelar: ",
                    &which_reservation) == 2)
  {
    return 2;
  }

  if (which_reservation > llist_get_size(reservation_list) ||
      which_reservation < 1)
  {
    printf("Não existe um item correspondente ao número que escolheu.\n");
    return 1;
  }

  llist_remove_by_index(reservation_list, which_reservation - 1);
  write_reservations("reservations.txt", reservation_list);
  write_reservations("pre_reservations.txt", pre_reservation_list);

  return 0;
}

void write_reservations(char *file, llist *reservation_list)
{
  FILE *fp;
  reservation *aux;
  lnode *where = reservation_list->root;

  if ((fp = fopen(file, "w")) == NULL)
  {
    fprintf(stderr, "Ocorreu um erro na abertura do ficheiro.\n");
    return;
  }

  while (where != NULL)
  {
    aux = where->value;

    fprintf(fp, "%s, %d %d %d/%d/%d %d:%d, %d/%d/%d %d:%d\n", aux->client->name,
            aux->type,
            aux->reservation_type,
            aux->register_time.day,
            aux->register_time.month,
            aux->register_time.year,
            aux->register_time.hour,
            aux->register_time.minute,
            aux->actual_time.day,
            aux->actual_time.month,
            aux->actual_time.year,
            aux->actual_time.hour,
            aux->actual_time.minute);

    where = where->next;
  }

  fclose(fp);
}

void read_reservation(char *file, llist *client_list, llist *reservation_list)
{
  FILE *fp;
  reservation *reservation;
  client *client;
  char client_name[MAX_NAME_SIZE];

  if ((fp = fopen(file, "r")) == NULL)
  {
    return;
  }

  while (fscanf(fp, "%[^,],", client_name) == 1)
  {
    client = client_find_by_name(client_list, client_name);
    reservation = reservation_new(client, 1);

    fscanf(fp, "%d %d %d/%d/%d %d:%d, %d/%d/%d %d:%d\n",
           &(reservation->type),
           &(reservation->reservation_type),
           &(reservation->register_time.day),
           &(reservation->register_time.month),
           &(reservation->register_time.year),
           &(reservation->register_time.hour),
           &(reservation->register_time.minute),
           &(reservation->actual_time.day),
           &(reservation->actual_time.month),
           &(reservation->actual_time.year),
           &(reservation->actual_time.hour),
           &(reservation->actual_time.minute));

    llist_insert(reservation_list, reservation);
  }

  fclose(fp);
}

lnode *_reservation_sort_rec(lnode *start, int order)
{
  if (start == NULL)
  {
    return NULL;
  }

  // FIXME This code is awful

  if (order)
  {
    if (start->next != NULL && xtime_comp(&(((reservation*) start->value)->actual_time),
                                          &(((reservation*) start->next->value)->actual_time)) > 0)
    {
      start = _llist_swap(start, start->next);
    }
  }
  else
  {
    if (start->next != NULL && xtime_comp(&(((reservation*) start->value)->actual_time),
                                          &(((reservation*) start->next->value)->actual_time)) < 0)
    {
      start = _llist_swap(start, start->next);
    }
  }

  start->next = _reservation_sort_rec(start->next, order);

  if (order)
  {
    if (start->next != NULL && xtime_comp(&(((reservation*) start->value)->actual_time),
                                          &(((reservation*) start->next->value)->actual_time)) > 0)
    {
      start = _llist_swap(start, start->next);
      start->next = _reservation_sort_rec(start->next, order);
    }
  }
  else
  {
    if (start->next != NULL && xtime_comp(&(((reservation*) start->value)->actual_time),
                                          &(((reservation*) start->next->value)->actual_time)) < 0)
    {
      start = _llist_swap(start, start->next);
      start->next = _reservation_sort_rec(start->next, order);
    }
  }

  return start;
}

void reservation_sort(llist *reservation_list, int order)
{
  reservation_list->root = _reservation_sort_rec(reservation_list->root, order);
}

int reservation_type_check(int *request_reservation_type, char *request_reservation_type_str)
{
  if (strlen(request_reservation_type_str) != SINGLE_INPUT_SIZE)
  {
    printf("O input nao tem o tamanho correto.\n");
    return 1;
  }

  if (check_if_lower(request_reservation_type_str))
  {
    char_to_upper(request_reservation_type_str);
  }

  if (reservation_type_str_to_int(request_reservation_type_str,
                                  request_reservation_type))
  {
    printf("O input é incorreto.\n");
    return 1;
  }

  return 0;
}

int reservation_request_check(int *reservation_sort_order, char *which_order_str)
{
  if (strlen(which_order_str) != SINGLE_INPUT_SIZE)
  {
    printf("O input nao tem o tamanho correto.\n");
    return 1;
  }

  if (check_if_lower(which_order_str))
  {
    char_to_upper(which_order_str);
  }

  if (!strcmp(which_order_str, "R"))
  {
    *reservation_sort_order = 1;
    return 0;
  }
  else if (!strcmp(which_order_str, "A"))
  {
    *reservation_sort_order = 0;
    return 0;
  }
  else
  {
    printf("O input é incorreto.\n");
    return 1;
  }

  return 0;
}

void reservation_remove_outdated(llist *reservation_list)
{
  time_t current_time = time(NULL);
  xtime current_xtime;
  lnode *start = reservation_list->root;

  time_t_to_xtime(&current_xtime, &current_time);

  while (start != NULL)
  {
    if (xtime_comp(&(((reservation*) start->value)->actual_time), &current_xtime) < 0)
    {
      llist_remove(reservation_list, start->value);
    }

    start = start->next;
  }
}

int reservation_get_duration_mins(reservation *which)
{
  if (which->type == RESERVATION_TYPE_CLEANING)
  {
    return 30; // Cleanings take 30 minutes...
  }
  else
  {
    return 60; // ... but checkings take 60 minutes.
  }
}

reservation *reservation_any_collision(reservation *which, llist *reservation_list)
{
  lnode *current_node = reservation_list->root;

  xtime start_of_which = which->actual_time;
  xtime end_of_which = start_of_which;
  end_of_which.minute += reservation_get_duration_mins(which);

  while (current_node != NULL)
  {
    reservation *current = (reservation*) current_node->value;

    xtime start_of_current = current->actual_time;
    xtime end_of_current = start_of_current;
    end_of_current.minute += reservation_get_duration_mins(current);

    /* Check if "which" starts during current */

    if (xtime_comp(&start_of_which, &start_of_current) >= 0 &&
        xtime_comp(&start_of_which, &end_of_current) <= 0)
    {
      return current;
    }

    /* Check if "which" ends during current */

    if (xtime_comp(&end_of_which, &start_of_current) >= 0 &&
        xtime_comp(&end_of_which, &end_of_current) <= 0)
    {
      return current;
    }

    current_node = current_node->next;
  }

  return NULL;
}

int pre_reservation_request_check(char *pre_reservation_decision_str)
{
  if (strlen(pre_reservation_decision_str) != SINGLE_INPUT_SIZE)
  {
    printf("O input nao tem o tamanho correto.\n");
    return 1;
  }

  if (check_if_lower(pre_reservation_decision_str))
  {
    char_to_upper(pre_reservation_decision_str);
  }

  if (!strcmp(pre_reservation_decision_str, "G"))
  {
    return 0;
  }
  else if (!strcmp(pre_reservation_decision_str, "M"))
  {
    return 0;
  }
  else
  {
    printf("O input é incorreto.\n");
    return 1;
  }

  return 0;
}

void reservation_update_pre_reservations(llist *reservation_list, llist *pre_reservation_list)
{
  lnode *current_node = pre_reservation_list->root;
  int how_many = 0;

  while (current_node != NULL)
  {
    reservation *current_pre_reservation = (reservation*) current_node->value;

    /* No collision, woo! */
    if (!reservation_any_collision(current_pre_reservation, reservation_list))
    {
      current_pre_reservation->reservation_type = RESERVA;
      llist_insert(reservation_list, current_pre_reservation);

      llist_remove(pre_reservation_list, current_pre_reservation);

      how_many++;
    }

    current_node = current_node->next;
  }

  if (how_many)
  {
    printf("Uma ou mais pré-reservas foram movidas das pré-reservas para as reservas.\n");
  
    write_reservations("reservations.txt", reservation_list);
    write_reservations("pre_reservations.txt", pre_reservation_list);
  }
}

void reservation_list_reservations_by_client(client *request_client, llist *reservation_list,
                                             int pre_reservations)
{
  lnode *current_node = reservation_list->root;

  int many_found = 0;

  clear_screen();

  while (current_node != NULL)
  {
    reservation *current_reservation = (reservation*) current_node->value;

    if (current_reservation->client == request_client)
    {
      if (!pre_reservations)
      {
        printf("%sListando reserva número %d\n", COLOR_CYAN, ++many_found);
      }
      else
      {
        printf("%sListando pré reserva número %d\n", COLOR_CYAN, ++many_found);
      }

      reset_color();

      reservation_print(current_reservation);
    }

    current_node = current_node->next;
  }

  if (!many_found)
  {
    if (!pre_reservations)
    {
      printf("Não foram encontradas reservas associadas a este cliente.\n");
    }
    else
    {
      printf("Não foram encontradas pré reservas associadas a este cliente.\n");
    }
  }
}
