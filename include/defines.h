/*
** defines.h for 42sh in /home/antoin_g/rendu/Unix/PSU_2015_42sh
**
** Made by Loïs
** Login   <antoin_g@epitech.net>
**
** Started on  Sun Jun  5 23:15:18 2016 Loïs
** Last update Sun Jun  5 23:30:08 2016 Loïs
*/

#ifndef DEFINES_H_
# define DEFINES_H_

/*
** ALL
*/
# define OPEN_ERROR "Error : open failure\n"
# define READ_ERROR "Error : read failure\n"
# define MALLOC_ERROR "Error : malloc failure\n"
# define STAT_ERROR "Error : stat failure\n"
# define FORK_ERROR "Error : processus duplication failed\n"
# define EXEC_ERROR "Error : execution failed\n"
# define END_OF_SHELL "exit\n"
# define SUCCESS 1
# define UNSUCCESS 0
# define FAILURE -1
/*
** UTILS
*/
#ifndef READ_SIZE
# define READ_SIZE (256)
#endif /* !READ_SIZE */
# define MINIMUM_INT "-2147483648"
/*
** GETENV
*/
# define PATH_OSTYPE "/proc/sys/kernel/ostype"
# define HOST_SIZE 500
/*
** BUILTINS
*/
# define SETENV_ERR "setenv: Too many arguments.\n"
# define UNSETENV_ERR "unsetenv: Too few arguments.\n"
# define INV_SET "setenv: Variable name must contain"
# define INV_SETENV INV_SET " alphanumeric characters.\n"
# define FIRST_INV_SETENV "setenv: Variable name must begin with a letter.\n"
# define CD_TOO "cd: Too many arguments.\n"
# define NO_HOME "cd: No home directory.\n"
# define USAGE_CD "Usage: cd [-|<dir>].\n"
# define NO_DIR ": Aucun fichier ou dossier de ce type.\n"
# define N_OPT "-n"
# define ECHO_PROMPT "? "
# define ENV "env"
# define EXIT_TOO_ARG "exit: Expression Syntax.\n"
# define NO_RIGHT ": Permission denied.\n"
/*
** PROMPT
*/
# define BASE_PROMPT "> "
# define HIDE_CTRL_C "\b\b  \n"
# define SIZE_DAY 3
# define SIZE_MON_S 4
# define SIZE_MON_E 7
/*
** EXEC
*/
# define END_PIPE "Broken pipe\n"
# define END_QUIT "Quit (core dumped)\n"
# define END_BUS "Bus error (core dumped)\n"
# define END_SEGV "Segmentation fault (core dumped)\n"
# define END_FPE "Floating exception (core dumped)\n"
# define END_ABRT "Abort (core dumped)\n"
# define DEF_PATH "/usr/bin:/usr/sbin:/bin:/sbin:"
# define DEFAULT_PATH DEF_PATH "/usr/local/bin:/usr/local/sbin"
# define NO_EXIST 255
/*
** LEXER
*/
# define SEP ";"
# define AND "&&"
# define OR "||"
# define SL_RED "<"
# define DL_RED "<<"
# define SR_RED ">"
# define DR_RED ">>"
# define IS_RED_LEFT(X) (strcmp(SL_RED, X) == 0 || strcmp(DL_RED, X) == 0)
# define IS_RED_RIGHT(X) (strcmp(SR_RED, X) == 0 || strcmp(DR_RED, X) == 0)
# define PIPE "|"
# define NB_LX_TYPES 4
# define NB_LX_SEP 1
# define NB_LX_CMP 2
# define NB_LX_RED 4
# define NB_LX_PIPE 1
# define ERR_NULL_CMD 2
# define ERR_NULL_CMD_MSG "Invalid null command.\n"
# define ERR_MISSING_FILE 3
# define ERR_MISSING_FILE_MSG "Missing name for redirect.\n"
# define ERR_AMBIGUOUS_RED 4
# define ERR_AMBIGUOUS_RED_MSG "Ambiguous output redirect.\n"

typedef enum	e_lx_type
  {
    LX_SEP,
    LX_CMP,
    LX_RED,
    LX_PIPE,
    LX_WORD
  }		t_lx_type;

typedef enum	e_rule_type
  {
    RULE_SEP,
    RULE_CMP,
    RULE_RED,
    RULE_PIPE,
    RULE_CMD
  }		t_rule_type;

/*
** HISTORY
*/
# define HIST_TOO_ARG "history: Too many arguments.\n"
# define HIST_NOT_NBR "history: Badly formed number.\n"
# define USAGE_HIST "Usage: history [-chrSLMT] [# number of events].\n"
# define HIST_FILE ".42history"
# define NO_EX_AFTER " \t<>|&;!"
# define NOT_EVENT ": Event not found.\n"
# define MAX_SIZE_NB_HIST 10000
# define RIGHT_HISTO 0600
# define MAX_HIST_SIZE 99999
/*
** REDIRECT
*/
# define FILE_PERMISSIONS 0664
# define TMP_FILE ".tmp_file"
# define REDIRECT_PROMPT "? "
# define NEW_LINE "\n"
# define FAILED -1
# define SUCCESS 1
# define NO_FILE ": No such file or directory.\n"

#endif /* !DEFINES_H_ */
