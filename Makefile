# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llalba <llalba@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 16:05:23 by llalba            #+#    #+#              #
#    Updated: 2021/11/09 16:40:15 by llalba           ###   ########.fr        #
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
			$(SRC_PATH)ft_lstadd_back_cmd.c \
			$(SRC_PATH)ft_lstadd_front_cmd.c \
			$(SRC_PATH)ft_lstclear_cmd.c \
			$(SRC_PATH)ft_lstlast_cmd.c \
			$(SRC_PATH)ft_lstnew_cmd.c \
			$(SRC_PATH)ft_lstsize_cmd.c \
			$(SRC_PATH)minishell.c \
			$(SRC_PATH)env_to_list.c \
			$(SRC_PATH)list_to_env.c \
			$(SRC_PATH)preliminary_checks.c \
			$(SRC_PATH)secondary_checks.c \
			$(SRC_PATH)convert_env_var.c \
			$(SRC_PATH)convert_env_special_cases.c \
			$(SRC_PATH)s_cmd_list.c \
			#$(SRC_PATH)export.c \
			#$(SRC_PATH)unset.c \
			#$(SRC_PATH)builtins.c \
			#$(SRC_PATH)multipipe/init_pipe.c \
			#$(SRC_PATH)multipipe/multipipe.c \
			#$(SRC_PATH)multipipe/utils_multipipe.c

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
