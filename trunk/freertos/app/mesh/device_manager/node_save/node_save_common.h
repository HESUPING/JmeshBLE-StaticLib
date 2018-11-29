/*
 * node_save_common.h
 *
 *  Created on: 2018-8-22
 *      Author: jiachuang
 */

#ifndef FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_COMMON_H_
#define FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_COMMON_H_
#include "mesh_model.h"




//write
void bxfs_write1(uint8_t dir1 ,                                              uint8_t file , void * data , uint16_t length);
void bxfs_write2(uint8_t dir1 , uint8_t dir2  ,                              uint8_t file , void * data , uint16_t length);
void bxfs_write3(uint8_t dir1 , uint8_t dir2 , uint8_t dir3 ,                uint8_t file , void * data , uint16_t length);
//read
void bxfs_read1 (uint8_t dir1 ,                                              uint8_t file , void * data , uint16_t length);
void bxfs_read2 (uint8_t dir1 , uint8_t dir2 ,                                uint8_t file , void * data , uint16_t length);
void bxfs_read3 (uint8_t dir1 , uint8_t dir2 , uint8_t dir3 ,                uint8_t file , void * data , uint16_t length);
//delete
void bxfs_delete1(uint8_t dir1 , uint8_t file                               );
void bxfs_delete2(uint8_t dir1 , uint8_t dir2 , uint8_t file                );
void bxfs_delete3(uint8_t dir1 , uint8_t dir2 , uint8_t dir3 , uint8_t file );
//list
void bxfs_listfile3(uint8_t dir1 , uint8_t dir2 , uint8_t dir3);
void bxfs_listfile2(uint8_t dir1 , uint8_t dir2);

void get_config_server_save_dir(uint8_t * element_dir , uint8_t * model_dir);
void node_save_init_make_dir(void);
uint8_t get_element_save_dir(mesh_elmt_t *elmt);
uint8_t get_model_dir_index_in_its_element(model_base_t *model);


//list file interface
uint8_t get_node_save_file_count(void);
uint8_t get_node_save_file_list(uint8_t position);



#endif /* FREERTOS_APP_MESH_NODE_SAVE_NODE_SAVE_COMMON_H_ */
