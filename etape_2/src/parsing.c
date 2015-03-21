/*
** parsing.c for parsing in /home/terran_j/rendu/elcrypt/etape_2/src
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Sat Mar 21 19:50:17 2015 Julie Terranova
** Last update Sat Mar 21 19:51:39 2015 Julie Terranova
*/

#include "elnetcat.h"

int     check_points(char *av)
{
  int i;

  i = 0;
  while (av[i])
    {
      if (av[i] == ':')
	return (0);
      i++;
    }
  return (-1);
}

void    fill_ip_port(t_server *server, char *av)
{
  size_t i;
  int bool;

  i = 0;
  bool = 0;
  while (av[i])
    {
      if (av[i] != ':' && bool == 0)
        server->ip[i] = av[i];
      if (av[i] == ':' && strlen(av) > i)
        {
          server->ip[i] = '\0';
          av += i + 1;
          bool = 1;
        }
      if (bool == 1)
        server->port = atoi(av);
      i++;
    }
}

void    fill_host_port(t_client *client, char *av)
{
  size_t i;
  int bool;

  i = 0;
  bool = 0;
  while (av[i])
    {
      if (av[i] != ':' && bool == 0)
        client->host[i] = av[i];
      if (av[i] == ':' && strlen(av) > i)
        {
          client->host[i] = '\0';
          av += i + 1;
          bool = 1;
        }
      if (bool == 1)
        client->port = atoi(av);
      i++;
    }
}

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

uint64_t construct_block(unsigned char *buf)
{
  uint64_t block;
  int i;

  block = 0;
  i = -1;
  while (++i < BBLOCK)
    block = (block << 8) + buf[i];
  return (block);
}
