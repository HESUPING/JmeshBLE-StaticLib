#ifndef _AES128_H
#define _AES128_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
/*
 * Advanced Encryption Standard
 * @author Dani Huertas
 * @email huertas.dani@gmail.com
 *
 * Based on the document FIPS PUB 197
 */
 
extern void ArrayXor(int len, unsigned char*a1, unsigned char*a2, unsigned char*des);

extern int security_AES_CMAC(unsigned char* key,unsigned short length,unsigned char* m,unsigned char* MAC);

extern int security_s1_salt_generation(unsigned char* m, uint8_t len_m, unsigned char* s1);
/*
 * Addition in GF(2^8)
 * http://en.wikipedia.org/wiki/Finite_field_arithmetic
 */


/*
 * Subtraction in GF(2^8)
 * http://en.wikipedia.org/wiki/Finite_field_arithmetic
 */


/*
 * Multiplication in GF(2^8)
 * http://en.wikipedia.org/wiki/Finite_field_arithmetic
 * Irreducible polynomial m(x) = x8 + x4 + x3 + x + 1
 */


/*
 * Addition of 4 byte words
 * m(x) = x4+1
 */


/*
 * Multiplication of 4 byte words
 * m(x) = x4+1
 */


/*
 * The cipher Key.
 */


/*
 * Number of columns (32-bit words) comprising the State. For this
 * standard, Nb = 4.
 */


/*
 * Number of 32-bit words comprising the Cipher Key. For this
 * standard, Nk = 4, 6, or 8.
 */


/*
 * Number of rounds, which is a function of  Nk  and  Nb (which is
 * fixed). For this standard, Nr = 10, 12, or 14.
 */


/*
 * S-box transformation table
 */

/*
 * Inverse S-box transformation table
 */


/*
 * Generates the round constant Rcon[i]
 */


/*
 * Transformation in the Cipher and Inverse Cipher in which a Round
 * Key is added to the State using an XOR operation. The length of a
 * Round Key equals the size of the State (i.e., for Nb = 4, the Round
 * Key length equals 128 bits/16 bytes).
 */


/*
 * Transformation in the Cipher that takes all of the columns of the
 * State and mixes their data (independently of one another) to
 * produce new columns.
 */


/*
 * Transformation in the Inverse Cipher that is the inverse of
 * MixColumns().
 */


/*
 * Transformation in the Cipher that processes the State by cyclically
 * shifting the last three rows of the State by different offsets.
 */


/*
 * Transformation in the Inverse Cipher that is the inverse of
 * ShiftRows().
 */


/*
 * Transformation in the Cipher that processes the State using a non­
 * linear byte substitution table (S-box) that operates on each of the
 * State bytes independently.
 */


/*
 * Transformation in the Inverse Cipher that is the inverse of
 * SubBytes().
 */

/*
 * Function used in the Key Expansion routine that takes a four-byte
 * input word and applies an S-box to each of the four bytes to
 * produce an output word.
 */

/*
 * Function used in the Key Expansion routine that takes a four-byte
 * word and performs a cyclic permutation.
 */


/*
 * Key Expansion
 */


extern int aes128_encryption(const uint8_t key[], const uint8_t plaintext[], uint8_t* ciphertext);

extern int aes128_decryption(const uint8_t key[], const uint8_t cypher[], uint8_t* plain_text);

#endif // _AES_LIB_H
