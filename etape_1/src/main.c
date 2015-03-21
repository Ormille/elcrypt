/*
** main.c for elcrypt in /home/terran_j/rendu/elcrypt/etape_1
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Fri Mar 20 21:05:57 2015 Julie Terranova
** Last update Sat Mar 21 17:14:01 2015 Julie Terranova
*/

#include <inttypes.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "elcrypt.h"

int is_decimal(char *nb)
{
  int i;

  i = 0;
  while (nb[i])
    {
      if (!(nb[i] >= '0' && nb[i] <= '9'))
	return (-1);
      i++;
    }
  return (0);
}

uint64_t get_key(char *av)
{
  uint64_t ret;
  size_t i;

  ret = 0;
  if (strlen(av) >= 2 && av[0] == '0' && av[1] == 'x')
    sscanf(av, "%lx", &ret);
  else if (strlen(av) >= 1 && av[0] == '%')
    {
      av += 2;
      i = 0;
      while (i < strlen(av))
	{
	  if (av[i] == '1')
	    ret = ret * 2 + 1;
	  else if (av[i] == '0')
	    ret *= 2;
	  i++;
	}
    }
  else if (is_decimal(av) == 0)
    sscanf(av, "%" SCNu64, &ret);
  else
    ret = construct_block((unsigned char *)av);
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
