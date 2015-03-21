/*
** elcrypt.h for elcrypt in /home/terran_j/rendu/elcrypt/etape_1
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Fri Mar 20 21:06:36 2015 Julie Terranova
** Last update Sat Mar 21 11:58:23 2015 moran-_d
*/

#ifndef ELCRYPT_H_
# define ELCRYPT_H_

#include <stdint.h>

#define BLOCK	(64)
#define HBLOCK	(BLOCK / 2)
#define BBLOCK	(BLOCK / 8)
#define HBBLOCK	(BBLOCK / 2)
#define TURNS	(8)

#define ENCRYPT	(0)
#define DECRYPT	(TURNS - 1)

#define to_uint64(buffer) (*(uint64_t*)buffer)

typedef struct elc_s elc;

struct elc_s {
  int64_t key;
  int64_t skey;
  int fin;
  int fout;
  int mode;
};

/* Main */
int main(int argc, char **argv);

int crypt(char **av, elc opt);

/* Parse */
elc *parse_args(char **argv); /* for each arg check if -X */

/* Block */
uint64_t construct_block(unsigned char *buf);
void deconstruct_block(uint64_t block, unsigned char *buf);

/* Elcrypt */
int elcrypt(elc *elc, int turn); /* for each block, do feistel */

/* Feistel */
uint64_t feistel(elc *elc, uint64_t block, int turn);	/* while i < TURNS do feistel */
								/* return block */
uint32_t feistel_key(uint64_t key, uint32_t block, int turn);	/* get secondary key */

#endif
