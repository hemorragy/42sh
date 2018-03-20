/*
** aff_prompt.c for aff_prompt in /home/antoin_g/rendu/Unix/PSU_2015_42sh/srcs/lois
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Mon May 23 16:22:17 2016 Loïs
** Last update Sun Jun  5 04:45:35 2016 Loïs
*/

#include "functions.h"

static const t_prompt	g_prompt[] =
  {
    {'/', &prmt_pwd},
    {'~', &prmt_pwd_home},
    {'M', &prmt_full_host},
    {'m', &prmt_part_host},
    {'%', &prmt_double},
    {'n', &prmt_user},
    {'$', &prmt_env},
    {'t', &prmt_hour_ap},
    {'@', &prmt_hour_ap},
    {'T', &prmt_hour},
    {'p', &prmt_hour_sec_ap},
    {'P', &prmt_hour_sec},
    {'D', &prmt_day},
    {'d', &prmt_day_week},
    {'W', &prmt_mon_nb},
    {'w', &prmt_mon},
    {'Y', &prmt_year_comp},
    {'y', &prmt_year},
    {'?', &prmt_ret},
    {0, NULL}
  };

static int	parse_prompt_tools(const char *prompt, const t_sh *data, int *i)
{
  int		idx;
  bool		check;

  check = 0;
  idx = 0;
  while (g_prompt[idx].value && !check)
    {
      if (g_prompt[idx].value == prompt[*i + 1])
	{
	  if (g_prompt[idx].function(prompt, data, i))
	    return (1);
	  check = 1;
	}
      ++idx;
    }
  if (!check)
    my_putchar(prompt[*i], 1);
  return (0);
}

static int	parse_prompt(const char *prompt, const t_sh *data)
{
  int		i;

  i = 0;
  while (prompt[i])
    {
      if (prompt[i] != '%' || (prompt[i] == '%' && !prompt[i + 1]))
	my_putchar(prompt[i], 1);
      else
	if (parse_prompt_tools(prompt, data, &i))
	  return (1);
      ++i;
    }
  return (0);
}

int	aff_prompt(t_sh *data)
{
  char	*prompt;

  prompt = env_value(data->env, "PROMPT=");
  if (!prompt)
    my_putstr(BASE_PROMPT, 1);
  else
    if (parse_prompt(prompt, data))
      return (1);
  return (0);
}
