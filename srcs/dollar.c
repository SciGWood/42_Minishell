/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:28:55 by gwen              #+#    #+#             */
/*   Updated: 2024/03/13 17:54:31 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
/* '$' != "$" && $ */

int	ft_echo_print(char **sp_prompt)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if ((ft_strlen(sp_prompt[1]) == 2 && ft_strncmp(sp_prompt[1], "-n", 2) == 0)
		|| !sp_prompt[1])
		return (0);
	else
	{
		while (sp_prompt[j])
			j++;
		while (i < j - 1)
		{
			printf("%s ", sp_prompt[i]);
			i++;
		}
		printf("%s", sp_prompt[i]);
		printf("\n");
	}
	return (0);
}

int	ft_dollar_env(char *spl)
{
	char	*output;
	char	**s;

	if (spl[0] == '?')
	{
		printf("%d", g_exit_status);
		s = ft_split(spl, '?');
		if (s[0])
			printf("%s", s[0]);
		ft_free_tab(s);
		printf(" ");
		g_exit_status = 0;
		return (0);
	}
	output = getenv(spl);
	if (output)
	{
		printf("%s", output);
		return (0);
	}
	else
		return (1);
}

void	ft_dollar_print_02(char *str)
{
	char	**qt_spl;
	int		i;

	i = 0;
	qt_spl = ft_split_prompt(str, " \'$");
	while (qt_spl[i])
	{
		if (!ft_strnstr(qt_spl[i], "$", ft_strlen(qt_spl[i])))
			printf("%s", qt_spl[i]);
		else if (ft_strnstr(qt_spl[i], "$", ft_strlen(qt_spl[i])))
		{
			if (qt_spl[i + 1] && ft_dollar_env(qt_spl[i + 1]) == 0)
				i++;
			else
				printf("%s", qt_spl[i]);
		}
		i++;
	}
	ft_free_tab(qt_spl);
}

void	ft_dollar_print_01(char **split_prompt)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (split_prompt[j])
		j++;
	while (i < j - 1)
	{
		if (ft_strnstr(split_prompt[i], "$", ft_strlen(split_prompt[i])))
			ft_dollar_print_02(split_prompt[i]);
		else
			printf("%s ", split_prompt[i]);
		i++;
	}
	if (ft_strnstr(split_prompt[i], "$", ft_strlen(split_prompt[i])))
		ft_dollar_print_02(split_prompt[i]);
	else
		printf("%s", split_prompt[i]);
	printf("\n");
}

void	ft_check_dollar(int i, int flag, char **new_spl, t_michel *michel)
{
	char	*output;

	if ((!new_spl[i] || new_spl[i][0] == '\0') && michel->qt != 'u')
		printf("\n");
	else if (michel->qt != 'u')
	{
		output = getenv(&new_spl[i][1]);
		if (flag == '$')
		{
			if (!new_spl[i][1] || new_spl[i][1] == '$')
				print_error(4, new_spl[i], 127);
			else if (new_spl[i][1] == '?' && !new_spl[i][2])
				ft_dollar_exit_status();
			else if (output)
				print_error(3, output, 1);
		}
		else if ((!output && !ft_strnstr(new_spl[i], "$",
					ft_strlen(new_spl[i])))
			|| (ft_strnstr(new_spl[i], "$", ft_strlen(new_spl[i]))
				&& michel->qt == '\''))
			ft_echo_print(new_spl);
		else if (ft_strnstr(new_spl[i], "$", ft_strlen(new_spl[i])))
			ft_dollar_print_01(new_spl);
	}
}
/* else if ((!output && new_spl[i][0] != '$')
	|| (new_spl[i][0] == '$' && michel->qt == '\''))
	ft_echo_print(new_spl); */
/* else if (new_spl[i][0] == '$')//&& michel->qt != 'u')
	ft_dollar_print_01(new_spl); */
