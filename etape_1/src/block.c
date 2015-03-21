/*
** block.c for block in /home/moran-_d/rendu/elcrypt/etape_1
** 
** Made by moran-_d
** Login   <moran-_d@epitech.net>
** 
** Started on  Sat Mar 21 10:24:00 2015 moran-_d
** Last update Sat Mar 21 16:29:02 2015 moran-_d
*/

#include <stdio.h>
#include "elcrypt.h"

uint64_t construct_block(unsigned char *buf)
{
  uint64_t block;
  int i;

  block = 0;
  i = -1;
  while (++i < BBLOCK)
    block = (block << 8) + buf[i];
  return (block);
}

void deconstruct_block(uint64_t block, unsigned char *buf)
{
  int i;

  i = BBLOCK;
  while (--i >= 0)
    {
      buf[i] = block;
      block = block >> 8;
    }
}

int sub_padding(unsigned char *buf)
{
  return (BBLOCK - (int)buf[7]);
}

int add_padding(unsigned char *buf, int len)
{
  int nb;

  if (len == 0)
    len = 8;
  nb = len;
  while (--len >= 0)
    {
      printf("buf[%d] = %d\n", 7 - len, nb);
      buf[7 - len] = nb;
    }
  return (BBLOCK);
}
