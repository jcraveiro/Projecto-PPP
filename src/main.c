#include "main.h"

void main_loop()
{
  int which_option = -1;

  clear_screen();
  printf("%sQuer voltar para o menu principal estando noutra localização? Insira '0'.\n", COLOR_GREEN);
  reset_color();

  while (which_option != EXIT_OPTION)
  {
    do
    {
      which_option = menu_wait();

      if (which_option == 1)
      {
        int option_1_aux = reservation_request_new(reservation_list, client_list, pre_reservation_list);

        if (option_1_aux == 1)
        {
          printf("Nao conseguimos concluir a operação.\n");
          break;
        }
        else if (option_1_aux == 2)
        {
          clear_screen();
          break;
        }
        else
        {
          clear_screen();

          printf("Reserva adicionada com sucesso.\n\n");
        }
      }
      else if (which_option == 2)
      {
        if (llist_get_size(reservation_list) == 0)
        {
          printf("A lista está vazia.\n\n");
          break;
        }

        int option_2_aux = reservation_request_cancel(reservation_list);
        reservation_update_pre_reservations(reservation_list, pre_reservation_list);
        clear_screen();

        if (option_2_aux == 1)
        {
          printf("Nao conseguimos concluir a operação.\n");
          break;
        }
        else if (option_2_aux == 2)
        {
          clear_screen();
          break;
        }
        else
        {
          clear_screen();
          printf("Reserva cancelada com sucesso.\n\n");
        }
      }
      else if (which_option == 3)
      {
        if (llist_get_size(reservation_list) == 0)
        {
          printf("A lista está vazia.\n\n");
          break;
        }

        int option_3_aux = reservation_request_listing(reservation_list);

        if (option_3_aux == 1)
        {
          break;
        }
        else if (option_3_aux == 2)
        {
          clear_screen();
          break;
        }
        else
        {

        }
      }
      else if (which_option == 4)
      {
        if (llist_get_size(pre_reservation_list) == 0)
        {
          printf("A lista está vazia.\n\n");
          break;
        }

        int option_4_aux = reservation_request_listing(pre_reservation_list);

        if (option_4_aux == 1)
        {
          break;
        }
        else if (option_4_aux == 2)
        {
          clear_screen();
          break;
        }
        else
        {

        }
      }
      else if (which_option == 5)
      {
        if (llist_get_size(pre_reservation_list) == 0)
        {
          printf("A lista está vazia.\n\n");
          break;
        }

        int option_5_aux = reservation_request_cancel(pre_reservation_list);
        reservation_update_pre_reservations(reservation_list, pre_reservation_list);
        clear_screen();

        if (option_5_aux == 1)
        {
          printf("Nao conseguimos concluir a operação.\n");
          break;
        }
        else if (option_5_aux == 2)
        {
          clear_screen();
          break;
        }
        else
        {
          clear_screen();
          printf("Reserva cancelada com sucesso.\n\n");
        }
      }
      else if (which_option == 6)
      {
        if (llist_get_size(client_list) == 0)
        {
          printf("Não existem clientes.\n\n");
          break;
        }

        if (llist_get_size(reservation_list) == 0)
        {
          printf("Não existem reservas.\n\n");
          break;
        }

        char client_name_str[MAX_NAME_SIZE];
        int option_6_aux = 1;

        do {
          option_6_aux = client_request_name(client_list, client_name_str);
        } while (option_6_aux == 1);

        client *request_client = client_find_by_name(client_list, client_name_str);

        reservation_list_reservations_by_client(request_client, reservation_list, 0);

        if (option_6_aux == 1)
        {
          printf("Nao conseguimos concluir a operação.\n");
          break;
        }
        else if (option_6_aux == 2)
        {
          clear_screen();
          break;
        }
      }
      else if (which_option == 7)
      {
        if (llist_get_size(client_list) == 0)
        {
          printf("Não existem clientes.\n\n");
          break;
        }

        if (llist_get_size(pre_reservation_list) == 0)
        {
          printf("Não existem pré reservas.\n\n");
          break;
        }

        char client_name_str[MAX_NAME_SIZE];
        int option_6_aux = 1;

        do {
          option_6_aux = client_request_name(client_list, client_name_str);
        } while (option_6_aux == 1);

        client *request_client = client_find_by_name(client_list, client_name_str);

        reservation_list_reservations_by_client(request_client, pre_reservation_list, 1);

        if (option_6_aux == 1)
        {
          printf("Nao conseguimos concluir a operação.\n");
          break;
        }
        else if (option_6_aux == 2)
        {
          clear_screen();
          break;
        }
      }
      else if (which_option == 8)
      {
        clear_screen();
        printf("Programa feito por:\n");

        printf("%s", COLOR_GREEN);

        printf("      _             _     _                                   \n");
        printf("   __| | __ ___   _(_) __| |   __ _  ___  _ __ ___   ___  ___ \n");
        printf("  / _` |/ _` \\ \\ / / |/ _` |  / _` |/ _ \\| '_ ` _ \\ / _ \\/ __|\n");
        printf(" | (_| | (_| |\\ V /| | (_| | | (_| | (_) | | | | | |  __/\\__ \\\n");
        printf("  \\__,_|\\__,_| \\_/ |_|\\__,_|  \\__, |\\___/|_| |_| |_|\\___||___/\n");
        printf("                              |___/                           \n");

        printf("\n%s", COLOR_CYAN);

        printf("    _        /\\/|                                  _           \n");
        printf("   (_) ___  |/\\/_  ___     ___ _ __ __ ___   _____(_)_ __ ___  \n");
        printf("   | |/ _ \\ / _` |/ _ \\   / __| '__/ _` \\ \\ / / _ \\ | '__/ _ \\ \n");
        printf("   | | (_) | (_| | (_) | | (__| | | (_| |\\ V /  __/ | | | (_) |\n");
        printf("  _/ |\\___/ \\__,_|\\___/   \\___|_|  \\__,_| \\_/ \\___|_|_|  \\___/ \n");
        printf(" |__/                                                          \n");

        reset_color();

        printf("\n");
      }
    } while (which_option <= 0);
  }
}

int main()
{
  client_list = llist_new();
  reservation_list = llist_new();
  pre_reservation_list = llist_new();

  read_client("clients.txt", client_list);
  read_reservation("reservations.txt", client_list, reservation_list);
  read_reservation("pre_reservations.txt", client_list, pre_reservation_list);

  reservation_remove_outdated(reservation_list);
  reservation_remove_outdated(pre_reservation_list);

  reservation_update_pre_reservations(reservation_list, pre_reservation_list);

  /* Start the actual application */
  menu_load();
  main_loop();

  write_client("clients.txt", client_list);
  write_reservations("reservations.txt", reservation_list);
  write_reservations("pre_reservations.txt", pre_reservation_list);

  llist_destroy(client_list);
  llist_destroy(reservation_list);
  llist_destroy(pre_reservation_list);

  return 0;
}
