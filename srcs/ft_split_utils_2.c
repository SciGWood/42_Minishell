/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 10:54:09 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/13 10:54:09 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lenword_between_qt_2(const char *str, int *i, int *len)
{
	char	qt;

	qt = str[*i + *len];
	(*len)++;
	while (str[*i + *len] != qt && str[*i + *len])
		(*len)++;
	if (str[*i + *len] != '\0')
		(*len)++;
}

int	check_sep(char *arg, char **sep_allowed)
{
	int		j;

	j = 0;
	while (sep_allowed[j])
	{
		if (ft_strncmp(arg, sep_allowed[j],
				ft_strlen(arg)) == 0)
			return (1);
		j++;
	}
	return (0);
}
