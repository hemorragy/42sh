/*
** structs.h for 42sh in /home/antoin_g/rendu/Unix/tmp/PSU_2015_42sh
**
** Made by Loïs
** Login   <antoin_g@epitech.net>
**
** Started on  Sun Jun  5 23:41:53 2016 Loïs
** Last update Sun Jun  5 23:41:55 2016 Loïs
*/

#ifndef STRUCTS_H_
# define STRUCTS_H_

# include <stdbool.h>
# include "defines.h"

/*
** REDIRECT
*/

typedef int	(*t_redir)(const char *file, const char *type);

typedef struct	s_fd
{
  int		in;
  int		out;
}		t_fd;

/*
** HISTORY
*/

typedef struct		s_hist_list
{
  int			nb;
  char			*cmd;
  unsigned long		time;
  struct s_hist_list	*next;
  struct s_hist_list	*prev;
}			t_hist_list;

typedef struct	s_hist
{
  int		size;
  char		*hist_pwd;
  t_hist_list	*first;
  t_hist_list	*last;
}		t_hist;

/*
** EXIT
*/

typedef struct	s_exit
{
  bool		end;
  int		ret;
}		t_exit;

/*
** ALL
*/

typedef struct	s_sh
{
  bool		ex;
  int		last_ret;
  t_exit	exit;
  char		**env;
  t_fd		fd;
  t_hist	hist;
}		t_sh;

/*
** HISTORY OPT
*/

typedef int	(*t_func_hist)(const char **, t_sh *sh);

typedef struct	s_hist_opt
{
  char		opt;
  t_func_hist	func;
}		t_hist_opt;

/*
** UTILS
*/

typedef struct	s_gnl
{
  int		test;
  char		*line;
}		t_gnl;

/*
** GETENV
*/

typedef char	**(*t_default)(char **);

typedef struct	s_def
{
  char		*value;
  t_default	function;
}		t_def;

/*
** BUILTINS
*/

typedef int	(*t_build)(const char **, t_sh *);

typedef struct	s_built
{
  char		*value;
  t_build	function;
}		t_built;

typedef struct	s_echo
{
  char		prev;
  char		next;
}		t_echo;

/*
** PROMPT
*/

t_sh		*g_data;
typedef int	(*t_prmt)(const char *, const t_sh *, int *);

typedef struct	s_prompt
{
  char		value;
  t_prmt	function;
}		t_prompt;

/*
** EXEC
*/

typedef struct	s_end
{
  int		sig;
  char		*str;
}		t_end;

/*
** PARSER/LEXER
*/

typedef struct	s_lx
{
  t_lx_type	type;
  char		*value;
  struct s_lx	*next;
  struct s_lx	*prev;
}		t_lx;

typedef struct	s_lx_data
{
  t_lx_type	type;
  char		*value;
  char		*str;
  char		***lx_tab;
  int		idx_str;
}		t_lx_data;

typedef struct	s_node
{
  t_rule_type	type;
  char		*lexem;
  char		**args;
  struct s_node	*left;
  struct s_node	*right;
}		t_node;

/*
** PIPE
*/

typedef struct	s_pipe_info
{
  int		fd_in;
  int		is_end;
  int		pp[2];
}		t_pipe_info;

#endif /* !STRUCTS_H_ */
