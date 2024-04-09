/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:58:14 by gwen              #+#    #+#             */
/*   Updated: 2024/03/13 16:32:55 by gpeyre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include "../libft/libft.h"
# include <stdarg.h>
# include <fcntl.h>
# include <strings.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>

# define BLUE "\001\033[34m\002"
# define WHITE "\001\033[0m\002"

/*Global Variable*/
extern int	g_exit_status;

typedef struct s_pipex
{
	int		in_fd;
	int		out_fd;
	char	**file;
	int		first_file;
}				t_pipex;

typedef struct s_michel
{
	char	**envp;
	char	**env;
	char	*prompt;
	char	**spl_prompt;
	char	**cmds;
	char	*sub_prompt;
	char	*new_prompt;
	char	**split_prompt;
	int		origin_stdin;
	int		origin_stdout;
	char	*sep_allowed[6];
	char	*sep_in[3];
	char	*sep_out[3];
	int		var_nb;
	int		ignore;
	int		flag;
	int		qt;
	int		spl_qt_nb;
	int		dbl_qt_nb;
	int		miss_file;
}				t_michel;

/*builtins.c*/
int		ft_pwd(void);
int		ft_cd(const char *path, char **split_cmd);
int		ft_env(char *envp[]);
int		ft_unset(char **split_prompt, t_michel *michel);
int		ft_export(t_michel *michel, char *cmd);

/*dollar.c*/
int		ft_echo_print(char **split_prompt);
int		ft_dollar_env(char *spl);
void	ft_dollar_print_02(char *str);
void	ft_dollar_print_01(char **split_prompt);
void	ft_check_dollar(int i, int flag, char **new_spl, t_michel *michel);

/*dollar_bis.c*/
void	ft_dup2(t_michel *michel);
void	ft_echo_closed_qt(t_michel *michel);
int		ft_echo_dollar(t_michel *michel, char **split_cmd, char *cmd);

/*env.c*/
int		ft_len_char(char *str, char c);
void	ft_rem_var(t_michel *michel, char *var_to_remove);
char	*ft_shlvl(char	*lvlp);
void	ft_getenvp(t_michel *michel);

/* error_2.c */
void	ft_remove_nl(t_michel *michel);
void	add_next_cmd(t_michel *michel);
void	write_next_cmd(void);
char	*manage_nonext(t_michel *michel);
char	*check_usage_error(t_michel *michel);

/* error.c */
char	*ft_make_error(int error_code, char *token, char *exit);
void	print_error(int error_code, char *token, int exit_status);

/* execution.c */
int		ft_fork(char **cmd, char **env, t_michel *michel);
void	ft_exec(char **cmd, char **env, t_michel *michel);

/*export_01.c*/
char	**ft_tab_copy(char **env);
void	ft_ignore(t_michel *michel, char *var_to_remove);
void	ft_double_var(t_michel *michel, char **spl, int i, int j);
void	ft_var_change(t_michel *michel, int i, char *var_to_remove, int flag);
void	ft_check_var(t_michel *michel, char **spl);

/*export_02.c*/
void	ft_print_export(char **env_copy);
char	**ft_sort_env(char **env);
void	ft_add_var_env(t_michel *michel, int i);
int		ft_is_valid_identifier(char *str);
void	ft_getenv(t_michel *michel, int var_nb);

/* extract_cmds_2.c */
int		count_cmds(char *cmds);
// char	*fill_cmds(char *cmds, char **new_spl, int i);
char	*fill_cmds(char *cmds, t_michel *michel, int i);
char	*extract_cmds_2(t_michel *michel);

/* extract_cmds.c */
char	**extract_cmds(t_michel *michel);
void	init_sep_extract(t_michel *michel);

/*ft_split_echo*/
void	between_qt_echo(char const *str, int *i, t_michel *michel);
char	**ft_split_qt_ter(char const *s, char c, t_michel *michel);

/*ft_split_export*/
void	lenword_between_qt_echo(const char *str, int *i, int *len,
			t_michel *michel);
char	**ft_split_qt_bis(char const *s, char c, t_michel *michel);

/* ft_split_prompt.c */
char	**ft_split_prompt(char *str, char *charset);

/* ft_split_qt.c */
char	**ft_split_qt(char const *s, char c);

/* ft_split_utils_2.c */
void	lenword_between_qt_2(const char *str, int *i, int *len);
int		check_sep(char *arg, char **sep_allowed);

/* ft_split_utils.c */
void	between_qt(char const *str, int *i, char qt);
void	lenword_between_qt(const char *str, int *i, int *len);
void	manage_charset(char *str, int *index, int *len, char *charset);
void	manage_charset_gnw(char *str, int index, int *len);
void	manage_charset_gnw_2(char *str, int i, int *len, char *charset);

/*init_exit.c*/
void	ft_init_struct(t_michel *michel);
void	ft_free_msh(t_michel *michel);
void	ft_dollar_exit_status(void);
int		ft_exit(t_michel *michel);
int		ft_exec_exit(char *cmd, t_michel *michel);

/*minishell.c*/
int		ft_parse_token(t_michel *michel);
int		ft_builtins_env(t_michel *michel, char **split_cmd, char *cmd);
int		ft_parse_wo_token(t_michel *michel, char **split_cmd, char *cmd);
int		ft_parse_prompt(t_michel *michel);

/*msh_utils.c*/
void	ft_free_tab(char **tab);
int		len_wo_space(char *str);
char	*voiding_space(t_michel *michel);
void	check_qt_peer(t_michel *michel);

/* open_file.c */
int		open_heredoc(t_pipex *data);
int		ft_heredoc(t_pipex *data, t_michel *michel, int i);

/* open_file.c */
int		redirect_stdin(char *arg, t_pipex *data, t_michel *michel);
int		redirect_stdout(char *arg, t_pipex *data, char option);
int		open_file(t_michel *michel);

/* pipe.c */
int		ft_pipe(char **cmds, t_michel *michel);

/*signals.c*/
void	ft_sigquit(void);
void	handle_sigint(int sigint);

#endif