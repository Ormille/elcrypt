/*
** feistel.c for feistel in /home/moran-_d/rendu/elcrypt/etape_1/src
** 
** Made by moran-_d
** Login   <moran-_d@epitech.net>
** 
** Started on  Fri Mar 20 22:22:03 2015 moran-_d
** Last update Sat Mar 21 10:16:51 2015 moran-_d
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "elcrypt.h"

uint32_t feistel_key(uint64_t key, uint32_t block, int turn)
{
  key = key;
  block = block;
  turn = turn;
  return (0);
}

uint64_t feistel(elc *elc, uint64_t block, int turn)
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
      tmp = feistel_key(elc->key, right, t);
      tmp = tmp ^ left;
      left = right;
      right = tmp;
    }
  block = left;
  block = (block << 32) + right;
  return (block);
}
