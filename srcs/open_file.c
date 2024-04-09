/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:22:18 by gpeyre            #+#    #+#             */
/*   Updated: 2024/02/12 16:22:18 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_stdin(char *arg, t_pipex *data, t_michel *michel)
{
	char	**file;

	file = ft_split_qt(arg, ' ');
	data->in_fd = open(file[0], O_RDONLY, 0777);
	if (data->in_fd == -1)
	{
		close(data->in_fd);
		ft_free_tab(file);
		michel->miss_file += 1;
		if (data->first_file)
		{
			data->file = ft_split_qt(arg, ' ');
			data->first_file = 0;
		}
		return (1);
	}
	dup2(data->in_fd, STDIN_FILENO);
	close(data->in_fd);
	ft_free_tab(file);
	return (0);
}

int	redirect_stdout(char *arg, t_pipex *data, char option)
{
	char	**file;

	file = ft_split_qt(arg, ' ');
	if (option == 'T')
		data->out_fd = open(file[0], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (option == 'A')
		data->out_fd = open(file[0], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (!data->out_fd)
		print_error(3, file[0], 1);
	dup2(data->out_fd, STDOUT_FILENO);
	close(data->out_fd);
	ft_free_tab(file);
	return (0);
}

void	sep_loop(t_michel *michel, t_pipex *data, int *i)
{
	while (michel->spl_prompt[*i])
	{
		if (ft_strncmp(michel->spl_prompt[*i], ">",
				ft_strlen(michel->spl_prompt[*i])) == 0)
		{
			redirect_stdout(michel->spl_prompt[*i + 1], data, 'T');
			break ;
		}
		else if (ft_strncmp(michel->spl_prompt[*i], ">>",
				ft_strlen(michel->spl_prompt[*i])) == 0)
		{
			redirect_stdout(michel->spl_prompt[*i + 1], data, 'A');
			break ;
		}
		else if (ft_strncmp(michel->spl_prompt[*i], "<",
				ft_strlen(michel->spl_prompt[*i])) == 0)
			redirect_stdin(michel->spl_prompt[*i + 1], data, michel);
		else if (ft_strncmp(michel->spl_prompt[*i], "<<",
				ft_strlen(michel->spl_prompt[*i])) == 0)
		{
			ft_heredoc(data, michel, *i);
			open_heredoc(data);
		}
		(*i)++;
	}
}
			/* if (ft_strncmp(michel->spl_prompt[i + 2], "|",
					ft_strlen(michel->spl_prompt[i + 2])) == 0) */

int	open_file(t_michel *michel)
{
	t_pipex	data;
	int		i;

	data.first_file = 1;
	data.file = NULL;
	i = 0;
	sep_loop(michel, &data, &i);
	if (michel->miss_file)
	{
		print_error(3, data.file[0], 1);
		ft_free_tab(data.file);
	}
	return (0);
}

/* 
int main()
{
	t_michel michel;

	ft_init_struct(&michel);
	michel.prompt = "cat -e << EXT | rev >> outfile";
	michel.spl_prompt = ft_split_prompt(michel.prompt, "<>|");

	open_file(&michel);
	ft_free_tab(michel.spl_prompt);
	return (0);
} */