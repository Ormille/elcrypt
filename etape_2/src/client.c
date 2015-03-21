/*
** client.c for client in /home/terran_j/rendu/elcrypt/etape_2/src
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Sat Mar 21 19:48:53 2015 Julie Terranova
** Last update Sat Mar 21 19:49:14 2015 Julie Terranova
*/

#include "elnetcat.h"

void    continue_client(t_client client)
{
  printf("client host: %s\n", client.host);
  printf("client port: %d\n", client.port);
  printf("client key: %" PRIu64 "\n", client.key);
}
