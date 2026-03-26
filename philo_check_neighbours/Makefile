NAME = philo_check_neighbours

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP

SRC = philo.c \
      forks.c \
      helpers.c \
      error_handling.c \
      cleanup.c \
      routine.c \
      init.c \
      monitors.c

OBJ = ${SRC:.c=.o}

DEP = $(OBJ:.o=.d)

all: ${NAME}

${NAME}: ${OBJ}
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJ) -o $(NAME) -lpthread

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f ${OBJ} ${DEP}

fclean: clean
	rm -f ${NAME}

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re


