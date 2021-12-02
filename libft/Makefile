# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llalba <llalba@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/21 11:04:04 by fmonbeig          #+#    #+#              #
#    Updated: 2021/12/02 21:25:07 by llalba           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

blue			= /bin/echo -e -n "\x1b[1m\x1b[34m$1\x1b[0m"
green			= /bin/echo -e -n "\x1b[1m\x1b[32m$1\x1b[0m"
filename		= /bin/echo -e -n "\x1b[30m\x1b[47m\x1b[1m$1\x1b[0m"

NAME			= libft.a

CC				= gcc

CFLAG			= -Wall -Wextra -Werror

SRC				= ft_strlen.c \
				ft_swap.c \
				ft_sort_int_tab.c \
				ft_bzero.c \
				ft_memcpy.c\
				ft_memccpy.c\
				ft_memmove.c\
				ft_memchr.c \
				ft_memcmp.c \
				ft_strlen.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_memset.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strcmp.c \
				ft_strncmp.c \
				ft_strlcpy.c \
				ft_strlcat.c \
				ft_strnstr.c \
				ft_atoi.c \
				ft_calloc.c \
				ft_strdup.c \
				ft_substr.c \
				ft_strtrim.c \
				ft_strjoin.c \
				ft_split.c \
				ft_itoa.c \
				ft_strmapi.c \
				ft_putchar_fd.c \
				ft_putstr_fd.c \
				ft_putstr.c \
				ft_putstr_limited.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putnbr.c \
				ft_putchar.c  \
				ft_countnbr.c \
				ft_putnbr_no_minus.c \
				ft_putnbr_base.c \
				ft_putnbr_base_pointer.c \
				ft_countnbr_base.c \
				ft_putnbr_unsigned_int.c \
				ft_countnbr_unsigned_int.c \
				ft_countnbr_base_pointer.c \
				ft_str_insert.c \
				ft_free_split.c \
				ft_split_n_join.c \
				ft_strlen_split.c

OBJ				= $(SRC:.c=.o)

$(NAME):		$(OBJ)
				@ar cr $(NAME) $(OBJ)
				@ranlib $(NAME)

all:			$(NAME)

%.o: %.c
				@$(CC) $(CFLAG) -I includes -o $@ -c $<

clean:
				@rm -f $(OBJ) $(OBJ_BONUS)

fclean:			clean
				@rm -f $(NAME)

re:				fclean all

.PHONY: all clean fclean re
