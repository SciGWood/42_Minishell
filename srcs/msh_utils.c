/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 11:58:00 by gwen              #+#    #+#             */
/*   Updated: 2024/03/13 18:06:33 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

int	len_wo_space(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			len++;
		i++;
	}
	return (len);
}

void	still_new_prompt(t_michel *michel, char *new_prompt)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (michel->prompt[i])
	{
		if (michel->prompt[i] == ' ')
			i++;
		else
		{
			new_prompt[j] = michel->prompt[i];
			i++;
			j++;
		}
	}
	new_prompt[j] = '\0';
}

char	*voiding_space(t_michel *michel)
{
	char	*prompt_wo_space;
	int		len;

	len = len_wo_space(michel->prompt);
	if (len == 0)
		return (ft_strdup(""));
	prompt_wo_space = (char *)malloc((len + 1) * sizeof(char));
	if (!prompt_wo_space)
		return (NULL);
	still_new_prompt(michel, prompt_wo_space);
	return (prompt_wo_space);
}

void	check_qt_peer(t_michel *michel)
{
	int	i;

	i = 0;
	michel->spl_qt_nb = 0;
	michel->dbl_qt_nb = 0;
	michel->qt = 0;
	while (michel->prompt[i])
	{
		if (michel->prompt[i] == 39)
			michel->spl_qt_nb++;
		else if (michel->prompt[i] == 34)
			michel->dbl_qt_nb++;
		i++;
	}
	if (ft_strnstr(michel->prompt, "echo ", ft_strlen(michel->prompt))
		&& (michel->spl_qt_nb >= 1 || michel->dbl_qt_nb >= 1))
		ft_echo_closed_qt(michel);
	if (michel->qt == 'u' || (michel->spl_qt_nb % 2 != 0
			|| michel->dbl_qt_nb % 2 != 0))
		printf("42_Minishell_GG : unclosed quotes\n");
}
