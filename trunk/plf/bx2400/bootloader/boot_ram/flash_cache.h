#ifndef FLASH_CACHE_H_
#define FLASH_CACHE_H_
#include <stdint.h>

void flash_cache_config(uint32_t);
void flash_cache_enable(uint32_t);
void flash_cache_disable(void);
void flash_cache_flush(uint32_t,uint32_t);
void flash_cache_flush_all(void);

#endif
