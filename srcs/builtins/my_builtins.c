/*
** my_builtins.c for my_builtins in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Mon May 16 14:29:57 2016 Loïs
** Last update Sun Jun  5 18:12:21 2016 Loïs
*/

#include <string.h>
#include "functions.h"

static const t_built	g_built[] =
  {
    {"exit", &my_exit},
    {"cd", &my_cd},
    {"echo", &my_echo},
    {"setenv", &my_setenv},
    {"unsetenv", &my_unsetenv},
    {"history", &my_history},
    {NULL, NULL}
  };

int	set_return_value(int ret, int exit, t_sh *data)
{
  data->last_ret = exit;
  data->exit.ret = exit;
  return (ret);
}

int	my_builtins(const char **cmd, t_sh *data)
{
  int	i;

  i = 0;
  while (g_built[i].value)
    {
      if (!strcmp(cmd[0], g_built[i].value))
	{
	  if (g_built[i].function(cmd, data))
	    return (-1);
	  return (1);
	}
      ++i;
    }
  return (0);
}
