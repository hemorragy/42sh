/*
** my_free.c for my_free in /home/antoin_g/rendu/Unix/PSU_2015_42sh
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Mon May 30 17:15:50 2016 Loïs
** Last update Sat Jun  4 19:05:01 2016 Loïs
*/

#include <stdlib.h>
#include "structs.h"

void	free_tab(char **tab)
{
  int	i;

  i = 0;
  while (tab[i])
    {
      free(tab[i]);
      ++i;
    }
  free(tab);
}

void		free_hist(t_sh *data)
{
  t_hist_list	*tmp;
  t_hist_list	*current;

  current = data->hist.first;
  while (current)
    {
      tmp = current;
      current = current->next;
      free(tmp->cmd);
      free(tmp);
    }
}
