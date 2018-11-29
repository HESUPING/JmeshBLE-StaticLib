/*
 * mesh_tools.c
 *
 *  Created on: 2018-1-24
 *      Author: jiachuang
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "string.h"
#include "log.h"
#include "mesh_tools.h"
#include "stdlib.h"
#if (NVDS_SUPPORT)
#include "nvds.h"               // NVDS definitions
#endif //(NVDS_SUPPORT)

/*
 * DEFINES
 ****************************************************************************************
 */
//mesh log
#define MESH_LOG_BUFFER_SIZE            64

/*
 * LOCAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
static const uint8_t mesh_log_hex_tab[] = "0123456789ABCDEF";



/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief  tools for memory reverse and copy.
 *
 * @param[in]  p_src      Pointer to the memcpy source data.
 * @param[out] p_dst      Pointer to the memcpy destination data.
 * @param[in]  length     The length of data to be memcpy.
 *
 * @note  Source and destination addresses cannot have an intersection.
 *
 ****************************************************************************************
 */
void memcpy_rev(void * p_dst, void * p_src, uint8_t length)
{
    uint8_t * src = (uint8_t *) p_src;
    uint8_t * dst = (uint8_t *) p_dst;
    
	dst += (length - 1);
	while(length --)
	{
        *dst = * src;
        dst--;
        src ++;
	}
}


/**
 ****************************************************************************************
 * @brief  tools for printf to segger rtt log data .(temp buff use local variable array)
 *
 * @param[in]  data      Pointer to the data to be printf to segger rtt log.
 * @param[in]  length    The length of data to be printf.
 *
 ****************************************************************************************
 */
void log_mesh_received_data(uint8_t * data , uint8_t length)
{
    uint8_t tmp_h,tmp_l;
    uint8_t mesh_log_format_buff[MESH_LOG_BUFFER_SIZE];
    uint8_t *bufptr = mesh_log_format_buff;
    uint32_t total_length;
    //start
    *bufptr = '\n'; bufptr ++;
    *bufptr = '>' ; bufptr ++;
    *bufptr = '>' ; bufptr ++;
    //content
    for(uint8_t i=0;i<length;i++)
    {
        tmp_h = data[i] >> 4;
        tmp_l = data[i] & 0x0F;
        *bufptr = mesh_log_hex_tab[tmp_h];  bufptr++;
        *bufptr = mesh_log_hex_tab[tmp_l];  bufptr++;
    }
    //end
    *bufptr = '\n'; bufptr ++;

    //print
    total_length = length * 2 + 4;
    SEGGER_RTT_Write(0,mesh_log_format_buff,total_length);
    #if (USE_INTERNAL_LOG == 1)
    internal_log_write(mesh_log_format_buff,total_length);
    #endif
}
/**
 ****************************************************************************************
 * @brief  tools for printf to segger rtt log data.(temp buff use malloc)
 *
 * @param[in]  data      Pointer to the data to be printf to segger rtt log.
 * @param[in]  length    The length of data to be printf.
 *
 ****************************************************************************************
 */
void log_hex_data(uint8_t * data , uint8_t length)
{
    uint8_t tmp_h,tmp_l;
    uint8_t *mesh_log_format_buff=0;
    uint8_t *bufptr=0;
    uint32_t total_length;
    //init
    total_length = length * 2 + 1;
    mesh_log_format_buff = pvPortMalloc(total_length);
    bufptr = mesh_log_format_buff;
    //content
    for(uint8_t i=0;i<length;i++)
    {
        tmp_h = data[i] >> 4;
        tmp_l = data[i] & 0x0F;
        *bufptr = mesh_log_hex_tab[tmp_h];  bufptr++;
        *bufptr = mesh_log_hex_tab[tmp_l];  bufptr++;
    }
    //end
    *bufptr = '\n'; bufptr ++;
    //print
    SEGGER_RTT_Write(0,mesh_log_format_buff,total_length);
    #if (USE_INTERNAL_LOG == 1)
    internal_log_write(mesh_log_format_buff,total_length);
    #endif
    //free
    vPortFree(mesh_log_format_buff);
}

/**
 ****************************************************************************************
 * @brief  tools for reverse the src data.
 *
 * @param[in]  p_src      Pointer to the memcpy source data.
 * @param[in]  length     The length of data to be reverse.
 *
 ****************************************************************************************
 */
void reverse_self(void * p_src , uint8_t length)
{
    uint8_t *src1 = (uint8_t*)p_src;
    uint8_t *src2 = src1 + length - 1;
    uint8_t i=length / 2;
    uint8_t tmp=0;
    while(i--)
    {
        tmp = *src1;
        *src1 = *src2;
        *src2 = tmp;
        src1 ++;
        src2 --;
    }
}

/**
 ****************************************************************************************
 * @brief  tools for random generate.
 *
 * @param[out] p_out      Pointer to the random data.
 * @param[in]  len        generate random length in byte.
 *
 ****************************************************************************************
 */
void tools_random_generate(uint8_t *p_out,uint8_t len)
{
	uint32_t tmp=0;
	uint8_t random_idx = 0;
	uint8_t random_remain = 0;


	while(random_idx <len)
	{
		tmp = rand();
		random_remain = len - random_idx;

		if(random_remain>=4)
		{
			memcpy((p_out+random_idx),(uint8_t *)&tmp,4);
			random_idx += 4;
		}
		else
		{
			memcpy((p_out+random_idx),(uint8_t *)&tmp,random_remain);
			random_idx += random_remain;
		}
	}
}

/**
 ****************************************************************************************
 * @brief  tools for get the gap public bd address.
 *
 * @param[out] p_out_addr      Pointer to the gap public bd address data.
 *
 ****************************************************************************************
 */
void tools_gap_public_bd_addr_get(uint8_t *p_out_addr)
{
    const uint8_t default_bdaddr[BD_ADDR_LEN] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB};
    uint8_t len = BD_ADDR_LEN;

    // get BD address
#if (NVDS_SUPPORT)
    if (nvds_get(NVDS_TAG_BD_ADDRESS, &len, p_out_addr) != NVDS_OK)
#endif //(NVDS_SUPPORT)
    {
        memcpy(&p_out_addr, (uint8_t *)&default_bdaddr[0], sizeof(default_bdaddr));
    }
}

#endif /* OSAPP_MESH */



