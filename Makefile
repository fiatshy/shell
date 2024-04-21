TARGET = philo
FLAGS = -Wall -Werror -Wextra
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re

all: $(TARGET)

%.o: %.c
	gcc -c $(FLAGS) $< 

$(TARGET): 
	make -C mandatory/
	mv mandatory/philo philo

bonus: 
	make -C bonuses/
	mv bonuses/philo_bonus philo_bonus
	touch $@

clean:
	rm -f $(OBJ) bonus
	make -C mandatory clean
	make -C bonuses clean

fclean: clean
	rm -f $(TARGET) philo_bonus
	make -C mandatory fclean
	make -C bonuses fclean

re: fclean all

