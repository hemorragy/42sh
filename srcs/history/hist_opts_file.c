/*
** hist_opts_file.c for hist_opts_file in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Sat Jun  4 20:32:04 2016 Loïs
** Last update Sun Jun  5 04:48:23 2016 Loïs
*/

#include <stdlib.h>
#include "functions.h"

int	hist_file_s(const char **tab, t_sh *data)
{
  if (!tab[2])
    add_hist_to_file(data, data->hist.hist_pwd);
  else
    add_hist_to_file(data, tab[2]);
  return (set_return_value(0, 0, data));
}

int	hist_file_l(const char **tab, t_sh *data)
{
  if (!tab[2])
    {
      if (get_history(data, data->hist.hist_pwd))
	return (1);
    }
  else
    get_history(data, tab[2]);
  return (set_return_value(0, 0, data));
}

static t_hist_list	**get_hist_tab(t_sh *data)
{
  t_hist_list		**tab;
  t_hist_list		*tmp;
  int			i;

  if (!(tab = malloc(sizeof(t_hist_list *) * (data->hist.size + 1))))
    return (print_err(MALLOC_ERROR));
  tmp = data->hist.first;
  i = 0;
  while (tmp)
    {
      tab[i] = tmp;
      ++i;
      tmp = tmp->next;
    }
  tab[i] = NULL;
  return (tab);
}

static void	sort_tab(t_hist_list **tab)
{
  t_hist_list	*tmp;
  int		swap;
  int		i;

  swap = 0;
  i = 0;
  while (tab[i + 1] || swap)
    {
      if (tab[i]->time > tab[i + 1]->time)
	{
	  tmp = tab[i];
	  tab[i] = tab[i + 1];
	  tab[i + 1] = tmp;
	  ++swap;
	}
      ++i;
      if (!tab[i + 1] && swap)
	{
	  swap = 0;
	  i = 0;
	}
    }
}

int		hist_file_m(const char **tab, t_sh *data)
{
  t_hist_list	**sort;
  int		i;

  if (hist_file_l(tab, data) || !(sort = get_hist_tab(data)))
    return (1);
  if (tab[0] && tab[1])
    sort_tab(sort);
  i = 0;
  while (sort[i])
    {
      if (!i)
	sort[i]->prev = NULL;
      else
	sort[i]->prev = sort[i - 1];
      sort[i]->next = sort[i + 1];
      sort[i]->nb = i + 1;
      ++i;
    }
  data->hist.first = sort[0];
  data->hist.last = (i > 0) ? sort[i - 1] : sort[i];
  data->hist.size = i;
  free(sort);
  return (0);
}
