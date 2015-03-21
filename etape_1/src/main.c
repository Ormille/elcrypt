/*
** main.c for elcrypt in /home/terran_j/rendu/elcrypt/etape_1
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Fri Mar 20 21:05:57 2015 Julie Terranova
** Last update Sat Mar 21 13:34:28 2015 moran-_d
*/

#include <inttypes.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "elcrypt.h"

uint64_t get_key(char *av)
{
  uint64_t ret;

  sscanf(av, "%" SCNu64, &ret);

  return (ret);
}

int	in_loop(char **av, elc *opt, char **src, char **dest)
{
  int i;
  int mk;

  i = (mk = 0) - 1;
  while (av[++i] && i != 8)
    {
      if ((mk & 1) == 0 && strcmp("-f", av[i]) == 0 && (mk += 1) >= 0)
	*src = av[i + 1];
      else if ((mk & 1) == 1 && strcmp("-f", av[i]) == 0)
	return (printf("-f already declared\n"));
      if ((mk & 2) == 0 && strcmp("-o", av[i]) == 0 && (mk += 2) >= 0)
	*dest = av[i + 1];
      else if ((mk & 2) == 1 && strcmp("-o", av[i]) == 0)
	return (printf("-o already declared\n"));
      if ((mk & 4) == 0 && strcmp("-k", av[i]) == 0 && (mk += 4) >= 0)
	{
	  opt->key = get_key(av[i + 1]);
	  opt->skey = parity_bits_key(opt->key);
	}
      else if ((mk & 4) == 1 && strcmp("-k", av[i]) == 0)
	return (printf("-k already declared\n"));
    }
  if (mk != 7)
    return (printf("Wrong argument\n"));
  return (0);
}

int	crypt(char **av, elc *opt)
{
  char *src;
  char *dest;

  if (in_loop(av, opt, &src, &dest) != 0)
    return (-1);
  if ((opt->fin = open(src, O_RDONLY)) == -1)
    return (printf("Error with source file\n"));
  if ((opt->fout = open(dest, O_CREAT | O_EXCL | O_RDWR, 0644))
      == -1)
    return (printf("Error with destination file\n"));
  elcrypt(opt, opt->mode);
  return (0);
}

void	verify_arguments(char **av)
{
  int i;
  int arg;
  elc opt;

  i = -1;
  arg = 0;
  while (av[++i])
    {
      if (strcmp("-d", av[i]) == 0)
	{
	  opt.mode = DECRYPT;
	  crypt(av, &opt);
	  arg += 1;
	  return;
	}
      if (strcmp("-e", av[i]) == 0)
	{
	  opt.mode = ENCRYPT;
	  crypt(av, &opt);
	  arg += 1;
	  return;
	}
    }
  if (arg == 0)
    printf("Error: Missing -d or -e\n");
}

int	main(int ac, char **av)
{
  if (ac == 8)
    verify_arguments(av);
  else
    printf("Usage: ./elcrypt [-d | -e] [-f src_file] [-o dest_file] %s\n",
	   "[-k key]");
  return (0);
}
