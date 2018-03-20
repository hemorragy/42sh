/*
** epure_str.c for epure_str in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Fri May 27 03:26:37 2016 Loïs
** Last update Mon May 30 15:40:35 2016 Loïs
*/

#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "defines.h"

static void	epure_tools(const char *str, char *new, int *i, int *idx)
{
  if (*i)
    {
      new[*idx] = ' ';
      ++*idx;
    }
  while (str[*i] == ' ' || str[*i] == '\t')
    ++*i;
}

char	*epure_str(char *str)
{
  char	*new;
  int	i;
  int	idx;

  i = 0;
  idx = 0;
  if (!(new = malloc(sizeof(char) * (strlen(str) + 1))))
    return (print_err(MALLOC_ERROR));
  while (str[i])
    {
      if (str[i] == ' ' || str[i] == '\t')
	epure_tools(str, new, &i, &idx);
      else
	{
	  new[idx] = str[i];
	  ++idx;
	  ++i;
	}
    }
  if (idx > 0 && new[idx - 1] == ' ')
    --idx;
  new[idx] = 0;
  free(str);
  return (new);
}
