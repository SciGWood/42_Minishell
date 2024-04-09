/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_qt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 16:10:43 by gpeyre            #+#    #+#             */
/*   Updated: 2024/02/08 16:10:43 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	len_tab(char const *str, char c)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == 39 || str[i] == 34)
		{
			between_qt(str, &i, str[i]);
			len++;
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

static int	len_word(int *index, char const *str, char c)
{
	int	len;

	len = 0;
	while (str[*index] == c)
		(*index)++;
	if (str[*index] == 39 || str[*index] == 34)
		lenword_between_qt(str, index, &len);
	else
	{
		while (str[*index + len] != c && str[*index + len] != 39
			&& str[*index + len] != 34 && str[*index + len])
			len++;
	}
	return (len);
}

static char	*get_next_word(int *index, char const *str, char c)
{
	char	*res;
	int		len;
	int		i;

	i = 0;
	len = len_word(index, str, c);
	if (len == 0)
		return (NULL);
	res = malloc((len + 1) * sizeof(char));
	while (i < len)
	{
		res[i] = str[*index];
		i++;
		(*index)++;
	}
	if (str[*index] == 39 || str[*index] == 34)
		(*index)++;
	res[i] = 0;
	return (res);
}

char	**ft_split_qt(char const *s, char c)
{
	char	**res;
	int		len;
	int		i;
	int		j;

	if (!s)
		return (NULL);
	len = len_tab(s, c);
	i = 0;
	j = 0;
	if (len == 0)
		return (NULL);
	res = malloc(len * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < len - 1)
	{
		res[i] = get_next_word(&j, s, c);
		i++;
	}
	res[i] = 0;
	return (res);
}
/* int main(void)
{
	char const str[] = "cat \"<infile\"";
	char c = ' ';
	// int len = len_tab(str, c);
	// printf("%d\n", len);
	int i = 0;
	char **res;

	res = ft_split_qt(str, c);

	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
} */