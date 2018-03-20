/*
** default_env.c for default_env in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Fri May 13 06:48:51 2016 Loïs
** Last update Sun Jun  5 04:43:14 2016 Loïs
*/

#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "functions.h"

char		**add_grp(char **env)
{
  int		i;
  struct group	*grp;

  if (!(env = one_more(env)))
    return (NULL);
  i = 0;
  while (env[i])
    ++i;
  if (!(env[i] = strdup("GROUP=")))
    return (print_err(MALLOC_ERROR));
  grp = getgrgid(getgid());
  if (grp)
    {
      if (!(env[i] = realloc(env[i], sizeof(char) *
			     (strlen(env[i]) + strlen(grp->gr_name) + 1))))
	return (print_err(MALLOC_ERROR));
      strcat(env[i], grp->gr_name);
    }
  env[i + 1] = NULL;
  return (env);
}

char		**add_usr(char **env)
{
  int		i;
  struct passwd	*usr;

  if (!(env = one_more(env)))
    return (NULL);
  i = 0;
  while (env[i])
    ++i;
  if (!(env[i] = strdup("USER=")))
    return (print_err(MALLOC_ERROR));
  usr = getpwuid(getuid());
  if (usr)
    {
      if (!(env[i] = realloc(env[i], sizeof(char) *
			     (strlen(env[i]) + strlen(usr->pw_name) + 1))))
	return (print_err(MALLOC_ERROR));
      strcat(env[i], usr->pw_name);
    }
  env[i + 1] = NULL;
  return (env);
}

char	**add_pwd(char **env)
{
  int	i;
  char	*pwd;

  if (!(env = one_more(env)))
    return (NULL);
  i = 0;
  while (env[i])
    ++i;
  if (!(env[i] = strdup("PWD=")))
    return (print_err(MALLOC_ERROR));
  pwd = getcwd(NULL, 0);
  if (pwd)
    {
      if (!(env[i] = realloc(env[i], sizeof(char)
			     * (strlen(env[i]) + strlen(pwd) + 1))))
	return (print_err(MALLOC_ERROR));
      strcat(env[i], pwd);
      free(pwd);
    }
  env[i + 1] = NULL;
  return (env);
}
