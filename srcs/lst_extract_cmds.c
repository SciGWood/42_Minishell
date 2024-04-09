/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_extract_cmds.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 16:19:55 by gpeyre            #+#    #+#             */
/*   Updated: 2024/02/29 16:19:55 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*manage_pipe(t_michel *michel, char *cmds, int *i)
{
	if (!michel->miss_file)
	{
		if (!cmds)
			cmds = ft_strdup("");
		cmds = ft_strjoin_and_free(cmds, michel->spl_prompt[*i]);
		cmds = ft_strjoin_and_free(cmds, michel->spl_prompt[*i + 1]);
	}
	(*i)++;
	return (cmds);
}

char	*pull_file(t_michel *michel, char *cmds, int *i)
{
	if (*i >= 1 && michel->spl_prompt[*i - 1] && !michel->miss_file)
	{
		if (*i >= 2 && check_sep(michel->spl_prompt[*i - 2], michel->sep_in))
			(*i)++;
		else
		{
			if (cmds)
			{
				free(cmds);
				cmds = NULL;
			}
			cmds = fill_cmds(cmds, michel, *i - 1);
			(*i)++;
		}
	}
	else
	{
		if (michel->miss_file)
			michel->miss_file -= 1;
		(*i)++;
	}
	return (cmds);
}

char	*fill_cmds(char *cmds, t_michel *michel, int i)
{
	if (!michel->miss_file)
	{
		if (!cmds)
			cmds = ft_strdup("");
		cmds = ft_strjoin_and_free(cmds, michel->spl_prompt[i]);
	}
	return (cmds);
}

void	manage_save_next(t_michel *michel, int *i)
{
	if (michel->spl_prompt[*i + 2])
	{
		if (!ft_strncmp(michel->spl_prompt[*i + 2], "|",
				ft_strlen(michel->spl_prompt[*i + 2])))
			(*i) += 3;
		else
			(*i) += 2;
		while (michel->spl_prompt[*i])
		{
			michel->sub_prompt = fill_cmds(michel->sub_prompt, michel, *i);
			(*i)++;
		}
	}
	else
		(*i)++;
}

char	*extract_cmds_2(t_michel *michel)
{
	int		i;
	char	*cmds;

	i = 0;
	cmds = NULL;
	while (michel->spl_prompt[i])
	{
		if (ft_strncmp(michel->spl_prompt[i], "|",
				ft_strlen(michel->spl_prompt[i])) == 0)
			cmds = manage_pipe(michel, cmds, &i);
		else if (check_sep(michel->spl_prompt[i], michel->sep_in))
			cmds = pull_file(michel, cmds, &i);
		else if (check_sep(michel->spl_prompt[i], michel->sep_out))
			manage_save_next(michel, &i);
		else
			cmds = fill_cmds(cmds, michel, i);
		if (michel->spl_prompt[i])
			i++;
	}
	return (cmds);
}
