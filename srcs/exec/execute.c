/*
** execute.c for execute in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Wed Jun  1 02:12:29 2016 Loïs
** Last update Sun Jun  5 15:13:31 2016 Loïs
*/

#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include "functions.h"
#include "defines.h"

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

void	sig_in_func(int sig)
{
  (void)sig;
  my_putstr("\n", 1);
}

static int	do_func(const char *path, const char **tab, t_sh *sh)
{
  pid_t		id;
  int		status;
  int		i;

  if ((id = fork()) == -1)
    return (print_error(FORK_ERROR));
  if (id)
    {
      signal(SIGINT, sig_in_func);
      waitpid(id, &status, WUNTRACED | WCONTINUED);
      i = -1;
      if (WIFSIGNALED(status))
	while (g_end[++i].str)
	  if (WTERMSIG(status) == g_end[i].sig)
	    my_putstr(g_end[i].str, 1);
      if (WIFEXITED(status))
	sh->last_ret = WEXITSTATUS(status);
    }
  else
    {
      if (execve(path, (char * const *)tab, sh->env) == -1)
	return (print_error(EXEC_ERROR));
      return (-1);
    }
  return (0);
}

char	**get_path(t_sh *sh, const char **tab)
{
  char	**path;
  char	*tmp;
  int	i;

  if (tab[0][0] == '/')
    {
      if (!(path = my_str_to_wordtab("a", ' ')))
	return (NULL);
      path[0][0] = '\0';
    }
  else
    {
      tmp = (!env_value(sh->env, "PATH=")) ? DEFAULT_PATH
	: env_value(sh->env, "PATH=");
      if (!(path = my_str_to_wordtab(tmp, ':')))
	return (NULL);
      i = 0;
      while (path[i])
	++i;
      if (!(path = realloc(path, sizeof(char *) * (i + 2))) ||
	  !(path[i] = strdup("")))
	return (NULL);
      path[i + 1] = NULL;
    }
  return (path);
}

char	*get_complete_path(const char **tab, char *path)
{
  if (!(path = realloc(path, sizeof(char) *
			  (strlen(path) + strlen(tab[0]) + 2))))
    return (print_err(MALLOC_ERROR));
  if (strlen(path) && path[strlen(path) - 1] != '/')
    path = strcat(path, "/");
  path = strcat(path, tab[0]);
  return (path);
}

int	exec_func(t_sh *sh, const char **tab)
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
	  if (do_func(path[i], tab, sh))
	    return (-1);
	  check = 1;
	}
      ++i;
    }
  free_tab(path);
  if (!check)
    relative_error(tab);
  return (0);
}
