/*
** var_env.c for azd in /home/debrau_c/Documents/cours/PSU/save_var_env
**
** Made by debrau_c
** Login   <debrau_c@epitech.net>
**
** Started on  Mon May 30 15:55:18 2016 debrau_c
** Last update Fri Jun  3 22:43:06 2016 marel_m
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "var_env.h"
#include "42s.h"

int	var_env_copy_all_env(char *new, char *env, int j, int k)
{
  int	m;

  m = j;
  while (env[k] != '\0')
    {
      new[m] = env[k];
      ++k;
      ++m;
    }
  new[m] = '\0';
  return (0);
}

int	var_env_modify(char **str, char **env, int index, char *talon)
{
  int	i;
  int	j;
  int	k;
  char	*new;

  i = 0;
  while (env[i] != NULL)
    {
      if (strncmp(env[i], talon, var_env_strclen(env[i], '=')) == 0)
	{
	  if (!(new = malloc(sizeof(char) * (strlen(env[i]) + strlen(str[0]) + 1))))
	    return (1);
	  j = var_env_place_j(new, *str, index);
	  if ((k = var_env_place_k(env[i])) < 0)
	    return (1);
	  var_env_copy_all_env(new, env[i], j, k);
	  while (str[0][j] != '\0' && str[0][j] != ' ' && str[0][j] != '"')
	    j++;
	  strcat(new, &str[0][j]);
	  free(*str);
	  *str = new;
	  return (0);
	}
      i++;
    }
  return (1);
}

int	var_env_octopus(t_sh *sh, char **str, char **env, int *i)
{
  char	*talon;

  if ((talon = var_env_strcdup(&str[0][*i + 1], ' ')) == NULL)
    return (1);
  printf("%s\n", talon);
  if (var_env_modify(str, env, *i, talon))
    {
      sh->exit = 1;
      printf("%s: Undefined variable.\n", talon);
      return (1);
    }
  free(talon);
  return (0);
}

int	var_env_format(t_sh *sh, char **str, char **env)
{
  int	i;
  int	on_quotes;

  i = 0;
  on_quotes = 0;
  while (str[0][i])
    {
      if (!on_quotes && str[0][i] == '\'')
	on_quotes = 1;
      else if (on_quotes && str[0][i] == '\'')
	on_quotes = 0;
      if (!on_quotes && str[0][i] == '$' && str[0][i + 1] != '\0')
	if (var_env_octopus(sh, str, env, &i))
	  return (1);
      i++;
    }
  return (0);
}
