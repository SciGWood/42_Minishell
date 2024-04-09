/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:21:06 by gwen              #+#    #+#             */
/*   Updated: 2024/03/13 16:33:35 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_init_struct(t_michel *michel)
{
	michel->envp = NULL;
	michel->env = NULL;
	michel->prompt = NULL;
	michel->spl_prompt = NULL;
	michel->cmds = NULL;
	michel->sub_prompt = NULL;
	michel->new_prompt = NULL;
	michel->split_prompt = NULL;
	michel->origin_stdin = dup(STDIN_FILENO);
	michel->origin_stdout = dup(STDOUT_FILENO);
	michel->sep_allowed[0] = ">";
	michel->sep_allowed[1] = "<";
	michel->sep_allowed[2] = ">>";
	michel->sep_allowed[3] = "<<";
	michel->sep_allowed[4] = "|";
	michel->sep_allowed[5] = NULL;
	init_sep_extract(michel);
	michel->var_nb = 0;
	michel->ignore = 0;
	michel->flag = 0;
	michel->qt = 0;
	michel->spl_qt_nb = 0;
	michel->dbl_qt_nb = 0;
	michel->miss_file = 0;
}

/* if (michel->prompt)
	free(michel->prompt); */
void	ft_free_msh(t_michel *michel)
{
	if (michel->env)
		ft_free_tab(michel->env);
	rl_clear_history();
}

void	ft_dollar_exit_status(void)
{
	char	*number;

	number = ft_itoa(g_exit_status);
	print_error(4, number, 127);
	free(number);
}

/* g_exit_status = 0; */
int	ft_exit(t_michel *michel)
{
	printf("exit\n");
	return (ft_free_msh(michel), g_exit_status);
}

int	ft_exec_exit(char *cmd, t_michel *michel)
{
	char	**new_spl;

	(void)michel;
	new_spl = ft_split_qt_bis(cmd, ' ', michel);
	if (!new_spl[1])
	{
		ft_free_tab(new_spl);
		g_exit_status = 0;
		return (g_exit_status);
	}
	if (!ft_isdigit_str(new_spl[1], 1))
		print_error(6, new_spl[1], 2);
	else
	{
		g_exit_status = ft_atoi(new_spl[1]);
		if (new_spl[2])
			print_error(7, NULL, 1);
	}
	ft_free_tab(new_spl);
	return (g_exit_status);
}
