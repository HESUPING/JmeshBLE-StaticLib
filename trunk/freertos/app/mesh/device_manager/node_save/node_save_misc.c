/*
 * node_save_misc.c
 *
 *  Created on: 2018��8��22��
 *      Author: jiachuang
 */

#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "node_save.h"
#include "node_save_macro.h"
#include "node_save_misc.h"
#include "node_save_common.h"
#include "bxfs.h"
#include "mesh_iv_operation_ex.h"


/***************misc*****************/

void node_save_misc_provision_now_status(void)
{
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_misc_provision_now_status\n");
    bxfs_write1(MESHDIR1_MISC , MESHFILE1_MISC_PROVISION_NOW_STATUS ,        &provision_now_status       , MESH_SIZE_PROVISION_NOW_STATUS);
}


void node_save_misc_sequence_number(void)
{
    uint32_t save_seq;
    if((sequence_number % 100) == 0)
    {
        save_seq = sequence_number + 100;
        if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_misc_sequence_number\n");
        bxfs_write1(MESHDIR1_MISC , MESHFILE1_MISC_SEQUENCE_NUMBER ,             &save_seq            , MESH_SIZE_SEQUENCE_NUMBER);
    }
    else
    {
        if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"Only seq%%100 == 0 will be saved.\n");
    }
}

void node_save_misc_iv_index(void)
{
    uint32_t iv_index= 0;
    iv_index = mesh_beacon_iv_index_get();
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_misc_iv_index\n");
    bxfs_write1(MESHDIR1_MISC , MESHFILE1_MISC_IV_INDEX ,                    &iv_index                   , MESH_SIZE_IV_INDEX);
}


void node_recover_misc(void)
{
    uint32_t iv_index= 0;
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_recover_misc:provision_now_status\n");
    bxfs_read1(MESHDIR1_MISC , MESHFILE1_MISC_PROVISION_NOW_STATUS ,        &provision_now_status       , MESH_SIZE_PROVISION_NOW_STATUS);
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_recover_misc:sequence_number\n");
    bxfs_read1(MESHDIR1_MISC , MESHFILE1_MISC_SEQUENCE_NUMBER ,             &sequence_number            , MESH_SIZE_SEQUENCE_NUMBER);
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_recover_misc:iv_index\n");
    bxfs_read1(MESHDIR1_MISC , MESHFILE1_MISC_IV_INDEX ,                    &iv_index                   , MESH_SIZE_IV_INDEX);
    mesh_beacon_iv_index_set(iv_index);
}

/***************misc*****************/



/***************element*****************/

void node_save_element_uni_adddr(void)
{
    for(uint8_t i=0;i<ELEMENT_NUM;i++)
    {
        if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_element%d_uni_adddr\n",i);
        bxfs_write1(MESHDIR1_ELMT_MIN + i , MESHFILE1_ELMT_UNI_ADDR , &server_elmts[i].uni_addr , MESH_SIZE_UNI_ADDR);
    }
}

void node_recover_element_uni_adddr(void)
{
    for(uint8_t i=0;i<ELEMENT_NUM;i++)
    {
        if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_recover_element%d_uni_adddr\n",i);
        bxfs_read1(MESHDIR1_ELMT_MIN + i , MESHFILE1_ELMT_UNI_ADDR , &server_elmts[i].uni_addr , MESH_SIZE_UNI_ADDR);
    }
}

/***************element*****************/






#endif
