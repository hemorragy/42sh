/*
** history.c for history in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Fri Jun  3 16:14:28 2016 Loïs
** Last update Sun Jun  5 04:47:34 2016 Loïs
*/

#include <string.h>
#include "functions.h"

static const t_hist_opt	g_opt[] =
  {
    {'c', &hist_clean},
    {'M', &hist_file_m},
    {'L', &hist_file_l},
    {'S', &hist_file_s},
    {'r', &hist_nbr},
    {'T', &hist_nbr},
    {'h', &hist_nbr},
    {0, NULL},
  };

static int		is_valid_opt(const char *str)
{
  static const char	opt_list[] = "chrSLMT";
  int			i;

  i = 1;
  if (!str[1])
    return (0);
  while (str[i])
    {
      if (!strchr(opt_list, str[i]))
	return (0);
      ++i;
    }
  return (1);
}

static int	my_history_tools(const char **cmd, t_sh *data)
{
  bool		test;
  int		i;

  if (!is_valid_opt(cmd[1]))
    {
      my_putstr(USAGE_HIST, 2);
      return (set_return_value(0, 1, data));
    }
  i = 0;
  test = 0;
  while (g_opt[i].opt && !test)
    {
      if (strchr(cmd[1], g_opt[i].opt))
	{
	  test = 1;
	  if (g_opt[i].func(cmd, data))
	    return (1);
	}
      ++i;
    }
  return (0);
}

int	my_history(const char **cmd, t_sh *data)
{
  if (cmd[1] && cmd[2] && cmd[3])
    {
      my_putstr(HIST_TOO_ARG, 2);
      return (set_return_value(0, 1, data));
    }
  if (!cmd[1])
    {
      if (print_hist(data, NULL, -1))
	return (-1);
    }
  else if (cmd[1][0] != '-')
    {
      if (!my_str_isnumber(cmd[1]))
	{
	  my_putstr(HIST_NOT_NBR, 2);
	  return (0);
	}
      if (print_hist(data, NULL, my_hist_getnbr(cmd[1])))
	return (1);
    }
  else
    return (my_history_tools(cmd, data));
  return (set_return_value(0, 0, data));
}
