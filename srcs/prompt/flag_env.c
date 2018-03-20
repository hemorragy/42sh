/*
** flag1.c for flag1 in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Mon May 23 17:02:30 2016 Loïs
** Last update Sun Jun  5 04:45:12 2016 Loïs
*/

#include <string.h>
#include "functions.h"

int	prmt_double(const char *prompt, const t_sh *data, int *i)
{
  (void)prompt, (void)data;
  my_putchar('%', 1);
  ++*i;
  return (0);
}

int	prmt_full_host(const char *prompt, const t_sh *data, int *i)
{
  char	*host;

  (void)prompt;
  ++*i;
  if ((host = env_value(data->env, "HOST=")))
    my_putstr(host, 1);
  return (0);
}

int	prmt_part_host(const char *prompt, const t_sh *data, int *i)
{
  char	*host;
  int	idx;

  (void)prompt;
  ++*i;
  idx = 0;
  if ((host = env_value(data->env, "HOST=")))
    while (host[idx] && host[idx] != '.')
      {
	my_putchar(host[idx], 1);
	++idx;
      }
  return (0);
}

int	prmt_pwd(const char *prompt, const t_sh *data, int *i)
{
  char	*pwd;

  (void)prompt;
  ++*i;
  if ((pwd = env_value(data->env, "PWD=")))
    my_putstr(pwd, 1);
  return (0);
}

int	prmt_pwd_home(const char *prompt, const t_sh *data, int *i)
{
  char	*pwd;
  char	*home;

  (void)prompt;
  ++*i;
  if (!(pwd = env_value(data->env, "PWD=")))
    return (0);
  home = env_value(data->env, "HOME=");
  if (home && strlen(home) && !strncmp(pwd, home, strlen(home)))
    {
      my_putchar('~', 1);
      if (pwd[strlen(home)] != '/')
	my_putchar('/', 1);
      my_putstr(pwd + strlen(home), 1);
    }
  else
    my_putstr(pwd, 1);
  return (0);
}
