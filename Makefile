# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulyssezyberaj <ulyssezyberaj@student.42    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/22 18:16:23 by ulyssezyber       #+#    #+#              #
#    Updated: 2025/04/23 02:21:15 by ulyssezyber      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC  	=   cc
RM 		=  	rm -f
CFLAGS  =   -Wall -Wextra -Werror -I. -MMD
NAME    =   pipex
BONUS	=	pipex_bonus
LIBFT 	= 	libft/libft.a

SRCS    =   srcs/pipex.c \
			srcs/utils.c \
			srcs/free.c \
			srcs/open_files.c \
			srcs/parsing.c \
			srcs/pipes.c \

BSRCS	=	bonus/pipex_bonus.c \
			bonus/utils_bonus.c \
			bonus/free_bonus.c \
			bonus/here_doc_bonus.c \
			bonus/open_files_bonus.c \
			bonus/parsing_bonus.c \
			bonus/pipes_bonus.c \

OBJS    =   $(SRCS:.c=.o)
BOBJS	=	$(BSRCS:.c=.o)

DEPS 	= 	$(SRCS:.c=.d)
BDEPS	=	$(BSRCS:.c=.d)

all: $(NAME)

bonus: $(BONUS)

-include ${DEPS} ${BDEPS}

${LIBFT}:
	make -C libft

${NAME}: ${LIBFT} ${OBJS}
	${CC} ${CFLAGS} $(OBJS) $(LIBFT) $(MLX_EX) -o $(NAME) -lm 

${BONUS}: ${LIBFT} ${BOBJS}
	${CC} ${CFLAGS} $(BOBJS) $(LIBFT) $(MLX_EX) -o $(BONUS) -lm 

clean:
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS) $(BOBJS)
	$(RM) $(DEPS) $(BDEPS)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re