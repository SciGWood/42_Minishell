/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 15:51:18 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/12 14:33:35 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*find_right_path(char **cmds, char **env)
{
	char	*way;
	char	*temp;
	int		i;
	char	**path;

	i = 0;
	way = NULL;
	if (access(cmds[0], F_OK | X_OK) != -1)
		return (cmds[0]);
	path = ft_split(find_path(env), ':');
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		way = ft_strjoin(temp, cmds[0]);
		free(temp);
		if (access(way, F_OK | X_OK) != -1)
		{
			ft_free_tab(path);
			return (way);
		}
		free(way);
		i++;
	}
	ft_free_tab(path);
	return (NULL);
}

int	ft_fork(char **cmd, char **env, t_michel *michel)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
		ft_exec(cmd, env, michel);
	else
	{
		waitpid(pid, &status, 0);
		g_exit_status = WEXITSTATUS(status);
	}
	return (g_exit_status);
}

void	ft_exec(char **cmd, char **env, t_michel *michel)
{
	char	*way;

	way = NULL;
	way = find_right_path(cmd, env);
	if (!way)
	{
		if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0]))
			&& access(cmd[0], F_OK | X_OK) == -1)
			print_error(3, cmd[0], 127);
		else
			print_error(4, cmd[0], 127);
		ft_free_msh(michel);
		ft_free_tab(michel->spl_prompt);
		ft_free_tab(michel->cmds);
		ft_free_tab(cmd);
		exit(g_exit_status);
	}
	else if (execve(way, cmd, env) == -1)
	{
		g_exit_status = 128;
		free(way);
		ft_free_msh(michel);
		ft_free_tab(cmd);
		exit(g_exit_status);
	}
}
