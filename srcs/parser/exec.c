/*
** exec.c for exec in /home/brunet_f/modules/elem/PSU_2015_42sh
** 
** Made by Julien Brunet
** Login   <brunet_f@brunet-f-pc>
** 
** Started on  Sat Jun  4 03:27:56 2016 Julien Brunet
** Last update Sun Jun  5 23:08:41 2016 Julien Brunet
*/

#include <string.h>
#include <unistd.h>
#include "functions.h"

static int	run_left_node(t_node *node, t_sh *this)
{
  if (node->type == RULE_RED)
    return (run_redir(node, this));
  if (run_left_node(node->left, this))
    return (-1);
  if (node->type == RULE_CMP &&
      node->lexem != NULL &&
      ((strcmp(node->lexem, OR) == 0 && this->last_ret == 0) ||
       (strcmp(node->lexem, AND) == 0 && this->last_ret != 0)))
    return (0);
  if (node->right != NULL && run_left_node(node->right, this))
    return (-1);
  return (0);
}

int	exec_tree(t_node *tree, t_sh *this)
{
  return (run_left_node(tree, this));
}
