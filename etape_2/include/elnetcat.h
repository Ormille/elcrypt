/*
** elcrypt.h for elcrypt in /home/terran_j/rendu/elcrypt/etape_1
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Fri Mar 20 21:06:36 2015 Julie Terranova
** Last update Sat Mar 21 20:46:20 2015 Julie Terranova
*/

#ifndef ELNETCAT_H_
# define ELNETCAT_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <inttypes.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>

#define BLOCK   (64)
#define BBLOCK  (BLOCK / 8)

typedef struct s_server
{
  char ip[100];
  int port;
  uint64_t key;
  int is_running;
} t_server;

typedef struct s_client
{
  char host[100];
  int port;
  uint64_t key;
  int is_running;
} t_client;

int     check_points(char *av);
void    fill_ip_port(t_server *server, char *av);
void    fill_host_port(t_client *client, char *av);
int	is_decimal(char *nb);
uint64_t construct_block(unsigned char *buf);
int    init_server(t_server server);
void    continue_server(int sd, t_server server);
int    init_client(t_client client);
void    fill_sock_struct(struct sockaddr_in *sin, int port);

#endif
