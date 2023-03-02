# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbouchon <lbouchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/20 11:25:51 by lbouchon          #+#    #+#              #
#    Updated: 2023/03/02 12:00:37 by lbouchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc -pthread
RM = rm -rf
DIR = srcs/
CFLAGS = -Wall -Wextra -Werror
NORMINETTE = norminette

SRCS = $(DIR)main.c			\
		$(DIR)ft_utils.c	\
		$(DIR)time.c		\

OBJS = ${SRCS:.c=.o}

all	: ${NAME}

${NAME} : ${OBJS}
		@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
		@echo "\033[0;42mPhilo is now compile !\033[0m"

clean :
		$(RM) $(OBJS)

fclean : clean
	${RM} ${NAME}

re : fclean all

%.o: %.c
		@echo "\033[1;33mCompiling philo...\033[0m"
		${CC} ${FLAGS} -o $@ -c $<

norm :
		${NORMINETTE}

.PHONY: all clean fclean re norm