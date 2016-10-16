#include "utils.h"

void clear_screen()
{
  #ifdef WINDOWS
    system("cls");
  #else
    system("clear");
  #endif
}

int get_str_input(char *say_what, char *save_where, int input_size)
{
  printf("%s%s", COLOR_GREEN, say_what);
  reset_color();

  if (fgets(save_where, input_size, stdin) == NULL)
  {
    return 1;
  }

  strtok(save_where, "\n");

  if (strlen(save_where) == input_size - 1)
  {
    dump_line(stdin);
    return 1;
  }

  if (!strcmp(save_where, "0"))
  {
    return 2;
  }

  return 0;
}

int get_int_input(char *say_what, int *save_where)
{
  char temp_buffer[MAX_INT_DIGITS];
  int i;
  printf("%s%s", COLOR_GREEN, say_what);
  reset_color();

  if (fgets(temp_buffer, MAX_INT_DIGITS, stdin) == NULL)
  {
    return 1;
  }

  strtok(temp_buffer, "\n");

  if (strlen(temp_buffer) == MAX_INT_DIGITS - 1)
  {
    dump_line(stdin);
    return 1;
  }

  for (i = 0; temp_buffer[i] != '\0'; i++)
  {
    if (temp_buffer[i] < '0' || temp_buffer[i] > '9')
    {
      return 1;
    }
  }
  
  if (!strcmp(temp_buffer, "0"))
    {
      return 2;
    }

  *save_where = atoi(temp_buffer);
  return 0;
}

void time_to_str(xtime *which_time, char *save_where)
{
  sprintf(save_where, "%02d/%02d/%04d, às %02d:%02d", which_time->day,
                                                      which_time->month,
                                                      which_time->year,
                                                      which_time->hour,
                                                      which_time->minute);
}

int ask_date(xtime *save_where)
{
  time_t current_time = time(NULL);
  xtime current_xtime;
  char current_time_str[MAX_TIME_CHARS];
  char actual_time[MAX_TIME_CHARS];
  char permited_chars[MAX_TIME_CHARS] = "0123456789/: ";
  char *c;
  int i;

  time_t_to_xtime(&current_xtime, &current_time);
  time_to_str(&current_xtime, current_time_str);

  printf("São agora %s\n", current_time_str);

  printf("%sInsira a data que prentende, no formato DD/MM/AAAA HH:MM: ", COLOR_GREEN);
  reset_color();

  if (fgets(actual_time, MAX_TIME_CHARS, stdin) == NULL)
  {
    return 1;
  }

  strtok(actual_time, "\n");

  if (!strcmp(actual_time, "0"))
  {
    return 2;
  }

  if (strlen(actual_time) == MAX_TIME_CHARS - 1)
  {
    dump_line(stdin);
    return 1;
  }

  for (i = 0; actual_time[i] != '\0'; i++)
  {
    c = strchr(permited_chars, actual_time[i]);

    if (c == NULL)
    {
      return 1;
    }
  }

  sscanf(actual_time, "%d/%d/%d %d:%d", &save_where->day,
         &save_where->month,
         &save_where->year,
         &save_where->hour,
         &save_where->minute);

  return 0;
}

void time_t_to_xtime(xtime *save_where, time_t *which_time)
{
  struct tm *current_time_info = localtime(which_time);
  save_where->day = current_time_info->tm_mday;
  save_where->month = current_time_info->tm_mon + 1;
  save_where->year = current_time_info->tm_year + 1900;

  save_where->hour = current_time_info->tm_hour;
  save_where->minute = current_time_info->tm_min;
}

void dump_line(FILE *fp)
{
  int ch;

  while ((ch = fgetc(fp)) != EOF && ch != '\n')
    /* empty body */;
}


int check_if_lower(char *string)
{
  int i;

  for (i = 0; string[i] != '\0'; i++)
  {
    if (string[i] >= 'a' && string[i] <= 'z')
    {
      return 1;
    }
  }

  return 0;
}

void char_to_upper(char *lower)
{
  *(lower) = 'A' + *(lower) - 'a';
}
