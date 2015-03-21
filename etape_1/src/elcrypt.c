/*
** elcrypt.c for elcrypt in /home/moran-_d/rendu/elcrypt/etape_1/src
**
** Made by moran-_d
** Login   <moran-_d@epitech.net>
**
** Started on  Fri Mar 20 22:06:10 2015 moran-_d
** Last update Sat Mar 21 11:58:48 2015 moran-_d
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "elcrypt.h"

uint64_t parity_bits_key(uint64_t key)
{
  uint64_t ret;
  char tmp;
  int i;

  ret = 0;
  i = BBLOCK;
  while (--i >= 0)
    {
      key = key >> 1;
      tmp = (char)key;
      ret = (ret << 7) + tmp;
      key = key >> 7;
    }
  return (ret);
}

int sub_padding(unsigned char *buf)
{
  return (BBLOCK - (int)buf[7]);
}

int add_padding(unsigned char *buf, int len)
{
  int nb;

  nb = len;
  if (len == 0)
    len = 8;
  while (--len >= 0)
    buf[len] = nb;
  return (BBLOCK);
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
  if (elc->mode == ENCRYPT)
    len = add_padding(buf, len);
  block = construct_block(buf);
  block = feistel(elc, block, turn);
  deconstruct_block(block, buf);
  if (elc->mode == DECRYPT)
    len = sub_padding(buf);
  write(elc->fout, buf, len);
  return (0);
}
