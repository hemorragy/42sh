/*
** echo.c for echo in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Tue May 17 15:05:33 2016 Loïs
** Last update Sun Jun  5 04:41:59 2016 Loïs
*/

#include <stdlib.h>
#include <string.h>
#include "functions.h"

static const t_echo	g_echo[] =
  {
    {'\\', '\\'},
    {'a', '\a'},
    {'b', '\b'},
    {'c', 'c'},
    {'e', '\e'},
    {'f', '\f'},
    {'n', '\n'},
    {'r', '\r'},
    {'t', '\t'},
    {'v', '\v'},
    {'0', '\0'},
    {0, 0}
  };

static int	analyze_combin(char *str, int *i)
{
  bool		check;
  int		idx;

  check = 0;
  idx = 0;
  while (g_echo[idx].prev && !check)
    {
      if (g_echo[idx].prev == str[*i + 1])
	{
	  if (g_echo[idx].next == 'c')
	    {
	      free(str);
	      return (1);
	    }
	  my_putchar(g_echo[idx].next, 1);
	  check = 1;
	}
      ++idx;
    }
  if (!check)
    my_putchar(str[*i], 1);
  else
    ++*i;
  return (0);
}

static int	print_it(char *str)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] == '\\' && str[i + 1])
	{
	  if (analyze_combin(str, &i))
	    return (0);
	}
      else
	my_putchar(str[i], 1);
      ++i;
    }
  free(str);
  return (0);
}

static int	get_size_print(const char **cmd)
{
  int		size;
  int		i;

  i = 1;
  size = 1;
  while (cmd[i])
    {
      if (i != 1 || strcmp(cmd[i], N_OPT))
	size = size + strlen(cmd[i]) + 1;
      ++i;
    }
  return (size);
}

int	my_echo(const char **cmd, t_sh *data)
{
  char	*print;
  int	i;

  (void)data;
  if (!(print = malloc(sizeof(char) * get_size_print(cmd))))
    return (print_error(MALLOC_ERROR));
  print[0] = 0;
  i = 1;
  while (cmd[i])
    {
      if (i != 1 || strcmp(cmd[i], N_OPT))
	{
	  print = strcat(print, cmd[i]);
	  if (cmd[i + 1])
	    print = strcat(print, " ");
	}
      ++i;
    }
  if (print_it(print))
    return (set_return_value(0, 0, data));
  if (!cmd[1] || strcmp(cmd[1], N_OPT))
    my_putchar('\n', 1);
  return (set_return_value(0, 0, data));
}
