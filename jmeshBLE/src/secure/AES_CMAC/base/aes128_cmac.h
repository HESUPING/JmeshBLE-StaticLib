/*
 * aes128_cmac.h
 *
 *  Created on: 2017Äê10ÔÂ10ÈÕ
 *      Author: wz
 */

#include "aes128.h"

#ifndef _AES128_CMAC_H
#define _AES128_CMAC_H

void leftshift(int len, uint8_t* add, uint8_t*des);

void ArrayXor(int len, uint8_t*a1, uint8_t*a2, uint8_t*des);

void LoadMacKey(uint8_t *key);

void GenerateMAC(int len, uint8_t *add, uint8_t *macvalue);

uint8_t VerifyMAC(int len, uint8_t *add, uint8_t *macvalue1);

#endif
