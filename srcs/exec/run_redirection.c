/*
** run_redirection.c for run_redirection in /home/alliel_a/PSU_2015_42sh/srcs/adrien
**
** Made by Adrien Alliel
** Login   <alliel_a@alliel-a-pc>
**
** Started on  Sun Jun  5 16:41:46 2016 Adrien Alliel
** Last update Sun Jun  5 23:39:09 2016 Chai Bittan
*/

#include <unistd.h>
#include "functions.h"

void	init_tab(t_redir *redir)
{
  redir[0] = &redirect_right;
  redir[1] = &redirect_double_right;
  redir[2] = &redirect_left;
  redir[3] = &redirect_double_left;
  redir[4] = '\0';
}

int	pars_tab(t_redir redir[5], char *file, char *redirect_type)
{
  int	i;
  int	type;

  i = 0;
  while (redir[i])
    {
      if ((type = redir[i](file, redirect_type)) == SUCCESS)
	return (type);
      ++i;
    }
  return (-1);
}

int		run_redir(t_node *node, t_sh *sh)
{
  t_node	*tmp;
  t_node	*old;
  t_redir	redir[5];
  int		ret;

  old = node;
  tmp = node->right;
  init_tab(redir);
  while (tmp != NULL)
    {
      if (pars_tab(redir, tmp->left->lexem, old->lexem) == FAILED)
	{
	  my_putstr(tmp->left->lexem, 2);
	  my_putstr(NO_FILE, 2);
	  return (0);
	}
      old = tmp;
      tmp = tmp->right;
    }
  ret = run_pipe(node->left, sh);
  dup2(sh->fd.in, 0);
  dup2(sh->fd.out, 1);
  return (ret);
}
