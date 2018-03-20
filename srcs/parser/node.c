/*
** node.c for node in /home/brunet_f/modules/elem/PSU_2015_42sh/srcs/julien
** 
** Made by Julien Brunet
** Login   <brunet_f@brunet-f-pc>
** 
** Started on  Thu Jun  2 18:34:06 2016 Julien Brunet
** Last update Sat Jun  4 21:10:41 2016 Julien Brunet
*/

#include <stdlib.h>
#include "functions.h"

void	display_type(t_rule_type type)
{
  if (type == RULE_SEP)
    my_putstr("RULE_SEP", 1);
  else if (type == RULE_CMD)
    my_putstr("RULE_CMD", 1);
  else if (type == RULE_PIPE)
    my_putstr("RULE_PIPE", 1);
  else if (type == RULE_CMP)
    my_putstr("RULE_CMP", 1);
  else
    my_putstr("RULE START", 1);
}

t_node		*create_node(int type, char **args)
{
  t_node	*node;

  if ((node = malloc(sizeof(*node))) == NULL)
    return (NULL);
  node->left = NULL;
  node->right = NULL;
  node->lexem = NULL;
  node->args = args;
  node->type = type;
  return (node);
}

void	display_node(t_node *node)
{
  int	i;

  if (node->args != NULL)
    {
      i = 0;
      while (node->args[i])
	{
	  my_putstr(node->args[i], 1);
	  my_putstr(" ", 1);
	  ++i;
	}
    }
  else
    my_putstr("NO ARGS\n", 1);
  my_putstr("\n", 1);
}
