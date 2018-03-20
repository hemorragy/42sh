/*
** pipe.c for pipe in /home/bittan_c/rendu2/Programmation_Shell/PSU_2015_42sh/srcs/chai
**
** Made by Chai Bittan
** Login   <bittan_c@bittan-c-pc>
**
** Started on  Fri Jun  3 18:06:08 2016 Chai Bittan
** Last update Sun Jun  5 23:39:24 2016 Chai Bittan
*/

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include "structs.h"
#include "functions.h"

static const t_end	g_end[] =
  {
    {SIGSEGV, END_SEGV},
    {SIGFPE, END_FPE},
    {SIGABRT, END_ABRT},
    {SIGPIPE, END_PIPE},
    {SIGQUIT, END_QUIT},
    {SIGBUS, END_BUS},
    {0, NULL}
  };

static int	do_func_pipe(const char *path, const char **tab, t_sh *sh)
{
  if (execve(path, (char * const *)tab, sh->env) == -1)
    return (print_error(EXEC_ERROR));
  return (-1);
}

static int	exec_func_pipe(t_sh *sh, const char **tab)
{
  char	**path;
  bool	check;
  int	i;

  if (!(path = get_path(sh, tab)))
    return (-1);
  i = 0;
  check = 0;
  while (path[i] && !check)
    {
      if (!(path[i] = get_complete_path(tab, path[i])))
	return (-1);
      if (!access(path[i], F_OK | X_OK) && strchr(path[i], '/'))
	{
	  if (do_func_pipe(path[i], tab, sh))
	    return (-1);
	  check = 1;
	}
      ++i;
    }
  free_tab(path);
  if (!check)
    relative_error(tab);
  return ((!check));
}

static int	pipe_child(const char **cmd, t_sh *sh, t_pipe_info *p_info)
{
  int		builtins_value;

  if (!p_info->is_end && dup2(p_info->pp[1], 1) == -1)
    return (-1);
  if (dup2(p_info->fd_in, 0) == -1)
    return (-1);
  close(p_info->pp[0]);
  if ((builtins_value = my_builtins(cmd, sh)))
    return (builtins_value);
  if (exec_func_pipe(sh, cmd))
    return (-1);
  return (-1);
}

static void	pipe_parent(t_pipe_info *p_info, t_sh *sh, int id)
{
  int		status;
  int		i;

  i = -1;
  if (p_info->is_end)
    {
      signal(SIGINT, sig_in_func);
      waitpid(id, &status, WUNTRACED | WCONTINUED);
      if (WIFSIGNALED(status))
	while (g_end[++i].str)
	  if (WTERMSIG(status) == g_end[i].sig)
	    my_putstr(g_end[i].str, 1);
      if (WIFEXITED(status))
	{
	  sh->exit.ret = (WEXITSTATUS(status) == NO_EXIST) ? 1 : 0;
	  sh->last_ret = (WEXITSTATUS(status) == NO_EXIST) ? 1
	    : WEXITSTATUS(status);
	}
    }
  close(p_info->pp[1]);
  p_info->fd_in = p_info->pp[0];
}

int		run_pipe(t_node *node, t_sh *sh)
{
  t_pipe_info	p_info;
  int		builtins_value;
  int		pid;

  p_info.fd_in = 0;
  while (node && node->left && node->left->args)
    {
      p_info.is_end = (node->right == NULL);
      if (p_info.is_end &&
	  (builtins_value = my_builtins((const char **)node->left->args, sh)))
	return (builtins_value == -1 ? -1 : 0);
      if (pipe(p_info.pp) == -1)
	return (-1);
      if ((pid = fork()) == -1)
	return (print_error(FORK_ERROR));
      else if (pid)
	pipe_parent(&p_info, sh, pid);
      else
	exit(pipe_child((const char **)node->left->args, sh, &p_info)
	     * 0 + NO_EXIST);
      node = node->right;
    }
  return (0);
}
