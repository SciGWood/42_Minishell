/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 09:36:21 by gpeyre            #+#    #+#             */
/*   Updated: 2024/02/22 09:36:21 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_clean_prompt(t_michel *michel)
{
	int	i;
	int	spc_nbr;

	spc_nbr = 0;
	i = 0;
	while (michel->prompt[i])
	{
		if (michel->prompt[i] == 39 || michel->prompt[i] == 34)
			between_qt(michel->prompt, &i, michel->prompt[i]);
		else if (michel->prompt[i] == '|')
			spc_nbr += 2;
		i++;
	}
	return (spc_nbr);
}

void	do_space(char *temp, int *i, int *j)
{
	temp[*j] = ' ';
	temp[*j + 1] = '|';
	temp[*j + 2] = ' ';
	(*j) += 3;
	(*i)++;
}

void	pass_qt(t_michel *michel, char *temp, int *i, int *j)
{
	char	qt;

	qt = michel->prompt[*i];
	temp[*j] = michel->prompt[*i];
	(*i)++;
	(*j)++;
	while (michel->prompt[*i] != qt && michel->prompt[*i])
	{
		temp[*j] = michel->prompt[*i];
		(*i)++;
		(*j)++;
	}
}

char	*clean_prompt(t_michel *michel)
{
	int		i;
	int		j;
	int		spc_nbr;
	char	*temp;

	spc_nbr = len_clean_prompt(michel);
	temp = malloc((ft_strlen(michel->prompt) + spc_nbr + 1) * sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	j = i;
	while (michel->prompt[i])
	{
		if (michel->prompt[i] == '|')
			do_space(temp, &i, &j);
		else if (michel->prompt[i] == 39 || michel->prompt[i] == 34)
			pass_qt(michel, temp, &i, &j);
		temp[j] = michel->prompt[i];
		i++;
		j++;
	}
	temp[j] = 0;
	return (temp);
}

/* int main()
{
	t_michel michel;

	michel.prompt = "  len|wc   'len|cat' ";
	int len= len_clean_prompt(&michel);
	printf("%d\n", len);
	// char *prompt_wo_space = voiding_space(&michel);
	char *prompt_clean = clean_prompt(&michel);
	// printf("%s\n", prompt_wo_space);
	printf("%s\n", prompt_clean);
	// free(prompt_wo_space);
	free(prompt_clean);
	return (0);
} */