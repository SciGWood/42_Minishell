/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:48:39 by gpeyre            #+#    #+#             */
/*   Updated: 2024/02/05 15:48:39 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	len_tab(char *str, char *charset)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (!ft_strchr(charset, str[i]) && str[i])
		{
			while (!ft_strchr(charset, str[i]) && str[i])
			{
				if (str[i] == 39 || str[i] == 34)
					between_qt(str, &i, str[i]);
				if (str[i])
					i++;
			}
		}
		else if (ft_strchr(charset, str[i]))
			manage_charset(str, &i, &len, charset);
		len++;
	}
	return (len);
}

static char	*get_next_word(int *index, char *str, char *charset)
{
	int		len;
	char	*res;
	int		i;

	i = 0;
	len = 0;
	if (!ft_strchr(charset, str[*index]) && str[*index])
		manage_charset_gnw_2(str, *index, &len, charset);
	else if (ft_strchr(charset, str[*index]))
		manage_charset_gnw(str, *index, &len);
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = str[*index];
		i++;
		(*index)++;
	}
	res[i] = 0;
	return (res);
}

char	**ft_split_prompt(char *str, char *charset)
{
	char	**res;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = len_tab(str, charset);
	res = malloc((len + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = get_next_word(&j, str, charset);
		i++;
	}
	res[i] = 0;
	return (res);
}

/* int main(void)
{
	char str[] = "grep hi '<infile' <    infile";
	char charset[] = "<>|";
	int len = len_tab(str, charset);
	printf("%d\n", len);
	int i = 0;
	char** res;

	res = ft_split_prompt(str, charset);
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