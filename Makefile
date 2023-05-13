# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouhbi <aouhbi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 22:50:02 by aouhbi            #+#    #+#              #
#    Updated: 2023/05/13 15:22:16 by aouhbi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = pipex.c spliting.c joining.c command_handling.c

B_SRC = pipex_bonus.c bonus_tools.c command_handling.c file_handling.c get_next_line.c \
		get_next_line_utils.c spliting.c joining.c bonus_weapons.c

OBJ = ${SRC:.c=.o}

B_OBJ = ${B_SRC:.c=.o}

CC = cc

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

NAME = pipex

BONUS = pipex_bonus

all : ${NAME}

${NAME} : ${OBJ}
	${CC} ${FLAGS} ${OBJ} -o ${NAME}

${BONUS} : ${B_OBJ}
	${CC} ${FLAGS} ${B_OBJ} -o $@

%.o : %.c pipex.h
	${CC} ${FLAGS} -c $< -o $@

%.o : %.c pipex_bonus.h
	${CC} ${FLAGS} -c $< -o $@

clean :
	${RM} ${OBJ} ${B_OBJ}

fclean : clean
	${RM} ${NAME} ${BONUS}

re : fclean all

.PHONY : all clean fclean re