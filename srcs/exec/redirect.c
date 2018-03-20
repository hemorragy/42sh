/*
** redirect.c for redirect in /home/alliel_a/PSU_2015_42sh/srcs/adrien
**
** Made by Adrien Alliel
** Login   <alliel_a@alliel-a-pc>
**
** Started on  Wed Jun  1 03:22:53 2016 Adrien Alliel
** Last update Sun Jun  5 23:19:28 2016 Adrien Alliel
*/

#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "functions.h"

int	redirect_right(const char *file, const char *type)
{
  int	fd;

  if (strcmp(type, SR_RED) == 0)
    {
      if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
		     FILE_PERMISSIONS)) == -1)
	return (FAILED);
      if (dup2(fd, 1) == -1)
	return (FAILED);
      close(fd);
      return (SUCCESS);
    }
  return (FAILED);
}

int	redirect_double_right(const char *file, const char *type)
{
  int	fd;

  if (strcmp(type, DR_RED) == 0)
    {
      if ((fd = open(file, O_WRONLY | O_APPEND | O_CREAT,
		     FILE_PERMISSIONS)) == -1)
	return (FAILED);
      if (dup2(fd, 1) == -1)
	return (FAILED);
      close(fd);
      return (SUCCESS);
    }
  return (FAILED);
}

int	redirect_left(const char *file, const char *type)
{
  int	fd;

  if (strcmp(type, SL_RED) == 0)
    {
      if ((fd = open(file, O_RDONLY)) == -1)
	return (FAILED);
      if (dup2(fd, 0) == -1)
	return (FAILED);
      close(fd);
      return (SUCCESS);
    }
  return (FAILED);
}

int	redirect_double_left(const char *file, const char *type)
{
  char	*data;
  int	fd;

  if (strcmp(type, DL_RED) == 0)
    {
      if ((fd = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC,
		     FILE_PERMISSIONS)) == FAILED)
	return (FAILED);
      my_putstr(REDIRECT_PROMPT, 1);
      while (((data = get_next_line(0)) != NULL) &&
	     strcmp(data, file) != 0)
	{
	  write(fd, data, strlen(data));
	  write(fd, NEW_LINE, 1);
	  my_putstr(REDIRECT_PROMPT, 1);
	  free(data);
	}
      if ((fd = open(TMP_FILE, O_RDONLY)) == FAILED)
	return (FAILED);
      if (dup2(fd, 0) == FAILED)
	return (FAILED);
      close(fd);
      return (SUCCESS);
    }
  return (FAILED);
}
