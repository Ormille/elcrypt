/*
** feistel.c for feistel in /home/moran-_d/rendu/elcrypt/etape_1/src
** 
** Made by moran-_d
** Login   <moran-_d@epitech.net>
** 
** Started on  Fri Mar 20 22:22:03 2015 moran-_d
** Last update Sat Mar 21 19:38:05 2015 moran-_d
*/

#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "elcrypt.h"

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
  /*  printf("sec = %"PRIu32"\n", (uint32_t)second ^ block); */
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
