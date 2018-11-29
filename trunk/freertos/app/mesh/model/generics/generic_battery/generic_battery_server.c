#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "generic_battery_common.h"
#include "generic_battery_server.h"
#include "string.h"
static generic_battery_server_t s_generic_battery_server;

void send_generic_battery_status()
{

}
void generic_battery_get_rx(mesh_elmt_t *elmt,uint8_t *payload,uint8_t size)
{
	
	//deal with by user
	send_generic_battery_status();
}

void handle_battery_status_change(uint8_t type)
{


}

//user interface

uint8_t generic_battery_get()
{

}


uint32_t generic_battery_server_init(generic_battery_server_t *server)
{
	memcmp(&s_generic_battery_server,server,sizeof(generic_battery_server_t));
}

#endif

