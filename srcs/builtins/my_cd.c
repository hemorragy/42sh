/*
** my_cd.c for my_cd in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Fri May 13 08:24:29 2016 Loïs
** Last update Sun Jun  5 19:01:07 2016 Loïs
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

static void	cd_base(const char **cmd, t_sh *data)
{
  if (chdir(cmd[1]))
    {
      my_putstr(cmd[1], 2);
      if (access(cmd[1], F_OK))
	my_putstr(NO_DIR, 2);
      else
	my_putstr(NO_RIGHT, 2);
      set_return_value(0, 1, data);
    }
  else
    set_return_value(0, 0, data);
}

static void	cd_old(const char *old, const char **cmd, t_sh *data)
{
  if (cmd[1][1])
    {
      my_putstr(USAGE_CD, 2);
      set_return_value(0, 1, data);
    }
  else if (old == NULL || chdir(old))
    {
      my_putstr(NO_DIR, 2);
      set_return_value(0, 1, data);
    }
  else
    set_return_value(0, 0, data);
}

static void	cd_home(const char *home, t_sh *data)
{
  if (chdir(home))
    {
      my_putstr(NO_HOME, 2);
      set_return_value(0, 1, data);
    }
  else
    set_return_value(0, 0, data);
}

static void	my_cd_dispatch(const char **cmd, t_sh *data,
			       const char *home, const char *old)
{
  if (!cmd[1])
    cd_home(home, data);
  else if (cmd[1] && cmd[2])
    {
      my_putstr(CD_TOO, 2);
      set_return_value(0, 1, data);
    }
  else if (cmd[1][0] == '-')
    cd_old(old, cmd, data);
  else
    cd_base(cmd, data);
}

int		my_cd(const char **cmd, t_sh *data)
{
  static char	*home = NULL;
  static char	*old = NULL;
  char		*tmp;

  tmp = env_value(data->env, "HOME=");
  if (tmp && (!home || strcmp(tmp, home)))
    {
      if (home)
	free(home);
      if (!(home = strdup(tmp)))
	return (print_error(MALLOC_ERROR));
    }
  tmp = getcwd(NULL, 0);
  my_cd_dispatch(cmd, data, home, old);
  if (change_pwd(data))
    return (1);
  old = get_old(old, tmp);
  return (0);
}
