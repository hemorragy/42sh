/*
** lexer.c for 42sh in /home/eddy/PSU_2015_42sh/srcs/lexer
**
** Made by Eddy Chouikha
** Login   <eddy@epitech.net>
**
** Started on  Thu Jun  2 19:46:42 2016 Eddy Chouikha
** Last update Sun Jun  5 14:16:18 2016 Eddy Chouikha
*/

#include <string.h>
#include <stdlib.h>
#include "defines.h"
#include "functions.h"

static int	add_type(const t_lx_type type, const int nb_lx, char ***lx_tab)
{
  if (!(lx_tab[type] = malloc(sizeof(char *) * (nb_lx + 1))))
    return (FAILURE);
  lx_tab[type][nb_lx] = NULL;
  return (SUCCESS);
}

static int	init_data(t_lx_data *data, char ***lx_tab, char *str)
{
  if (add_type(LX_SEP, NB_LX_SEP, lx_tab) == FAILURE ||
      add_type(LX_CMP, NB_LX_CMP, lx_tab) == FAILURE ||
      add_type(LX_RED, NB_LX_RED, lx_tab) == FAILURE ||
      add_type(LX_PIPE, NB_LX_PIPE, lx_tab) == FAILURE)
    return (FAILURE);
  lx_tab[LX_SEP][0] = SEP;
  lx_tab[LX_CMP][0] = AND;
  lx_tab[LX_CMP][1] = OR;
  lx_tab[LX_RED][0] = SL_RED;
  lx_tab[LX_RED][1] = SR_RED;
  lx_tab[LX_RED][2] = DL_RED;
  lx_tab[LX_RED][3] = DR_RED;
  lx_tab[LX_PIPE][0] = PIPE;
  data->lx_tab = lx_tab;
  data->str = str;
  data->idx_str = 0;
  return (SUCCESS);
}

static int	is_lex(t_lx_data *data, int *idx, const int move_idx)
{
  int		idx_type;
  int		idx_lex;

  idx_type = 0;
  while (idx_type < NB_LX_TYPES)
    {
      idx_lex = 0;
      while (data->lx_tab[idx_type][idx_lex])
	{
	  if (strncmp(&data->str[*idx], data->lx_tab[idx_type][idx_lex],
		      strlen(data->lx_tab[idx_type][idx_lex])) == 0)
	    {
	      data->type = idx_type;
	      data->value = data->lx_tab[idx_type][idx_lex];
	      if (move_idx == 1)
		(*idx) += strlen(data->lx_tab[idx_type][idx_lex]);
	      return (SUCCESS);
	    }
	  ++idx_lex;
	}
      ++idx_type;
    }
  return (UNSUCCESS);
}

static int	is_word(t_lx_data *data)
{
  int			idx_tmp;

  idx_tmp = data->idx_str;
  while (data->str[idx_tmp] && data->str[idx_tmp] != ' '
	 && data->str[idx_tmp] != '\t'
	 && !(is_lex(data, &idx_tmp, 0)))
    ++idx_tmp;
  data->type = LX_WORD;
  if (!(data->value = strndup(&data->str[data->idx_str],
				   idx_tmp - data->idx_str)))
    return (FAILURE);
  (data->idx_str) = idx_tmp;
  return (SUCCESS);
}

t_lx		*lexer(char *str)
{
  t_lx_data	data;
  char		**lx_tab[NB_LX_TYPES];
  t_lx		*lx_list;
  t_lx		*lx_tmp;

  lx_list = NULL;
  lx_tmp = NULL;
  if (init_data(&data, lx_tab, str) == FAILURE)
    return (NULL);
  while (str[data.idx_str])
    {
      while (str[data.idx_str] == ' ' || str[data.idx_str] == '\t')
	++data.idx_str;
      if (str[data.idx_str] && ((is_lex(&data, &data.idx_str, 1) == SUCCESS) ||
				 (is_word(&data) == SUCCESS)))
	{
	  if (!(lx_tmp = add_lx(lx_tmp, data.type, data.value)))
	    return (NULL);
	  (!lx_list) ? (lx_list = lx_tmp) : (lx_tmp = lx_tmp->next);
	}
    }
  clean_lx_tab(&data);
  return (lx_list);
}
