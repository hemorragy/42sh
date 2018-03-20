/*
** flag2.c for flag2 in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Mon May 23 20:17:46 2016 Loïs
** Last update Sun Jun  5 04:44:58 2016 Loïs
*/

#include <string.h>
#include <stdlib.h>
#include "functions.h"

static char	*get_env_name(const char *env)
{
  int		i;

  i = 0;
  while (env[i] && env[i] != '=')
    ++i;
  return (strndup(env, i));
}

static int	prmt_env_tool(const t_sh *data, int *i,
			      const char *prompt, int *env_stat)
{
  int		id;
  char		*value;

  id = 0;
  while (data->env[id])
    {
      if (!(value = get_env_name(data->env[id])))
	return (1);
      if (!strncmp(prompt + *i + 2, value, strlen(value))
	  && env_stat[1] < (int)strlen(value))
	{
	  env_stat[1] = strlen(value);
	  env_stat[0] = id;
	}
      free(value);
      ++id;
    }
  return (0);
}

int	prmt_env(const char *prompt, const t_sh *data, int *i)
{
  char	*value;
  char	*search;
  int	env_stat[2];

  env_stat[0] = -1;
  env_stat[1] = 0;
  if (prmt_env_tool(data, i, prompt, env_stat))
    return (1);
  ++*i;
  if (env_stat[0] == -1)
    return (0);
  if (!(value = get_env_name(data->env[env_stat[0]])))
    return (1);
  if ((search = env_value(data->env, value)))
    my_putstr(search + 1, 1);
  free(value);
  *i = *i + env_stat[1];
  return (0);
}

int	prmt_user(const char *prompt, const t_sh *data, int *i)
{
  char	*user;

  (void)prompt;
  ++*i;
  if ((user = env_value(data->env, "USER=")))
    my_putstr(user, 1);
  return (0);
}

int	prmt_ret(const char *prompt, const t_sh *data, int *i)
{
  (void)prompt;
  ++*i;
  my_put_nbr(data->last_ret, 1);
  return (0);
}
