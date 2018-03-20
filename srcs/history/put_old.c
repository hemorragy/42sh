/*
** put_old.c for put_old in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Sun Jun  5 20:30:35 2016 Loïs
** Last update Sun Jun  5 23:25:33 2016 Loïs
*/

#include <stdlib.h>
#include <string.h>
#include "functions.h"

char		*add_cmd(char *str, char *cmd, int *start, int end)
{
  if (!(str = realloc(str, sizeof(char) * (strlen(str) +
					   ((strlen(cmd) - (end - *start) > 0) ?
					    strlen(cmd) : 0) + 1))))
    return (NULL);
  memmove(str + *start + strlen(cmd), str + end, strlen(str) - end + 1);
  memmove(str + *start, cmd, strlen(cmd));
  *start = *start + strlen(cmd) - 1;
  return (str);
}

static char	*last_one(char *str, t_sh *data, int *i)
{
  if (!data->hist.last)
    {
      my_putstr(NOT_EVENT, 2);
      data->ex = 1;
      return (str);
    }
  return (add_cmd(str, data->hist.last->cmd, i, *i + 2));
}

char	*add_hist_to_cmd(char *str, t_sh *data)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] == '!' && str[i + 1])
	if ((str[i + 1] == '-' && !(str = search_reverse(str, data, &i)))
	    || (str[i + 1] >= '0' && str[i + 1] <= '9'
		&& !(str = find_one(str, data, &i))) ||
	    (str[i + 1] == '!' && !(str = last_one(str, data, &i)))
	    || (!strchr(NO_EX_AFTER, str[i + 1])
		&& !(str = find_good(str, data, &i))))
	  return (NULL);
      ++i;
    }
  return (str);
}
