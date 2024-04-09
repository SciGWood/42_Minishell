/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:10:43 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/12 14:30:22 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	lenword_between_qt_echo(const char *str, int *i, int *len,
	t_michel *michel)
{
	while (((str[*i + *len] != michel->qt)
			|| str[*i + *len] != ' ') && str[*i + *len])
		(*len)++;
}

static int	len_tab_export(char const *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			if (str[i - 1] == c)
				len++;
			between_qt(str, &i, str[i]);
		}
		else if (str[i] != c && str[i] != 39 && str[i] != 34)
		{
			while (str[i] && str[i] != c && str[i] != 39 && str[i] != 34)
				i++;
			len++;
		}
		while (str[i] && str[i] == c)
			i++;
	}
	return (len + 1);
}

static int	len_word_export(int *index, char const *str, char c,
	t_michel *michel)
{
	int	len;

	len = 0;
	while (str[*index] == c)
		(*index)++;
	if ((str[*index] == 39 || str[*index] == 34) && str[*index - 1] == c)
		lenword_between_qt_echo(str, index, &len, michel);
	else
	{
		while (str[*index + len] != c && str[*index + len] != 39
			&& str[*index + len] != 34 && str[*index + len])
			len++;
		if ((str[*index + len] == 39 || str[*index + len] == 34)
			&& str[*index + len - 1] != c)
			lenword_between_qt_echo(str, index, &len, michel);
	}
	return (len);
}

static char	*get_next_word_export(int *index, char const *str, char c,
	t_michel *michel)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = len_word_export(index, str, c, michel);
	if (len == 0)
		return (NULL);
	res = malloc((len + 1) * sizeof(char));
	while (i < len && str[*index])
	{
		while ((str[*index] == 39 || str[*index] == 34) && str[*index])
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

char	**ft_split_qt_bis(char const *s, char c, t_michel *michel)
{
	char	**res;
	int		len;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	len = len_tab_export(s, c);
	i = 0;
	j = 0;
	if (len == 0)
		return (NULL);
	res = malloc(len * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < len - 1)
	{
		res[i] = get_next_word_export(&j, s, c, michel);
		i++;
	}
	res[i] = 0;
	return (res);
}
