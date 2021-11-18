# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fmonbeig <fmonbeig@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 16:05:23 by llalba            #+#    #+#              #
#    Updated: 2021/11/18 17:44:08 by fmonbeig         ###   ########.fr        #
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
			$(SRC_PATH)input_check_1.c \
			$(SRC_PATH)input_check_2.c \
			$(SRC_PATH)input_check_3.c \
			$(SRC_PATH)env_to_list.c \
			$(SRC_PATH)convert_env_var.c \
			$(SRC_PATH)convert_env_special_cases.c \
			$(SRC_PATH)ft_cmd.c \
			$(SRC_PATH)ft_list_env.c \
			$(SRC_PATH)ft_pipe.c \
			$(SRC_PATH)free.c \
			$(SRC_PATH)parse_cmd.c \
			$(SRC_PATH)list_to_env.c \
			$(SRC_PATH)execute.c \
			#$(SRC_PATH)env.c \
			#$(SRC_PATH)error_var_name.c \
			#$(SRC_PATH)export.c \
			#$(SRC_PATH)print_export.c \
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
