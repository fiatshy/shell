TARGET = philo_bonus
FLAGS = -Wall -Werror -Wextra
SRC = philo_bonus.c init_bonus.c routine_bonus.c util_bonus.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(TARGET)

%.o: %.c
	gcc -c $< 

$(TARGET): $(OBJ)
	gcc $(OBJ) -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

