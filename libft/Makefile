# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/09 11:59:29 by ulyssezyber       #+#    #+#              #
#    Updated: 2025/04/23 01:09:38 by ulyssezyber      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC := cc

CFLAGS := -Wall -Wextra -Werror

SRCS = ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_strdup.c \
	ft_calloc.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putnbr_fd.c \
	ft_strjoin.c \
	ft_putendl_fd.c \
	ft_substr.c \
	ft_striteri.c \
	ft_itoa.c \
	ft_strtrim.c \
	ft_strmapi.c \
	ft_split.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_free_double_tab.c \
	ft_printf.c \
	buffer.c \
	format_utils.c \
	parser.c \
	render_char.c \
	render_int.c \
	utils.c

OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re