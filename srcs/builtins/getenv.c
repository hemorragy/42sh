/*
** getenv.c for getenv in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Thu May 12 15:39:45 2016 Loïs
** Last update Sun Jun  5 04:41:31 2016 Loïs
*/

#include <stdlib.h>
#include <string.h>
#include "functions.h"

static const t_def	g_def[] =
  {
    {"OSTYPE=", &add_ostype},
    {"PWD=", &add_pwd},
    {"USER=", &add_usr},
    {"GROUP=", &add_grp},
    {"HOST=", &add_host},
    {NULL, NULL}
  };

char	*env_value(char **env, const char *value)
{
  int	i;

  i = 0;
  while (env[i])
    {
      if (!strncmp(env[i], value, strlen(value)))
	return (env[i] + strlen(value));
      ++i;
    }
  return (NULL);
}

char	**one_more(char **env)
{
  int	i;

  i = 0;
  while (env[i])
    ++i;
  if (!(env = realloc(env, sizeof(char *) * (i + 2))))
    return (print_err(MALLOC_ERROR));
  return (env);
}

static int	value_exist(const char **env, const char *value)
{
  int		i;

  i = 0;
  while (env[i])
    {
      if (!strncmp(env[i], value, strlen(value)))
	return (1);
      ++i;
    }
  return (0);
}

static char	**add_default_env(char **env)
{
  int		i;

  i = 0;
  while (g_def[i].value)
    {
      if (!value_exist((const char **)env, g_def[i].value))
	if (!(env = g_def[i].function(env)))
	  return (NULL);
      ++i;
    }
  return (env);
}

char	**get_env(const char **env)
{
  char	**my_env;
  int	i;

  i = 0;
  while (env[i])
    ++i;
  if (!(my_env = malloc(sizeof(char *) * (i + 1))))
    return (print_err(MALLOC_ERROR));
  i = 0;
  while (env[i])
    {
      if (!(my_env[i] = strdup(env[i])))
	return (print_err(MALLOC_ERROR));
      ++i;
    }
  my_env[i] = NULL;
  if (!(my_env = add_default_env(my_env)))
    return (NULL);
  return (my_env);
}
