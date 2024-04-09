/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:11:39 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/13 14:21:50 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_remove_nl(t_michel *michel)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * ft_strlen(michel->prompt));
	while (michel->prompt[i] != '\n')
	{
		tmp[j] = michel->prompt[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	free(michel->prompt);
	michel->prompt = ft_strdup(tmp);
	free(tmp);
}

void	add_next_cmd(t_michel *michel)
{
	int		fd;
	char	*next_line;

	fd = open("next_cmd", O_RDONLY, 00777);
	while (1)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
			break ;
		michel->prompt = ft_strjoin_and_free(michel->prompt, next_line);
		free(next_line);
	}
	ft_remove_nl(michel);
	close(fd);
}

void	write_next_cmd(void)
{
	char	*line;
	int		fd;

	fd = open("next_cmd", O_CREAT | O_RDWR | O_TRUNC, 00777);
	while (1)
	{
		ft_putstr_fd(">", 0);
		line = get_next_line(0);
		if (!line)
			return ;
		if (ft_strnstr(line, "\n", ft_strlen(line)))
		{
			ft_putstr_fd(line, fd);
			break ;
		}
		ft_putstr_fd(line, fd);
	}
	close(fd);
	free(line);
}

char	*manage_nonext(t_michel *michel)
{
	int	i;

	i = 0;
	while (michel->spl_prompt[i])
		i++;
	if (check_sep(michel->spl_prompt[i - 1], michel->sep_allowed) == 1)
	{
		if (ft_strncmp(michel->spl_prompt[i - 1], "|",
				ft_strlen(michel->spl_prompt[i - 1])) == 0)
		{
			write_next_cmd();
			add_next_cmd(michel);
			michel->new_prompt = voiding_space(michel);
			ft_free_tab(michel->spl_prompt);
			michel->spl_prompt = ft_split_prompt(michel->new_prompt, "<>|");
			free(michel->new_prompt);
		}
		else
			return (ft_strdup("new_line"));
	}
	return (NULL);
}

char	*check_usage_error(t_michel *michel)
{
	int		i;
	char	*nonext;

	i = 0;
	nonext = manage_nonext(michel);
	if (nonext)
		return (nonext);
	while (michel->spl_prompt[i])
	{
		if (check_sep(michel->spl_prompt[i], michel->sep_allowed)
			&& michel->spl_prompt[i + 1])
		{
			if (check_sep(michel->spl_prompt[i + 1], michel->sep_allowed))
			{
				nonext = ft_strdup(michel->spl_prompt[i + 1]);
				return (nonext);
			}
		}
		i++;
	}
	return (NULL);
}

/* int main()
{
	t_michel michel;
	char 	*res;

	michel.prompt = "cat < infile |";
	michel.new_prompt = voiding_space(&michel);
	michel.spl_prompt = ft_split_prompt(michel.new_prompt, "<>|");
	michel.sep_allowed[0] = ">";
	michel.sep_allowed[1] = "<";
	michel.sep_allowed[2] = ">>";
	michel.sep_allowed[3] = "<<";
	michel.sep_allowed[4] = "|";
	michel.sep_allowed[5] = NULL;

	res = check_usage_error(&michel);
	if (res)
		printf("%s\n", res);
	printf("%s\n", michel.prompt);
	free(michel.new_prompt);
	ft_free_tab(michel.spl_prompt);
	return (0);
} */