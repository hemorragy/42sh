/*
** my_cd_tools.c for my_cd_tools in /home/antoin_g/rendu/Unix/PSU_2015_42sh
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Fri Jun  3 01:23:55 2016 Loïs
** Last update Sun Jun  5 18:57:50 2016 Loïs
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "functions.h"

char		*get_old(char *old, char *tmp)
{
  char		*act;

  act = getcwd(NULL, 0);
  if (tmp == NULL)
    {
      if (old != NULL)
	free(old);
      old = NULL;
    }
  else
    {
      if (strcmp(tmp, act))
	{
	  if (old != NULL)
	    free(old);
	  if (!(old = strdup(tmp)))
	    return (print_err(MALLOC_ERROR));
	}
      free(tmp);
    }
  if (act != NULL)
    free(act);
  return (old);
}

int		change_pwd(t_sh *data)
{
  static char	*cmd[] = {"setenv", "PWD", NULL, NULL};
  int		tmp_ex;
  int		tmp_ret;

  tmp_ex = data->exit.ret;
  tmp_ret = data->last_ret;
  if (!(cmd[2] = getcwd(NULL, 0)))
    return (0);
  if (my_setenv((const char **)cmd, data))
    return (1);
  free(cmd[2]);
  data->exit.ret = tmp_ex;
  data->last_ret = tmp_ret;
  return (0);
}
