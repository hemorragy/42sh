/*
** default_env_type.c for default_env_type in /home/antoin_g/rendu/Unix/PSU_2015_42sh
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Mon May 30 19:56:44 2016 Loïs
** Last update Sun Jun  5 04:42:34 2016 Loïs
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "functions.h"

char	**add_host(char **env)
{
  char	*tmp;
  int	i;

  if (!(env = one_more(env)))
    return (NULL);
  i = 0;
  while (env[i])
    ++i;
  if (!(env[i] = strdup("HOST="))
      || !(tmp = malloc(sizeof(char) * (HOST_SIZE + 1))))
    return (print_err(MALLOC_ERROR));
  env[i + 1] = NULL;
  if (!gethostname(tmp, HOST_SIZE))
    {
      if (!(env[i] = realloc(env[i], sizeof(char) *
			     (strlen(env[i]) + strlen(tmp) + 1))))
	return (print_err(MALLOC_ERROR));
      strcat(env[i], tmp);
    }
  free(tmp);
  return (env);
}

static int	add_ostype_tools(char **env, char *buff, int fd, int i)
{
  int		size;

  while ((size = read(fd, buff, 1)))
    {
      if (size == -1)
	return (print_error(READ_ERROR));
      buff[size] = 0;
      if (buff[0] >= ' ' || !buff[0])
	{
	  if (!(env[i] = realloc(env[i], sizeof(char) * (strlen(env[i]) + 2))))
	    return (print_error(MALLOC_ERROR));
	  strcat(env[i], buff);
	}
    }
  return (0);
}

char	**add_ostype(char **env)
{
  int	i;
  int	fd;
  char	*buff;

  if (!(env = one_more(env)))
    return (NULL);
  i = 0;
  while (env[i])
    ++i;
  if (!(env[i] = strdup("OSTYPE=")))
    return (print_err(MALLOC_ERROR));
  env[i + 1] = NULL;
  if (!access(PATH_OSTYPE, F_OK | R_OK))
    {
      if ((fd = open(PATH_OSTYPE, O_RDONLY)) == -1)
	return (env);
      if (!(buff = malloc(sizeof(char) * 2)))
	return (print_err(MALLOC_ERROR));
      if (add_ostype_tools(env, buff, fd, i))
	return (NULL);
      free(buff);
    }
  return (env);
}
