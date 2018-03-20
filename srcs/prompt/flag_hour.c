/*
** flag3.c for flag3 in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Thu May 26 17:38:43 2016 Loïs
** Last update Sun Jun  5 20:07:26 2016 Loïs
*/

#include "functions.h"

int		prmt_hour_ap(const char *prompt, const t_sh *data, int *i)
{
  struct tm	*tm;
  time_t	count;

  (void)prompt, (void)data;
  ++*i;
  count = time(NULL);
  if (!(tm = localtime(&count)))
    return (1);
  my_put_nbr(tm->tm_hour % 12, 1);
  my_putchar(':', 1);
  if (tm->tm_min < 10)
    my_putchar('0', 1);
  my_put_nbr(tm->tm_min, 1);
  if (tm->tm_hour > 12)
    my_putstr("pm", 1);
  else
    my_putstr("am", 1);
  return (0);
}

int		prmt_hour(const char *prompt, const t_sh *data, int *i)
{
  struct tm	*tm;
  time_t	count;

  (void)prompt, (void)data;
  ++*i;
  count = time(NULL);
  if (!(tm = localtime(&count)))
    return (1);
  my_put_nbr(tm->tm_hour, 1);
  my_putchar(':', 1);
  if (tm->tm_min < 10)
    my_putchar('0', 1);
  my_put_nbr(tm->tm_min, 1);
  return (0);
}

int		prmt_hour_sec_ap(const char *prompt, const t_sh *data, int *i)
{
  struct tm	*tm;
  time_t	count;

  (void)prompt, (void)data;
  ++*i;
  count = time(NULL);
  if (!(tm = localtime(&count)))
    return (1);
  my_put_nbr(tm->tm_hour % 12, 1);
  my_putchar(':', 1);
  if (tm->tm_min < 10)
    my_putchar('0', 1);
  my_put_nbr(tm->tm_min, 1);
  my_putchar(':', 1);
  if (tm->tm_sec < 10)
    my_putchar('0', 1);
  my_put_nbr(tm->tm_sec, 1);
  if (tm->tm_hour > 12)
    my_putstr("pm", 1);
  else
    my_putstr("am", 1);
  return (0);
}

int		prmt_hour_sec(const char *prompt, const t_sh *data, int *i)
{
  struct tm	*tm;
  time_t	count;

  (void)prompt, (void)data;
  ++*i;
  count = time(NULL);
  if (!(tm = localtime(&count)))
    return (1);
  my_put_nbr(tm->tm_hour, 1);
  my_putchar(':', 1);
  if (tm->tm_min < 10)
    my_putchar('0', 1);
  my_put_nbr(tm->tm_min, 1);
  my_putchar(':', 1);
  if (tm->tm_sec < 10)
    my_putchar('0', 1);
  my_put_nbr(tm->tm_sec, 1);
  return (0);
}
