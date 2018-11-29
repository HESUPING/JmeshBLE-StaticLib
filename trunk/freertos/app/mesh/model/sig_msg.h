#ifndef SIG_MSG_H_
#define SIG_MSG_H_
#include "mesh_env.h"
#include "mesh_model.h"
typedef void (*model_msg_handler_t)(mesh_elmt_t *,model_base_t *,access_pdu_rx_t *);
typedef struct
{
    model_msg_handler_t hdl;
    uint32_t model_id;
}msg_handler_model_t;

#define ONE_OCTET_OPCODE_GEN(offset,msg) ((offset)+(msg))
#define TWO_OCTETS_OPCODE_GEN(offset,msg) (((offset)+(msg))|0x8000)
#define CONFIGURATION_SERVER_MODEL_ID 0x0000
#define CONFIGURATION_CLIENT_MODEL_ID 0x0001
#define HEALTH_SERVER_MODEL_ID 0x0002
#define HEALTH_CLIENT_MODEL_ID 0x0003
#define FOUNDATION_MODELS_ONE_OCTET_OPCODE_OFFSET 0x0

enum Foundation_Models_One_Octet_Opcode
{
    Config_AppKey_Add = 0,
    Config_AppKey_Update,
    Config_Composition_Data_Status,
    Config_Model_Publication_Set,
    Health_Current_Status,
    Health_Fault_Status,
    Config_Heartbeat_Publication_Status,
    One_Octet_Opcode_Msg_Num_Max,
};

#define FOUNDATION_MODELS_TWO_OCTETS_OPCODE_OFFSET 0x0
enum Foundation_Models_Two_Octets_Opcode
{
    Config_AppKey_Delete = 0x0,
    Config_AppKey_Get ,
    Config_AppKey_List,
    Config_AppKey_Status,
    Health_Attention_Get,
    Health_Attention_Set,
    Health_Attention_Set_Unacknowledged,
    Health_Attention_Status,
    Config_Composition_Data_Get,
    Config_Beacon_Get,
    Config_Beacon_Set,
    Config_Beacon_Status,
    Config_Default_TTL_Get,
    Config_Default_TTL_Set,
    Config_Default_TTL_Status,
    Config_Friend_Get,
    Config_Friend_Set,
    Config_Friend_Status,
    Config_GATT_Proxy_Get,
    Config_GATT_Proxy_Set,
    Config_GATT_Proxy_Status,
    Config_Key_Refresh_Phase_Get,
    Config_Key_Refresh_Phase_Set,
    Config_Key_Refresh_Phase_Status,
    Config_Model_Publication_Get,
    Config_Model_Publication_Status,
    Config_Model_Publication_Virtual_Address_Set,
    Config_Model_Subscription_Add,
    Config_Model_Subscription_Delete,
    Config_Model_Subscription_Delete_All,
    Config_Model_Subscription_Overwrite,
    Config_Model_Subscription_Status,
    Config_Model_Subscription_Virtual_Address_Add,
    Config_Model_Subscription_Virtual_Address_Delete,
    Config_Model_Subscription_Virtual_Address_Overwrite,
    Config_Network_Transmit_Get,
    Config_Network_Transmit_Set,
    Config_Network_Transmit_Status,
    Config_Relay_Get,
    Config_Relay_Set,
    Config_Relay_Status,
    Config_SIG_Model_Subscription_Get,
    Config_SIG_Model_Subscription_List,
    Config_Vendor_Model_SubScription_Get,
    Config_Vendor_Model_SubScription_List,
    Config_Low_Power_Node_PollTimeout_Get,
    Config_Low_Power_Node_PollTimeout_Status,
    Health_Fault_Clear,
    Health_Fault_Clear_Unacknowledged,
    Health_Fault_Get,
    Health_Fault_Test,
    Health_Fault_Test_Unacknowledged,
    Health_Period_Get,
    Health_Period_Set,
    Health_Period_Set_Unacknowledged,
    Health_Period_Status,
    Config_Heartbeat_Publication_Get,
    Config_Heartbeat_Publication_Set,
    Config_Heartbeat_Subscription_Get,
    Config_Heartbeat_Subscription_Set,
    Config_Heartbeat_Subscription_Status,
    Config_Model_App_Bind,
    Config_Model_App_Status,
    Config_Model_App_Unbind,
    Config_NetKey_Add,
    Config_NetKey_Delete,
    Config_NetKey_Get,
    Config_NetKey_List,
    Config_NetKey_Status,
    Config_NetKey_Update,
    Config_Node_Identity_Get,
    Config_Node_Identity_Set,
    Config_Node_Identity_Status,
    Config_Node_Reset,
    Config_Node_Reset_Status,
    Config_SIG_Model_App_Get,
    Config_SIG_Model_App_List,
    Config_Vendor_Model_App_Get,
    Config_Vendor_Model_App_List,
    Two_Octets_Opcode_Msg_Num_Max
};

#define GENERIC_ONOFF_SERVER_MODEL_ID 0x1000
#define GENERIC_ONOFF_CLIENT_MODEL_ID 0x1001
#define GENERIC_ONOFF_OPCODE_OFFSET 0x201
enum Generic_OnOff_Opcode
{
    Generic_OnOff_Get,
    Generic_OnOff_Set,
    Generic_OnOff_Set_Unacknowledged,
    Generic_OnOff_Status,
    Generic_OnOff_Opcode_Max
};

#define GENERIC_LEVEL_OPCODE_OFFSET 0x205
enum Generic_Level_Opcode
{
    Generic_Level_Get,
    Generic_Level_Set,
    Generic_Level_Set_Unacknowledged,
    Generic_Level_Status,
    Generic_Delta_Set,
    Generic_Delta_Unacknowledged,
    Generic_Move_Set,
    Generic_Move_Set_Unacknowledged,
    Generic_Level_Opcode_Max,
};

#define GENERIC_DEFAULT_TRANSITION_TIME_OPCODE_OFFSET 0x20D
enum Generic_Default_Transition_Time_Opcode
{
	Generic_Default_Transition_Time_Get,
	Generic_Default_Transition_Time_Set,
	Generic_Default_Transition_Time_Set_Unacknowledged,
	Generic_Default_Transition_Time_Status,
	Generic_Default_Transition_Time_Opcode_Max
};

#define SENSOR_ONE_OCTET_OPCODE_OFFSET 0x51
enum Sensor_One_Octet_Opcode
{
    Sensor_Descriptor_Status,
    Sensor_Status,
    Sensor_Column_Status,
    Sensor_Series_Status,
    Sensor_One_Octet_Opcode_Max
};

#define SENSOR_TWO_OCTETS_OPCODE_OFFSET 0x230
enum Sensor_Two_Octets_Opcode
{
    Sensor_Descriptor_Get,
    Sensor_Get,
    Sensor_Column_Get,
    Sensor_Series_Get,
    Sensor_Two_Octets_Opcode_Max
};

#define LIGHT_TWO_OCTETS_OPCODE_OFFSET 0x24B
enum Light_Two_Octets_Opcode
{
	Light_Lightness_Get,
	Light_Lightness_Set,
	Light_Lightness_Set_Unacknowledged,
	Light_Lightness_Status,
	
	Light_Lightness_Linear_Get,
	Light_Lightness_Linear_Set,
	Light_Lightness_Linear_Set_Unacknowledged,
	Light_Lightness_Linear_Status,

	Light_Lightness_Last_Get,
	Light_Lightness_Last_Status,
	Light_Lightness_Default_Get,
	Light_Lightness_Default_Status,

	Light_Lightness_Range_Get,
	Light_Lightness_Range_Status,

	Light_Lightness_Default_Set,
	Light_Lightness_Default_Set_Unacknowledged,
	Light_Lightness_Range_Set,
	Light_Lightness_Range_Set_Unacknowledged,

	Light_Ctl_Get,
	Light_Ctl_Set,
	Light_Ctl_Set_Unacknowledged,
	Light_Ctl_Status,
	Light_Ctl_Temperature_Get,
	Light_Ctl_Temperature_Range_Get,
	Light_Ctl_Temperature_Range_Status,
	Light_Ctl_Temperature_Set,
	Light_Ctl_Temperature_Set_Unacknowledged,
	Light_Ctl_Temperature_Status,
	Light_Ctl_Default_Get,
	Light_Ctl_Default_Status,
	Light_Ctl_Default_Set,
	Light_Ctl_Default_Set_Unacknowledged,
	Light_Ctl_Temperature_Range_Set,
	Light_Ctl_Temperature_Range_Set_Unacknowledged,

	Light_Hsl_Get,
	Light_Hsl_Hue_Get,
	Light_Hsl_Hue_Set,
	Light_Hsl_Hue_Set_Unacknowledged,
	Light_Hsl_Hue_Status,
	Light_Hsl_Saturation_Get,
	Light_Hsl_Saturation_Set,
	Light_Hsl_Saturation_Set_Unacknowledged,
	Light_Hsl_Saturation_Status,
	Light_Hsl_Set,
	Light_Hsl_Set_Unacknowledged,
	Light_Hsl_Status,
	Light_Hsl_Target_Get,
	Light_Hsl_Target_Status,
	Light_Hsl_Default_Get,
	Light_Hsl_Default_Status,
	Light_Hsl_Range_Get,
	Light_Hsl_Range_Status,

	Light_Hsl_Default_Set,
	Light_Hsl_Default_Set_Unacknowledged,
	Light_Hsl_Range_Set,
	Light_Hsl_Range_Set_Unacknowledged
	
};

typedef struct
{
    msg_handler_model_t *ptr;
    uint16_t offset;
    uint8_t num;
}msg_map_t;
typedef struct
{
    msg_map_t *msg_map;
    uint16_t size;
}msg_map_array_t;
msg_handler_model_t *mesh_sig_msg_handler_search(uint8_t *access_payload);


#endif



