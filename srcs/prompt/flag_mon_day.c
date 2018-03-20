/*
** flag4.c for flag4 in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Thu May 26 19:08:58 2016 Loïs
** Last update Sun Jun  5 04:44:18 2016 Loïs
*/

#include "functions.h"

int		prmt_day(const char *prompt, const t_sh *data, int *i)
{
  struct tm	*tm;
  time_t	count;

  (void)prompt, (void)data;
  ++*i;
  count = time(NULL);
  if (!(tm = localtime(&count)))
    return (1);
  if (tm->tm_mday < 10)
    my_putchar('0', 1);
  my_put_nbr(tm->tm_mday, 1);
  return (0);
}

int		prmt_day_week(const char *prompt, const t_sh *data, int *i)
{
  struct tm	*tm;
  time_t	count;
  char		*date;
  int		idx;

  (void)prompt, (void)data;
  ++*i;
  count = time(NULL);
  if (!(tm = localtime(&count)) || !(date = asctime(tm)))
    return (1);
  idx = 0;
  while (idx < SIZE_DAY)
    {
      my_putchar(date[idx], 1);
      ++idx;
    }
  return (0);
}

int		prmt_mon_nb(const char *prompt, const t_sh *data, int *i)
{
  struct tm	*tm;
  time_t	count;

  (void)prompt, (void)data;
  ++*i;
  count = time(NULL);
  if (!(tm = localtime(&count)))
    return (1);
  if (tm->tm_mon < 9)
    my_putchar('0', 1);
  my_put_nbr(tm->tm_mon + 1, 1);
  return (0);
}

int		prmt_mon(const char *prompt, const t_sh *data, int *i)
{
  struct tm	*tm;
  time_t	count;
  char		*date;
  int		idx;

  (void)prompt, (void)data;
  ++*i;
  count = time(NULL);
  if (!(tm = localtime(&count)) || !(date = asctime(tm)))
    return (1);
  idx = SIZE_MON_S;
  while (idx < SIZE_MON_E)
    {
      my_putchar(date[idx], 1);
      ++idx;
    }
  return (0);
}
