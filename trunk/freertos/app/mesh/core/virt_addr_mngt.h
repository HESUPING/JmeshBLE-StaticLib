#ifndef VIRT_ADDR_MNGT_H_
#define VIRT_ADDR_MNGT_H_
#include <stdint.h>
#include <stdbool.h>
#include "mesh_definitions.h"
#define VIRT_ADDR_SET_BUF_SIZE 5
typedef struct
{
    uint8_t label_uuid[LABEL_UUID_SIZE];
    uint16_t virt_addr;
}virt_addr_mngt_t;
void virt_addr_search(uint16_t virt_addr,virt_addr_mngt_t **buf,uint8_t *matched_num);
void virt_addr_add(uint8_t *label_uuid,uint8_t *status);
void virt_addr_salt_init(void);
#endif
