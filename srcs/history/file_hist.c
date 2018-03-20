/*
** file_hist.c for file_hist in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Sat Jun  4 16:36:44 2016 Loïs
** Last update Sun Jun  5 04:55:06 2016 Loïs
*/

#include <fcntl.h>
#include "functions.h"

static void	print_time_hist(unsigned long nb, int fd)
{
  unsigned long	a;

  a = 1;
  while (a <= nb / 10)
    a = a * 10;
  while (a > 0)
    {
      my_putchar(nb / a % 10 + '0', fd);
      a = a / 10;
    }
}

int		add_hist_to_file(t_sh *data, const char *file)
{
  t_hist_list	*tmp;
  int		fd;

  fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, RIGHT_HISTO);
  if (fd != -1)
    {
      tmp = data->hist.first;
      while (tmp)
	{
	  print_time_hist(tmp->time, fd);
	  my_putchar('\n', fd);
	  my_putstr(tmp->cmd, fd);
	  my_putchar('\n', fd);
	  tmp = tmp->next;
	}
    }
  return (0);
}
