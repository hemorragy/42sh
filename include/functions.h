/*
** functions.h for 42sh in /home/antoin_g/rendu/Unix/tmp/PSU_2015_42sh
**
** Made by Loïs
** Login   <antoin_g@epitech.net>
**
** Started on  Sun Jun  5 23:41:42 2016 Loïs
** Last update Sun Jun  5 23:41:44 2016 Loïs
*/

#ifndef FUNCTIONS_H_
# define FUNCTIONS_H_

# include <time.h>
# include "structs.h"

/*
** PROMPT
*/
int	aff_prompt(t_sh *data);
int	prmt_ret(const char *prompt, const t_sh *data, int *i);
int	prmt_day(const char *prompt, const t_sh *data, int *i);
int	prmt_pwd(const char *prompt, const t_sh *data, int *i);
int	prmt_env(const char *prompt, const t_sh *data, int *i);
int	prmt_mon(const char *prompt, const t_sh *data, int *i);
int	prmt_user(const char *prompt, const t_sh *data, int *i);
int	prmt_year(const char *prompt, const t_sh *data, int *i);
int	prmt_hour(const char *prompt, const t_sh *data, int *i);
int	prmt_double(const char *prompt, const t_sh *data, int *i);
int	prmt_mon_nb(const char *prompt, const t_sh *data, int *i);
int	prmt_hour_ap(const char *prompt, const t_sh *data, int *i);
int	prmt_day_week(const char *prompt, const t_sh *data, int *i);
int	prmt_hour_sec(const char *prompt, const t_sh *data, int *i);
int	prmt_pwd_home(const char *prompt, const t_sh *data, int *i);
int	prmt_year_comp(const char *prompt, const t_sh *data, int *i);
int	prmt_full_host(const char *prompt, const t_sh *data, int *i);
int	prmt_part_host(const char *prompt, const t_sh *data, int *i);
int	prmt_hour_sec_ap(const char *prompt, const t_sh *data, int *i);
/*
** UTILS
*/
int	my_getnbr(const char *str);
int	print_error(const char *str);
int	my_str_isnumber(const char *str);
void	my_putchar(char c, int fd);
void	my_put_nbr(int nb, int fd);
void	free_tab(char **tab);
void	my_putstr(const char *str, int fd);
void	*print_err(const char *str);
char	*epure_str(char *str);
char	*get_next_line(int fd);
char	*add_two_str(char *s1, char *s2);
char	**my_str_to_wordtab(const char *str, char sepparator);
/*
** GETENV
*/
char	**get_env(const char **env);
char	**add_pwd(char **env);
char	**add_usr(char **env);
char	**add_grp(char **env);
char	**add_host(char **env);
char	**add_ostype(char **env);
/*
** BUILTINS
*/
int	change_pwd(t_sh *data);
int	my_cd(const char **cmd, t_sh *data);
int	my_exit(const char **cmd, t_sh *data);
int	my_echo(const char **cmd, t_sh *data);
int	my_setenv(const char **cmd, t_sh *data);
int	my_unsetenv(const char **cmd, t_sh *data);
int	my_builtins(const char **cmd, t_sh *data);
int	set_return_value(int ret, int exit, t_sh *data);
char	*get_old(char *old, char *tmp);
char	*env_value(char **env, const char *value);
char	**one_more(char **env);
/*
** EXEC
*/
int	exec_func(t_sh *sh, const char **tab);
void	sig_in_func(int sig);
void	relative_error(const char **tab);
char	*get_complete_path(const char **tab, char *path);
char	**get_path(t_sh *sh, const char **tab);
/*
** PIPE
*/
int	run_pipe(t_node *node, t_sh *sh);
/*
** LEXER
*/
t_lx	*lexer(char *str);
t_lx	*create_lx(const t_lx_type type, char *value);
t_lx	*add_lx(t_lx *list, const t_lx_type type, char *value);
void	clean_lx_list(t_lx *list);
void	clean_lx_tab(t_lx_data *data);
/*
** PARSER
*/
t_node		*parse(t_lx *, int *);
t_lx		*remove_lx(t_lx **, t_lx *);
t_node		*rule_sep(t_lx *, int *);
t_node		*rule_cmp(t_lx *, int *);
t_node		*rule_red(t_lx *, int *);
t_node		*rule_pipe(t_lx *, int *);
t_node		*rule_cmd(t_lx *, int *);
t_node		*create_node(int, char **);
void		display_node(t_node *);
char		**export_list_part(t_lx *, int);
int		is_cmd_empty(t_node *);
void		*throw_parser_error(int, int *);
int		exec_tree(t_node *, t_sh *);
/*
** HISTORY
*/
int	init_hist(t_sh *data);
int	print_hour(time_t time);
int	hist_nbr(const char **tab, t_sh *data);
int	hist_clean(const char **tab, t_sh *data);
int	my_history(const char **cmd, t_sh *data);
int	hist_file_s(const char **tab, t_sh *data);
int	hist_file_m(const char **tab, t_sh *data);
int	hist_file_l(const char **tab, t_sh *data);
int	get_history(t_sh *data, const char *file);
int	add_new_hist(t_sh *data, const char *cmd);
int	print_hist(t_sh *data, const char *opt, int n);
int	add_hist_to_file(t_sh *data, const char *file);
char	*read_hist(int fd);
void	free_hist(t_sh *data);
unsigned long	my_hist_getnbr(const char *str);
char	*search_reverse(char *str, t_sh *data, int *i);
char	*find_good(char *str, t_sh *data, int *i);
char	*find_one(char *str, t_sh *data, int *i);
char	*add_hist_to_cmd(char *str, t_sh *data);
char	*add_cmd(char *str, char *cmd, int *start, int end);
/*
** REDIRECT
*/
int	run_redir(t_node *node, t_sh *sh);
int	redirect_left(const char *file, const char *type);
int	redirect_right(const char *file, const char *type);
int	redirect_double_left(const char *file, const char *type);
int	redirect_double_right(const char *file, const char *type);

#endif /* !FUNCTIONS_H_ */
