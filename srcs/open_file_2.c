/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:00:20 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/13 14:00:20 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_heredoc(t_pipex *data)
{
	data->in_fd = open("heredoc", O_RDONLY, 0777);
	if (!data->in_fd)
		print_error(3, "heredoc", 1);
	dup2(data->in_fd, STDIN_FILENO);
	close(data->in_fd);
	return (0);
}

int	ft_heredoc(t_pipex *data, t_michel *michel, int i)
{
	char	*line;
	char	**delim;

	delim = ft_split_qt(michel->spl_prompt[i + 1], ' ');
	data->in_fd = open("heredoc", O_CREAT | O_RDWR | O_TRUNC, 00777);
	while (1)
	{
		ft_putstr_fd(">", 0);
		line = get_next_line(0);
		if (!line)
			return (1);
		if (ft_strlen(delim[0]) + 1 == ft_strlen(line)
			&& ft_strncmp(line, delim[0], ft_strlen(delim[0])) == 0)
			break ;
		ft_putstr_fd(line, data->in_fd);
	}
	close(data->in_fd);
	free(line);
	ft_free_tab(delim);
	return (0);
}
