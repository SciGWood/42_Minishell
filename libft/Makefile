# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/18 14:10:42 by gdetourn          #+#    #+#              #
#    Updated: 2024/02/27 10:31:28 by gpeyre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CFLAGS	= -Wall -Wextra -Werror
CC		= cc

SRC		= 	ft_atoi_itoa.c \
			ft_split.c \
			ft_str.c\
			ft_strcat.c \
			ft_strjoin.c \
			get_next_line.c \

OBJ		= $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
		ar rc $@ $^

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ)

fclean: clean
		rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re