/*
** rules.c for rules in /home/brunet_f/modules/elem/PSU_2015_42sh/srcs/julien
** 
** Made by Julien Brunet
** Login   <brunet_f@brunet-f-pc>
** 
** Started on  Thu Jun  2 18:07:11 2016 Julien Brunet
** Last update Sun Jun  5 22:44:38 2016 Julien Brunet
*/

#include <string.h>
#include "functions.h"

t_node		*rule_sep(t_lx *list, int *err)
{
  t_node	*new;

  if ((new = create_node(RULE_SEP, NULL)) == NULL ||
      (new->left = rule_cmp(list, err)) == NULL)
    return (NULL);
  while (list != NULL && list->type != LX_SEP)
    list = list->next;
  if (list != NULL)
    {
      if ((new->right = rule_sep(list->next, err)) == NULL)
	return (NULL);
      new->lexem = strdup(SEP);
    }
  return (new);
}

t_node		*rule_cmp(t_lx *list, int *err)
{
  t_node	*new;
  int		empty;

  empty = 0;
  if (((new = create_node(RULE_CMP, NULL)) == NULL) ||
      ((new->left = rule_red(list, err)) == NULL))
    return (NULL);
  while (list != NULL && list->type != LX_CMP && list->type != LX_SEP)
    list = list->next;
  if (list != NULL && list->type == LX_CMP)
    {
      if ((empty = is_cmd_empty(new->left)) && strcmp(list->value, OR) == 0)
	return (throw_parser_error(ERR_NULL_CMD, err));
      if ((new->right = rule_cmp(list->next, err)) == NULL)
	return (NULL);
      if (!empty && is_cmd_empty(new->right))
	return (throw_parser_error(ERR_NULL_CMD, err));
      new->lexem = strdup(list->value);
    }
  return (new);
}

t_node		*rule_pipe(t_lx *list, int *err)
{
  t_node	*new;

  if (((new = create_node(RULE_PIPE, NULL)) == NULL) ||
      ((new->left = rule_cmd(list, err)) == NULL))
    return (NULL);
  while (list && list->type != LX_PIPE &&
	 list->type != LX_CMP && list->type != LX_SEP)
    list = list->next;
  if (list != NULL && list->type == LX_PIPE)
    {
      if (is_cmd_empty(new->left))
	return (throw_parser_error(ERR_NULL_CMD, err));
      if ((new->right = rule_pipe(list->next, err)) == NULL)
	return (NULL);
      if (is_cmd_empty(new->right))
	return (throw_parser_error(ERR_NULL_CMD, err));
      new->lexem = strdup(PIPE);
    }
  return (new);
}

t_node		*rule_cmd(t_lx *list, int *err)
{
  int		i;
  t_lx		*tmp;

  (void)err;
  i = 0;
  tmp = list;
  while (tmp != NULL && tmp->type == LX_WORD)
    {
      ++i;
      tmp = tmp->next;
    }
  return (create_node(RULE_CMD, export_list_part(list, i)));
}
