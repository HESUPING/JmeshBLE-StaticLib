#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "sig_msg.h"
//config server/client
#include "config_server.h"
#include "config_client.h"
//generic model
#include "generic_onoff_server.h"
#include "generic_onoff_client.h"
//key refresh
#include "mesh_kr_comm.h"
#include "mesh_kr_server.h"
#include "mesh_kr_client.h"
//config messages
#include "config_relay.h"
#include "config_composition_data.h"





msg_handler_model_t fd_model_msg_one_opcode[One_Octet_Opcode_Msg_Num_Max]=
{
    [Config_AppKey_Add] = {config_appkey_add_rx,CONFIGURATION_SERVER_MODEL_ID},
    [Config_AppKey_Update] = {config_appkey_update_rx,CONFIGURATION_SERVER_MODEL_ID},
    [Config_Composition_Data_Status] = {config_composition_data_status_rx,CONFIGURATION_CLIENT_MODEL_ID},
    [Config_Model_Publication_Set] = {config_model_publication_set_rx,CONFIGURATION_SERVER_MODEL_ID},
    [Config_Heartbeat_Publication_Status] = {NULL,0},
    
    [Health_Current_Status] = {NULL,0},
    [Health_Fault_Status] = {NULL,0},
    
};

msg_handler_model_t fd_model_msg_two_opcode[Two_Octets_Opcode_Msg_Num_Max]=
{
    [Config_AppKey_Status] = {config_appkey_status_rx,CONFIGURATION_CLIENT_MODEL_ID},
    [Config_Model_Publication_Status] = {config_model_publication_status_rx,CONFIGURATION_CLIENT_MODEL_ID},
    [Config_Model_App_Bind] = {config_model_app_bind_rx,CONFIGURATION_SERVER_MODEL_ID},
    [Config_Model_App_Status] = {config_model_app_status_rx,CONFIGURATION_CLIENT_MODEL_ID},
    //Subscription
    [Config_Model_Subscription_Add] = {config_model_subscription_update_rx,CONFIGURATION_SERVER_MODEL_ID},
    [Config_Model_Subscription_Delete] = {config_model_subscription_update_rx,CONFIGURATION_SERVER_MODEL_ID},
    [Config_Model_Subscription_Overwrite] = {config_model_subscription_update_rx,CONFIGURATION_SERVER_MODEL_ID},
    [Config_Model_Subscription_Status] = {config_model_subscription_status_rx,CONFIGURATION_CLIENT_MODEL_ID},
    //config relay
    [Config_Relay_Get]    = {config_relay_get_rx,    CONFIGURATION_SERVER_MODEL_ID},
    [Config_Relay_Set]    = {config_relay_set_rx,    CONFIGURATION_SERVER_MODEL_ID},
    [Config_Relay_Status] = {config_relay_status_rx, CONFIGURATION_CLIENT_MODEL_ID},

    //config netkey
    [Config_NetKey_Update]    = {config_server_update_netkey_rx,    CONFIGURATION_SERVER_MODEL_ID},
    [Config_NetKey_Status]    = {config_client_net_key_status_rx,    CONFIGURATION_CLIENT_MODEL_ID},

    //config phase 
    [Config_Key_Refresh_Phase_Get]    = {handle_config_key_refresh_phase_get_rx,    CONFIGURATION_SERVER_MODEL_ID},
    [Config_Key_Refresh_Phase_Set]    = {handle_config_key_refresh_phase_set_rx,    CONFIGURATION_SERVER_MODEL_ID},
    [Config_Key_Refresh_Phase_Status] = {config_key_refresh_phase_status_rx,        CONFIGURATION_CLIENT_MODEL_ID},
    //composition data
    [Config_Composition_Data_Get] = {config_composition_data_get_rx, CONFIGURATION_SERVER_MODEL_ID},
};

msg_handler_model_t generic_onoff_model_msg[Generic_OnOff_Opcode_Max]=
{
    [Generic_OnOff_Get] = {generic_onoff_get_rx,GENERIC_ONOFF_SERVER_MODEL_ID},
    [Generic_OnOff_Set] = {generic_onoff_set_rx,GENERIC_ONOFF_SERVER_MODEL_ID},
    [Generic_OnOff_Set_Unacknowledged] = {generic_onoff_set_unacknowledged_rx,GENERIC_ONOFF_SERVER_MODEL_ID},
    [Generic_OnOff_Status] = {generic_onoff_status_rx,GENERIC_ONOFF_CLIENT_MODEL_ID},
};

msg_handler_model_t sensor_model_msg_one_octet[Sensor_One_Octet_Opcode_Max]=
{
0
};

msg_handler_model_t sensor_model_msg_two_octets[Sensor_Two_Octets_Opcode_Max]=
{
0
};

msg_map_t one_octet_msg_map[]=
{
    {fd_model_msg_one_opcode,FOUNDATION_MODELS_ONE_OCTET_OPCODE_OFFSET,One_Octet_Opcode_Msg_Num_Max},
    {sensor_model_msg_one_octet,SENSOR_ONE_OCTET_OPCODE_OFFSET,Sensor_One_Octet_Opcode_Max},
};

msg_map_t two_octets_msg_map[]=
{   
    {fd_model_msg_two_opcode,FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET,Two_Octets_Opcode_Msg_Num_Max},
    {generic_onoff_model_msg,GENERIC_ONOFF_OPCODE_OFFSET,Generic_OnOff_Opcode_Max},
    {sensor_model_msg_two_octets,SENSOR_TWO_OCTETS_OPCODE_OFFSET,Sensor_Two_Octets_Opcode_Max},
};

msg_map_array_t sig_msg_map_entry[2]=
{
    [0] = {one_octet_msg_map,ARRAY_LEN(one_octet_msg_map)},
    [1] = {two_octets_msg_map,ARRAY_LEN(two_octets_msg_map)},
};


msg_handler_model_t *mesh_sig_msg_handler_search(uint8_t *access_payload)
{
    msg_map_array_t *msg_map;
    uint16_t opcode_offset;
    uint8_t hdl_index = 0;
    uint8_t two_byte_opcode = 0;
    if((access_payload[0]&0x80) == 0)
    {
        msg_map = &sig_msg_map_entry[0];
        opcode_offset = access_payload[0] & 0x7f;
        two_byte_opcode = 0;
    }else
    {
        msg_map = &sig_msg_map_entry[1];
        opcode_offset = ((access_payload[0] & 0x3f)<<8)  | access_payload[1];
        two_byte_opcode = 1;
    }
    LOG(3,"mesh_sig_msg_handler_search:opcode_offset=0x%x\n",opcode_offset);
    uint16_t i;
    for(i=0;i<msg_map->size;++i)
    {
        if(opcode_offset >= msg_map->msg_map[i].offset && opcode_offset < (msg_map->msg_map[i].num + msg_map->msg_map[i].offset))
        {
            break;
        }
    }

    if(two_byte_opcode == 0)
    {
        hdl_index = opcode_offset;
    }
    else
    {
        hdl_index = opcode_offset - msg_map->msg_map[i].offset;
    }
    LOG(3,"mesh_sig_msg_handler_search:hdl_index=0x%x\n",hdl_index);
    if(i<msg_map->size)
    {
        return & msg_map->msg_map[i].ptr[hdl_index];
    }else
    {
        return NULL;
    }
}



#endif

