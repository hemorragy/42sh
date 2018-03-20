/*
** flag5.c for flag5 in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Fri May 27 01:31:58 2016 Loïs
** Last update Sun Jun  5 04:44:01 2016 Loïs
*/

#include "functions.h"

int		prmt_year_comp(const char *prompt, const t_sh *data, int *i)
{
  struct tm	*tm;
  time_t	count;

  (void)prompt, (void)data;
  ++*i;
  count = time(NULL);
  if (!(tm = localtime(&count)))
    return (1);
  my_put_nbr(tm->tm_year + 1900, 1);
  return (0);
}

int		prmt_year(const char *prompt, const t_sh *data, int *i)
{
  struct tm	*tm;
  time_t	count;

  (void)prompt, (void)data;
  ++*i;
  count = time(NULL);
  if (!(tm = localtime(&count)))
    return (1);
  my_put_nbr(tm->tm_year % 100, 1);
  return (0);
}
