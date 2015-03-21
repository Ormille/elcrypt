/*
** server.c for server in /home/terran_j/rendu/elcrypt/etape_2/src
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Sat Mar 21 19:47:59 2015 Julie Terranova
** Last update Sun Mar 22 00:25:36 2015 moran-_d
*/

#include "elnetcat.h"

int	read_on_term(t_server *server, int cd)
{
  char buf[4096];
  elc elc;
  int len;

  elc.mode = DECRYPT;
  elc.skey = parity_bits_key(server->key);
  elc.fin = cd;
  elc.fout = 1;
  while (server->is_running == 1)
    {
      memset(buf, 0, 4096);
      if ((len = read(elc.fin, buf, 4096)) > 0)
	{
	  if (len % 8 != 0)
	    printf("Not a good one, skipping.\n");
	  else if (decrypt(&elc, buf, elc.mode, (int)len / 8) < 0)
	    return (-1);
	}
      else if (len <= 0)
	return (-1);
    }
  return (0);
}

void	continue_server(int sd, t_server *server)
{
  struct sockaddr_in sin_client;
  int client_len;
  int cd;

  server->is_running = 1;
  while (server->is_running == 1)
    {
      client_len = sizeof(sin_client);
      if ((cd = accept(sd, (struct sockaddr *)&sin_client, (socklen_t *)
                       &client_len)) == -1)
        {
          close (sd);
          return;
        }
      if (read_on_term(server, cd) < 0)
	{
	  close(cd);
	  return;
	}
    }
  close(cd);
}

int    init_server(t_server *server)
{
  int   sd;
  struct sockaddr_in sin;
  struct protoent *pe;

  pe = getprotobyname("TCP");
  if ((sd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (printf("Socket error\n"));
  fill_sock_struct(&sin, server->port);
  if ((bind(sd, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
    {
      close(sd);
      return (printf("Error while binding\n"));
    }
  if ((listen(sd, 42)) == -1)
    {
      close (sd);
      return (printf("Error while listening\n"));
    }
  continue_server(sd, server);
  close(sd);
  return (0);
}

void    fill_sock_struct(struct sockaddr_in *sin, int port)
{
  sin->sin_family = AF_INET;
  sin->sin_port = htons(port);
  sin->sin_addr.s_addr = INADDR_ANY;
}
