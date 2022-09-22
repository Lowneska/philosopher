SRC =	srcs/main.c \
		srcs/parsing.c\
		srcs/initialisation.c\
		srcs/display.c\
		srcs/philosophers.c\
		srcs/routine.c\
		srcs/waiter.c\

OBJS =	objs/main.o \
		objs/parsing.o\
		objs/initialisation.o\
		objs/display.o\
		objs/philosophers.o\
		objs/routine.o\
		objs/waiter.o\

NAME = philo

CC = gcc

INC = include/

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra  -pthread -fsanitize=thread

all : ${NAME}

bonus : ${NAME_BONUS}

objs/%.o : srcs/%.c
	mkdir -p ./objs
	$(CC) $(CFLAGS) -I${INC} -c $< -o $@

%.o : %.c
	$(CC) $(CFLAGS) -I${INC} -c $< -o $@

${NAME} : ${OBJS}
	$(CC) $(CFLAGS) ${OBJS} -o ${NAME}

clean:
		$(RM) ${OBJS}
		$(RM) ./objs

fclean: clean
		$(RM) $(NAME)

re:	fclean all