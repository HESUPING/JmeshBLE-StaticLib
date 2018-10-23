#ifndef JMESH_APPKEY_H
#define JMESH_APPKEY_H

#include"../../jmesh/jmesh_config.h"

typedef struct st_jmesh_appkey{
    unsigned long netkey_index:12;
    unsigned long appkey_index:12;
    unsigned long aid:7;
    unsigned long is_valid:1;
    unsigned char key[16];
}jmesh_appkey_t;

void jmesh_appkey_init(void);
int jmesh_appkey_update(unsigned short netkey_index,unsigned short appkey_index,jmesh_key_t key);
int jmesh_appkey_set(unsigned short netkey_index,unsigned short appkey_index,unsigned char *key);
int jmesh_appkey_delete(unsigned short netkey_index,unsigned short appkey_index);
int jmesh_appkey_list(unsigned short netkey_index,unsigned char buffer_size,unsigned char* pdu);
jmesh_appkey_t* jmesh_appkey_get_by_aid(unsigned short netkey_index,unsigned char aid,jmesh_appkey_t* prev_key);
jmesh_appkey_t* jmesh_appkey_get_by_key_index(unsigned short netkey_index,unsigned short appkey_index);
jmesh_appkey_t* jmesh_appkey_get_by_index(unsigned char index);
int jmesh_appkey_get_index(jmesh_appkey_t* appkey);

#define JMESH_APPKEY_GET_KEY(appkey) ((appkey)->key)
#define JMESH_APPKEY_GET_AID(appkey)  ((appkey)->aid)

/*
 * list appkey index
 *
 * Description: list all appkeys bound to the netkey,the response is a config appkey list message
 * Arguments  : input = netkey index,index buffer size
                output = config appkey list message pdu
                ----------------------------------------
                | status | netkeyIndex | appkeyIndexes |
                ----------------------------------------
                |octect0 |  octect1-2  | variable      |
                ----------------------------------------
 * Returns    : pdu length
 * Note       : config appkey add
                config appkey update
                config appkey delete
                config appkey status
                config appkey get
                config appkey list
 */
int jmesh_state_list_appkey(unsigned short netkey_index,unsigned char buffer_size,unsigned char* key_index);

#endif // JMESH_APPKEY_H
