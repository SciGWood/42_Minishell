/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 23:10:20 by gwen              #+#    #+#             */
/*   Updated: 2024/03/04 11:35:23 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_export(char **env_copy)
{
	char	**split_var;
	int		i;

	i = 0;
	while (env_copy[i])
	{
		split_var = ft_split(env_copy[i], '=');
		if (ft_strncmp(env_copy[i], "_", ft_len_char(env_copy[i], '=')) == 0)
			ft_free_tab(split_var);
		else
		{
			if (!split_var[1])
			{
				if (ft_strnstr(env_copy[i], "=", ft_strlen(env_copy[i])))
					printf("declare -x %s=\"\"\n", split_var[0]);
				else
					printf("declare -x %s\n", env_copy[i]);
			}
			else
				printf("declare -x %s=\"%s\"\n", split_var[0], split_var[1]);
			ft_free_tab(split_var);
		}
		i++;
	}
}

char	**ft_sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j], 100) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
	return (env);
}

void	ft_add_var_env(t_michel *michel, int i)
{
	int	j;

	j = 1;
	while (michel->split_prompt[j])
	{
		michel->env[i] = ft_strdup(michel->split_prompt[j]);
		i++;
		j++;
	}
	michel->env[i] = 0;
}

int	ft_is_valid_identifier(char *str)
{
	char	**spl;

	if (ft_strnstr(str, "=", ft_strlen(str)))
	{
		spl = ft_split(str, '=');
		if (ft_strnstr(str, "-", ft_len_char(str, '='))
			|| (str[0] == '=' && !str[1])
			|| (spl[0] && (ft_isdigit_str(spl[0], 0))))
		{
			ft_free_tab(spl);
			print_error(5, str, 1);
			return (1);
		}
		ft_free_tab(spl);
	}
	else
	{
		if (ft_strnstr(str, "-", ft_strlen(str))
			|| ft_isdigit_str(str, 0))
		{
			print_error(5, str, 1);
			return (1);
		}
	}
	return (0);
}

void	ft_getenv(t_michel *michel, int var_nb)
{
	int		i;

	i = 0;
	while (michel->envp[i])
		i++;
	michel->env = ft_calloc(i + 1 + var_nb, sizeof(char *));
	i = 0;
	while (michel->envp[i])
	{
		michel->env[i] = ft_strdup(michel->envp[i]);
		i++;
	}
	if (var_nb != 0)
		ft_add_var_env(michel, i);
	else
		michel->env[i] = 0;
}
