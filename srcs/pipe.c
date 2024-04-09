/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:25:50 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/04 14:56:00 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_error_p(int error, const char *str)
{
	printf("Error %s: %s\n", str, strerror(error));
	exit(1);
}

static int	len_cmds(char **cmds)
{
	int	len;

	len = 0;
	while (cmds[len])
		len++;
	return (len);
}

static void	do_pipe(char **env, t_michel *michel, char *cmd)
{
	int		pipe_fd[2];
	pid_t	child_pid;
	char	**split_cmd;

	if (pipe(pipe_fd) == -1)
		print_error_p(errno, "pipe");
	child_pid = fork();
	if (child_pid == -1)
		print_error_p(errno, "fork");
	if (child_pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		michel->flag = 'p';
		split_cmd = ft_split_qt(cmd, ' ');
		ft_parse_wo_token(michel, split_cmd, cmd);
		ft_exec(split_cmd, env, michel);
		ft_free_tab(split_cmd);
	}
	else
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
	}
}

int	ft_pipe(char **cmds, t_michel *michel)
{
	int		i;
	int		cmds_nbr;
	char	**last_cmd;
	int		res;

	i = 0;
	res = 0;
	cmds_nbr = len_cmds(cmds);
	if (cmds_nbr > 1)
	{
		while (i < cmds_nbr - 1)
		{
			do_pipe(michel->env, michel, cmds[i]);
			i++;
		}
		michel->flag = 0;
	}
	last_cmd = ft_split_qt(cmds[i], ' ');
	res = ft_parse_wo_token(michel, last_cmd, cmds[i]);
	ft_free_tab(last_cmd);
	return (res);
}
