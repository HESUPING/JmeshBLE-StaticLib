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
#include"../../driver/jmesh_driver_config.h"
#include"../../app/realcomm/realcomm_server_callback.h"
static void AT_read_cmd_handler(int argc,const char** argv);
static void AT_mac_cmd_handler(int argc,const char** argv);
static void AT_addr_cmd_handler(int argc,const char** argv);
static void AT_netkey_cmd_handler(int argc,const char** argv);
static void AT_del_nk_cmd_handler(int argc,const char** argv);
static void AT_get_nk_cmd_handler(int argc,const char** argv);
static void AT_appkey_cmd_handler(int argc,const char** argv);
static void AT_iv_index_cmd_handler(int argc,const char** argv);
static void AT_bind_cmd_handler(int argc,const char** argv);
static void AT_sub_cmd_handler(int argc,const char** argv);
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
	{AT_netkey_cmd_handler,         "AT+ADD_NK", 				"-ni,-key",       "AT+ADD_NK:100,11223344556677889900112233445566"},
    {AT_appkey_cmd_handler,         "AT+ADD_AK",   		 "-ni,-ai,-key",   "AT+ADD_AK:0,100,123456789011223344556677889900AA"},
    {AT_iv_index_cmd_handler,       "AT+IV_INDEX",       "-iv_index",	        "AT+IV_INDEX:0x12345678"},
    {AT_bind_cmd_handler,           "AT+BIND",            "-e,-model,-ai",  "AT+BIND:1,4,100"},
    {AT_sub_cmd_handler, 						"AT+SUB",				"e,-model,-addr","AT+ADD_SUB:1,4,10"},
    {AT_baud_set_cmd_handler,              "AT+BAUD_SET",          "-dest",	        "config addr set"},		
    {AT_tricolor_set_cmd_handler,        "AT+TRICOLOR_SET",        " ",      " "},
    {AT_realcomm_config_addr_cmd_handler,        "AT+REAL_CFG_ADDR",        " ",      " "},
    {AT_realcomm_config_addr_get_cmd_handler,        "AT+REAL_CFG_ADDR_GET",        " ",      " "},		
    {AT_realcomm_config_baud_cmd_handler,        "AT+REAL_CFG_BAUD",        " ",      " "},
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
			unsigned long baudrate = strtol(argv[0],NULL,0);
#if(JMESH_DRIVER_BX2400)
			if(jmesh_uart_baudrate_set(baudrate)<0) return ;
#endif
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

static void AT_mac_cmd_handler(int argc,const char** argv)
{
	unsigned char mac[6] = {0};
	if(argc == 1)
	{
		if(strlen(argv[0])!=12)
		{
			print_cmd("ERROR:invalid mac length!\n");
			return;
		}
		str_to_hex(argv[0],6,mac);
		jmesh_mac_set(mac);
		print_cmd("OK:set mac = %s\n",argv[0]);
	}else if(argc == 0)
	{
		jmesh_mac_get(mac);
		print_buffer_cmd(6,mac,"OK:read mac = ");				
	}else
	{
		print_cmd("ERROR:invalid arguement num!\n");			
	}
}

static void AT_iv_index_cmd_handler(int argc,const char** argv)
{
	unsigned long iv_index = 0;
	unsigned short netkey_index = 0;
	unsigned char buffer[6] = {0};
	
	int len =jmesh_netkey_state_list(6,buffer);
	if(len == 0)
	{
		print_cmd("ERROR:no valid netkey!\n");
	}else
	{
		netkey_index = buffer[0] + ((buffer[1]&0xff)>>8);
	}
				
    if(argc==1){
		iv_index = strtol(argv[0],NULL,0);
		jmesh_netkey_test_set_iv_index(netkey_index,iv_index);
		print_cmd("OK:set iv_index is :0x%x\n",iv_index);
    }else if(argc == 0)
	{
		iv_index = jmesh_netkey_get_iv_index(netkey_index);
		print_cmd("OK:read iv_index = 0x%x\n",iv_index);
	}else 
	{
		print_cmd("ERROR:invalid arguement num!\n");			
	}

}
static void AT_read_cmd_handler(int argc,const char** argv)
{
	jmesh_mac_t mac;
	unsigned short netkey_index = 0;
	unsigned short appkey_index = 0xfff;
	unsigned char  key[16] = {0};
	unsigned char buffer[10] = {0};
	jmesh_appkey_t* jmesh_appkey;
	if(argc == 0)
	{
		jmesh_mac_get(mac);
		print_buffer_cmd(6,mac,"Jmesh mac:");	
		print_cmd("Jmesh addr: %d\n",jmesh_get_primary_addr());			
		print_cmd("Jmesh iv_index = 0x%08x\n",jmesh_netkey_get_iv_index(netkey_index));
		print_cmd("Jmesh seq = 0x%x\n",jmesh_seq_get());
		jmesh_netkey_state_get(netkey_index, key);
		print_buffer_cmd(16,key,"Jmesh netkey_index = %d,netkey = ",netkey_index);
		int length = jmesh_appkey_list(netkey_index,10,buffer);
		for(int i=0;i<length;i+=3)
		{
			if(length - i < 3)
			{
				appkey_index = buffer[i] + ((buffer[i+1]&0x0f)<<8);	
				jmesh_appkey = jmesh_appkey_get_by_key_index(netkey_index,appkey_index);
				print_buffer_cmd(16,jmesh_appkey->key,"netkey_index = %d,appkey_index = %d,Jmesh appkey = ",netkey_index,appkey_index);	
				break;
			}
			else
			{
				appkey_index = buffer[i] + ((buffer[i+1]&0x0f)<<8);		
				jmesh_appkey = jmesh_appkey_get_by_key_index(netkey_index,appkey_index);
				print_buffer_cmd(16,jmesh_appkey->key,"netkey_index = %d,appkey_index = %d,Jmesh appkey = ",netkey_index,appkey_index);	
				appkey_index = (buffer[i+1]>>4) + (buffer[i+2]<<4);	
				jmesh_appkey = jmesh_appkey_get_by_key_index(netkey_index,appkey_index);
				print_buffer_cmd(16,jmesh_appkey->key,"netkey_index = %d,appkey_index = %d,Jmesh appkey = ",netkey_index,appkey_index);	
			}
		}
	}
	else
	{
		print_cmd("ERROR:invalid arguement num!\n");						
		
	}
}
static void AT_addr_cmd_handler(int argc,const char** argv)
{
    unsigned short mesh_addr = 0;
    if(argc==1){
		mesh_addr = strtol(argv[0],NULL,0);
		jmesh_set_primary_addr(mesh_addr);
		print_cmd("OK:set mesh addr = %d\n",mesh_addr);
    }
	else if(argc == 0)
	{
		mesh_addr = jmesh_get_primary_addr();
		print_cmd("OK:read mesh addr = %d\n",mesh_addr);				
	}
	else
	{
		print_cmd("ERROR:invalid arguement num!\n");			
	}
}
static void AT_netkey_cmd_handler(int argc,const char** argv)
{
    unsigned short netkey_index=0;
    unsigned char key[16];
	unsigned char buffer[6] = {0};
			
    if(argc==3){
		if(strcmp(argv[0],"ADD") != 0)
		{
			print_cmd("ERROR:invalid arguement!\n");
			return;
		} 
		netkey_index = strtol(argv[1],NULL,0);
        str_to_hex(argv[2],16,key);
		jmesh_netkey_state_set(netkey_index,key);
		print_buffer_cmd(16,key,"OK: set netkey index =%d,netkey = ",netkey_index);
    }
	else if(argc == 2)
	{
		if(strcmp(argv[0],"DELETE") != 0)
		{
			print_cmd("ERROR:invalid arguement!\n");
			return;
		}
		netkey_index = strtol(argv[1],NULL,0);
		int ret = jmesh_netkey_state_del(netkey_index);
		if(ret == JMESH_STATUS_SUCCESS)
		{
			print_cmd("OK:delete netkey index = %d \n",netkey_index);					
		}else{
			print_cmd("ERROR:invalid netkey index!\n");
		}
	}
	else if(argc == 0)
	{
		int len =jmesh_netkey_state_list(6,buffer);
		if(len ==  0)
		{
			print_cmd("ERROR:no valid netkey!\n");
		}else
		{
			JMESH_LITTLE_ENDIAN_PICK2(netkey_index,buffer);
			int ret = jmesh_netkey_state_get(netkey_index, key);
			if(ret == JMESH_STATUS_SUCCESS)
			{
				print_buffer_cmd(16,key,"OK:read netkey index = %d,netkey = ",netkey_index);					
			}else{
				print_cmd("ERROR:invalid netkey index!\n");
			}
		}			
	}
	else
	{
		print_cmd("ERROR:invalid arguement num!\n");						
	}
}

static void AT_appkey_cmd_handler(int argc,const char** argv)
{
    unsigned short netkey_index=0,appkey_index=0;
    unsigned char key[16];
	unsigned char buffer[6] = {0};
	
    if(argc==4)
	{
		if(strcmp(argv[0],"ADD") != 0)
		{
				print_cmd("ERROR:invalid arguement!\n");
				return;
		} 
        netkey_index = strtol(argv[1],NULL,0);
		appkey_index = strtol(argv[2],NULL,0);
        str_to_hex(argv[3],16,key);
		int ret = jmesh_appkey_set(netkey_index,appkey_index,key);
		if(ret == JMESH_STATUS_SUCCESS)
				print_buffer_cmd(16,key,"OK:add appkey index = %d, appkey = ",appkey_index);
		else
				print_cmd("ERROR:invalid key index!\n");
    }
	else if(argc == 3)
	{
		if(strcmp(argv[0],"DELETE") != 0)
		{
				print_cmd("ERROR:invalid arguement!\n");
				return;
		} 
		netkey_index = strtol(argv[1],NULL,0);
		appkey_index = strtol(argv[2],NULL,0);	
		int ret = jmesh_appkey_delete(netkey_index,appkey_index);
		if(ret == JMESH_STATUS_SUCCESS)
		{
				print_cmd("OK:delete appkey index = %d",appkey_index);						
		}else{
				print_cmd("ERROR:invalid key index!\n");
		}				
	}
	else if(argc == 0)	
	{
		int len =jmesh_netkey_state_list(6,buffer);
		if(len == 0)
		{
			print_cmd("ERROR:no valid netkey!\n");
		}else
		{
			JMESH_LITTLE_ENDIAN_PICK2(netkey_index,buffer);
			if(len == 0)
				jmesh_appkey_list(netkey_index,6,buffer);
			else
			{	
				print_cmd("ERROR:no valid appkey!\n");
				return ;
			}
			JMESH_LITTLE_ENDIAN_PICK2(appkey_index,buffer);
			jmesh_appkey_t* ret = jmesh_appkey_get_by_key_index(netkey_index,appkey_index);	
			if(ret == NULL)
				print_cmd("ERROR:no valid appkey!\n");
			else
				print_buffer_cmd(16,ret->key,"get appkey = ");						
		}				
	}
	else
	{
		print_cmd("ERROR:invalid arguement num!\n");						
	}
}

static void AT_bind_cmd_handler(int argc,const char** argv)
{
    unsigned short element_addr=0,appkey_index=0;
	unsigned long model_id_int  = 0;
	unsigned char buffer[6] = {0};	
	jmesh_model_id_t model_id;
	jmesh_model_t*  model;
	int ret = 0;
					
    if(argc==4){	
		element_addr = strtol(argv[1],NULL,0);
		model_id_int = strtol(argv[2],NULL,0);
		model_id.company_id = model_id_int>>16;
		if(model_id.company_id)  // vendor id
		{
			model_id.model_id = model_id_int&0xffff;
			model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_addr(element_addr),model_id.company_id,model_id.model_id);
		}else {                  //sig id
			model_id.sig_id  = model_id_int&0xffff;
			model_id.model_id = JMESH_MODEL_ID_INVALID;		
			model = jmesh_model_get_by_sig_id(jmesh_element_get_by_addr(element_addr),model_id.sig_id);					
		}		
        appkey_index = strtol(argv[3],NULL,0);	
				
		if(strcmp(argv[0],"ADD") == 0)
		{
			ret = jmesh_model_bind_app(model,jmesh_appkey_get_by_index(appkey_index));
			if(JMESH_STATUS_SUCCESS == ret)
				print_cmd("OK: bind appkey index = %d \n",appkey_index);
			else
				print_cmd("ERROR:cann't bind the appkey\n");
		}else if(strcmp(argv[0],"DELETE") == 0)
		{
			ret = jmesh_model_unbind_app(model,jmesh_appkey_get_by_index(appkey_index));
			if(JMESH_STATUS_SUCCESS == ret)
				print_cmd("OK: unbind appkey index = %d \n",appkey_index);
			else
				print_cmd("ERROR:cann't unbind the appkey\n");					
		}else{
			print_cmd("ERROR:invalid arguement!\n");
		}			
	}
	else if(argc == 3)
	{
		element_addr = strtol(argv[1],NULL,0);
		model_id_int = strtol(argv[2],NULL,0);
		model_id.company_id = model_id_int>>16;
		if(model_id.company_id)  // vendor id
		{
			model_id.model_id = model_id_int&0xffff;
			model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_addr(element_addr),model_id.company_id,model_id.model_id);
		}else {                  //sig id
			model_id.sig_id  = model_id_int&0xffff;
			model_id.model_id = JMESH_MODEL_ID_INVALID;		
			model = jmesh_model_get_by_sig_id(jmesh_element_get_by_addr(element_addr),model_id.sig_id);					
		}		
		if(strcmp(argv[0],"GET") == 0)
		{
			int length = jmesh_model_bind_list(model,6, buffer);
			JMESH_LITTLE_ENDIAN_PICK2(appkey_index,buffer);	
			print_cmd("OK: model id %x get bind appkey index = %d \n",model_id_int,appkey_index);
		}
	}else if(argc == 0)
		{
			for(int i=0;i<10;i++)
			{
				model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_index(1),0xbcbd,i);
				if(model ==NULL) continue;
				int length = jmesh_model_bind_list(model,6, buffer);
				
				for(int j=0;j<length;j+=3)
				{
					if(length - j < 3)
					{
						appkey_index = buffer[j] + ((buffer[j+1]&0x0f)<<8);	
						print_cmd("OK:model id = 0x%08x ,appkey index = %d \n",(0xbcbd<<16)||i, appkey_index);
						break;
					}
					appkey_index = buffer[j] + ((buffer[j+1]&0x0f)<<8);						
					print_cmd("OK:model id = 0x%08x ,appkey index = %d \n",(0xbcbd<<16)||i, appkey_index);
					appkey_index = (buffer[j+1]>>4) + (buffer[j+2]<<4);
					print_cmd("OK:model id = 0x%08x ,appkey index = %d \n",(0xbcbd<<16)||i, appkey_index);
				}
			}
				
		}else{
			print_cmd("ERROR:invalid arguement num!\n");						
				
		}
}

static void AT_sub_cmd_handler(int argc,const char** argv)
{
    unsigned short element_addr=0,group_addr=0;
	unsigned long model_id_int  = 0;
	unsigned char buffer[6] = {0};	
	jmesh_model_id_t model_id;
	jmesh_model_t*  model;
	int ret = 0;

	element_addr = strtol(argv[1],NULL,0);
	model_id_int = strtol(argv[2],NULL,0);
	model_id.company_id = model_id_int>>16;
	if(model_id.company_id)  // vendor id
	{
		model_id.model_id = model_id_int&0xffff;
		model = jmesh_model_get_by_vendor_id(jmesh_element_get_by_addr(element_addr),model_id.company_id,model_id.model_id);
	}else {                  //sig id
		model_id.sig_id  = model_id_int&0xffff;
		model_id.model_id = JMESH_MODEL_ID_INVALID;		
		model = jmesh_model_get_by_sig_id(jmesh_element_get_by_addr(element_addr),model_id.sig_id);					
	}			
		
    if(argc==4){		
        group_addr = strtol(argv[3],NULL,0);	
		if(group_addr <= JMESH_ADDR_UNICAST_MAX)
		{
				print_cmd("ERROR:invalid group mesh address !\n");
		}
		if(strcmp(argv[0],"ADD") == 0)
		{
				ret = jmesh_model_subscription_list_add(model,group_addr);
			
				if(JMESH_STATUS_SUCCESS == ret)
						print_cmd("OK: add subscription group mesh address = %d \n",group_addr);
				else
						print_cmd("ERROR:add subscription failed\n");
		}else if(strcmp(argv[0],"DELETE") == 0)
		{
				ret = jmesh_model_subscription_list_remove(model,group_addr);
				if(JMESH_STATUS_SUCCESS == ret)
						print_cmd("OK: delete subscription group mesh address = %d \n",group_addr);
				else
						print_cmd("ERROR:delete subscription group mesh address \n");					
		}else{
				print_cmd("ERROR:invalid arguement!\n");
		}			
		}else if(argc == 3)
		{
				if(strcmp(argv[0],"GET") == 0)
				{
						int length = jmesh_model_subscription_list(model, buffer);
						JMESH_LITTLE_ENDIAN_PICK2(group_addr,buffer);	
						print_cmd("OK: model id %x subscription group address = %d \n",model_id_int,group_addr);
				}
		}
		else{
				print_cmd("ERROR:invalid arguement num!\n");						
				
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
				unsigned long baudrate = strtol(argv[0],NULL,0);
				print_cmd("set realcomm config baud = %d\n",baudrate);
//				realcomm_config_server(realcomm_config_addr_get()+1,0,1,baudrate_to_enum(baudrate),0);
//				realcomm_server_config_callback(baudrate_to_enum(baudrate),0);
		}	
}
