/*
** elcrypt.c for elcrypt in /home/moran-_d/rendu/elcrypt/etape_1/src
**
** Made by moran-_d
** Login   <moran-_d@epitech.net>
**
** Started on  Fri Mar 20 22:06:10 2015 moran-_d
** Last update Sat Mar 21 10:35:00 2015 moran-_d
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "elcrypt.h"

uint64_t add_padding(unsigned char *buf, int len)
{
  buf = buf;
  len = len;
  return (0);
}

int elcrypt(elc *elc, int turn)
{
  unsigned char buf[8];
  uint64_t block;
  int len;

  memset(buf, 0, BBLOCK);
  while ((len = read(elc->fin, buf, BBLOCK)) == BBLOCK)
    {
      block = construct_block(buf);
      block = feistel(elc, block, turn);
      deconstruct_block(block, buf);
      write(elc->fout, buf, BBLOCK);
      memset(buf, 0, BBLOCK);
    }
  if (len < 0)
    return (printf("Error during reading\n"));

  block = add_padding(buf, len);
  block = feistel(elc, block, turn);
  deconstruct_block(block, buf);
  write(elc->fout, buf, BBLOCK);
  return (0);
}
