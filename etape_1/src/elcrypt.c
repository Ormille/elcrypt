/*
** elcrypt.c for elcrypt in /home/moran-_d/rendu/elcrypt/etape_1/src
**
** Made by moran-_d
** Login   <moran-_d@epitech.net>
**
** Started on  Fri Mar 20 22:06:10 2015 moran-_d
** Last update Fri Mar 20 22:34:44 2015 Julie Terranova
*/

#include <string.h>
#include <unistd.h>
#include "elcrypt.h"

int elcrypt(elc *elc, int turn)
{
  char buf[BBLOCK];
  int64_t block;
  int len;

  while ((len = read(elc->fin, buf, BBLOCK)) == BBLOCK)
    {
      block = (int64_t)buf;
      block = feistel(elc, block, elc->mode);
      memcpy(buf, block, BBLOCK);
      //      write(elc->fout,
    }
}
