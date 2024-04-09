/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:13:01 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/12 14:31:16 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	between_qt(char const *str, int *i, char qt)
{
	(*i)++;
	while (str[*i] != qt && str[*i])
		(*i)++;
	if (str[*i] != '\0')
		(*i)++;
}

void	lenword_between_qt(const char *str, int *i, int *len)
{
	char	qt;

	qt = 0;
	if (*i >= 1 && (str[*i - 1] == 39 || str[*i - 1] == 34))
		qt = str[*i - 1];
	else
	{
		qt = str[*i];
		(*i)++;
	}
	(*len)++;
	while (str[*i + *len] != qt && str[*i + *len])
		(*len)++;
}
	/* if (str[*i + *len] != '\0')
		(*len)++; */

void	manage_charset(char *str, int *index, int *len, char *charset)
{
	if ((str[*index] == '<' || str[*index] == '>')
		&& str[*index + 1] == str[*index])
		(*index)++;
	if (str[*index] != '\0')
		(*index)++;
	if (str[*index - 1] == '<' || str[*index - 1] == '>')
	{
		while (str[*index] == ' ' && str[*index])
			(*index)++;
		while (!ft_strchr(charset, str[*index]) && str[*index] != ' '
			&& str[*index])
		{
			if (str[*index] == 39 || str[*index] == 34)
				between_qt(str, index, str[*index]);
			if (str[*index] != '\0')
				(*index)++;
		}
		while (str[*index] == ' ' && str[*index])
			(*index)++;
		(*len)++;
	}
}

void	manage_charset_gnw(char *str, int index, int *len)
{
	if ((str[index] == '<' || str[index] == '>')
		&& str[index + 1] == str[index])
		(*len)++;
	if (str[index + *len] != '\0')
		(*len)++;
}

void	manage_charset_gnw_2(char *str, int i, int *len, char *charset)
{
	if (i >= 1 && (str[i - 1] == '<' || str[i - 1] == '>'))
	{
		while (str[i + *len] == ' ' && str[i + *len])
			(*len)++;
		while (!ft_strchr(charset, str[i + *len]) && str[i + *len] != ' '
			&& str[i + *len])
		{
			if (str[i + *len] == 39 || str[i + *len] == 34)
				lenword_between_qt_2(str, &i, len);
			else if (str[i + *len] != '\0')
				(*len)++;
		}
		while (str[i + *len] == ' ' && str[i + *len])
			(*len)++;
	}
	else
	{
		while (!ft_strchr(charset, str[i + *len]) && str[i + *len])
		{
			if (str[i + *len] == 39 || str[i + *len] == 34)
				lenword_between_qt_2(str, &i, len);
			else if (str[i + *len] != '\0')
				(*len)++;
		}
	}
}
