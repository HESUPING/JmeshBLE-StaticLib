#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "health_client.h"

#include "common.h"
//opcode handler
void health_fault_status_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{


}
void health_period_status_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{


}
void health_attention_status_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{


}

// interface for user
uint32_t health_client_fault_get(health_client_t * p_client, uint16_t company_id)
{


}

uint32_t health_client_fault_clear(health_client_t * p_client, uint16_t company_id, bool acked)
{


}

uint32_t health_client_fault_test(health_client_t * p_client, uint16_t company_id, uint8_t test_id, bool acked)
{


}
uint32_t health_client_period_get(health_client_t * p_client)
{

}

uint32_t health_client_period_set(health_client_t * p_client, uint8_t fast_period_divisor, bool acked)
{

}
uint32_t health_client_attention_get(health_client_t * p_client)
{


}

uint32_t health_client_init(health_client_t * p_client)
{

}


#endif

