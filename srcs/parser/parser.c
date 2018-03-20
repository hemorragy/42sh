/*
** parser.c for parser in /home/brunet_f/modules/elem/PSU_2015_42sh/srcs/julien
** 
** Made by Julien Brunet
** Login   <brunet_f@brunet-f-pc>
** 
** Started on  Thu Jun  2 01:14:04 2016 Julien Brunet
** Last update Sun Jun  5 22:44:11 2016 Julien Brunet
*/

#include <stdlib.h>
#include <string.h>
#include "functions.h"

char	**export_list_part(t_lx *list, int size)
{
  int	i;
  char	**exp;

  if (size == 0 || list == NULL ||
      (exp = malloc(sizeof(char *) * (size + 1))) == NULL)
    return (NULL);
  i = 0;
  while (i < size)
    {
      if ((exp[i] = strdup(list->value)) == NULL)
	return (NULL);
      list = list->next;
      ++i;
    }
  exp[i] = NULL;
  return (exp);
}

t_lx	*remove_lx(t_lx **list, t_lx *item)
{
  t_lx	*next;

  if (item->next != NULL)
    item->next->prev = item->prev;
  if (item->prev != NULL)
    item->prev->next = item->next;
  next = item->next;
  if (item == *list)
    *list = next;
  free(item);
  return (next);
}

int		is_cmd_empty(t_node *node)
{
  while (node->left != NULL)
    node = node->left;
  return (node->args == NULL);
}

void		*throw_parser_error(int code, int *err)
{
  if (code == ERR_NULL_CMD)
    my_putstr(ERR_NULL_CMD_MSG, 2);
  else if (code == ERR_AMBIGUOUS_RED)
    my_putstr(ERR_AMBIGUOUS_RED_MSG, 2);
  else if (code == ERR_MISSING_FILE)
    my_putstr(ERR_MISSING_FILE_MSG, 2);
  *err = code;
  return (NULL);
}

t_node		*parse(t_lx *list, int *err)
{
  return (rule_sep(list, err));
}
