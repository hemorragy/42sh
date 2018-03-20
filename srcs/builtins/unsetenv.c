/*
** unsetenv.c for unsetenv in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Wed May 11 20:13:26 2016 Loïs
** Last update Sun Jun  5 04:38:08 2016 Loïs
*/

#include <stdlib.h>
#include <string.h>
#include "functions.h"

static int	is_to_delete(const char *value, const char **cmd)
{
  char		*tmp;
  int		i;

  i = 1;
  while (cmd[i])
    {
      if (!(tmp = malloc(sizeof(char) * (strlen(cmd[i]) + 2))))
	return (-1);
      tmp = strcpy(tmp, cmd[i]);
      tmp = strcat(tmp, "=");
      if (!strncmp(tmp, value, strlen(tmp)))
	{
	  free(tmp);
	  return (1);
	}
      ++i;
      free(tmp);
    }
  return (0);
}

static int	fill_new_env(t_sh *data, char **tmp, const char **cmd)
{
  int		i;
  int		idx;
  int		check;

  i = 0;
  idx = 0;
  while (tmp[i])
    {
      if ((check = is_to_delete(tmp[i], cmd)))
	{
	  if (check == -1)
	    return (1);
	  free(tmp[i]);
	}
      else
	{
	  data->env[idx] = tmp[i];
	  ++idx;
	}
      ++i;
    }
  data->env[idx] = NULL;
  return (0);
}

static int	change_env(t_sh *data, const char **cmd)
{
  int		i;
  char		**tmp;

  i = 0;
  while (data->env[i])
    ++i;
  tmp = data->env;
  if (!(data->env = malloc(sizeof(char *) * (i + 1)))
      || fill_new_env(data, tmp, cmd))
    return (print_error(MALLOC_ERROR));
  free(tmp);
  i = 0;
  while (data->env[i])
    ++i;
  if (!(data->env = realloc(data->env, sizeof(char *) * (i + 1))))
    return (print_error(MALLOC_ERROR));
  return (0);
}

int	my_unsetenv(const char **cmd, t_sh *data)
{
  if (!cmd[1])
    {
      my_putstr(UNSETENV_ERR, 2);
      return (set_return_value(0, 1, data));
    }
  else
    if (change_env(data, cmd))
      return (1);
  return (set_return_value(0, 0, data));
}
