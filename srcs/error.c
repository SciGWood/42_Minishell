/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 10:58:02 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/12 14:32:34 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_make_error(int error_code, char *token, char *exit)
{
	if (error_code == 2)
	{
		exit = ft_strjoin_and_free(exit, "syntax error near unexpected token ");
		exit = ft_strjoin_and_free(exit, token);
		exit = ft_strjoin_and_free(exit, "\n");
	}
	if (error_code == 3)
	{
		exit = ft_strjoin_and_free(exit, token);
		exit = ft_strjoin_and_free(exit, ": No such file or directory\n");
	}
	if (error_code == 4)
	{
		free(exit);
		exit = ft_strjoin(token, ": command not found\n");
	}
	if (error_code == 5)
	{
		exit = ft_strjoin_and_free(exit, "export: \"");
		exit = ft_strjoin_and_free(exit, token);
		exit = ft_strjoin_and_free(exit, "\" : not a valid identifier\n");
	}
	return (exit);
}

void	print_error(int error_code, char *token, int exit_status)
{
	char	*exit_sentence;

	g_exit_status = exit_status;
	exit_sentence = ft_strjoin("42_Minishell_GG: ", "");
	exit_sentence = ft_make_error(error_code, token, exit_sentence);
	if (2 <= error_code && error_code <= 5)
		ft_putstr_fd(exit_sentence, 2);
	if (error_code == 6)
	{
		exit_sentence = ft_strjoin_and_free(exit_sentence, "exit: ");
		exit_sentence = ft_strjoin_and_free(exit_sentence, token);
		exit_sentence = ft_strjoin_and_free(exit_sentence,
				": numeric argument required\n");
		ft_putstr_fd(exit_sentence, 2);
	}
	if (error_code == 7)
	{
		exit_sentence = ft_strjoin_and_free(exit_sentence, "exit: ");
		exit_sentence = ft_strjoin_and_free(exit_sentence,
				"too many arguments\n");
		ft_putstr_fd(exit_sentence, 2);
	}
	free(exit_sentence);
}
