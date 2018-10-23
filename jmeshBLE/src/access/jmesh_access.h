#ifndef JMESH_ACCESS_H
#define JMESH_ACCESS_H

#include"jmesh_message.h"
#include"jmesh_model.h"
#include"jmesh_element.h"
#include"jmesh_access_callback.h"
#include"../jmesh/jmesh_pdu.h"
#include"../jmesh/jmesh_config.h"


void jmesh_access_init(void);

void jmesh_access_add_element(jmesh_element_t* element);
int jmesh_element_get_index(jmesh_element_t* element);
int jmesh_element_get_num(void);
jmesh_element_t* jmesh_element_get_by_index(int index);
jmesh_element_t* jmesh_element_get_by_addr(unsigned short addr);
unsigned short jmesh_element_get_addr(jmesh_element_t* element);

int jmesh_access_send(unsigned short dst,unsigned short netkey_index,unsigned short appkey_index,jmesh_model_t* model,const unsigned char* message,unsigned short length,unsigned char* data);

int jmesh_access_recv(jmesh_access_pdu_t* pdu);
int jmesh_config_send(unsigned short dst,jmesh_model_t* model,const unsigned char* message,unsigned short netkey_index,unsigned short length,unsigned char* data);
int jmesh_config_recv(jmesh_access_pdu_t* pdu);
int jmesh_element_get_num(void);
#endif // JMESH_ACCESS_H
