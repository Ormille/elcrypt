/*
** client.c for client in /home/terran_j/rendu/elcrypt/etape_2/src
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Sat Mar 21 19:48:53 2015 Julie Terranova
** Last update Sat Mar 21 21:08:24 2015 Julie Terranova
*/

#include "elnetcat.h"

void	continue_client(t_client client, int sd)
{
  char str[4096];

  client.is_running = 1;
  while (client.is_running == 1)
    {
      write(0, "Client_prompt_>>> ", strlen("Client_prompt_>>> "));
      memset(str, 0, 4096);
      if ((read(sd, str, 4095)) > 0)
	{
	  /* diego_func(&client); */
	  client = client;
	  printf("%s\n", str);
	}
    }
}

int    init_client(t_client client)
{
  int   sd;
  struct sockaddr_in sin;
  struct protoent *pe;

  pe = getprotobyname("TCP");
  if ((sd = socket(AF_INET, SOCK_STREAM, pe->p_proto)) == -1)
    return (printf("Socket error\n"));
  sin.sin_family = AF_INET;
  sin.sin_port = htons(client.port);
  sin.sin_addr.s_addr = inet_addr(client.host);
  if ((connect(sd, (const struct sockaddr *)&sin, sizeof(sin))) == -1)
    {
      close(sd);
      return (printf("Error while connecting\n"));
    }
  continue_client(client, sd);
  close(sd);
  return (0);
}
