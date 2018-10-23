#ifndef JMESH_LOWPOWER_H
#define JMESH_LOWPOWER_H
#include"../../jmesh/jmesh_config.h"
#include"../../jmesh/jmesh_pdu.h"




void jmesh_lowpower_init(void);
void jmesh_lowpower_sleep(void);
void jmesh_lowpower_wakeup_callback(void);
void jmesh_lowpower_recv_pdu_callback(void);
void jmesh_lowpower_recv(unsigned short netkey_indexz,unsigned short length,jmesh_pdu_t* pdu);

void jmesh_lowpower_subscription_list_add(unsigned short addr);
void jmesh_lowpower_subscription_list_remove(unsigned short addr);

#endif // JMESH_LOWPOWER_H
