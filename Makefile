# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llalba <llalba@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/24 16:05:23 by llalba            #+#    #+#              #
#    Updated: 2021/10/07 14:29:22 by llalba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minitalk

SERVER_NAME	= server

CLIENT_NAME	= client

CC			= gcc

FLAGS		= -Wall -Werror -Wextra

SRCS_PATH	= srcs/

CLIENT_SRC	= \
			$(SRCS_PATH)client.c \
			$(SRCS_PATH)utils.c

CLIENT_BNS	= \
			$(SRCS_PATH)client_bonus.c \
			$(SRCS_PATH)utils_bonus.c

SERVER_SRC	= \
			$(SRCS_PATH)server.c \
			$(SRCS_PATH)utils.c

SERVER_BNS	= \
			$(SRCS_PATH)server_bonus.c \
			$(SRCS_PATH)utils_bonus.c

OBJS		= $(SERVER_SRC:.c=.o) $(CLIENT_SRC:.c=.o)

BONUS_OBJS	= $(SERVER_BNS:.c=.o) $(CLIENT_BNS:.c=.o)

$(NAME):	$(OBJS)
			$(CC) $(FLAGS) -o $(CLIENT_NAME) $(CLIENT_SRC:.c=.o)
			$(CC) $(FLAGS) -o $(SERVER_NAME) $(SERVER_SRC:.c=.o)

bonus:		$(BONUS_OBJS)
			$(CC) $(FLAGS) -o $(CLIENT_NAME) $(CLIENT_BNS:.c=.o)
			$(CC) $(FLAGS) -o $(SERVER_NAME) $(SERVER_BNS:.c=.o)

all:		$(NAME)

clean:
			@rm -rf $(OBJS)
			@rm -rf $(BONUS_OBJS)

fclean:		clean
			@rm -f $(CLIENT_NAME)
			@rm -f $(SERVER_NAME)

re:			fclean all

.PHONY:		all clean fclean re