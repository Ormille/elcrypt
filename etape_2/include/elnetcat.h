/*
** elcrypt.h for elcrypt in /home/terran_j/rendu/elcrypt/etape_1
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Fri Mar 20 21:06:36 2015 Julie Terranova
** Last update Sat Mar 21 19:54:11 2015 Julie Terranova
*/

#ifndef ELNETCAT_H_
# define ELNETCAT_H_

#include <inttypes.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BLOCK   (64)
#define BBLOCK  (BLOCK / 8)

typedef struct s_server
{
  char ip[100];
  int port;
  uint64_t key;
} t_server;

typedef struct s_client
{
  char host[100];
  int port;
  uint64_t key;
} t_client;

int     check_points(char *av);
void    fill_ip_port(t_server *server, char *av);
void    fill_host_port(t_client *client, char *av);
int	is_decimal(char *nb);
uint64_t construct_block(unsigned char *buf);
void    continue_server(t_server server);
void    continue_client(t_client client);

#endif
