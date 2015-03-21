/*
** server.c for server in /home/terran_j/rendu/elcrypt/etape_2/src
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Sat Mar 21 19:47:59 2015 Julie Terranova
** Last update Sat Mar 21 19:48:40 2015 Julie Terranova
*/

#include "elnetcat.h"

void    continue_server(t_server server)
{
  printf("server ip: %s\n", server.ip);
  printf("server port: %d\n", server.port);
  printf("server key: %" PRIu64 "\n", server.key);
}
