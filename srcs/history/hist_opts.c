/*
** hist_opts.c for hist_opts in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Sat Jun  4 05:03:41 2016 Loïs
** Last update Sun Jun  5 04:53:43 2016 Loïs
*/

#include <stdio.h>
#include <string.h>
#include "functions.h"

int	hist_clean(const char **tab, t_sh *data)
{
  (void)tab;
  free_hist(data);
  remove(data->hist.hist_pwd);
  data->hist.first = NULL;
  data->hist.last = NULL;
  data->hist.size = 0;
  return (set_return_value(0, 0, data));
}

static int	print_reverse(t_hist_list *tmp, int n, const char *opt)
{
  int		i;

  while (tmp && n)
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
      tmp = tmp->prev;
      --n;
    }
  return (0);
}

int		hist_nbr(const char **tab, t_sh *data)
{
  int		n;

  if (tab[2] && !my_str_isnumber(tab[2]))
    {
      my_putstr(HIST_NOT_NBR, 2);
      return (set_return_value(0, 1, data));
    }
  n = (!tab[2]) ? -1 : (int)my_hist_getnbr(tab[2]);
  if (!strchr(tab[1], 'r'))
    {
      if (print_hist(data, tab[1], n))
	return (1);
    }
  else
    if (print_reverse(data->hist.last, n, tab[1]))
      return (1);
  return (set_return_value(0, 0, data));
}
