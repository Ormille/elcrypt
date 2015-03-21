/*
** client.c for client in /home/terran_j/rendu/elcrypt/etape_2/src
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Sat Mar 21 19:48:53 2015 Julie Terranova
** Last update Sun Mar 22 00:19:55 2015 moran-_d
*/

#include "elnetcat.h"

void	continue_client(t_client *client, int sd)
{
  char buf[4096];
  elc elc;
  int len;

  elc.mode = ENCRYPT;
  elc.skey = parity_bits_key(client->key);
  elc.fin = 0;
  elc.fout = sd;
  client->is_running = 1;
  while (client->is_running == 1)
    {
      if ((len = read(elc.fin, buf, 4096)) > 0)
        {
          if (encrypt(&elc, buf, elc.mode, len) < 0)
            return;
        }
    }
}

int    init_client(t_client *client)
{
  int   sd;
  struct sockaddr_in sin;
  struct protoent *pe;

  pe = getprotobyname("TCP");
  if ((sd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (printf("Socket error\n"));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(client->port);
  sin.sin_addr.s_addr = inet_addr(client->host);
  if ((connect(sd, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
    {
      close(sd);
      return (printf("Error while connecting\n"));
    }
  continue_client(client, sd);
  close(sd);
  return (0);
}
