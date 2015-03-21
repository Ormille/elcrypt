/*
** block.c for block in /home/moran-_d/rendu/elcrypt/etape_1
** 
** Made by moran-_d
** Login   <moran-_d@epitech.net>
** 
** Started on  Sat Mar 21 10:24:00 2015 moran-_d
** Last update Sun Mar 22 00:26:24 2015 moran-_d
*/

#include <inttypes.h>
#include <stdio.h>
#include "elcrypt.h"

uint64_t parity_bits_key(uint64_t key)
{
  uint64_t ret;
  int i;

  ret = 0;
  i = BBLOCK;
  while (--i >= 0)
    {
      key = key >> 1;
      ret = (ret << 7) + ((unsigned char)key & 127);
      key = key >> 7;
    }
  return (ret);
}

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
      buf[7 - len] = nb;
    }
  return (BBLOCK);
}
