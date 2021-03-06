/*
  Diffie-Hellman key exchange (without HMAC) aka ECDH_anon in RFC4492
  1. Alice picks a (secret) random natural number 'a', calculates P = a * G and sends P to Bob.
     'a' is Alice's private key. 
     'P' is Alice's public key.
  2. Bob picks a (secret) random natural number 'b', calculates Q = b * G and sends Q to Alice.
     'b' is Bob's private key.
     'Q' is Bob's public key.
  3. Alice calculates S = a * Q = a * (b * G).
  4. Bob calculates T = b * P = b * (a * G).
  .. which are the same two values since multiplication in the field is commutative and associative.
  T = S = the new shared secret.
  Pseudo-random number generator inspired / stolen from: http://burtleburtle.net/bob/rand/smallprng.html
*/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <time.h>
#include "ecdh.h"

static void ecdh_demo(void)
{
  static uint8_t puba[ECC_PUB_KEY_SIZE];
  static uint8_t prva[ECC_PRV_KEY_SIZE] = {0x55,0xff,0x72,0x56,0x3e,0x87,0x3c,0xc3,0xbe,0x29,0x7e,0xd3,0x32,0x52,0x87,0x74,0x37,0xa9,0x9f,0x81,0xb8,0x7d,0x09,0x54};
  static uint8_t seca[ECC_PUB_KEY_SIZE];
  static uint8_t pubb[ECC_PUB_KEY_SIZE];
  static uint8_t prvb[ECC_PRV_KEY_SIZE] = {0x95,0xff,0x72,0x56,0x3e,0x57,0x3c,0x35,0xbe,0x35,0x7e,0xd3,0x32,0xb8,0xaa,0x09,0x54,0x57,0xd2,0x93,0x57,0xd2,0x93,0x56};
  static uint8_t secb[ECC_PUB_KEY_SIZE];
  uint32_t i;


  /* 1. Alice picks a (secret) random natural number 'a', calculates P = a * g and sends P to Bob. */
  // for (i = 0; i < ECC_PRV_KEY_SIZE; ++i)
  // {
  //   prva[i] = prng_next();
  // }
  printf("Private A: ");
  for (int i = 0; i <ECC_PRV_KEY_SIZE; i++ )
  {
      printf("%x" ,prva[i]);
  }
  printf("\n");
  assert(ecdh_generate_keys(puba, prva));
  printf("Public A: ");
  for (int i = 0; i <ECC_PUB_KEY_SIZE; i++ )
  {
      printf("%x" ,puba[i]);
  }
  printf("\n");

  /* 2. Bob picks a (secret) random natural number 'b', calculates Q = b * g and sends Q to Alice. */
  // for (i = 0; i < ECC_PRV_KEY_SIZE; ++i)
  // {
  //   prvb[i] = prng_next();
  // }
  printf("Private B: ");
  for (int i = 0; i <ECC_PRV_KEY_SIZE; i++ )
  {
      printf("%x" ,prvb[i]);
  }
  printf("\n");
  assert(ecdh_generate_keys(pubb, prvb));
    printf("Public B: ");
  for (int i = 0; i <ECC_PUB_KEY_SIZE; i++ )
  {
      printf("%x" ,pubb[i]);
  }
  printf("\n");

//   /* 3. Alice calculates S = a * Q = a * (b * g). */
//   assert(ecdh_shared_secret(prva, pubb, seca));

//   /* 4. Bob calculates T = b * P = b * (a * g). */
//   assert(ecdh_shared_secret(prvb, puba, secb));

//   /* 5. Assert equality, i.e. check that both parties calculated the same value. */
//   for (i = 0; i < ECC_PUB_KEY_SIZE; ++i)
//   {
//     assert(seca[i] == secb[i]);
//   }
}

int main(int argc, char* argv[])
{
  int i;
  int ncycles = 1;

  if (argc > 1)
  {
    ncycles = atoi(argv[1]);
  }

  for (i = 0; i < ncycles; ++i)
  {
    ecdh_demo();
  }

  return 0;
}