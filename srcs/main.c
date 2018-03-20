/*
** main.c for main in /home/chouik_e/Rendu/PSU_2015_42sh/srcs
**
** Made by Eddy Chouikha
** Login   <chouik_e@chouik-e-pc>
**
** Started on  Sun May  8 14:01:48 2016 Eddy Chouikha
** Last update Sun Jun  5 23:11:27 2016 Chai Bittan
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "defines.h"
#include "functions.h"

static void	sigs(int sig)
{
  if (sig == SIGINT)
    {
      my_putstr(HIDE_CTRL_C, 1);
      aff_prompt(g_data);
    }
}

static void	end_of_shell(t_sh *data, const struct stat *detail)
{
  free_tab(data->env);
  add_hist_to_file(data, data->hist.hist_pwd);
  free_hist(data);
  free(data->hist.hist_pwd);
  if (S_ISCHR(detail->st_mode))
    my_putstr(END_OF_SHELL, 1);
}

static char	*tree_action(char *str, t_sh *data)
{
  t_lx		*lexems;
  int		err;
  t_node	*tree;

  err = 0;
  if (!(str = add_hist_to_cmd(str, data)))
    return (NULL);
  if (!data->ex)
    if ((str = epure_str(str)) == NULL ||
	add_new_hist(data, str) ||
	(lexems = lexer(str)) == NULL ||
	((tree = parse(lexems, &err)) == NULL && err == 0) ||
	(err == 0 && exec_tree(tree, data) == -1))
      return (NULL);
  return (str);
}

static int	shell_loop(t_sh *data, const struct stat *detail)
{
  char		*str;

  while (!data->exit.end && (str = get_next_line(0)))
    {
      data->ex = 0;
      if (str[0] < 32)
	return (0);
      if (str[0])
	if (!(str = tree_action(str, data)))
	  return (-1);
      g_data = data;
      signal(SIGINT, sigs);
      if (S_ISCHR(detail->st_mode) && !data->exit.end)
	aff_prompt(data);
      free(str);
    }
  end_of_shell(data, detail);
  return (data->exit.ret);
}

int		main(int ac, char **av, char **env)
{
  struct stat	detail;
  t_sh		data;

  (void)ac, (void)av;
  if (fstat(0, &detail))
    return (print_error(STAT_ERROR));
  data.last_ret = 0;
  data.exit.end = 0;
  data.exit.ret = 0;
  if (!(data.env = get_env((const char **)env)) || init_hist(&data)
      || get_history(&data, data.hist.hist_pwd))
    return (-1);
  data.fd.in = dup(0);
  data.fd.out = dup(1);
  if (S_ISCHR(detail.st_mode))
    aff_prompt(&data);
  g_data = &data;
  signal(SIGINT, sigs);
  signal(SIGTERM, sigs);
  return (shell_loop(&data, &detail));
}
