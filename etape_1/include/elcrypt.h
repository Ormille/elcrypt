/*
** elcrypt.h for elcrypt in /home/terran_j/rendu/elcrypt/etape_1
**
** Made by Julie Terranova
** Login   <terran_j@epitech.net>
**
** Started on  Fri Mar 20 21:06:36 2015 Julie Terranova
** Last update Fri Mar 20 22:40:49 2015 moran-_d
*/

#ifndef ELCRYPT_H_
# define ELCRYPT_H_

#include <stdint.h>

#define BLOCK	(64)
#define HBLOCK	(BLOCK / 2)
#define BBLOCK	(BLOCK / 8)
#define TURNS	(8)

#define ENCRYPT	(0)
#define DECRYPT	(TURNS)

typedef struct elc_s elc;

struct elc_s {
  int64_t key;
  int fin;
  int fout;
  int mode;
};

/* Main */
int main(int argc, char **argv);

int crypt(char **av, elc opt);

/* Parse */
elc *parse_args(char **argv); /* for each arg check if -X */

/* Elcrypt */
int elcrypt(elc *elc, int turn); /* for each block, do feistel */
int64_t add_padding(char *buf, int len);

/* Feistel */
int64_t feistel(elc *elc, char *block, int turn);	/* while i < TURNS do feistel */
							/* return block */
int32_t feistel_key(int64_t key, int turn);		/* get secondary key */

#endif
