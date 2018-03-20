/*
** my_str_to_wordtab.c for my_str_to_wordtab in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Fri May 27 03:13:48 2016 Loïs
** Last update Mon May 30 15:44:12 2016 Loïs
*/

#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "defines.h"

static int	count_word(const char *str, char sepparator)
{
  int		i;
  int		count;

  i = 0;
  count = 0;
  while (str[i])
    {
      if (i == 0 || str[i - 1] == sepparator)
	++count;
      ++i;
    }
  return (count);
}

char	**my_str_to_wordtab(const char *str, char sepparator)
{
  char	**tab;
  int	prev;
  int	idx;
  int	i;

  if (!(tab = malloc(sizeof(char *) * (count_word(str, sepparator) + 1))))
    return (NULL);
  i = 0;
  idx = 0;
  while (str[i])
    {
      prev = i;
      while (str[i] && str[i] != sepparator)
	++i;
      if (!(tab[idx] = strndup(str + prev, i - prev)))
	return (print_err(MALLOC_ERROR));
      ++idx;
      i = (str[i]) ? i + 1 : i;
    }
  tab[idx] = NULL;
  return (tab);
}
