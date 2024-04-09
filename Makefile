# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpeyre <gpeyre@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 14:40:12 by gdetourn          #+#    #+#              #
#    Updated: 2024/03/13 16:32:35 by gpeyre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME	= minishell

# Compiler options
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -g #-fsanitize=address

# Libft
LIBFT_PATH = ./libft/
LIBFT_LIB = $(LIBFT_PATH)libft.a

# Minishell files
SRC_PATH = ./srcs/

SRCS		=	./srcs/builtins.c \
				./srcs/clean_prompt.c \
				./srcs/dollar_bis.c \
				./srcs/dollar.c \
				./srcs/env.c \
				./srcs/error_2.c \
				./srcs/error.c \
				./srcs/execution.c \
				./srcs/export_01.c \
				./srcs/export_02.c \
				./srcs/lst_extract_cmds.c \
				./srcs/extract_cmds.c \
				./srcs/ft_split_echo.c \
				./srcs/ft_split_export.c \
				./srcs/ft_split_prompt.c \
				./srcs/ft_split_qt.c \
				./srcs/ft_split_utils_2.c \
				./srcs/ft_split_utils.c \
				./srcs/init_exit.c \
				./srcs/minishell.c \
				./srcs/msh_utils.c \
				./srcs/open_file_2.c \
				./srcs/open_file.c \
				./srcs/pipe.c \
				./srcs/signals.c

#SRC			=	$(addprefix srcs/, ${SRCS})

OBJ			= $(SRCS:.c=.o)
#OBJ_PATH	= ./objs/
#OBJ			= $(addprefix objs/, $(SRCS:.c=.o))

# Includes
INCLUDES = 	-I ./includes/\
			-I ./libft/\

# Colors
RESET = \033[0m
BOLD = \033[1m
RED = \033[91m
GREEN = \033[92m
YELLOW = \033[33m
ORANGE = \033[93m
BLUE = \033[94m

all : $(LIBFT_LIB) $(NAME)

# Compiling Libft
#${OBJ}: ${SRC}
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(LIBFT_LIB):	
	@echo "$(BOLD)$(RED)🛠️ 🚧      Compiling Libft     🚧🛠️$(RESET)"
	@echo "\n"	
	@make -sC $(LIBFT_PATH)
	@echo "\n"
	@echo "$(BOLD)$(GREEN)🎆     Libft Compiled    🎆$(RESET)"
	@echo "\n"
	@echo "$(BOLD)$(BLUE)-----------------------$(RESET)"
	@echo "\n"

# Compiling Minishell
$(NAME): $(OBJ)
	@echo "$(BOLD)$(RED)🛠️ 🚧      Compiling Minishell      🚧🛠️$(RESET)"
	@echo "\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) -lreadline
	@echo "$(BOLD)$(GREEN)⌨️ 🖥 🖱 💾    Minishell ready to use    💾🖱 🖥 ⌨️$(RESET)"
	@echo "\n"

clean:
	@make clean -sC $(LIBFT_PATH)
	@rm -rf $(OBJ)
	@echo "$(BOLD)$(ORANGE)🧹🧼     Cleaned .o Libft's files   🧼🧹$(RESET)"
	@echo "$(BOLD)$(ORANGE)🧹🧼     Cleaned .o Minishell's files  🧼🧹$(RESET)"

fclean: clean
#	@make fclean -sC 
	@rm -rf $(LIBFT_LIB) $(NAME)
	@echo "$(BOLD)$(ORANGE)🧹🧼    Cleaned libs and Minishell exec    🧼🧹$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
