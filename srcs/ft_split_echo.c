/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:10:43 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/12 14:55:47 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	between_qt_echo(char const *str, int *i, t_michel *michel)
{
	(*i)++;
	while (str[*i] != michel->qt && str[*i])
		(*i)++;
	if (str[*i] != '\0')
		(*i)++;
}

static int	len_tab_echo(char const *str, char c, t_michel *michel)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == michel->qt)
		{
			if (str[i - 1] == c)
				len++;
			between_qt_echo(str, &i, michel);
		}
		else if (str[i] != c && str[i] != michel->qt)
		{
			while (str[i] && str[i] != c && str[i] != michel->qt)
				i++;
			len++;
		}
		while (str[i] && str[i] == c)
			i++;
	}
	return (len + 1);
}

static int	len_word_echo(int *index, char const *str, char c, t_michel *michel)
{
	int	len;

	len = 0;
	while (str[*index] == c)
		(*index)++;
	if ((str[*index] == michel->qt) && str[*index - 1] == c)
		lenword_between_qt_echo(str, index, &len, michel);
	else
	{
		while (str[*index + len] != c && str[*index + len]
			&& str[*index + len] != michel->qt)
			len++;
		if ((str[*index + len] == michel->qt)
			&& str[*index + len - 1] != c)
			lenword_between_qt_echo(str, index, &len, michel);
	}
	return (len);
}

static char	*get_next_word_echo(int *index, char const *str, char c,
	t_michel *michel)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = len_word_echo(index, str, c, michel);
	if (len == 0)
		return (NULL);
	res = malloc((len + 1) * sizeof(char));
	while (i < len && str[*index])
	{
		while (str[*index] == michel->qt && str[*index])
			(*index)++;
		if (str[*index] == '\0')
			break ;
		res[i] = str[*index];
		i++;
		(*index)++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_split_qt_ter(char const *s, char c, t_michel *michel)
{
	char	**res;
	int		len;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	len = len_tab_echo(s, c, michel);
	i = 0;
	j = 0;
	if (len == 0)
		return (NULL);
	res = malloc(len * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < len - 1)
	{
		res[i] = get_next_word_echo(&j, s, c, michel);
		i++;
	}
	res[i] = 0;
	return (res);
}
