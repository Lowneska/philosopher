SRC =	srcs/main.c \
		srcs/parsing.c\
		srcs/initialisation.c\
		srcs/display.c\
		srcs/philosophers.c\
		srcs/routine.c\

SRC_B =	

OBJS_B =

OBJS =	objs/main.o \
		objs/parsing.o\
		objs/initialisation.o\
		objs/display.o\
		objs/philosophers.o\
		objs/routine.o\
	

NAME = philo

NAME_BONUS = philo_bonus

CC = gcc

INC = include/

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra

all : ${NAME}

bonus : ${NAME_BONUS}

objs/%.o : srcs/%.c
	mkdir -p ./objs
	$(CC) $(CFLAGS) -I${INC} -c $< -o $@

objs_bonus/%.o : src_bonus/%.c
	mkdir -p ./objs_bonus
	$(CC) $(CFLAGS) -I${INC} -c $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -I${INC} -c $< -o $@

${NAME} : ${OBJS}
	$(CC) $(CFLAGS) ${OBJS} -o ${NAME}

${NAME_BONUS} : ${OBJS_B}
	$(CC) $(CFLAGS) ${OBJS_B}-o ${NAME_BONUS}
clean:
		$(RM) ${OBJS} $(OBJ_B)
		$(RM) ./objs

fclean: clean
		$(RM) $(NAME) $(NAME_BONUS)

re:	fclean all