/*
** exec_error.c for exec_error in /home/antoin_g/rendu/Unix/PSU_2015_42sh
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Fri Jun  3 03:25:12 2016 Loïs
** Last update Sun Jun  5 15:14:19 2016 Loïs
*/

#include "functions.h"

void	relative_error(const char **tab)
{
  int	i;
  int	test;

  i = 0;
  test = 0;
  while (tab[0][i] && tab[0][0] != '/')
    {
      if (tab[0][i] == '/')
        test = i + 1;
      ++i;
    }
  my_putstr(tab[0] + test, 2);
  my_putstr(": Command not found.\n", 2);
}
