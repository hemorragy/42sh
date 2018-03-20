/*
** lexer_utils.c for 42sh in /home/eddy/PSU_2015_42sh/srcs/lexer
**
** Made by Eddy Chouikha
** Login   <eddy@epitech.net>
**
** Started on  Thu Jun  2 19:47:01 2016 Eddy Chouikha
** Last update Sun Jun  5 14:00:15 2016 Eddy Chouikha
*/

#include <stdlib.h>
#include "defines.h"
#include "functions.h"

t_lx	*create_lx(const t_lx_type type, char *value)
{
  t_lx	*new;

  if (!(new = malloc(sizeof(t_lx))))
    return (NULL);
  new->type = type;
  new->value = value;
  new->prev = NULL;
  new->next = NULL;
  return (new);
}

t_lx	*add_lx(t_lx *list, const t_lx_type type, char *value)
{
  t_lx	*new;

  if (!(new = create_lx(type, value)))
    return (NULL);
  if (!list)
    return (new);
  new->prev = list;
  new->prev->next = new;
  return (list);
}

void	clean_lx_tab(t_lx_data *data)
{
  int	idx;

  idx = 0;
  while (idx < NB_LX_TYPES - 1)
    {
      free(data->lx_tab[idx]);
      ++idx;
    }
}

void	clean_lx_list(t_lx *list)
{
  t_lx	*tmp;

  tmp = list;
  while (tmp->next != NULL)
    {
      list = list->next;
      if (tmp->type == LX_WORD)
	free(tmp->value);
      free(tmp);
      tmp = list;
    }
  free(list);
}
