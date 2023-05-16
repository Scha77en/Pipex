SOURCE = ./src
OBJECTS = ./obj
INCLUDE = ./include
SOURCE_BONUS = ./bonus
OBJECTS_BONUS = ./obj_bonus

SRC =  pipex.c spliting.c joining.c command_handling.c

OBJ = ${addprefix ${OBJECTS}/, ${SRC:.c=.o}}

SRC_BONUS = pipex_bonus.c bonus_tools.c command_handling.c file_handling.c get_next_line.c \
		get_next_line_utils.c spliting.c joining.c bonus_weapons.c

OBJ_BONUS = ${addprefix ${OBJECTS_BONUS}/, ${SRC_BONUS:.c=.o}}

NAME = pipex

NAME_BONUS = pipex_bonus

CC = cc -g -fsanitize=address

FLAGS = -Wall -Wextra -Werror

RM = rm -rf

all : ${NAME}

bonus : ${NAME_BONUS}

${NAME} : ${OBJ}
	${CC} ${FLAGS} $^ -o ${NAME}

${OBJECTS}/%.o : ${SOURCE}/%.c ${INCLUDE}/pipex.h
	@mkdir -p ${dir $@}
	${CC} ${FLAGS} -c $< -o $@

${NAME_BONUS} : ${OBJ_BONUS}
	${CC} ${FLAGS} ${OBJ_BONUS} -o $@

${OBJECTS_BONUS}/%.o : ${SOURCE_BONUS}/%.c ${INCLUDE}/pipex_bonus.h
	@mkdir -p ${dir $@}
	${CC} ${FLAGS} -c $< -o $@

clean :
	${RM} ${OBJECTS} ${OBJECTS_BONUS}

fclean : clean
	${RM} ${NAME} ${NAME_BONUS}

re : fclean all

.PHONY : all clean fclean re