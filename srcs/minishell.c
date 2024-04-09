/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:26:26 by gwen              #+#    #+#             */
/*   Updated: 2024/03/13 15:26:48 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

int	ft_builtins_env(t_michel *michel, char **split_cmd, char *cmd)
{
	if (ft_strlen(split_cmd[0]) == 6
		&& ft_strncmp(split_cmd[0], "export", 6) == 0)
		return (ft_export(michel, cmd));
	else if (ft_strlen(split_cmd[0]) == 5
		&& ft_strncmp(split_cmd[0], "unset", 5) == 0)
		return (ft_unset(split_cmd, michel));
	else if (ft_strlen(split_cmd[0]) == 4
		&& ft_strncmp(split_cmd[0], "echo", 4) == 0)
		return (ft_echo_dollar(michel, split_cmd, cmd));
	else if (ft_strncmp(split_cmd[0], "$", 1) == 0)
		return (ft_echo_dollar(michel, split_cmd, cmd));
	else if (ft_strlen(split_cmd[0]) == 3
		&& ft_strncmp(split_cmd[0], "env", 3) == 0)
		return (ft_env(michel->env));
	return (-1);
}
/* split_cmd, split_cmd[1]
split_cmd, split_cmd[0] */

int	ft_parse_wo_token(t_michel *michel, char **split_cmd, char *cmd)
{
	if (ft_strlen(split_cmd[0]) == 4
		&& ft_strncmp(split_cmd[0], "exit", 4) == 0)
		return (ft_exec_exit(cmd, michel), 'e');
	else if (ft_strlen(split_cmd[0]) == 3
		&& ft_strncmp(split_cmd[0], "pwd", 3) == 0)
		return (ft_pwd());
	else if (ft_strlen(split_cmd[0]) == 2
		&& ft_strncmp(split_cmd[0], "cd", 2) == 0)
		return (ft_cd(split_cmd[1], split_cmd));
	if (ft_builtins_env(michel, split_cmd, cmd) != -1)
		return (0);
	else
	{
		if (michel->flag == 'p')
			return (0);
		else
			ft_fork(split_cmd, michel->env, michel);
		return (0);
	}
}

int	ft_parse_token(t_michel *michel)
{
	int		res;

	if (michel->sub_prompt)
	{
		ft_free_tab(michel->spl_prompt);
		free(michel->prompt);
		michel->spl_prompt = ft_split_prompt(michel->sub_prompt, "<>|");
		michel->prompt = ft_strdup(michel->sub_prompt);
		free(michel->sub_prompt);
		michel->sub_prompt = NULL;
	}
	open_file(michel);
	michel->cmds = extract_cmds(michel);
	if (!michel->cmds)
	{
		ft_dup2(michel);
		return (0);
	}
	res = ft_pipe(michel->cmds, michel);
	ft_free_tab(michel->cmds);
	ft_dup2(michel);
	if (michel->sub_prompt)
		ft_parse_token(michel);
	return (res);
}
	/* int i = 0;
	while (michel->cmds[i])
	{
		printf("%s\n", michel->cmds[i]);
		i++;
	}
	printf("finish extract\n"); */

int	ft_parse_prompt(t_michel *michel)
{
	int		ret;
	char	*error;

	ret = 0;
	check_qt_peer(michel);
	michel->new_prompt = voiding_space(michel);
	if (!ft_strncmp(michel->new_prompt, "", ft_strlen(michel->new_prompt)))
		return (free(michel->new_prompt), ret);
	michel->spl_prompt = ft_split_prompt(michel->new_prompt, "<>|");
	free(michel->new_prompt);
	error = check_usage_error(michel);
	if (error)
	{
		print_error(2, error, 2);
		free(error);
	}
	else
	{
		ft_free_tab(michel->spl_prompt);
		michel->spl_prompt = ft_split_prompt(michel->prompt, "<>|");
		ret = ft_parse_token(michel);
		free(michel->prompt);
	}
	return (ft_free_tab(michel->spl_prompt), ret);
}
	/* if (!michel->spl_prompt[1])
	{
		ft_free_tab(michel->spl_prompt);
		michel->spl2_prompt = ft_split_qt(michel->prompt, ' ');
		ret = ft_parse_wo_token(michel, michel->spl2_prompt);
		return (ft_free_tab(michel->spl2_prompt), ret);
	} */

int	main(int argc, char *argv[], char *envp[])
{
	t_michel	michel;
	int			result;

	(void)argv;
	result = 0;
	if (argc != 1)
		return (print_error(7, "", 0), 1);
	ft_init_struct(&michel);
	michel.envp = envp;
	ft_getenvp(&michel);
	signal(SIGINT, handle_sigint);
	ft_sigquit();
	while (1)
	{
		michel.prompt = readline(BLUE"42_Minishell_GG: "WHITE);
		if (michel.prompt == NULL)
			return (ft_exit(&michel), g_exit_status);
		add_history(michel.prompt);
		if (ft_strncmp(michel.prompt, "", ft_strlen(michel.prompt)) != 0)
			result = ft_parse_prompt(&michel);
		if (result == 'e')
			return (ft_exit(&michel), g_exit_status);
		rl_on_new_line();
	}
	return (0);
}
/* free(michel.prompt); */