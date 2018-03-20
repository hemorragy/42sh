/*
** exit.c for exit in /home/antoin_g/rendu/Unix/PSU_2015_42sh
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Sun Jun  5 03:37:33 2016 Loïs
** Last update Sun Jun  5 04:26:14 2016 Loïs
*/

#include "functions.h"

int	my_exit(const char **cmd, t_sh *data)
{
  if (cmd[1] && (cmd[2] ||
		 !my_str_isnumber((cmd[1][0] == '-') ? cmd[1] + 1 : cmd[1])))
    {
      my_putstr(EXIT_TOO_ARG, 2);
      return (set_return_value(0, 1, data));
    }
  data->exit.end = 1;
  if (!cmd[1])
    data->exit.ret = 0;
  else
    data->exit.ret = my_getnbr(cmd[1]);
  data->exit.ret = (data->exit.ret > 0) ? data->exit.ret % 256
    : data->exit.ret % -256;
  return (0);
}
