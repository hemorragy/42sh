/*
** print_history.c for print_history in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Sat Jun  4 15:26:15 2016 Loïs
** Last update Sun Jun  5 19:16:39 2016 Loïs
*/

#include <string.h>
#include "functions.h"

static t_hist_list	*print_hist_tool(t_sh *data, int n)
{
  int			i;
  t_hist_list		*tmp;

  i = 0;
  tmp = data->hist.first;
  if (n >= 0)
    while (data->hist.size - i > n)
      {
        tmp = tmp->next;
        ++i;
      }
  return (tmp);
}

int		print_hour(time_t time)
{
  struct tm	*tm;

  if (!(tm = localtime(&time)))
    return (1);
  my_put_nbr(tm->tm_hour, 1);
  my_putchar(':', 1);
  if (tm->tm_min < 10)
    my_putchar('0', 1);
  my_put_nbr(tm->tm_min, 1);
  return (0);
}

int		print_hist(t_sh *data, const char *opt, int n)
{
  t_hist_list	*tmp;
  int		i;

  tmp = print_hist_tool(data, n);
  while (tmp)
    {
      i = MAX_SIZE_NB_HIST;
      if (!opt || !strchr(opt, 'h'))
	{
	  while (tmp->nb < i)
	    {
	      my_putchar(' ', 1);
	      i = i / 10;
	    }
	  my_put_nbr(tmp->nb, 1);
	  my_putchar('\t', 1);
	  if (print_hour(tmp->time))
	    return (1);
	  my_putchar('\t', 1);
	}
      my_putstr(tmp->cmd, 1);
      my_putchar('\n', 1);
      tmp = tmp->next;
    }
  return (0);
}
