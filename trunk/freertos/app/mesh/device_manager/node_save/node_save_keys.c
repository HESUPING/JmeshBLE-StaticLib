/*
 * node_save_keys.c
 *
 *  Created on: 2018-8-22
 *      Author: jiachuang
 */

#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "node_save_macro.h"
#include "node_save_common.h"
#include "node_save_keys.h"
#include "node_save.h"
#include "mesh_node_base.h"
#include "network_keys_dm.h"
#include "app_keys_dm.h"
#include "device_keys_dm.h"
#include "bxfs.h"



static uint8_t recover_gen_netkeys_total = 0;
static uint8_t recover_gen_netkeys_curr  = 0;


/***************appkey*****************/


void node_save_app_key_add(app_key_t *buf,uint8_t save_index)
{
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_app_key_add\n");
    //temp buff
    app_key_nodesave_t save_buf;
    //get dir and filename
    uint8_t dir1_keys     = MESHDIR1_KEYS;
    uint8_t dir2_key_type = MESHDIR2_KEYS_APPKEYLIST;
    uint8_t file_name     = save_index;

    //app_key_t -> app_key_nodesave_t
    save_buf.src_app_key = *buf;
    save_buf.netkey_global_idx = buf->bound_netkey->global_idx;

    //save to bxfs
    if(file_name != MESH_SAVE_ERROR)
    {
        bxfs_write2(dir1_keys , dir2_key_type , file_name , &save_buf , MESH_SIZE_APPKEYLIST);
    }
}


void node_save_app_key_recover(void)
{
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_app_key_recover\n");
    //temp buffer
    app_key_t           appkey_buf;
    app_key_nodesave_t  save_buf;
    net_key_t *         p_net_key;
    //dir & filename
    uint8_t dir1_keys     = MESHDIR1_KEYS;
    uint8_t dir2_key_type = MESHDIR2_KEYS_APPKEYLIST;
    uint8_t file_name     = 0;

    //list all appkey
    bxfs_listfile2(dir1_keys,dir2_key_type);
    for(uint8_t i=0;i<get_node_save_file_count();i++)
    {
        file_name  = get_node_save_file_list(i);
        bxfs_read2(dir1_keys , dir2_key_type , file_name , &save_buf , MESH_SIZE_DEVKEYLIST);
        /* app_key_nodesave_t -> app_key_t */
        //1.recover structure
        appkey_buf = save_buf.src_app_key;
        //2.recover bound netkey.
        dm_netkey_index_to_netkey_handle(save_buf.netkey_global_idx,&p_net_key);
        appkey_buf.bound_netkey = p_net_key;
        //3.add to dm system
        err_t status =  dm_appkey_recovery_from_bxfs(file_name , &appkey_buf);
    }
}

void node_save_app_key_delete(uint8_t save_index)
{
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_app_key_delete\n");
    //dir & filename
    uint8_t dir1_keys     = MESHDIR1_KEYS;
    uint8_t dir2_key_type = MESHDIR2_KEYS_APPKEYLIST;
    uint8_t file_name     = save_index;
    //delete
    bxfs_delete2(dir1_keys , dir2_key_type , file_name);
}
/***************appkey*****************/


/***************netkey*****************/


void node_save_net_key_add(net_key_t *buf,uint8_t save_index)
{
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_net_key_add\n");
    //temp buffer
    net_key_nodesave_t save_buf;

    //dir & filename
    uint8_t dir1_keys       = MESHDIR1_KEYS;
    uint8_t dir2_key_type   = MESHDIR2_KEYS_NETKEYLIST;
    uint8_t file_name       = save_index;

    //init save buf
    memcpy(save_buf.netkey[KEY_PRIMARY],buf->key[KEY_PRIMARY].netkey,MESH_KEY_LENGTH);
    memcpy(save_buf.netkey[KEY_UPDATED],buf->key[KEY_UPDATED].netkey,MESH_KEY_LENGTH);
    save_buf.global_idx = buf->global_idx;
    save_buf.key_refresh_phase = buf->key_refresh_phase;

    //save to bxfs
    if(file_name != MESH_SAVE_ERROR)
    {
        bxfs_write2(dir1_keys , dir2_key_type , file_name, &save_buf , MESH_SIZE_NETKEYLIST);
    }
}

void node_recover_waiting_for_netkeys_generation_done_cb(void* dm_handle)
{
    //temp buffer
    net_key_t           netkey_buf;
    net_key_nodesave_t  save_buf;

    //dir & filename
    uint8_t dir1_keys       = MESHDIR1_KEYS;
    uint8_t dir2_key_type   = MESHDIR2_KEYS_NETKEYLIST;
    uint8_t file_name       = 0;

    //list file action
    if(recover_gen_netkeys_curr < recover_gen_netkeys_total)
    {
        if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_recover_waiting_for_netkeys_generation_done_cb\n");
        file_name = get_node_save_file_list(recover_gen_netkeys_curr);
        bxfs_read2(dir1_keys , dir2_key_type , file_name, &save_buf , MESH_SIZE_NETKEYLIST);
        //recover source netkey buff
        memcpy( netkey_buf.key[KEY_PRIMARY].netkey,save_buf.netkey[KEY_PRIMARY],MESH_KEY_LENGTH);
        memcpy( netkey_buf.key[KEY_UPDATED].netkey,save_buf.netkey[KEY_UPDATED],MESH_KEY_LENGTH);
        netkey_buf.global_idx = save_buf.global_idx;
        netkey_buf.key_refresh_phase = save_buf.key_refresh_phase;
        //add to dm system and generate all keys
        dm_netkey_recovery_from_bxfs(file_name , &netkey_buf , node_recover_waiting_for_netkeys_generation_done_cb);
        recover_gen_netkeys_curr ++;
    }
    else//next recover stage
    {
        node_save_process_next_stage();
    }
}







void node_save_net_key_recover(void)
{
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_net_key_recover\n");

    //dir & filename
    uint8_t dir1_keys     = MESHDIR1_KEYS;
    uint8_t dir2_key_type = MESHDIR2_KEYS_NETKEYLIST;
    uint8_t file_name     = 0;

    //list all files
    bxfs_listfile2(dir1_keys,dir2_key_type);
    //set total value
    recover_gen_netkeys_total = get_node_save_file_count();
    recover_gen_netkeys_curr = 0;
    //generate keys
    node_recover_waiting_for_netkeys_generation_done_cb(0);
}

void node_save_net_key_delete(uint8_t save_index)
{
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_net_key_delete\n");
    //dir & filename
    uint8_t dir1_keys     = MESHDIR1_KEYS;
    uint8_t dir2_key_type = MESHDIR2_KEYS_NETKEYLIST;
    uint8_t file_name     = save_index;
    //delete
    bxfs_delete2(dir1_keys , dir2_key_type , file_name);
}
/***************netkey*****************/


/***************devkey*****************/

void node_save_dev_key_add(dev_key_t *buf,uint8_t save_index)
{
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_dev_key_add\n");
    //temp buff
    dev_key_nodesave_t  dev_key_nodesave;
    uint8_t             net_key_global_idx;
    //get dir and filename
    uint8_t dir1_keys     = MESHDIR1_KEYS;
    uint8_t dir2_key_type = MESHDIR2_KEYS_DEVKEYLIST;
    uint8_t file_name     = save_index;

    // dev_key -> dev_key_nodesave
    dev_key_nodesave.src_dev_key = *buf;
    for(uint8_t i=0;i<DEVKEY_BOUND_NETKEY_MAX_NUM;i++)
    {
        net_key_global_idx = (buf->bound_netkey.pool[i] != NULL) ? (buf->bound_netkey.pool[i]->global_idx) : (0);
        dev_key_nodesave.net_key_global_index_pool[i] = net_key_global_idx;
    }

    //save to bxfs
    if(file_name != MESH_SAVE_ERROR)
    {
        bxfs_write2(dir1_keys , dir2_key_type , file_name , buf , MESH_SIZE_DEVKEYLIST);
    }
}



void node_save_dev_key_recover(void)
{
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_dev_key_recover\n");
    //temp buff
    dev_key_nodesave_t  dev_key_nodesave;
    dev_key_t           dev_key;
    err_t               err_no;
    net_key_t *         p_net_key;
    //dir & filename
    uint8_t dir1_keys     = MESHDIR1_KEYS;
    uint8_t dir2_key_type = MESHDIR2_KEYS_DEVKEYLIST;
    uint8_t file_name     = 0;

    //list all files
    bxfs_listfile2(dir1_keys,dir2_key_type);
    for(uint8_t i=0;i<get_node_save_file_count();i++)
    {
        file_name  = get_node_save_file_list(i);
        bxfs_read2(dir1_keys , dir2_key_type , file_name , &dev_key_nodesave , MESH_SIZE_DEVKEYLIST);
        /* dev_key_nodesave -> dev_key */
        //1.recover structure.
        dev_key = dev_key_nodesave.src_dev_key;
        //2.recover pool
        for(uint8_t j=0;j<DEVKEY_BOUND_NETKEY_MAX_NUM;j++)
        {
            err_no = dm_netkey_index_to_netkey_handle(dev_key_nodesave.net_key_global_index_pool[j] , &p_net_key);
            dev_key.bound_netkey.pool[j] = (err_no == MESH_CORE_ERROR_NOT_FOUND) ? (NULL) : (p_net_key);
        }
        //3.add to dm system
        err_t status = dm_devkey_recovery_from_bxfs(file_name , &dev_key);
    }
}

void node_save_dev_key_delete(uint8_t save_index)
{
    if(NODE_SAVE_LOG_ENABLE) LOG(LOG_LVL_INFO,"NODESAVE:node_save_dev_key_delete\n");
    //dir & filename
    uint8_t dir1_keys     = MESHDIR1_KEYS;
    uint8_t dir2_key_type = MESHDIR2_KEYS_DEVKEYLIST;
    uint8_t file_name     = save_index;
    //delete
    bxfs_delete2(dir1_keys , dir2_key_type , file_name);
}
/***************devkey*****************/




#endif
