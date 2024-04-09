/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:13:03 by gpeyre            #+#    #+#             */
/*   Updated: 2024/03/13 10:09:22 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmds(char *cmds)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (cmds[i])
	{
		if (cmds[i] == '|')
			i++;
		while (cmds[i] && cmds[i] != '|')
			i++;
		len++;
	}
	return (len);
}

void	save_cmds(char **cmds_temp, char **cmds)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmds_temp[i])
	{
		if (ft_strncmp(cmds_temp[i], "|", ft_strlen(cmds_temp[i])) == 0)
			i++;
		cmds[j] = ft_strdup(cmds_temp[i]);
		i++;
		j++;
	}
	cmds[j] = 0;
}

void	init_sep_extract(t_michel *michel)
{
	michel->sep_out[0] = ">";
	michel->sep_out[1] = ">>";
	michel->sep_out[2] = 0;
	michel->sep_in[0] = "<";
	michel->sep_in[1] = "<<";
	michel->sep_in[2] = 0;
}

char	**extract_cmds(t_michel *michel)
{
	char	*str_w_cmds;
	char	**cmds;
	char	**cmds_temp;

	str_w_cmds = extract_cmds_2(michel);
	if (!str_w_cmds)
		return (NULL);
	cmds_temp = ft_split_prompt(str_w_cmds, "|");
	cmds = (char **)malloc((count_cmds(str_w_cmds) + 1) * sizeof(char *));
	if (!cmds)
		return (NULL);
	free(str_w_cmds);
	save_cmds(cmds_temp, cmds);
	ft_free_tab(cmds_temp);
	return (cmds);
}

/* int main()
{
	t_michel michel;
	char 	**cmds;
	//char 	*str;
	int i = 0;

	ft_init_struct(&michel);
	michel.prompt = "< infile cat -e > outfile | grep 'hey' | rev";
	michel.spl_prompt = ft_split_prompt(michel.prompt, "<>|");
	//str = extract_cmds_2(&michel);
	cmds = extract_cmds(&michel);
	//printf("%s\n", str);
	//free(str);
	while (cmds[i])
	{
		printf("%s\n", cmds[i]);
		i++;
	}
	printf("finish extract cmds\n");
	if (michel.sub_prompt)
	{
		printf("%s\n", michel.sub_prompt);
		free(michel.sub_prompt);
	}
	ft_free_tab(cmds);
	ft_free_tab(michel.spl_prompt);
} */