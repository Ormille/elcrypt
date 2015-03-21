/*
** block.c for block in /home/moran-_d/rendu/elcrypt/etape_1
** 
** Made by moran-_d
** Login   <moran-_d@epitech.net>
** 
** Started on  Sat Mar 21 10:24:00 2015 moran-_d
** Last update Sat Mar 21 10:34:54 2015 moran-_d
*/

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
