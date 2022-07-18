##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## M
##

SRC = $(wildcard ./src/*.cpp ./src/Classes/*.cpp)

OBJECTS := $(filter %.o,$(SRC:.c=.o))
OBJECTS += $(filter %.o,$(SRC:.cpp=.o))

CFLAGS  = -w

NAME	=	doom.exe

all:	$(NAME)

%.o: %.c
	g++ -g $(CFLAGS) -c $< -o $@

%.o: %.cpp
	g++ -g $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	g++ -g $(CFLAGS) $^ -lsfml-graphics -lsfml-window -lsfml-system -o $@ 

clean:
	rm -f $(OBJECTS)

fclean:	clean
	rm -f $(NAME)

re: all
	rm -f $(OBJECTS) 

.PHONY: all clean fclean re