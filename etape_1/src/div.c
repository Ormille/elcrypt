/*
** div.c for div in /home/moran-_d/rendu/elcrypt/etape_1/src
** 
** Made by moran-_d
** Login   <moran-_d@epitech.net>
** 
** Started on  Sun Mar 22 00:37:28 2015 moran-_d
** Last update Sun Mar 22 00:37:58 2015 moran-_d
*/

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
