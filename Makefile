##
## Makefile for 42sh in /home/chouik_e/Rendu/PSU_2015_42sh
##
## Made by Eddy Chouikha
## Login   <chouik_e@epitech.net>
##
## Started on  Sun May  8 14:06:19 2016 Eddy Chouikha
## Last update Sun Jun  5 23:09:57 2016 Chai Bittan
##

CC		=	gcc -g

RM		=	rm -rf

CFLAGS		=	-Wall -Werror -Wextra
CPPFLAGS	=	-Iinclude

NAME		=	42sh

EXEC		=	srcs/exec/

UTILS		=	srcs/utils/

LEXER		=	srcs/lexer/

PARSER		=	srcs/parser/

PROMPT		=	srcs/prompt/

BUILT		=	srcs/builtins/

HIST		=	srcs/history/

SRCS		=	srcs/main.c \
			$(PROMPT)flag_env.c \
			$(PROMPT)flag_hour.c \
			$(PROMPT)flag_year.c \
			$(PROMPT)aff_prompt.c \
			$(PROMPT)flag_env_var.c \
			$(PROMPT)flag_mon_day.c \
			$(BUILT)exit.c \
			$(BUILT)echo.c \
			$(BUILT)my_cd.c \
			$(BUILT)getenv.c \
			$(BUILT)setenv.c \
			$(BUILT)unsetenv.c \
			$(BUILT)my_cd_tools.c \
			$(BUILT)default_env.c \
			$(BUILT)my_builtins.c \
			$(BUILT)default_env_type.c \
			$(UTILS)aff.c \
			$(UTILS)my_free.c \
			$(UTILS)my_getnbr.c \
			$(UTILS)epure_str.c \
			$(UTILS)string_gest.c \
			$(UTILS)get_next_line.c \
			$(UTILS)my_str_to_wordtab.c \
			$(EXEC)pipe.c \
			$(EXEC)execute.c \
			$(EXEC)redirect.c \
			$(EXEC)exec_error.c \
			$(EXEC)run_redirection.c \
			$(LEXER)lexer.c \
			$(LEXER)lexer_utils.c \
			$(PARSER)node.c \
			$(PARSER)exec.c \
			$(PARSER)rules.c \
			$(PARSER)parser.c \
			$(PARSER)rule_red.c \
			$(HIST)history.c \
			$(HIST)put_old.c \
                        $(HIST)switch_ex.c \
			$(HIST)hist_opts.c \
			$(HIST)read_hist.c \
			$(HIST)file_hist.c \
			$(HIST)get_history.c \
			$(HIST)print_history.c \
			$(HIST)hist_opts_file.c


OBJS		=	$(SRCS:.c=.o)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
		$(CC) -o $(NAME) $(OBJS)

clean	:
		$(RM) $(OBJS)

fclean	:	clean
		$(RM) $(NAME)

re	:	fclean all

.PHONY	:	all clean fclean re
