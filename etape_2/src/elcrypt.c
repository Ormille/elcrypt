/*
** elcrypt.c for elcryp in /home/moran-_d/rendu/elcrypt/etape_2/src
** 
** Made by moran-_d
** Login   <moran-_d@epitech.net>
** 
** Started on  Sat Mar 21 21:53:44 2015 moran-_d
** Last update Sun Mar 22 00:26:13 2015 moran-_d
*/

#include "elnetcat.h"

uint32_t feistel_key(uint64_t key, uint32_t block, int turn)
{
  uint64_t second;

  second = key;
  while (turn > 0)
    {
      second = second << 4;
      second += ((second & 0x0F00000000000000) >> 7 * 8);
      second = second & 0x00FFFFFFFFFFFFFF;
      --turn;
    }
  return (((uint32_t)second) ^ block);
}

uint64_t feistel_enc(elc *elc, uint64_t block, int turn)
{
  uint32_t left;
  uint32_t right;
  uint32_t tmp;
  int t;
  int i;

  i = -1;
  left = (uint32_t)(block >> 32);
  right = (uint32_t)block;
  while (++i < TURNS)
    {
      t = abs(turn - i);
      tmp = feistel_key(elc->skey, right, t);
      tmp = tmp ^ left;
      left = right;
      right = tmp;
    }
  block = left;
  block = (block << 32) + right;
  return (block);
}

uint64_t feistel_dec(elc *elc, uint64_t block, int turn)
{
  uint32_t left;
  uint32_t right;
  uint32_t tmp;
  int t;
  int i;

  i = -1;
  left = block >> 32;
  right = block;
  while (++i < TURNS)
    {
      t = abs(turn - i);
      tmp = feistel_key(elc->skey, left, t);
      tmp = tmp ^ right;
      right = left;
      left = tmp;
    }
  block = left;
  block = (block << 32) + right;
  return (block);
}

int encrypt(elc *elc, char *linebuf, int turn, int nbr)
{
  unsigned char buf[8];
  uint64_t block;
  int len;
  int i;

  i = 8;
  while (i <= nbr)
    {
      memcpy(buf, linebuf + i - 8, BBLOCK);
      block = construct_block(buf);
      block = feistel_enc(elc, block, turn);
      deconstruct_block(block, buf);
      write(elc->fout, buf, BBLOCK);
      i += 8;
    }
  memcpy(buf, linebuf + i - 8, BBLOCK);
  len = add_padding(buf, 8 - nbr % 8);
  block = construct_block(buf);
  block = feistel_enc(elc, block, turn);
  deconstruct_block(block, buf);
  write(elc->fout, buf, len);
  return (0);
}

int decrypt(elc *elc, char *linebuf, int turn, int nbr)
{
  unsigned char buf[8];
  uint64_t block;
  int len;
  int i;

  i = -1;
  while (++i < nbr - 1)
    {
      memcpy(buf, linebuf + i * 8, BBLOCK);
      block = construct_block(buf);
      block = feistel_dec(elc, block, turn);
      deconstruct_block(block, buf);
      write(elc->fout, buf, BBLOCK);
    }
  memcpy(buf, linebuf + i * 8, BBLOCK);
  block = construct_block(buf);
  block = feistel_dec(elc, block, turn);
  deconstruct_block(block, buf);
  if ((len = sub_padding(buf)) < 0 || len > 8)
    return (printf("Some error while getting padding : %d\n", len));
  write(elc->fout, buf, len);
  return (0);
}
