/*
** lib.c for lib in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Mon May  9 13:26:11 2016 Loïs
** Last update Sat Jun  4 23:43:54 2016 Loïs
*/

#include <limits.h>
#include <unistd.h>
#include <string.h>
#include "defines.h"

void	my_putchar(char c, int fd)
{
  write(fd, &c, 1);
}

void	my_putstr(const char *str, int fd)
{
  write(fd, str, strlen(str));
}

void	*print_err(const char *str)
{
  write(2, str, strlen(str));
  return (NULL);
}

int	print_error(const char *str)
{
  write(2, str, strlen(str));
  return (-1);
}

void	my_put_nbr(int nb, int fd)
{
  long	a;

  if (nb == INT_MIN)
    my_putstr(MINIMUM_INT, 1);
  else
    {
      if (nb < 0)
        {
          my_putchar('-', 1);
          nb = -nb;
        }
      a = 1;
      while (a <= nb / 10)
        a = a * 10;
      while (a > 0)
        {
          my_putchar(nb / a % 10 + '0', fd);
          a = a / 10;
        }
    }
}
