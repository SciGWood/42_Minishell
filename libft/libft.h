/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:02:23 by gdetourn          #+#    #+#             */
/*   Updated: 2024/02/29 14:59:44 by gwen             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <strings.h>

/*ft_atoi_itoa.c*/
int		ft_isdigit(int c);
int		ft_isdigit_str(char *str, int flag);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);

/*ft_split.c*/
char	**ft_split(char const *s, char c);

/*ft_str.c*/
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *str, const char *to_find, size_t n);

/* ft_strcat.c */
char	*ft_strcat(char *dest, const char *src);

/*ft_strjoin.c*/
void	*ft_calloc(size_t nmemb, size_t size);
size_t	ft_strlcat(char *dst, char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(char	*src);
char	*ft_strjoin(const char *s1, const char *s2);

/*get_next_line.c*/
char	*ft_next_line(char *stash);
char	*ft_get_line(char *stash);
char	*ft_strjoin_and_free(char *s1, char *s2);
char	*ft_read_text(int fd, char *stash);
char	*get_next_line(int fd);

#endif
