/*
 * boot.h
 *
 *  Created on: 2016Äê4ÔÂ3ÈÕ
 *      Author: Administrator
 */

#ifndef PLF_BX2400_SRC_ARCH_BOOT_ARMCC_BOOT_H_
#define PLF_BX2400_SRC_ARCH_BOOT_ARMCC_BOOT_H_
#include <stdint.h>
extern const uint32_t Load$$ISR_VECTOR$$Base;
#define LOAD_ISR_VECTOR_BASE (&Load$$ISR_VECTOR$$Base) 
extern const uint32_t Load$$JMP_TABLE$$Limit;
#define LOAD_JMP_TABLE_LIMIT (&Load$$JMP_TABLE$$Limit)
extern const uint32_t Load$$RAM_CODE$$Base;
#define LOAD_RAM_CODE_BASE (&Load$$RAM_CODE$$Base)
extern const uint32_t Load$$RW_RAM$$Limit;
#define LOAD_RW_RAM_LIMIT (&Load$$RW_RAM$$Limit)
extern const uint32_t Image$$ISR_VECTOR$$Base;
#define ISR_VECTOR_BASE (&Image$$ISR_VECTOR$$Base)
extern const uint32_t Image$$RAM_CODE$$Base;
#define RAM_CODE_BASE (&Image$$RAM_CODE$$Base)
extern const uint32_t Image$$ZI_RAM$$Base;
#define ZI_RAM_BASE (&Image$$ZI_RAM$$Base)
extern const uint32_t Image$$ZI_RAM$$ZI$$Length;
#define ZI_RAM_LENGTH (&Image$$ZI_RAM$$ZI$$Length)
/// RAM unloaded section
extern const uint32_t Image$$RAM_UNLOADED$$Base;
#define RAM_UNLOADED_BASE (&Image$$RAM_UNLOADED$$Base)
extern const uint32_t Load$$NVDS_AREA$$Base;
#define LOAD_NVDS_AREA_BASE (&Load$$NVDS_AREA$$Base)
extern const uint32_t Load$$NVDS_AREA$$Length;
#define LOAD_NVDS_AREA_LENGTH (&Load$$NVDS_AREA$$Length)
extern const uint32_t Image$$NVDS_AREA$$Base;
#define NVDS_AREA_BASE (&Image$$NVDS_AREA$$Base)
extern uint32_t __initial_sp;
#define STACK_TOP __initial_sp
#endif /* PLF_BX2400_SRC_ARCH_BOOT_ARMCC_BOOT_H_ */
