#Makefile

CFLAGS += -W
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -ansi
CFLAGS += -pedantic
CFLAGS += -Wno-unused-parameter

NAME		= swim_mill

SRC		= main.c \
		../common/utils.c \
		game_loop.c

OBJ		= $(SRC:.c=.o)

$(NAME): $(OBJ)
	gcc -o $(NAME) $(OBJ)
	mv $(NAME) ..

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ../$(NAME)

re: fclean all
