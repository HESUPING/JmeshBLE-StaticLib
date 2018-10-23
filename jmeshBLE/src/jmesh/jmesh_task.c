#include"jmesh_task.h"
#include"../onchip_system/os_core.h"
#include"jmesh_pdu.h"
#include"../upper/jmesh_upper.h"
#include"../access/jmesh_access.h"

static const os_event_handler_t jmesh_handler_table[JMESH_EVENT_SIZE]={
    (os_event_handler_t)jmesh_upper_access_send,
    (os_event_handler_t)jmesh_access_recv,
    (os_event_handler_t)jmesh_upper_config_send,
    (os_event_handler_t)jmesh_config_recv,
    (os_event_handler_t)jmesh_interface_send_handler,
    (os_event_handler_t)jmesh_interface_recv_handler,
};



OS_TASK(jmesh_task,event,data)
{
    OS_START();
    while(1){
        OS_YIELD_UNTIL(event<JMESH_EVENT_SIZE);
        jmesh_handler_table[event](data);
    }
    OS_END();
}



int jmesh_provision_send_handler(jmesh_pdu_t* pdu){
    return 0;
}
int jmesh_provision_recv_handler(jmesh_pdu_t* pdu)
{
    return 0;
}
