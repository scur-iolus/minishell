# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llalba <llalba@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 16:05:23 by llalba            #+#    #+#              #
#    Updated: 2021/10/07 18:27:57 by llalba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= gcc

FLAGS		= -Wall -Werror -Wextra

HEADERS		= include/

SRC_PATH	= src/

SRC			= \
			$(SRC_PATH)minishell.c \
			$(SRC_PATH)env.c \
			$(SRC_PATH)parsing.c

OBJS		= $(SRC:.c=.o)

$(NAME):	$(OBJS)
			make -C libft
			$(CC) $(FLAGS) -o $(NAME) $(OBJS)

all:		$(NAME)

clean:
			make clean -C libft
			@rm -rf $(OBJS)

fclean:		clean
			make fclean -C libft
			@rm -f $(CLIENT_NAME)

re:			fclean all

.PHONY:		all clean fclean re