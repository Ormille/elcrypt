/*
** elcrypt.c for elcrypt in /home/moran-_d/rendu/elcrypt/etape_1/src
**
** Made by moran-_d
** Login   <moran-_d@epitech.net>
**
** Started on  Fri Mar 20 22:06:10 2015 moran-_d
** Last update Sat Mar 21 21:53:14 2015 moran-_d
*/

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "elcrypt.h"

void print_buffer(char *added, unsigned char *buf)
{
  int i;

  i = -1;
  while (++i < 8)
    printf("%sbuf[%d] = %d\n", added, i, buf[i]);
}

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
  printf("Primary Key without parity bits = %"PRIu64"\n", ret);
  return (ret);
}

int encrypt(elc *elc, int turn)
{
  unsigned char buf[8];
  uint64_t block;
  int len;

  memset(buf, 0, BBLOCK);
  while ((len = read(elc->fin, buf, BBLOCK)) == BBLOCK)
    {
      block = construct_block(buf);
      block = feistel_enc(elc, block, turn);
      deconstruct_block(block, buf);
      write(elc->fout, buf, BBLOCK);
      memset(buf, 0, BBLOCK);
    }
  if (len < 0)
    return (printf("Error during reading\n") - 5);
  len = add_padding(buf, 8 - len);
  block = construct_block(buf);
  block = feistel_enc(elc, block, turn);
  deconstruct_block(block, buf);
  write(elc->fout, buf, len);
  return (0);
}

int decrypt(elc *elc, int turn)
{
  unsigned char buf2[8];
  unsigned char buf[8];
  uint64_t block;
  int len;

  if ((len = read(elc->fin, buf, BBLOCK)) == BBLOCK)
    while (len == BBLOCK)
	if ((len = read(elc->fin, buf2, BBLOCK)) == BBLOCK)
	  {
	    block = construct_block(buf);
	    block = feistel_dec(elc, block, turn);
	    deconstruct_block(block, buf);
	    write(elc->fout, buf, BBLOCK);
	    memcpy(buf, buf2, BBLOCK);
	  }
  if (len != 0)
    return (printf("Error during reading : %d\n", len));
  block = construct_block(buf);
  block = feistel_dec(elc, block, turn);
  deconstruct_block(block, buf);
  if ((len = sub_padding(buf)) < 0 || len > 8)
    return (printf("Something went wrong, len = %d\n", len));
  write(elc->fout, buf, len);
  return (0);
}

int elcrypt(elc *elc, int turn)
{
  if (elc->mode == ENCRYPT)
    return (encrypt(elc, turn));
  else if (elc->mode == DECRYPT)
    return (decrypt(elc, turn));
  printf("Wrong mode !!!\n");
  return (0);
}
