# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llalba <llalba@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 16:05:23 by llalba            #+#    #+#              #
#    Updated: 2021/10/11 18:55:16 by llalba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME := $(shell uname)

LIBFT_DIR	= libft

ifeq ($(UNAME), Linux)
ADDONS		= -L/usr/include -lreadline -L$(PWD)/$(LIBFT_DIR) -lft
endif
ifeq ($(UNAME), Darwin)
ADDONS		=
endif

NAME		= minishell

CC			= gcc

FLAGS		= -Wall -Werror -Wextra

HEADERS		= include/

SRC_PATH	= src/

SRC			= \
			$(SRC_PATH)minishell.c \
			$(SRC_PATH)env_to_list.c \
			$(SRC_PATH)list_to_env.c \
			$(SRC_PATH)parsing.c
			$(SRC_PATH)builtins.c \

OBJS		= $(SRC:.c=.o)

$(NAME):	$(OBJS)
			make -C $(LIBFT_DIR)
			$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(ADDONS)

all:		$(NAME)

clean:
			make clean -C $(LIBFT_DIR)
			@rm -rf $(OBJS)

fclean:		clean
			make fclean -C $(LIBFT_DIR)
			@rm -f $(CLIENT_NAME)

re:			fclean all

.PHONY:		all clean fclean re
