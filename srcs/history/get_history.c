/*
** get_history.c for get_history in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Fri Jun  3 20:05:12 2016 Loïs
** Last update Sun Jun  5 19:22:50 2016 Loïs
*/

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

static int	one_more_hist(t_sh *data)
{
  static int	nb = 1;
  t_hist_list	*new;

  if (nb >= MAX_HIST_SIZE)
    hist_clean(NULL, data);
  if (!(new = malloc(sizeof(t_hist_list))))
    return (print_error(MALLOC_ERROR));
  new->next = NULL;
  new->prev = NULL;
  if (!data->hist.first)
    data->hist.first = new;
  else
    {
      data->hist.last->next = new;
      new->prev = data->hist.last;
    }
  data->hist.last = new;
  new->nb = nb;
  new->time = 0;
  new->cmd = NULL;
  ++nb;
  ++data->hist.size;
  return (0);
}

int	add_new_hist(t_sh *data, const char *cmd)
{
  if (one_more_hist(data) || !(data->hist.last->cmd = strdup(cmd)))
    return (1);
  data->hist.last->time = time(NULL);
  return (0);
}

static void	get_last_check(t_sh *data)
{
  t_hist_list	*tmp;

  if (data->hist.last && !data->hist.last->cmd)
    {
      tmp = data->hist.last;
      data->hist.last = data->hist.last->prev;
      free(tmp);
    }
}

int		get_history(t_sh *data, const char *file)
{
  char		*str;
  int		fd;

  if ((fd = open(file, O_CREAT | O_RDONLY, RIGHT_HISTO)) == -1)
    return (0);
  while ((str = read_hist(fd)))
    {
      if (!data->hist.first || data->hist.last->cmd)
	if (one_more_hist(data))
	  return (-1);
      if (data->hist.last->time == 0)
	{
	  data->hist.last->time = my_hist_getnbr(str);
	  free(str);
	}
      else
	{
	  if (str[0] && !strchr(str, '!'))
	    data->hist.last->cmd = str;
	  else
	    free(str);
	}
    }
  get_last_check(data);
  return (0);
}

int	init_hist(t_sh *data)
{
  data->hist.first = NULL;
  data->hist.last = NULL;
  data->hist.size = 0;
  data->hist.hist_pwd = env_value(data->env, "HOME=");
  if (data->hist.hist_pwd)
    {
      if (!(data->hist.hist_pwd = strdup(data->hist.hist_pwd)))
	return (print_error(MALLOC_ERROR));
      if (data->hist.hist_pwd[strlen(data->hist.hist_pwd) - 1] != '/')
	if (!(data->hist.hist_pwd = add_two_str(data->hist.hist_pwd, "/")))
	  return (1);
    }
  else
    if (!(data->hist.hist_pwd = strdup("/")))
	return (print_error(MALLOC_ERROR));
  if (!(data->hist.hist_pwd = add_two_str(data->hist.hist_pwd, HIST_FILE)))
    return (1);
  return (0);
}
