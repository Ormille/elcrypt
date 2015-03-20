/*
** main.c for elcrypt in /home/terran_j/rendu/elcrypt/etape_1
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Fri Mar 20 21:05:57 2015 Julie Terranova
** Last update Fri Mar 20 22:22:30 2015 Julie Terranova
*/

#include <stdio.h>
#include <string.h>
#include "elcrypt.h"

int	crypt(char **av, elc opt)
{
  int mask;
  int i;

  i = (mask = 0);
  while (av[i] && i != 9)
    {
      if ((mask & 1) == 0 && strcmp("-f", av[i]) == 0)
	{
	  if ((opt.fin = open(av[i + 1], O_RDONLY)) == -1)
	    return (printf("Error with source file\n"));
	  mask = mask & 1;
	}
      else if ((mask & 1) == 1)
	return (printf("-f already declared\n"));
      if ((mask & 2) == 0 && strcmp("-o", av[i]) == 0)
	{
	  if ((opt.fout = open(av[i + 1], O_CREAT | O_EXCL | O_RDWR, 0644))
	      == -1)
	    return (printf("Error with destination file\n"));
	  mask = mask & 2;
	}
      else if ((mask & 2) == 1)
	return (printf("-o already declared\n"));
      if ((mask & 4) == 0 && strcmp("-k", av[i]) == 0)
	{
	  opt.key = strtoll(av[i + 1], NULL, 10);
	  mask = mask & 4;
	}
      else if ((mask & 4) == 1)
	return (printf("-k already declared\n"));
      i++;
    }
  return (0);
}

void	verify_arguments(char **av)
{
  int i;
  elc opt;

  i = 0;
  while (av[i])
    {
      if (strcmp("-d", av[i]) == 0)
	{
	  opt.mode = DECRYPT;
	  crypt(av, opt);
	  break;
	}
      if (strcmp("-e", av[i]) == 0)
	{
	  opt.mode = ENCRYPT;
	  crypt(av, opt);
	  break;
	}
      i++;
    }
}

int	main(int ac, char **av)
{
  if (ac == 9)
    verify_arguments(av);
  else
    printf("Usage: ./elcrypt [-d | -e] [-f src_file] [-o dest_file] [-k key]\n");
  return (0);
}
