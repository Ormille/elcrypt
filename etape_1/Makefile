##
## Makefile for elcrypt in /home/terran_j/rendu/elcrypt
##
## Made by Julie Terranova
## Login   <terran_j@epitech.net>
##
## Started on  Fri Mar 20 20:46:16 2015 Julie Terranova
## Last update Fri Mar 20 21:07:16 2015 Julie Terranova
##

NAME	= elcrypt

SRC	= src/main.c \

OBJ	= $(SRC:.c=.o)

CFLAGS	= -Wall -Wextra -Werror -ansi -pedantic -I include/

LDFLAGS= -lX11

all:    $(NAME)

$(NAME):$(OBJ)
	cc -o $(NAME) $(LDFLAGS) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:     fclean all

.PHONY: all clean fclean re
