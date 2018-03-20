/*
** setenv.c for setenv in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Mon May  9 13:03:40 2016 Loïs
** Last update Sun Jun  5 04:39:03 2016 Loïs
*/

#include <string.h>
#include <stdlib.h>
#include "functions.h"

static int	invalid_name(const char *cmd)
{
  int		i;

  i = 1;
  if (cmd[0] != '_' && (cmd[0] < 'a' || cmd[0] > 'z')
      && (cmd[0] < 'A' || cmd[0] > 'Z'))
    return (print_error(FIRST_INV_SETENV));
  while (cmd[i])
    {
      if (cmd[i] != '_' && (cmd[i] < 'a' || cmd[i] > 'z')
	  && (cmd[i] < 'A' || cmd[i] > 'Z') && (cmd[i] < '0' || cmd[i] > '9'))
	return (print_error(INV_SETENV));
      ++i;
    }
  return (0);
}

static int	check_ovw(const char **env, const char *value)
{
  char		*tmp;
  int		i;

  i = 0;
  if (!(tmp = strdup(value))
      || !(tmp = realloc(tmp, sizeof(char) * (strlen(tmp) + 2))))
    return (print_error(MALLOC_ERROR));
  tmp = strcat(tmp, "=");
  while (env[i] && strncmp(env[i], tmp, strlen(tmp)))
    ++i;
  free(tmp);
  if (env[i])
    return (i);
  return (-2);
}

static int	no_ovw(t_sh *data, const char **cmd)
{
  int		i;

  i = 0;
  while (data->env[i])
    ++i;
  if (!(data->env = realloc(data->env, sizeof(char *) * (i + 2)))
      || !(data->env[i] = realloc(data->env[i], sizeof(char)
				  * (strlen(cmd[1]) + 2))))
    return (print_error(MALLOC_ERROR));
  data->env[i] = strcpy(data->env[i], cmd[1]);
  data->env[i] = strcat(data->env[i], "=");
  if (cmd[2])
    {
      if (!(data->env[i] = realloc
	    (data->env[i], sizeof(char)
	     * (strlen(data->env[i]) + 1 + strlen(cmd[2])))))
	return (print_error(MALLOC_ERROR));
      data->env[i] = strcat(data->env[i], cmd[2]);
    }
  data->env[i + 1] = NULL;
  return (0);
}

static int	creat_newenv(t_sh *data, const char **cmd)
{
  int		size;
  int		i;

  i = 0;
  if (invalid_name(cmd[1]))
    return (set_return_value(0, 1, data));
  if ((i = check_ovw((const char **)data->env, cmd[1])) == -1)
    return (1);
  if (i >= 0)
    {
      size = strlen(cmd[1]) + 2;
      size = (cmd[2]) ? (int)(size + strlen(cmd[2])) : size;
      if (!(data->env[i] = realloc(data->env[i], sizeof(char) * size)))
	return (1);
      data->env[i] = strcpy(data->env[i], cmd[1]);
      data->env[i] = strcat(data->env[i], "=");
      if (cmd[2])
	data->env[i] = strcat(data->env[i], cmd[2]);
    }
  else
    if (no_ovw(data, cmd))
      return (1);
  return (set_return_value(0, 0, data));
}

int	my_setenv(const char **cmd, t_sh *data)
{
  int	i;

  if (!cmd[1])
    {
      i = 0;
      while (data->env[i])
	{
	  my_putstr(data->env[i], 1);
	  my_putchar('\n', 1);
	  ++i;
	}
    }
  else if (cmd[2] && cmd[3])
    {
      my_putstr(SETENV_ERR, 2);
      return (set_return_value(0, 1, data));
    }
  else
    if (creat_newenv(data, cmd))
      return (1);
  return (0);
}
