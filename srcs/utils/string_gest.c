/*
** lib.c for lib in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Fri Jun  3 17:07:19 2016 Loïs
** Last update Sat Jun  4 16:17:53 2016 Loïs
*/

#include <stdlib.h>
#include <string.h>

char	*add_two_str(char *s1, char *s2)
{
  if (!(s1 = realloc(s1, sizeof(char) * (strlen(s1) + strlen(s2) + 1))))
    return (NULL);
  s1 = strcat(s1, s2);
  return (s1);
}

int	my_str_isnumber(const char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] > '9' || str[i] < '0')
	return (0);
      ++i;
    }
  return (1);
}
