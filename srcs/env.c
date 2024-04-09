/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:44:40 by gwen              #+#    #+#             */
/*   Updated: 2024/03/12 16:49:21 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_len_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

void	ft_rem_var(t_michel *michel, char *var_to_remove)
{
	int		i;

	i = 0;
	while (michel->env[i])
	{
		if (ft_strncmp(michel->env[i], var_to_remove,
				ft_len_char(michel->env[i], '=')) == 0
			&& !ft_strnstr(var_to_remove, "_", 1))
		{
			while (michel->env[i + 1])
			{
				free(michel->env[i]);
				michel->env[i] = ft_strdup(michel->env[i + 1]);
				i++;
			}
			free(michel->env[i]);
			michel->env[i] = NULL;
		}
		i++;
	}
}

char	*ft_shlvl(char	*lvlp)
{
	char	**shlvl;
	char	*lvl;
	char	*level;
	int		l;

	l = 0;
	shlvl = ft_split(lvlp, '=');
	l = ft_atoi(shlvl[1]) + 1;
	level = ft_itoa(l);
	lvl = ft_strjoin(shlvl[0], "=");
	lvl = ft_strjoin_and_free(lvl, level);
	ft_free_tab(shlvl);
	free(level);
	return (lvl);
}

void	ft_getenvp(t_michel *michel)
{
	int		i;

	i = 0;
	while (michel->envp[i])
		i++;
	michel->env = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (michel->envp[i])
	{
		if (ft_strnstr(michel->envp[i], "SHLVL=", 6))
			michel->env[i] = ft_shlvl(michel->envp[i]);
		else
			michel->env[i] = ft_strdup(michel->envp[i]);
		i++;
	}
	michel->env[i] = 0;
}
