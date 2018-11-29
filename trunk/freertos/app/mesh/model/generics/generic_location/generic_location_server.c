#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "generic_location_server.h"
#include "generic_location_common.h"
#include "string.h"
static generic_location_server_t s_generic_location_server;

static void send_generic_location_global_status()
{


}
static void send_generic_location_local_status()
{


}
void generic_location_global_get_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	send_generic_location_global_status();
}
void generic_location_local_get_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	send_generic_location_global_status();
}
uint32_t generic_location_server_init(generic_location_server_t *server)
{
	memcpy(&s_generic_location_server,server,sizeof(generic_location_server_t));
}
#endif

