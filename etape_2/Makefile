##
## Makefile for elcrypt in /home/terran_j/rendu/elcrypt
##
## Made by Julie Terranova
## Login   <terran_j@epitech.net>
##
## Started on  Fri Mar 20 20:46:16 2015 Julie Terranova
## Last update Sat Mar 21 22:00:46 2015 moran-_d
##

NAME	= elnetcat

SRC	= src/main.c \
	src/parsing.c \
	src/block.c \
	src/elcrypt.c \
	src/server.c \
	src/client.c \

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -ansi -pedantic -I include/

LDFLAGS= -lX11 -lm

all:    $(NAME)

$(NAME):$(OBJ)
	cc -o $(NAME) $(LDFLAGS) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all

.PHONY: all clean fclean re
