# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 22:50:02 by aouhbi            #+#    #+#              #
#    Updated: 2023/04/25 16:17:22 by aouhbi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main_program.c tools.c tools2.c

OBJ = ${SRC:.c=.o}

CC = cc

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

NAME = pipex

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${FLAGS} ${OBJ} -o ${NAME}

%.o : %.c pipex.h
	${CC} ${FLAGS} -c $< -o $@

clean :
	${RM} ${OBJ}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY : all clean fclean re