/*
** main.c for elcrypt in /home/terran_j/rendu/elcrypt/etape_1
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Fri Mar 20 21:05:57 2015 Julie Terranova
** Last update Sat Mar 21 21:58:17 2015 moran-_d
*/

#include "elnetcat.h"

uint64_t recup_key(char *av)
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

int	server(char **av)
{
  t_server server;
  int mask;
  int i;

  i = (mask = 0);
  while (av[i])
    {
      if (strcmp("-k", av[i]) == 0 && i < 4)
	{
	  server.key = recup_key(av[i + 1]);
	  if ((mask & 1) == 0)
	    mask += 1;
	}
      if (check_points(av[i]) == 0)
	{
	  fill_ip_port(&server, av[i]);
	  if ((mask & 2) == 0)
	    mask += 2;
	}
      i++;
    }
  if (mask != 3)
    return (printf("Server: Syntax error\n"));
  init_server(&server);
  return (0);
}

int	client(char **av)
{
  t_client client;
  int mask;
  int i;

  i = (mask = 0);
  while (av[i])
    {
      if (strcmp("-k", av[i]) == 0 && i < 4)
	{
	  client.key = recup_key(av[i + 1]);
	  if ((mask & 1) == 0)
            mask += 1;
	}
      if (check_points(av[i]) == 0)
	{
	  fill_host_port(&client, av[i]);
	  if ((mask & 2) == 0)
            mask += 2;
	}
      i++;
    }
  if (mask != 3)
    return (printf("Client: Syntax error\n"));
  init_client(&client);
  return (0);
}

void	verify_arg(char **av)
{
  int i;
  int arg;

  i = -1;
  arg = 0;
  while (av[++i])
    {
      if (strcmp("-c", av[i]) == 0)
        {
	  client(av);
          arg += 1;
          return;
        }
      if (strcmp("-l", av[i]) == 0)
        {
	  server(av);
          arg += 1;
          return;
        }
    }
  if (arg == 0)
    printf("Error: Missing -c or -l\n");
}

int	main(int ac, char **av)
{
  if (ac == 5)
    verify_arg(av);
  else
    printf("Client usage: ./elnetcat -c host:port -k key\n%s\n",
	   "Server usage: ./elnetcat -l ip:port -k key");
  return (0);
}
