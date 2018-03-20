/*
** switch_ex.c for switch_ex in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Sun Jun  5 22:45:18 2016 Loïs
** Last update Sun Jun  5 23:25:26 2016 Loïs
*/

#include <string.h>
#include "functions.h"

static char	*error_ex_all(char *str, t_sh *data, int *i, int end)
{
  int		idx;

  idx = *i;
  while (++idx < end)
    my_putchar(str[idx], 2);
  my_putstr(NOT_EVENT, 2);
  data->ex = 1;
  return (str);
}

char		*find_good(char *str, t_sh *data, int *i)
{
  t_hist_list	*tmp;
  char		*cmd;
  int		end;

  end = *i + 1;
  while (str[end] && !strchr(NO_EX_AFTER, str[end]))
    ++end;
  --end;
  tmp = data->hist.first;
  cmd = NULL;
  while (tmp)
    {
      if (!strncmp(tmp->cmd, str + *i + 1, end - *i))
        cmd = tmp->cmd;
      tmp = tmp->next;
    }
  if (!cmd)
    return (error_ex_all(str, data, i, end));
  return (add_cmd(str, cmd, i, end + 1));
}

char		*find_one(char *str, t_sh *data, int *i)
{
  t_hist_list	*tmp;
  int		nb;
  int		idx;

  nb = my_getnbr(str + *i + 1);
  tmp = data->hist.first;
  while (tmp && tmp->nb != nb)
    tmp = tmp->next;
  if (!tmp)
    {
      my_put_nbr(nb, 2);
      my_putstr(NOT_EVENT, 2);
      data->ex = 1;
      return (str);
    }
  idx = *i + 1;
  while (str[idx] >= '0' && str[idx] <= '9')
    ++idx;
  return (add_cmd(str, tmp->cmd, i, idx));
}

char		*search_reverse(char *str, t_sh *data, int *i)
{
  t_hist_list	*tmp;
  int		nb;
  int		idx;

  nb = -my_getnbr(str + *i + 1);
  if (nb == 0)
    return (find_good(str, data, i));
  tmp = data->hist.last;
  while (tmp && nb > 1)
    {
      --nb;
      tmp = tmp->prev;
    }
  if (!tmp)
    {
      my_put_nbr(-nb, 2);
      my_putstr(NOT_EVENT, 2);
      data->ex = 1;
      return (str);
    }
  idx = *i + 2;
  while (str[idx] >= '0' && str[idx] <= '9')
    ++idx;
  return (add_cmd(str, tmp->cmd, i, idx));
}
