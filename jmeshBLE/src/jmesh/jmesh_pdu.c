#include"jmesh_pdu.h"
#include"../onchip_system/os_memb.h"
#include"../driver/jmesh_system.h"


OS_MEMB_CREATE(jmesh_long_pdu_memb,JMESH_LONG_PDU_SIZE,JMESH_LONG_PDU_CACHE_SIZE);
OS_MEMB_CREATE(jmesh_short_pdu_memb,JMESH_SHORT_PDU_SIZE,JMESH_SHORT_PDU_CACHE_SIZE);



void jmesh_pdu_init(void)
{
    os_memb_init(jmesh_long_pdu_memb);
    os_memb_init(jmesh_short_pdu_memb);
}
jmesh_pdu_t* jmesh_pdu_new(int length)
{
    jmesh_pdu_t* pdu=NULL;
    if(length<=JMESH_SHORT_PDU_SIZE){
        pdu=os_memb_new(jmesh_short_pdu_memb);
    }
    else if(length<=JMESH_LONG_PDU_SIZE){
        pdu=os_memb_new(jmesh_long_pdu_memb);
    }
    return pdu;
}
void jmesh_pdu_free(jmesh_pdu_t* pdu)
{
    os_memb_free(jmesh_short_pdu_memb,pdu);
    os_memb_free(jmesh_long_pdu_memb,pdu);
}
