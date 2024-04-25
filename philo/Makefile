TARGET = philo
FLAGS = -Wall -Werror -Wextra
SRC = philo.c init.c util.c utils.c daily.c
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

