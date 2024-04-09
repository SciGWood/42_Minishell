/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:53:28 by gwen              #+#    #+#             */
/*   Updated: 2024/03/12 11:52:24 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(void)
{
	char	buf[1024];

	if (getcwd(buf, sizeof(buf)) != NULL)
		printf("%s\n", buf);
	else
		printf("Failed to get current working directory.\n");
	return (0);
}

int	ft_cd(const char *path, char **split_cmd)
{
	char	*home_path;

	if (!path)
	{
		home_path = getenv("HOME");
		if (chdir(home_path) == 0)
			g_exit_status = 0;
	}
	else if (split_cmd[2])
		print_error(7, "", 1);
	else
	{
		if (path[0] == '$')
		{
			home_path = getenv(&path[1]);
			if (chdir(home_path) == 0)
				g_exit_status = 0;
		}
		else if (chdir(path) == 0)
			g_exit_status = 0;
		else
			print_error(3, (char *)path, 1);
	}
	return (g_exit_status);
}

int	ft_env(char *env[])
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strnstr(env[i], "=", ft_strlen(env[i])))
			i++;
		else
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	ft_unset(char **split_prompt, t_michel *michel)
{
	int		i;
	int		var_nb;

	i = 1;
	var_nb = 0;
	michel->split_prompt = split_prompt;
	if (!michel->split_prompt[1])
		return (0);
	while (michel->split_prompt[i])
		i++;
	var_nb = i - 1;
	while (var_nb > 0)
	{
		ft_rem_var(michel, michel->split_prompt[var_nb]);
		var_nb--;
	}
	return (0);
}

int	ft_export(t_michel *michel, char *cmd)
{
	char	**env_copy;
	char	**tmp;
	int		i;

	i = 0;
	michel->split_prompt = ft_split_qt_bis(cmd, ' ', michel);
	while (michel->split_prompt[i])
		i++;
	michel->var_nb = i;
	if (!michel->split_prompt[1])
		michel->ignore = 0;
	tmp = ft_tab_copy(michel->split_prompt);
	michel->envp = michel->env;
	ft_check_var(michel, tmp);
	ft_getenv(michel, michel->var_nb);
	env_copy = ft_tab_copy(michel->env);
	ft_sort_env(env_copy);
	if (!michel->split_prompt[1] && michel->ignore != 1)
		ft_print_export(env_copy);
	ft_free_tab(env_copy);
	ft_free_tab(tmp);
	ft_free_tab(michel->envp);
	ft_free_tab(michel->split_prompt);
	return (0);
}
