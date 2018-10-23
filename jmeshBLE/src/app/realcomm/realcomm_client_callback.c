#include"realcomm_client.h"
#include"realcomm_server.h"
#include"../../access/jmesh_access.h"
#include"../../driver/jmesh_system.h"
#include"../../jmesh/jmesh_save_define.h"
#include"../../jmesh/jmesh_save.h"
#include"realcomm_client_callback.h"

static struct{
        unsigned short addr;
        unsigned short nid;
        unsigned short aid;
}server_para;

void realcomm_client_init_callback(void){
    server_para.addr=0;
    server_para.nid=0;
    server_para.aid=0;
		jmesh_save_read(JMESH_SAVE_REALCOMM_PARA,sizeof(server_para),(unsigned char*)&server_para);	
}

int realcomm_config_addr_get(void)
{
		return server_para.addr;
}

int realcomm_client_config_callback(unsigned short addr,unsigned short nid,unsigned short aid)
{
    server_para.addr=addr;
    server_para.nid=nid;
    server_para.aid=aid;
		jmesh_save_write(JMESH_SAVE_REALCOMM_PARA,sizeof(server_para),(unsigned char*)&server_para);		
    //write
    return 1;
}
void realcomm_client_uart_recv_callback(unsigned char length,unsigned char* data)
{

    jmesh_mutex_lock();
    jmesh_access_send(server_para.addr+1,server_para.nid,server_para.aid,&realcomm_client,message_realcomm_server_trans,length,data);
    jmesh_mutex_unlock();
}
