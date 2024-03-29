CC=gcc
FLAGS= -Wall
NAME=xbrightness
SRC=xbrightness.c

OBJ=$(SRC:.c=.o)

HEADER=xbrightness.h

install: all
	cp $(NAME) /usr/local/bin/
	@make clean

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) -o $(NAME) $(FLAGS) $(OBJ)

%.o: %.c
	$(CC) -o $@ $(FLAGS) -c $<

clean:
	rm -f *.o
	rm -f */*.o

fclean: clean
	rm -f $(NAME)
