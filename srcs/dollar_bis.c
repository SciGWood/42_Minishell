/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_bis.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:49:07 by gwen              #+#    #+#             */
/*   Updated: 2024/03/13 18:06:20 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_dup2(t_michel *michel)
{
	dup2(michel->origin_stdin, STDIN_FILENO);
	dup2(michel->origin_stdout, STDOUT_FILENO);
}

void	ft_echo_closed_qt(t_michel *michel)
{
	char	*str_echo;
	int		i;

	i = 4;
	str_echo = ft_strnstr(michel->prompt, "echo ", ft_strlen(michel->prompt));
	while (str_echo[i])
	{
		if (str_echo[i] == '\'' || (str_echo[i] == '\"'))
		{
			michel->qt = str_echo[i];
			i++;
			break ;
		}
		i++;
	}
	while (str_echo[i] && str_echo[i] != michel->qt)
	{
		if (str_echo[i] == '\'' && str_echo[i] != michel->qt)
			michel->spl_qt_nb--;
		if (str_echo[i] == '\"' && str_echo[i] != michel->qt)
			michel->dbl_qt_nb--;
		i++;
	}
	if (str_echo[i] != michel->qt)
		michel->qt = 'u';
}

int	ft_echo_dollar(t_michel *michel, char **split_cmd, char *cmd)
{
	char	**new_spl;

	new_spl = ft_split_qt_ter(cmd, ' ', michel);
	if (ft_strlen(split_cmd[0]) == 4
		&& ft_strncmp(split_cmd[0], "echo", 4) == 0)
	{
		ft_check_dollar(1, 0, new_spl, michel);
		ft_free_tab(new_spl);
		return (0);
	}
	else if (ft_strncmp(split_cmd[0], "$", 1) == 0)
	{
		ft_check_dollar(0, '$', new_spl, michel);
		ft_free_tab(new_spl);
		return (0);
	}
	else
		return (1);
}
