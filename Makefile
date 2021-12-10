# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llalba <llalba@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 16:05:23 by llalba            #+#    #+#              #
#    Updated: 2021/12/10 17:41:14 by llalba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
ADDONS			= -L/usr/include -lreadline -L$(PWD)/$(LIBFT_DIR) -lft
endif
ifeq ($(UNAME), Darwin)
ADDONS			=
endif

blue			= /bin/echo -e -n "\x1b[1m\x1b[34m$1\x1b[0m"
green			= /bin/echo -e -n "\x1b[1m\x1b[32m$1\x1b[0m"
filename		= /bin/echo -e -n "\x1b[30m\x1b[47m\x1b[1m$1\x1b[0m"

NAME			= minishell

CC				= gcc

FLAGS			= -Wall -Werror -Wextra

HEADERS_DIR		= ./include/

LIBFT_DIR		= ./libft/

SRC_DIR			= ./src/

OBJ_DIR			= ./obj/

SRC_LIST		= \
				get_next_line.c \
				minishell.c \
				input_check_1.c \
				input_check_2.c \
				env_to_list.c \
				convert_env_var.c \
				convert_env_special_cases.c \
				ft_cmd.c \
				ft_list_env.c \
				free.c \
				heredoc.c \
				heredoc_utils.c \
				cmd_parsing.c \
				cmd_split_check.c \
				list_to_env.c \
				execute.c \
				pwd.c \
				exit.c \
				cd.c \
				cd2.c \
				cdpath.c \
				echo.c \
				env.c \
				unset.c \
				export.c \
				utils.c \
				utils2.c \
				print_export.c \
				signals.c \
				quotes.c \
				multipipe/dup.c \
				multipipe/utils_multipipe.c \
				multipipe/close_fd.c \
				multipipe/init_pipe.c \
				multipipe/process.c \
				multipipe/multipipe.c

SRC				= $(SRC_LIST)

OBJ				= $(SRC:%.c=$(OBJ_DIR)%.o)

$(NAME):		$(OBJ)
				@echo "🏗  Compiling libft..."
				@make -C $(LIBFT_DIR) --no-print-directory
				@$(call green,"Source code compiled in ")
				@$(call filename,"$(OBJ_DIR)")
				@$(call green,". ✅")
				@/bin/echo -e "\n💫 Linking everything..."
				@$(CC) $(FLAGS) -I $(HEADERS_DIR) -o $(NAME) $(OBJ) $(ADDONS)
				@$(call green,"Executable ")
				@$(call filename,"'$(NAME)'")
				@$(call green," successfully created. ✅")
				@/bin/echo -e "\n\n🚀 You're ready to go. Enjoy the ride!"

$(OBJ):			| $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
				@echo "🏗  Compiling $<..."
				@$(CC) $(CC_FLAGS) -I $(HEADERS_DIR) -c $< -o $@

$(OBJ_DIR):
				@mkdir -p $(OBJ_DIR)multipipe

all:			$(NAME)


clean:
				@/bin/echo "💦 Cleaning..."
				@make clean -C $(LIBFT_DIR) --no-print-directory
				@rm -rf $(OBJ)
				@$(call green,"Directory cleaned. ✅")
				@echo

fclean:			clean
				@make fclean -C $(LIBFT_DIR) --no-print-directory
				@rm -f $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
