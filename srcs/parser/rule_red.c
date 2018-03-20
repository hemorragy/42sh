/*
** rule_red.c for rule_red in /home/brunet_f/modules/elem/PSU_2015_42sh
** 
** Made by Julien Brunet
** Login   <brunet_f@brunet-f-pc>
** 
** Started on  Sun Jun  5 22:44:44 2016 Julien Brunet
** Last update Sun Jun  5 23:28:37 2016 Chai Bittan
*/

#include <string.h>
#include "functions.h"

static void	update_cache(int cache[3], int step, t_lx *lx)
{
  if (step == 0)
    {
      cache[0] = 0;
      cache[1] = 0;
      cache[2] = 0;
    }
  else
    {
      if (lx->type == LX_PIPE)
	cache[0] = 1;
      else if (lx->type == LX_RED)
	{
	  if (IS_RED_RIGHT(lx->value))
	    cache[1] = 1;
	  else if (IS_RED_LEFT(lx->value))
	    cache[2] = 1;
	}
    }
}

static int	check_red_err(int cache[3], t_lx *lx)
{
  if ((IS_RED_LEFT(lx->value) && (cache[0] || cache[2])) ||
      (IS_RED_RIGHT(lx->value) && cache[1]))
    return (ERR_AMBIGUOUS_RED);
  if (lx->next == NULL || lx->next->type != LX_WORD)
    return (ERR_MISSING_FILE);
  return (0);
}

static void	rule_red_cond(t_lx *list, t_node *new, t_lx *tmp)
{
  if (new->right == NULL)
    {
      new->right = create_node(RULE_RED, NULL);
      new->right->left = create_node(RULE_CMD, NULL);
      new->right->left->lexem = strdup(tmp->next->value);
      new->lexem = strdup(tmp->value);
    }
  else
    {
      new->right->right = create_node(RULE_RED, NULL);
      new->right->right->left->lexem = strdup(tmp->next->value);
      new->right->lexem = strdup(tmp->value);
    }
  tmp = remove_lx(&list, tmp);
  tmp = remove_lx(&list, tmp);
}

static t_node	*return_rule(t_node *new, int *err, t_lx *list)
{
  new->left = rule_pipe(list, err);
  return (new);
}

t_node		*rule_red(t_lx *list, int *err)
{
  t_node	*new;
  t_lx		*tmp;
  int		cache[4];

  if ((new = create_node(RULE_RED, NULL)) == NULL)
    return (NULL);
  tmp = list;
  update_cache(cache, 0, NULL);
  while (tmp != NULL && tmp->type != LX_CMP && tmp->type != LX_SEP)
    {
      if (tmp->type == LX_PIPE && cache[1])
	return (throw_parser_error(ERR_AMBIGUOUS_RED, err));
      if (tmp->type == LX_RED)
	{
	  if ((cache[4] = check_red_err(cache, tmp)))
	    return (throw_parser_error(cache[4], err));
	  rule_red_cond(list, new, tmp);
	}
      if (tmp != NULL)
	{
	  update_cache(cache, 1, tmp);
	  tmp = tmp->next;
	}
    }
  return (return_rule(new, err, list));
}
