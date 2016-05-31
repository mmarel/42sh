/*
** auto_completion_find.c for  in /home/sauvau_m/rendu/PSU_2015_42sh
**
** Made by Mathieu Sauvau
** Login   <sauvau_m@epitech.net>
**
** Started on  Tue May 24 11:00:59 2016 Mathieu Sauvau
** Last update Tue May 31 18:46:41 2016 Mathieu Sauvau
*/

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "42s.h"

int		find_in_(char *path, char *str, char **res, int in_env_path)
{
  DIR		*d;
  struct dirent	*dir;
  int		i;
  struct stat	st;
  char		*all_dir_path;

  if (!(d = opendir(path)))
    return (0);
  i = 0;
  while ((dir = readdir(d)))
    {
      if (dir->d_name[0] != '.' && strncmp(str, dir->d_name, strlen(str)) == 0)
	{
	  if (!(all_dir_path = get_all_dir_path(path, dir->d_name, in_env_path)) ||
	      !get_res(res, all_dir_path, dir->d_name, &st))
	    return (-1);
	  ++i;
	  free(all_dir_path);
	}
    }
  closedir(d);
  return (i);
}

/**
 ** COMPARE ALL IN RES IF START THE SAME
 ** CPY TO DIFF
 */

int		find_anywhere(char **env_path, char **res, t_autoc *autoc)
{
  int		n;

  n = 0;
  if (autoc->i_elem >= 1)
    {
      if (show_bin(autoc))
	n += find_in_env_path(env_path, autoc->elem, res);
      else
	n += find_in_(autoc->path, autoc->elem, res, 0);
    }
  return (n);
}

char		**find_routine(char **str, char **env_path, t_autoc *autoc)
{
  char		*res;
  char		**tab;

  tab = NULL;
  if (!(res = malloc(1)))
    return (NULL);
  res[0] = 0;
  if (find_anywhere(env_path, &res, autoc) == 1)
    {
      if (!get_new_str(str, autoc->path, autoc->elem, res))
	return (NULL);
      res[strlen(res) - 1] = 0;
      strcat(*str, res);
    }
  else
    tab =  my_str_to_word_tab(res, ' ');
  return (free(res), tab);
}

int		separate_path_elem(t_autoc *autoc, char **str, char *cur_str, int pos)
{
  if (!(autoc->path = get_path(cur_str)))
    return (-1);
  if (*str && (*str)[0])
    {
      if (!(autoc->elem = get_elem(cur_str)))
	return (-1);
    }
  else
    {
      if (!(autoc->elem = strdup(cur_str)))
	return (-1);
    }
  if ((autoc->i_elem == 1 && (*str)[0] == '.') ||
      (pos > 1 && (*str)[pos - 1] == ' '))
    {
      autoc->elem[0] = 0;
      autoc->show = 0;
    }
  return (0);
}

char		**find_match(char **env_path, char **str, int pos)
{
  t_autoc	autoc;
  char		**tab;
  char		*cur_str;

  cur_str = *str;
  autoc.tab_str = NULL;
  autoc.show = 1;
  autoc.i_elem = 0;
  if (*str && (*str)[0])
    {
      if ((autoc.tab_str = my_str_to_word_tab(*str, ' ')))
	{
	  autoc.i_elem = nb_word_tab(autoc.tab_str);
	  cur_str = autoc.tab_str[autoc.i_elem - 1];
	}
    }
  if (separate_path_elem(&autoc, str, cur_str, pos) == -1)
    return (NULL);
  printf("\n path %s elem %s\n", autoc.path, autoc.elem);
  tab = find_routine(str, env_path, &autoc);
  free_autoc(&autoc);
  return (tab);
}
