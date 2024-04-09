/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:45:37 by gwen              #+#    #+#             */
/*   Updated: 2024/03/12 14:00:58 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**ft_tab_copy(char **env)
{
	char	**env_copy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_copy = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env[i])
	{
		env_copy[i] = ft_strdup(env[i]);
		i++;
	}
	env_copy[i] = 0;
	return (env_copy);
}

void	ft_ignore(t_michel *michel, char *var_to_remove)
{
	int		i;

	i = 0;
	while (michel->split_prompt[i])
	{
		if (ft_strncmp(michel->split_prompt[i], var_to_remove,
				ft_strlen(var_to_remove)) == 0)
		{
			while (michel->split_prompt[i + 1])
			{
				free(michel->split_prompt[i]);
				michel->split_prompt[i]
					= ft_strdup(michel->split_prompt[i + 1]);
				i++;
			}
			free(michel->split_prompt[i]);
			michel->split_prompt[i] = NULL;
		}
		i++;
	}
}

void	ft_double_var(t_michel *michel, char **spl, int i, int j)
{
	if (ft_strncmp(michel->envp[i], spl[j],
			ft_len_char(michel->envp[i], '=')) == 0)
	{
		if (ft_strnstr(spl[j], "+=", ft_strlen(spl[j])))
			ft_var_change(michel, i, spl[j], 'a');
		else if (ft_strnstr(spl[j], "=", ft_strlen(spl[j]))
			&& !ft_strnstr(spl[j], "+", ft_strlen(spl[j])))
			ft_var_change(michel, i, spl[j], 'r');
		else
			ft_var_change(michel, i, spl[j], 's');
		michel->ignore = 1;
	}
}

void	ft_var_change(t_michel *michel, int i, char *var_to_remove, int flag)
{
	char	**var_split;
	char	*join_var;

	if (flag == 'a')
	{
		var_split = ft_split(var_to_remove, '=');
		join_var = ft_strjoin(michel->envp[i], var_split[1]);
		free(michel->envp[i]);
		michel->envp[i] = ft_strdup(join_var);
		ft_free_tab(var_split);
		free(join_var);
	}
	else if (flag == 'r')
	{
		free(michel->envp[i]);
		michel->envp[i] = ft_strdup(var_to_remove);
	}
	else if (flag == 'd')
		michel->ignore = 1;
	michel->var_nb--;
	ft_ignore(michel, var_to_remove);
}

void	ft_check_var(t_michel *michel, char **spl)
{
	int	i;
	int	j;

	j = 1;
	while (spl[j])
	{
		if (ft_is_valid_identifier(spl[j]) == 1)
			ft_var_change(michel, 1, spl[j], 'd');
		j++;
	}
	j = 1;
	while (spl[j])
	{
		i = 0;
		while (michel->envp[i])
		{
			ft_double_var(michel, spl, i, j);
			i++;
		}
		j++;
	}
}
