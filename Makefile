##
## Makefile for myftp in /home/terran_j/rendu/PSU_2014_myftp
##
## Made by Julie Terranova
## Login   <terran_j@epitech.net>
##
## Started on  Mon Mar  9 15:02:17 2015 Julie Terranova
## Last update Fri Mar 20 20:38:25 2015 Julie Terranova
##

NAME1	= serveur

NAME2	= client

SRC1	= server/src/main.c \

SRC2	= clients/src/main.c \

OBJ1=   $(SRC1:.c=.o)

OBJ2=   $(SRC2:.c=.o)

CFLAGS= -Wall -Wextra -Werror -ansi -pedantic -I server/include/ -I clients/include/

LDFLAGS1= -lX11

LDFLAGS2= -lX11

all:    $(NAME1) $(NAME2)

$(NAME1):$(OBJ1)
	cc -o $(NAME1) $(LDFLAGS1) $(OBJ1)

$(NAME2):$(OBJ2)
	cc -o $(NAME2) $(LDFLAGS2) $(OBJ2)

clean:
	rm -f $(OBJ1) rm -f $(OBJ2)

fclean: clean
	rm -f $(NAME1) rm -f $(NAME2)

re:     fclean all

.PHONY: all clean fclean re
