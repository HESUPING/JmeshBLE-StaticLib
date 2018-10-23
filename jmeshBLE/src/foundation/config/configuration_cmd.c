#include"configuration_cmd.h"
#include"../config/config_client_app.h"
#include"config_server.h"
#include"config_client.h"
#include"../../jmesh/jmesh_print.h"
#include"../state/jmesh_state.h"
#include"../../app/app_include.h"
#include"../../network/jmesh_netkey.h"
#include"../../network/jmesh_seq.h"
#include"../../jmesh/jmesh_addr.h"
#include"../../access/jmesh_access.h"
#include"../../driver/jmesh_uart.h"
cmd_state_t cmd_state = {
		.baudrate = 0,
};

static void config_appkey_update_cmd_handler(int argc,const char** argv);
static void config_beacon_get_cmd_handler(int argc,const char** argv);
static void config_beacon_set_cmd_handler(int argc,const char** argv);
static void config_composition_get_cmd_handler(int argc,const char** argv);
static void config_default_ttl_get_cmd_handler(int argc,const char** argv);
static void config_default_ttl_set_cmd_handler(int argc,const char** argv);
static void config_gatt_proxy_get_cmd_handler(int argc,const char** argv);
static void config_gatt_proxy_set_cmd_handler(int argc,const char** argv);
static void config_friend_get_cmd_handler(int argc,const char** argv);
static void config_friend_set_cmd_handler(int argc,const char** argv);
static void config_relay_get_cmd_handler(int argc,const char** argv);
static void config_relay_set_cmd_handler(int argc,const char** argv);
static void config_publication_get_cmd_handler(int argc,const char** argv);
static void config_publication_set_cmd_handler(int argc,const char** argv);
static void config_publication_virtual_set_cmd_handler(int argc,const char** argv);
static void config_subscription_add_cmd_handler(int argc,const char** argv);
static void config_subscription_virtual_add_cmd_handler(int argc,const char** argv);
static void config_subscription_delete_cmd_handler(int argc,const char** argv);
static void config_subscription_virtual_delete_cmd_handler(int argc,const char** argv);
static void config_subscription_overwrite_cmd_handler(int argc,const char** argv);
static void config_subscription_virtual_overwrite_cmd_handler(int argc,const char** argv);
static void config_subscription_delete_all_cmd_handler(int argc,const char** argv);
static void config_subscription_get_cmd_handler(int argc,const char** argv);
static void config_netkey_add_cmd_handler(int argc,const char** argv);
static void config_netkey_update_cmd_handler(int argc,const char** argv);
static void config_netkey_delete_cmd_handler(int argc,const char** argv);
static void config_netkey_get_cmd_handler(int argc,const char** argv);
static void config_key_refresh_phase_get_cmd_handler(int argc,const char** argv);
static void config_key_refresh_phase_set_cmd_handler(int argc,const char** argv);
static void config_node_identity_get_cmd_handler(int argc,const char** argv);
static void config_node_identity_set_cmd_handler(int argc,const char** argv);
static void config_node_reset_cmd_handler(int argc,const char** argv);
static void config_heartbeat_publication_get_cmd_handler(int argc,const char** argv);
static void config_heartbeat_publication_set_cmd_handler(int argc,const char** argv);
static void config_heartbeat_subscription_get_cmd_handler(int argc,const char** argv);
static void config_heartbeat_subscription_set_cmd_handler(int argc,const char** argv);
static void config_mesh_addr_set_cmd_handler(int argc,const char** argv);
static void config_mac_addr_set_cmd_handler(int argc,const char** argv);
static void config_read_cmd_handler(int argc,const char** argv);
static void config_iv_index_set_cmd_handler(int argc,const char** argv);
static void config_meter_addr_add_cmd_handler(int argc,const char** argv);
static void config_meter_addr_del_cmd_handler(int argc,const char** argv);
static void config_meter_addr_list_cmd_handler(int argc,const char** argv);
static void config_baudrate_set_cmd_handler(int argc,const char** argv);
static void config_model_app_bind_cmd_handler(int argc,const char** argv);
static void config_model_app_unbind_cmd_handler(int argc,const char** argv);
static void config_model_app_get_cmd_handler(int argc,const char** argv);
static void config_appkey_get_cmd_handler(int argc,const char** argv);
static void config_appkey_add_cmd_handler(int argc,const char** argv);
static void config_appkey_delete_cmd_handler(int argc,const char** argv);
static void AT_read_cmd_handler(int argc,const char** argv);
static void AT_mac_cmd_handler(int argc,const char** argv);
static void AT_addr_cmd_handler(int argc,const char** argv);
static void AT_add_nk_cmd_handler(int argc,const char** argv);
static void AT_del_nk_cmd_handler(int argc,const char** argv);
static void AT_get_nk_cmd_handler(int argc,const char** argv);
static void AT_add_ak_cmd_handler(int argc,const char** argv);
static void AT_del_ak_cmd_handler(int argc,const char** argv);
static void AT_get_ak_cmd_handler(int argc,const char** argv);
static void AT_iv_index_cmd_handler(int argc,const char** argv);
static void AT_bind_cmd_handler(int argc,const char** argv);
static void AT_unbind_cmd_handler(int argc,const char** argv);
static void AT_get_bind_cmd_handler(int argc,const char** argv);
static void AT_add_sub_cmd_handler(int argc,const char** argv);
static void AT_del_sub_cmd_handler(int argc,const char** argv);
static void AT_get_sub_cmd_handler(int argc,const char** argv);
static void AT_baud_set_cmd_handler(int argc,const char** argv);
static void AT_tricolor_set_cmd_handler(int argc,const char** argv);
static void AT_realcomm_config_addr_cmd_handler(int argc,const char** argv);
static void AT_realcomm_config_baud_cmd_handler(int argc,const char** argv);
static void AT_realcomm_config_addr_get_cmd_handler(int argc,const char** argv);

typedef struct st_jmesh_cmd{
    void(*handler)(int argc,const char** argv);
    char* cmd;
    char* desc;
    char* demo;
}jmesh_cmd_t;
jmesh_cmd_t jmesh_cmd_table[]={
		{AT_read_cmd_handler,           "AT+READ",          "-all",	        "AT+READ:all"},
		{AT_mac_cmd_handler,            "AT+MAC",           "-mac",	        "AT+MAC:12345678"},
		{AT_addr_cmd_handler,           "AT+ADDR",          "-addr",	        "AT+ADDR:10"},
		{AT_add_nk_cmd_handler,         "AT+ADD_NK", 				"-ni,-key",       "AT+ADD_NK:100,11223344556677889900112233445566"},
		{AT_del_nk_cmd_handler,         "AT+DEL_NK",   			"-ni",       "AT+DEL_NK:100"},
    {AT_get_nk_cmd_handler,         "AT+GET_NK",   		"-ni",                "AT+DEL_NK:100"},
    {AT_add_ak_cmd_handler,         "AT+ADD_AK",   		 "-ni,-ai,-key",   "AT+ADD_AK:0,100,123456789011223344556677889900AA"},
    {AT_del_ak_cmd_handler,         "AT+DEL_AK",    	"-ni,-ai",   "AT+DEL_AK:0,100"},
    {AT_get_ak_cmd_handler,         "AT+GET_AK",      	",-ni",         "AT+GET_AK:0"},
    {AT_iv_index_cmd_handler,       "AT+IV_INDEX",       "-iv_index",	        "AT+IV_INDEX:0x12345678"},
    {AT_bind_cmd_handler,           "AT+BIND",            "-e,-model,-ai",  "AT+BIND:1,4,100"},
    {AT_unbind_cmd_handler,         "AT+UNBIND",          "-e,-model,-ai","AT+UNBIND:1,4,100"},
    {AT_get_bind_cmd_handler,       "AT+GET_BIND",        "e,-model",       "AT+GET_BIND:1,4"},
    {AT_add_sub_cmd_handler, 				"AT+ADD_SUB",				"e,-model,-addr","AT+ADD_SUB:1,4,10"},
    {AT_del_sub_cmd_handler,        "AT+DEL_SUB",       "-e,-addr,-model","AT+DEL_SUB:1,4,10"},
    {AT_get_sub_cmd_handler,        "AT+GET_SUB",        "-e,-model",      "AT+GET_SUB:1,4"},
    {AT_baud_set_cmd_handler,              "AT+BAUD_SET",          "-dest",	        "config addr set"},		
    {AT_tricolor_set_cmd_handler,        "AT+TRICOLOR_SET",        " ",      " "},
    {AT_realcomm_config_addr_cmd_handler,        "AT+REAL_CFG_ADDR",        " ",      " "},
    {AT_realcomm_config_addr_get_cmd_handler,        "AT+REAL_CFG_ADDR_GET",        " ",      " "},		
    {AT_realcomm_config_baud_cmd_handler,        "AT+REAL_CFG_BAUD",        " ",      " "},

    {config_netkey_add_cmd_handler,                 "config netkey add", 			"-dest,-ni,-key",       ""},
    {config_netkey_delete_cmd_handler,              "config netkey delete",   "-dest,-ni,-key",       ""},
    {config_netkey_update_cmd_handler,              "config netkey update", 	"-dest,-ni,-key",       ""},
    {config_netkey_get_cmd_handler,                 "config netkey get",   		"-dest",                "config netkey get:1"},
    {config_appkey_add_cmd_handler,                 "config appkey add",   		 "-dest,-ni,-ai,-key",   ""},
    {config_appkey_delete_cmd_handler,              "config appkey delete",    "-dest,-ni,-ai,-key",   ""},
    {config_appkey_get_cmd_handler,                 "config appkey get",      "-dest,-index",         "config appkey get:1,0"},
    {config_iv_index_set_cmd_handler,              "config iv index set",          "-dest",	        "config addr set"},
    {config_model_app_bind_cmd_handler,             "config model app bind",            "-dest,-e,-ai,-model",  "config model app bind:1,1,123,bcbd,7"},
    {config_model_app_unbind_cmd_handler,           "config model app unbind",          "-dest,-e,-ai,-model",  "config model app unbind:1,1,123,7"},
    {config_model_app_get_cmd_handler,              "config model app get",             "-dest,e,-model",       "config model app get:1,1,1"},
    {config_subscription_add_cmd_handler, 					"config subscription add",				"-dest,-addr,-addr,-period","config heartbeat subscription set:1,2,1,1"},
    {config_subscription_delete_cmd_handler,        "config subscription delete",       "-dest,-e,-addr,-model","config subscription delete:1,1,2,bcbd,7"},
    {config_subscription_get_cmd_handler,           "config subscription get",          "-dest,-e,-model",      "config subscription get:1,1,bcbd,7"},

//    {config_mac_addr_set_cmd_handler,              "config mac addr set",          "-dest",	        "config mac addr set"},
//    {config_mesh_addr_set_cmd_handler,              "config mesh addr set",          "-dest",	        "config addr set"},
//    {config_appkey_add_cmd_handler,                 "config appkey add",                "-dest,-ni,-ai,-key",   "config appkey add:1,0,123,00112233445566778899aabbccddeeff"},
    {config_appkey_update_cmd_handler,              "config appkey update",             "-dest,-ni,-ai,-key",   "config appkey update:1,0,123,112233445566778899aabbccddeeff00"},
    {config_appkey_delete_cmd_handler,              "config appkey delete",             "-dest,-ni,-ai",        "config appkey delete:1,0,123"},
    {config_beacon_get_cmd_handler,                 "config beacon get",                "-dest",                "config beacon get:1"},
    {config_beacon_set_cmd_handler,                 "config beacon set",                "-dest,-state",         "config beacon set:1,1"},
    {config_composition_get_cmd_handler,            "config composition get",           "-dest,-page",          "config composition get:1,0"},
    {config_default_ttl_get_cmd_handler,            "config default ttl get",           "-dest",                "config default ttl get:1"},
    {config_default_ttl_set_cmd_handler,            "config default ttl set",           "-dest,-ttl",           "config default ttl set:1,5"},
    {config_gatt_proxy_get_cmd_handler,             "config gatt proxy get",            "-dest",                "config gatt proxy get:1"},
    {config_gatt_proxy_set_cmd_handler,             "config gatt proxy set",            "-dest,-state",         "config gatt proxy set:1,1"},
    {config_friend_get_cmd_handler,                 "config friend get",                "-dest",                "config friend get:1"},
    {config_friend_set_cmd_handler,                 "config friend set",                "-dest,-state",         "config friend set:1,1"},
    {config_relay_get_cmd_handler,                  "config relay get",                 "-dest",                "config relay get:1"},
    {config_relay_set_cmd_handler,                  "config relay set",                 "-dest,-state",         "config relay set:1,1"},
    {config_publication_get_cmd_handler,            "config publication get",           "-dest,-e,-model",      "config publication get:1,1,bcbd,7"},
    {config_publication_set_cmd_handler,            "config publication set",           "-dest,-e,-addr,-ai,-credentialFlag,-ttl,-period,-retransmitCount,-retransmitInterval,-model","config publication set:1,1,2,123,1,5,0,1,bcbd,123"},
    {config_publication_virtual_set_cmd_handler,    "config publication virtual set",   "-dest,-e,-vaddr,-ai,-credentialFlag,-ttl,-period,-retransmitCount,-retransmitInterval,-model","config publication virtual set:1,1,0102030405060708090a0b0c0d0e0f10,123,1,5,0,1,bcbd,123"},

//    {config_subscription_add_cmd_handler,           "config subscription add",          "-dest,-e,-addr,-model","config subscription add:1,1,2,bcbd,7"},
    {config_subscription_virtual_add_cmd_handler,   "config subscription virtual add",  "-dest,-e,-vaddr,-model","config subscription virtual add:1,1,0102030405060708090a0b0c0d0e0f10,bcbd,7"},
    {config_subscription_virtual_delete_cmd_handler,"config subscription virtual delete","-dest,-e,-vaddr,-model","config subscription virtual delete:1,1,0102030405060708090a0b0c0d0e0f10,bcbd,7"},
    {config_subscription_overwrite_cmd_handler,     "config subscription overwrite",    "-dest,-e,-addr,-model","config subscription overwrite:1,1,2,bcbd,7"},
    {config_subscription_virtual_overwrite_cmd_handler,"config subscription virtual overwrite","-dest,-e,-vaddr,-model","config subscription virtual overwrite:1,1,0102030405060708090a0b0c0d0e0f10,bcbd,7"},
    {config_subscription_delete_all_cmd_handler,    "config subscription delete all",   "-dest,-e,-model",      "config subscription delete all:1,1,bcbd,7"},


//    {config_netkey_add_cmd_handler,                 "config netkey add",                "-dest,-ni,-key",       "config netkey add:1,1,112233445566778899aabbccddeeff00"},
    {config_netkey_update_cmd_handler,              "config netkey update",             "-dest,-ni,-key",       "config netkey update:1,1,00112233445566778899aabbccddeeff"},
    {config_key_refresh_phase_get_cmd_handler,      "config key refresh phase get",           "-dest,-ni",            "config key refresh phase get:1,1"},
    {config_key_refresh_phase_set_cmd_handler,      "config key refresh phase set",           "-dest,-ni,-phase",     "config key refresh phase set:1,1,1"},
    {config_node_identity_get_cmd_handler,          "config node identity get",         "-dest,-ni",            "config node identity get:1,1"},
    {config_node_identity_set_cmd_handler,          "config node identity set",         "-dest,-ni,-identity",  "config node identity set:1,1,1"},

    {config_node_reset_cmd_handler,                 "config node reset",            "-dest",                "config node reset:1"},
    {config_heartbeat_publication_get_cmd_handler,  "config heartbeat publication get", "-dest",                "config heartbeat publication get:1"},
    {config_heartbeat_publication_set_cmd_handler,  "config heartbeat publication set", "-dest,-addr,-countLog,-period,-ttl-feature,-ni","config heartbeat publication set:1,2,1,1,0,3,0"},
    {config_heartbeat_subscription_get_cmd_handler, "config heartbeat subscription get","-dest",                "config heartbeat subscription get:1"},
//    {config_heartbeat_subscription_set_cmd_handler, "config heartbeat subscription set","-dest,-addr,-addr,-period","config heartbeat subscription set:1,2,1,1"},

};


#define JMESH_CMD_TABLE_SIZE (sizeof(jmesh_cmd_table)/sizeof(jmesh_cmd_t))
void configuration_cmd_process(unsigned char length,unsigned char* data)
{
  int i;
	int argc = 0;
	char* cmd;
	char* argv[15];
	if(memcmp("AT+",data,3)==0)	
	{
			jmesh_uart_send(JMESH_UART_0,length,data);
			print_cmd("\n");
	}
	
	cmd = strtok((char*)data, ":");
	for(i=0;i<JMESH_CMD_TABLE_SIZE;i++){
        if(0 == strcmp(cmd,jmesh_cmd_table[i].cmd)){
            for(argc=0;argc<15;argc++){
                if(NULL==(argv[argc]=strtok(NULL,","))){
                    break;
                }
            }
            jmesh_cmd_table[i].handler(argc,(const char**)argv);
            return;
        }
	}
}

static void AT_baud_set_cmd_handler(int argc,const char** argv)
{
   if(argc == 1)
	 {
			cmd_state.baudrate = strtol(argv[0],NULL,0);
#if(JMESH_DRIVER_BX2400 == 1)
			if(jmesh_uart_baudrate_set(cmd_state.baudrate)<0) return ;
#endif
			jmesh_save_write(JMESH_SAVE_BAUTRATE,sizeof(unsigned long),(unsigned char*)&cmd_state.baudrate);
	 }
}

int str_to_hex(const char* str,unsigned char hex_size,unsigned char* hex)
{
    int i,j;
    for(i=0,j=0;str[i]!='\0'&&j<hex_size;i+=2,j++){
        if(str[i]<='9')
            hex[j]=str[i]-'0';
        else if(str[i]<='F')
            hex[j]=str[i]-'A'+10;
        else
            hex[j]=str[i]-'a'+10;
        if(str[i+1]=='\0'){
            j++;
            break;
        }
        hex[j]<<=4;

        if(str[i+1]<='9')
            hex[j]|=str[i+1]-'0';
        else if(str[i+1]<='F')
            hex[j]|=str[i+1]-'A'+10;
        else
            hex[j]|=str[i+1]-'a'+10;
    }
    return j;
}

static void config_meter_addr_add_cmd_handler(int argc,const char** argv)
{
//    unsigned short mesh_addr = 0;
//    if(argc==1){
//				mesh_addr = strtol(argv[0],NULL,0);
//				gateway_meter_num++;
//				for(int i=0;i<GATEWAY_ADDR_NUM;i++)
//				{
//						if(mesh_addr == cmd_state.meter_list[i]) break;
//						if(cmd_state.meter_list[i] == 0)
//						{
//								cmd_state.meter_list[i] = mesh_addr;
//								jmesh_save_buffer_write(JMESH_SAVE_GATEWAY_METER_LIST,i,sizeof(unsigned short),(unsigned char*)&cmd_state.meter_list[i]);
//								print_cmd("meter add addr:%d success!\n",cmd_state.meter_list[i]);
//								break;
//						}
//				}
//    }
}
static void config_meter_addr_del_cmd_handler(int argc,const char** argv)
{
//    unsigned short mesh_addr = 0;
//    if(argc==1){
//				mesh_addr = strtol(argv[0],NULL,0);
//				gateway_meter_num--;
//				for(int i=0;i<GATEWAY_ADDR_NUM;i++)
//				{
//						if(cmd_state.meter_list[i] == mesh_addr)
//						{
//								cmd_state.meter_list[i] = 0;
//								jmesh_save_buffer_write(JMESH_SAVE_GATEWAY_METER_LIST,i,sizeof(unsigned short),(unsigned char*)&cmd_state.meter_list[i]);
//								print_cmd("meter del addr:%d success!\n",cmd_state.meter_list[i]);
//								break;
//						}
//				}
//    }

}
static void config_meter_addr_list_cmd_handler(int argc,const char** argv)
{
//    unsigned short mesh_addr = 0;
//    if(argc==0){
//				for(int i=0;i<GATEWAY_ADDR_NUM;i++)
//				{
//						jmesh_save_buffer_read(JMESH_SAVE_GATEWAY_METER_LIST,i,sizeof(unsigned short),(unsigned char*)&cmd_state.meter_list[i]);
//						if(cmd_state.meter_list[i] != 0)
//						{
//								print_cmd("meter list addr:%d\n",cmd_state.meter_list[i] );
//						}
//				}
//    }
}

static void AT_mac_cmd_handler(int argc,const char** argv)
{
		if(argc == 1)
		{
				unsigned char mac[6] = {0};
				print_cmd("set mac is:%s\n",argv[0]);
				str_to_hex(argv[0],6,mac);
				jmesh_mac_set(mac);
				return ;
		}
		print_cmd("error:argc num invalid!\n");
}

static void AT_iv_index_cmd_handler(int argc,const char** argv)
{
		unsigned long iv_index = 0;
		unsigned short netkey_index = 0xfff;
    if(argc==2){
				netkey_index = strtol(argv[0],NULL,0);
				iv_index = strtol(argv[1],NULL,0);
				jmesh_netkey_test_set_iv_index(netkey_index,iv_index);
				print_cmd("set iv_index is :0x%x\n",iv_index);
				return ;
    }
		print_cmd("error:argc num error!\n");
}
static void AT_read_cmd_handler(int argc,const char** argv)
{
		jmesh_mac_t mac;
		unsigned short netkey_index = 0xfff;
		unsigned short appkey_index = 0xfff;
		unsigned char buffer[100] = {0};
		netkey_index = strtol(argv[0],NULL,0);
//		int length = jmesh_appkey_list(netkey_index,sizeof(buffer),buffer);
		appkey_index = buffer[0] + (buffer[1]<<8);

		if(memcmp(argv[0],"ALL",strlen("ALL"))==0)
		{
				jmesh_mac_get(mac);
				print_buffer_cmd(6,mac,"Jmesh mac:");
				print_cmd("Jmesh addr: %d\n",jmesh_get_primary_addr());
				print_cmd("Jmesh iv_index = 0x%08x\n",jmesh_netkey_get_iv_index(netkey_index));
				print_cmd("Jmesh seq = 0x%x\n",jmesh_seq_get());
				if(jmesh_netkey_get_by_index(netkey_index)==NULL)
				{
						print_cmd("invalid netkey_index!\n");
						return ;
				}
				print_buffer_cmd(16,jmesh_netkey_get_by_index(netkey_index)->key[0],"Netkey: ");
//				if(appkey_index == 0)
//				{
//						print_cmd("no valid appkey!\n");
//				}else
//						print_buffer_cmd(16,jmesh_appkey_get_by_key_index(netkey_index,appkey_index)->key,"Appkey_index = %d, Appkey: ",appkey_index);
		}
}
static void AT_addr_cmd_handler(int argc,const char** argv)
{
    unsigned short mesh_addr = 0;
    if(argc==1){
				mesh_addr = strtol(argv[0],NULL,0);
				jmesh_set_primary_addr(mesh_addr);
				print_cmd("set mesh addr is :%d\n",mesh_addr);
    }
}
static void AT_add_nk_cmd_handler(int argc,const char** argv)
{
    unsigned short netkey_index=0;
    unsigned char key[16];
    if(argc==2){
				netkey_index = strtol(argv[0],NULL,0);
        str_to_hex(argv[1],16,key);

				jmesh_netkey_state_set(netkey_index,key);
				print_buffer_cmd(16,key,"set netkey index is:%d,netkey is: ",netkey_index);
				return ;
    }
		print_cmd("error: netkey add argc num error!\n");
}
static void AT_del_nk_cmd_handler(int argc,const char** argv)
{
    unsigned short netkey_index=0;
    if(argc==1){
				netkey_index = strtol(argv[0],NULL,0);
				jmesh_netkey_state_del(netkey_index);
				print_cmd("delete netkey successed!\n");
    }
}
static void AT_get_nk_cmd_handler(int argc,const char** argv)
{
    if(argc==1){
				unsigned short netkey_index = strtol(argv[0],NULL,0);
				jmesh_netkey_t* ret = jmesh_netkey_get_by_index(netkey_index);
				if(ret != NULL)
				{
						print_buffer_cmd(16,ret->key[0],"get netkey is :");
				}else {
						print_cmd("warning:no vaild netkey_key!\n");
				}
    }
}
static void AT_add_ak_cmd_handler(int argc,const char** argv)
{
    unsigned short netkey_index=0,appkey_index=0;
    unsigned char key[16];
    if(argc==3){
        netkey_index = strtol(argv[0],NULL,0);
				appkey_index = strtol(argv[1],NULL,0);
        str_to_hex(argv[2],16,key);
				int ret = jmesh_appkey_set(netkey_index,appkey_index,key);
				if(ret == JMESH_STATUS_SUCCESS)
						print_buffer_cmd(16,key,"set appkey index is %d, appkey is:",appkey_index);
				else
					print_cmd("warning: appkey storage failed!\n");
    }
}
static void AT_del_ak_cmd_handler(int argc,const char** argv)
{
   unsigned short netkey_index=0,appkey_index=0 ;

	 if(argc ==2)
	 {
        netkey_index = strtol(argv[0],NULL,0);
				appkey_index = strtol(argv[1],NULL,0);
				jmesh_appkey_delete(netkey_index,appkey_index);
				print_cmd("delete appkey_index %d successed!\n",appkey_index);
	 }
}
static void AT_get_ak_cmd_handler(int argc,const char** argv)
{
    unsigned short netkey_index=0xfff,appkey_index = 0;
    if(argc==2){
				netkey_index = strtol(argv[0],NULL,0);
				appkey_index = strtol(argv[1],NULL,0);
				jmesh_appkey_t* ret = jmesh_appkey_get_by_key_index(netkey_index,appkey_index);
				// judge if ret is valid
				if(ret == NULL)
				{
						print_cmd("warning: no valid appkey!!!\n");
						return ;
				}
				print_buffer_cmd(16,ret->key,"get appkey is:");
    }
}
static void AT_bind_cmd_handler(int argc,const char** argv)
{
    unsigned short element_addr=0,appkey_index=0;
		jmesh_model_id_t model_id;
		model_id.company_id = JMESH_MODEL_COMPANY_ID;

    if(argc==3){
				element_addr = strtol(argv[0],NULL,0);
				model_id.model_id = strtol(argv[1],NULL,0);
        appkey_index = strtol(argv[2],NULL,0);
				element_addr -= jmesh_get_primary_addr();			
				int ret = jmesh_model_bind_app(jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element_addr),model_id.company_id,model_id.model_id),jmesh_appkey_get_by_index(appkey_index));
				if(JMESH_STATUS_SUCCESS == ret)
						print_cmd("set bind appkey :element= %d,model= %d,appkey_index= %d \n",element_addr,model_id.model_id,appkey_index);
				else
						print_cmd("bind appkey storage failed!\n");
		}
}
static void AT_unbind_cmd_handler(int argc,const char** argv)
{
    unsigned short element_addr=0,appkey_index=0;
		jmesh_model_id_t model_id;
		model_id.company_id = JMESH_MODEL_COMPANY_ID;
		if(argc==3){
				element_addr = strtol(argv[0],NULL,0);
				model_id.model_id = strtol(argv[1],NULL,0);
        appkey_index = strtol(argv[2],NULL,0);
				element_addr -= jmesh_get_primary_addr();
				int ret = jmesh_model_unbind_app(jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element_addr),model_id.company_id,model_id.model_id),jmesh_appkey_get_by_index(appkey_index));
				if(JMESH_STATUS_SUCCESS == ret)
						print_cmd("set unbind appkey :element= %d,model= %d,appkey_index= %d \n",element_addr,model_id.model_id,appkey_index);
				else
						print_cmd("unbind appkey storage failed!\n");
		}
}

static void AT_get_bind_cmd_handler(int argc,const char** argv)
{
    unsigned short element_addr=0;
		unsigned char ret_buffer[100] = {0};
		jmesh_model_id_t model_id;
		model_id.company_id = JMESH_MODEL_COMPANY_ID;

    if(argc==2){
				element_addr = strtol(argv[0],NULL,0);
				model_id.model_id = strtol(argv[1],NULL,0);
				element_addr -= jmesh_get_primary_addr();
				int length =  jmesh_model_bind_list(jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element_addr),model_id.company_id,model_id.model_id),sizeof(ret_buffer), ret_buffer);
				if(length>0)
						print_buffer_cmd(length,ret_buffer,"get bind appkey is :");
				else
						print_cmd("no valid bind appkey!\n");
		}
}
static void AT_add_sub_cmd_handler(int argc,const char** argv)
{
    unsigned short element=0,address;
		jmesh_model_id_t model_id;
		model_id.company_id = JMESH_MODEL_COMPANY_ID;
    if(argc==3){
        element = strtol(argv[0],NULL,0);
			  model_id.model_id = strtol(argv[1],NULL,0);
				address = strtol(argv[2],NULL,0);
				element -= jmesh_get_primary_addr();
				int ret = jmesh_model_subscription_list_add(jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id),address);
				if(ret == JMESH_STATUS_SUCCESS)
						print_cmd("add subscription address:element= %d,model= %d,address = %d \n",element,model_id.model_id,address);
				else
						print_cmd("add subscription address storage failed!\n");
    }
}
static void AT_del_sub_cmd_handler(int argc,const char** argv)
{
    unsigned short element=0,address;
		jmesh_model_id_t model_id;
		model_id.company_id = JMESH_MODEL_COMPANY_ID;
		if(argc==3){
				element = strtol(argv[0],NULL,0);
        model_id.model_id = strtol(argv[1],NULL,0);
        address = strtol(argv[2],NULL,0);
				element -= jmesh_get_primary_addr();
				int ret = jmesh_model_subscription_list_remove(jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id),address);
				if(ret == JMESH_STATUS_SUCCESS)
						print_cmd("delete subscription address:element= %d,model= %d,address= %d \n",element,model_id.model_id,address);
				else
						print_cmd("add subscription address storage failed!\n");
    }
}
static void AT_get_sub_cmd_handler(int argc,const char** argv)
{
    unsigned short element=0;
		jmesh_model_id_t model_id;
		model_id.company_id = JMESH_MODEL_COMPANY_ID;
		unsigned short address[10] = {0};
    if(argc==2){
        element = strtol(argv[0],NULL,0);
        model_id.model_id = strtol(argv[1],NULL,0);
				element -= jmesh_get_primary_addr();
				unsigned char len = jmesh_model_subscription_list(jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(element),model_id.company_id,model_id.model_id),(unsigned char*)address);
//				unsigned short addr = jmesh_state_get_default_subscription(jmesh_get_model_instance(element,model));
				if(len == 0)
				{
						print_cmd("no valid subscription address!\n");
				}
				for(int i=0;i<len/2;i++)
				{
						print_cmd("get subscription address is : %d\n",address[i]);
				}
    }
}
static void AT_realcomm_config_addr_get_cmd_handler(int argc,const char** argv)
{
		print_cmd("get realcomm config addr is %d\n",realcomm_config_addr_get());
}
static void AT_tricolor_set_cmd_handler(int argc,const char** argv)
{
		unsigned char pwm_value[4];
		unsigned char pwm_nums;
		if(argc == 4)
		{		
				pwm_nums = strtol(argv[0],NULL,0);
				pwm_value[0] = strtol(argv[1],NULL,0);
				pwm_value[1] = strtol(argv[2],NULL,0);
				pwm_value[2] = strtol(argv[3],NULL,0);
				light_client_control(jmesh_get_primary_addr()+1 ,0,1,pwm_nums, pwm_value);
		}
}
static void AT_realcomm_config_addr_cmd_handler(int argc,const char** argv)
{
		if(argc == 1)
		{
				unsigned short addr = strtol(argv[0],NULL,0);
				print_cmd("set realcomm config addr is %d\n",addr);
				realcomm_config_client(jmesh_get_primary_addr()+1,0,1,addr);
		}
}
static void AT_realcomm_config_baud_cmd_handler(int argc,const char** argv)
{
		if(argc == 1)
		{
				unsigned short baud = strtol(argv[0],NULL,0);
				print_cmd("set realcomm config baud = %d\n",baud);
				realcomm_config_server(realcomm_config_addr_get()+1,0,1,baud,0);
		}	
}

static void config_appkey_update_cmd_handler(int argc,const char** argv)
{
    unsigned short dst=0,netkey_index=0,appkey_index=0;
    unsigned char key[16];
    if(argc==4){
        dst = strtol(argv[0],NULL,0);
        netkey_index = strtol(argv[1],NULL,0);
				appkey_index = strtol(argv[2],NULL,0);
        str_to_hex(argv[3],16,key);
        config_appkey_update(dst,netkey_index,appkey_index,key);
    }
}
static void config_netkey_add_cmd_handler(int argc,const char** argv)
{
    unsigned char key[16] = {0};
    if(argc == 3)
    {
        unsigned short dst = strtol(argv[0],NULL,0);
        unsigned short netkey_index = strtol(argv[1],NULL,0);
        str_to_hex(argv[2],16,key);
        config_netkey_add(dst,netkey_index,key);
    }
}
static void config_netkey_delete_cmd_handler(int argc,const char** argv)
{
		if(argc == 2)
		{
				unsigned short dst = strtol(argv[0],NULL,0);
				unsigned short netkey_index = strtol(argv[1],NULL,0);
				config_netkey_delete(dst,netkey_index);
		}
}
static void config_netkey_update_cmd_handler(int argc,const char** argv)
{
    unsigned short dst=0,netkey_index=0;
    unsigned char key[16];
    if(argc==3){
        dst = strtol(argv[0],NULL,0);
				netkey_index = strtol(argv[1],NULL,0);
        str_to_hex(argv[2],16,key);
        config_netkey_update(dst,netkey_index,key);
    }
}
static void config_netkey_get_cmd_handler(int argc,const char** argv)
{
		if(argc == 2)
		{
				unsigned short dst = strtol(argv[0],NULL,0);
				unsigned short netkey_index = strtol(argv[1],NULL,0);
				config_netkey_get(dst,netkey_index);
		}
}
static void config_appkey_add_cmd_handler(int argc,const char** argv)
{
	    unsigned char key[16];
		if(argc == 4)
		{
            unsigned short dst = strtol(argv[0],NULL,0);
            unsigned short netkey_index = strtol(argv[1],NULL,0);
            unsigned short appkey_index = strtol(argv[2],NULL,0);
            str_to_hex(argv[3],16,key);
            config_appkey_add(dst,netkey_index,appkey_index,key);
		}
}
static void config_appkey_delete_cmd_handler(int argc,const char** argv)
{
		if(argc == 3)
		{
				unsigned short dst = strtol(argv[0],NULL,0);
				unsigned short netkey_index = strtol(argv[1],NULL,0);
				unsigned short appkey_index = strtol(argv[2],NULL,0);
				config_appkey_delete(dst,netkey_index,appkey_index);
		}
}
static void config_appkey_get_cmd_handler(int argc,const char** argv)
{
		if(argc == 3)
		{
				unsigned short dst = strtol(argv[0],NULL,0);
				unsigned short netkey_index = strtol(argv[1],NULL,0);
				config_appkey_get(dst,netkey_index);
		}
}
static void config_iv_index_set_cmd_handler(int argc,const char** argv)
{

}
static void config_model_app_bind_cmd_handler(int argc,const char** argv)
{
		jmesh_model_id_t model_id ;
		model_id.company_id =	JMESH_MODEL_COMPANY_ID;
		if(argc == 5)
		{
				unsigned short dst = strtol(argv[0],NULL,0);
				unsigned short element = strtol(argv[1],NULL,0);
				model_id.model_id		 =  strtol(argv[2],NULL,0);
				unsigned short netkey_index = strtol(argv[3],NULL,0);
				unsigned short appkey_index = strtol(argv[4],NULL,0);
				config_model_app_bind(dst,element,netkey_index,appkey_index,&model_id);
		}
}
static void config_model_app_unbind_cmd_handler(int argc,const char** argv)
{
		jmesh_model_id_t model_id ;
		model_id.company_id =	JMESH_MODEL_COMPANY_ID;
		if(argc == 5)
		{
				unsigned short dst = strtol(argv[0],NULL,0);
				unsigned short element = strtol(argv[1],NULL,0);
				model_id.model_id		 =  strtol(argv[2],NULL,0);
				unsigned short netkey_index = strtol(argv[3],NULL,0);
				unsigned short appkey_index = strtol(argv[4],NULL,0);
				config_model_app_unbind(dst,element,netkey_index,appkey_index,&model_id);
		}
}
static void config_model_app_get_cmd_handler(int argc,const char** argv)
{
		jmesh_model_id_t model_id ;
		model_id.company_id =	JMESH_MODEL_COMPANY_ID;
		if(argc == 4)
		{
				unsigned short dst = strtol(argv[0],NULL,0);
				unsigned short element = strtol(argv[1],NULL,0);
				model_id.model_id		 =  strtol(argv[2],NULL,0);
				unsigned short netkey_index = strtol(argv[3],NULL,0);
				config_vendor_model_app_get(dst,element,netkey_index,&model_id);
		}
}
static void config_subscription_add_cmd_handler(int argc,const char** argv)
{
		jmesh_model_id_t model_id ;
		model_id.company_id =	JMESH_MODEL_COMPANY_ID;
		if(argc == 5)
		{
				unsigned short dst = strtol(argv[0],NULL,0);
				unsigned short element = strtol(argv[1],NULL,0);
				model_id.model_id		 =  strtol(argv[2],NULL,0);
				unsigned short netkey_index = strtol(argv[3],NULL,0);
				unsigned short addr = strtol(argv[4],NULL,0);
				config_model_subscription_add(dst,element,netkey_index,addr,&model_id);
		}
}
static void config_subscription_delete_cmd_handler(int argc,const char** argv)
{
		jmesh_model_id_t model_id ;
		model_id.company_id =	JMESH_MODEL_COMPANY_ID;
		if(argc == 5)
		{
				unsigned short dst = strtol(argv[0],NULL,0);
				unsigned short element = strtol(argv[1],NULL,0);
				model_id.model_id		 =  strtol(argv[2],NULL,0);
				unsigned short netkey_index = strtol(argv[3],NULL,0);
				unsigned short addr = strtol(argv[4],NULL,0);
				config_model_subscription_delete(dst,element,netkey_index,addr,&model_id);
		}
}
static void config_subscription_get_cmd_handler(int argc,const char** argv)
{
		jmesh_model_id_t model_id ;
		model_id.company_id =	JMESH_MODEL_COMPANY_ID;
		if(argc == 4)
		{
				unsigned short dst = strtol(argv[0],NULL,0);
				unsigned short element = strtol(argv[1],NULL,0);
				model_id.model_id		 =  strtol(argv[2],NULL,0);
				unsigned short netkey_index = strtol(argv[3],NULL,0);
				config_vendor_model_subscription_get(dst,element,netkey_index,&model_id);
		}
}

static void config_beacon_get_cmd_handler(int argc,const char** argv)
{
}
static void config_beacon_set_cmd_handler(int argc,const char** argv)
{
}

static void config_composition_get_cmd_handler(int argc,const char** argv)
{
}

static void config_default_ttl_get_cmd_handler(int argc,const char** argv)
{
}
static void config_default_ttl_set_cmd_handler(int argc,const char** argv)
{
}

static void config_gatt_proxy_get_cmd_handler(int argc,const char** argv)
{
}
static void config_gatt_proxy_set_cmd_handler(int argc,const char** argv)
{
}

static void config_friend_get_cmd_handler(int argc,const char** argv)
{
}
static void config_friend_set_cmd_handler(int argc,const char** argv)
{
}

static void config_relay_get_cmd_handler(int argc,const char** argv)
{
}
static void config_relay_set_cmd_handler(int argc,const char** argv)
{
}

static void config_publication_get_cmd_handler(int argc,const char** argv)
{

}


static void config_publication_set_cmd_handler(int argc,const char** argv)
{

}
static void config_publication_virtual_set_cmd_handler(int argc,const char** argv)
{

}

static void config_subscription_virtual_add_cmd_handler(int argc,const char** argv)
{

}

static void config_subscription_virtual_delete_cmd_handler(int argc,const char** argv)
{

}
static void config_subscription_overwrite_cmd_handler(int argc,const char** argv)
{
		jmesh_model_id_t model_id ;
		model_id.company_id =	JMESH_MODEL_COMPANY_ID;
		if(argc == 5)
		{
				unsigned short dst = strtol(argv[0],NULL,0);
				unsigned short element = strtol(argv[1],NULL,0);
				model_id.model_id		 =  strtol(argv[2],NULL,0);
				unsigned short netkey_index = strtol(argv[3],NULL,0);
				unsigned short addr = strtol(argv[4],NULL,0);
				config_model_subscription_overwrite(dst,element,netkey_index,addr,&model_id);
		}
}
static void config_subscription_virtual_overwrite_cmd_handler(int argc,const char** argv)
{

}
static void config_subscription_delete_all_cmd_handler(int argc,const char** argv)
{
		jmesh_model_id_t model_id;
		model_id.company_id = JMESH_MODEL_COMPANY_ID;
    if(argc==4){
        unsigned short dst = strtol(argv[0],NULL,0);
				model_id.model_id = strtol(argv[1],NULL,0);
        unsigned short element = strtol(argv[2],NULL,0);
				unsigned short netkey_index = strtol(argv[3],NULL,0);
			  config_model_subscription_delete_all(dst,element,netkey_index,&model_id);

    }
}


static void config_key_refresh_phase_get_cmd_handler(int argc,const char** argv)
{
//    unsigned short dst=0,netkey_index=0;
//    if(argc==2){
//        dst = strtol(argv[0],NULL,0);
//				netkey_index = strtol(argv[1],NULL,0);
//				config_key_refresh_phase_get(dst,netkey_index);
//		}
}
static void config_key_refresh_phase_set_cmd_handler(int argc,const char** argv)
{
//    unsigned short dst=0,netkey_index=0,phase=0;
//    if(argc==3){
//        dst = strtol(argv[0],NULL,0);
//				netkey_index = strtol(argv[1],NULL,0);
//				phase = strtol(argv[2],	NULL,0);
//				config_key_refresh_phase_set(dst,netkey_index,phase);
//		}
}

static void config_node_identity_get_cmd_handler(int argc,const char** argv)
{
    unsigned short dst=0,netkey_index=0;
    if(argc==2){
        dst = strtol(argv[0],NULL,0);
				netkey_index = strtol(argv[1],NULL,0);
				config_node_identity_get(dst,netkey_index);
		}
}
static void config_node_identity_set_cmd_handler(int argc,const char** argv)
{
    unsigned short dst=0,netkey_index=0,identity=0;
    if(argc==3){
        dst = strtol(argv[0],NULL,0);
				netkey_index = strtol(argv[1],NULL,0);
				identity = strtol(argv[2],NULL,0);
				config_node_identity_set(dst,netkey_index,identity);
		}
}

static void config_node_reset_cmd_handler(int argc,const char** argv)
{
    unsigned short dst=0,netkey_index = 0;
    if(argc==2){
        dst = strtol(argv[0],NULL,0);
				netkey_index = strtol(argv[1],NULL,0);
				config_node_reset(dst,netkey_index);
		}
}

static void config_heartbeat_publication_get_cmd_handler(int argc,const char** argv)
{
    unsigned short dst=0,netkey_index = 0;
    if(argc==2){
        dst = strtol(argv[0],NULL,0);
        netkey_index = strtol(argv[1],NULL,0);
				config_heartbeat_publication_get(dst,netkey_index);
		}


}
static void config_heartbeat_publication_set_cmd_handler(int argc,const char** argv)
{
	  unsigned short dst=0,heartbeat_dst=0,feature=0,netkey_index=0;
	  unsigned char count_log,period,ttl;
    if(argc==7){
        dst = strtol(argv[0],NULL,0);
        heartbeat_dst = strtol(argv[1],NULL,0);
        count_log = strtol(argv[2],NULL,0);
        period = strtol(argv[3],NULL,0);
        ttl = strtol(argv[4],NULL,0);
        feature = strtol(argv[5],NULL,0);
        netkey_index = strtol(argv[6],NULL,0);
				config_heartbeat_publication_set(dst,heartbeat_dst,count_log,period, ttl, feature, netkey_index);
		}
}
static void config_heartbeat_subscription_get_cmd_handler(int argc,const char** argv)
{
    unsigned short dst=0,netkey_index=0;
    if(argc==2){
        dst = strtol(argv[0],NULL,0);
        netkey_index = strtol(argv[1],NULL,0);
				config_heartbeat_subscription_get(dst,netkey_index);
		}
}
static void config_heartbeat_subscription_set_cmd_handler(int argc,const char** argv)
{
    unsigned short dst=0,heartbeat_source=0,heartbeat_dest=0,netkey_index;
		unsigned char period=0;
    if(argc==5){
        dst = strtol(argv[0],NULL,0);
				netkey_index = strtol(argv[1],NULL,0);
			  heartbeat_source = strtol(argv[2],NULL,0);
			  heartbeat_dest = strtol(argv[3],NULL,0);
			  period = strtol(argv[4],NULL,0);
				config_heartbeat_subscription_set(dst,netkey_index,heartbeat_source,heartbeat_dest,period);
		}
}
