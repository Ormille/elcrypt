/*
** elcrypt.h for elcrypt in /home/terran_j/rendu/elcrypt/etape_1
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Fri Mar 20 21:06:36 2015 Julie Terranova
** Last update Sun Mar 22 00:38:09 2015 moran-_d
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
  uint64_t key;
  uint64_t skey;
  int fin;
  int fout;
  int mode;
};

/* Main */
int main(int argc, char **argv);
int is_decimal(char *nb);
int crypt(char **av, elc *opt);

/* Parse */
elc *parse_args(char **argv);

/* Block */
uint64_t construct_block(unsigned char *buf);
void deconstruct_block(uint64_t block, unsigned char *buf);
int add_padding(unsigned char *buf, int len);
int sub_padding(unsigned char *buf);

/* Elcrypt */
int elcrypt(elc *elc, int turn);
uint64_t parity_bits_key(uint64_t key);

/* Feistel */
uint64_t feistel_enc(elc *elc, uint64_t block, int turn);
uint64_t feistel_dec(elc *elc, uint64_t block, int turn);
uint32_t feistel_key(uint64_t key, uint32_t block, int turn);

#endif
