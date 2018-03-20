/*
** my_getnbr.c for my_getnbr in /home/antoin_g/rendu/Unix/PSU_2015_42sh
**
** Made by Loïs
** Login   <antoin_g@lois-HP-EliteBook-840-G2>
**
** Started on  Sun Jun  5 01:55:18 2016 Loïs
** Last update Sun Jun  5 04:17:29 2016 Loïs
*/

int	my_getnbr(const char *str)
{
  int	i;
  int	nb;
  int	sign;

  i = 0;
  nb = 0;
  sign = 1;
  if (str[i] == '-')
    {
      sign = -sign;
      ++i;
    }
  while (str[i] >= '0' && str[i] <= '9')
    {
      nb = nb * 10 + (str[i] - '0');
      ++i;
    }
  return (nb * sign);
}

unsigned long	my_hist_getnbr(const char *str)
{
  unsigned long	nb;
  int		i;

  nb = 0;
  i = 0;
  while (str[i] >= '0' && str[i] <= '9')
    {
      nb = nb * 10 + (str[i] - '0');
      ++i;
    }
  return ((str[i]) ? 0 : nb);
}
