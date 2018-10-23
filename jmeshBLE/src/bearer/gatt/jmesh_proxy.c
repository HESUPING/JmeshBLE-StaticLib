#include"jmesh_gatt.h"
#include"jmesh_proxy.h"
#include"jmesh_proxy_config.h"
#include"../../jmesh/jmesh_pdu.h"
#include"../beacon/jmesh_beacon.h"
#include"../../network/jmesh_interface.h"
#include"string.h"
#include"../../jmesh/jmesh_print.h"
#include"../provisioning/jmesh_provisioning_client.h"
#include"../provisioning/jmesh_provisioning_server.h"

void jmesh_proxy_send(unsigned char interface,unsigned char type,jmesh_pdu_t* pdu)
{
    int i,seg_num,seg_len,tail_len;
    unsigned short svc_instance;
    jmesh_gatt_t* gatt;
    gatt=jmesh_gatt_get_by_interface(interface);
    if(gatt==NULL || !gatt->is_ready){
        jmesh_pdu_free(pdu);
        return;
    }
		pdu->length ++;	
    switch(type)
    {
        case JMESH_PROXY_TYPE_BEACON:
//            svc_instance = gatt->svc_instance+JMESHS_IDX_MESH_BEACON_TRANSMIT_VAL;
            break;
        case JMESH_PROXY_TYPE_NETWORK:
            svc_instance = gatt->svc_instance+JMESHS_IDX_MESH_NETWORK_TRANSMIT_OUT_VAL;
            break;
        case JMESH_PROXY_TYPE_CONFIG:
//            svc_instance = gatt->svc_instance+JMESHS_IDX_MESH_NETWORK_TRANSMIT_VAL;//config use ? svc instance
            break;
        case JMESH_PROXY_TYPE_PROVISION:
            svc_instance = gatt->svc_instance+JMESHS_IDX_MESH_PROVISIONING_DATA_OUT_VAL;
            break;
        default:
            jmesh_pdu_free(pdu);
            return;
    }
    pdu->proxy.type=type;

    if(/*gatt->mtu==0||*/gatt->mtu >= pdu->proxy.length+1){//proxy format add two byte ahead data: length,head,data.once send mtu-2
        pdu->proxy.SAR=JMESH_PROXY_SAR_COMPLETE;
        jmesh_gatt_send(gatt,svc_instance,pdu->length+1,pdu->pdu);
        jmesh_pdu_free(pdu);
        return;
    }
    else if(gatt->mtu>2){
        seg_len=gatt->mtu-2;
        seg_num=(pdu->length + seg_len-1)/seg_len;
        tail_len=pdu->length%seg_len;
        if(tail_len==0){
            tail_len=seg_len;
        }
        pdu->proxy.SAR=JMESH_PROXY_SAR_FIRST_SEGMENT;
        pdu->length=seg_len;
        jmesh_gatt_send(gatt,svc_instance,seg_len+2,pdu->pdu);

        pdu->proxy.SAR=JMESH_PROXY_SAR_CONTINUE_SEGMENT;
        for(i=1;i<seg_num-1;i++){
            pdu->pdu[seg_len*i]=seg_len;
            pdu->pdu[seg_len*i+1]=pdu->proxy.head;
            jmesh_gatt_send(gatt,svc_instance,seg_len+2,pdu->pdu+seg_len*i);
        }
        pdu->proxy.SAR=JMESH_PROXY_SAR_LAST_SEGMENT;
        pdu->pdu[seg_len*i]=seg_len;
        pdu->pdu[seg_len*i+1]=pdu->proxy.head;
        jmesh_gatt_send(gatt,svc_instance,tail_len+2,pdu->pdu+seg_len*i);
    }
    jmesh_pdu_free(pdu);
}



void jmesh_proxy_recv(jmesh_gatt_t* gatt,unsigned short instance,unsigned char length,unsigned char* data)
{
    unsigned char type;
    jmesh_pdu_t* pdu=(jmesh_pdu_t*)data;
		print_buffer_note(length,data,"receive proxy data:");
    if(pdu->proxy.length+1!=length){
        return;
    }
    switch(instance-gatt->svc_instance){
        case(JMESHS_IDX_MESH_BEACON_IN_VAL):
            type=JMESH_PROXY_TYPE_BEACON;
            break;
        case(JMESHS_IDX_MESH_NETWORK_TRANSMIT_IN_VAL):
            type=JMESH_PROXY_TYPE_NETWORK;
            break;
        case(JMESHS_IDX_MESH_PROVISIONING_DATA_IN_VAL):
            type=JMESH_PROXY_TYPE_PROVISION;
            break;
        default:
            return;
    }
    if(pdu->proxy.type!=type){
        return;
    }
    switch(pdu->proxy.SAR){
        case(JMESH_PROXY_SAR_COMPLETE):
            if(gatt->recv_cache!=NULL){
                jmesh_pdu_free(gatt->recv_cache);
            }
            if(NULL!=(gatt->recv_cache=jmesh_pdu_new(length))){
                memcpy(gatt->recv_cache->pdu,data,length);
            }
            break;
        case(JMESH_PROXY_SAR_FIRST_SEGMENT):
            if(gatt->recv_cache!=NULL){
                jmesh_pdu_free(gatt->recv_cache);
            }
            if(NULL!=(gatt->recv_cache=jmesh_pdu_new(0xff))){
                memcpy(gatt->recv_cache->pdu,data,length);
            }
            return;
        case(JMESH_PROXY_SAR_CONTINUE_SEGMENT):
            if(gatt->recv_cache!=NULL){
                if(gatt->recv_cache->proxy.type==pdu->proxy.type && gatt->recv_cache->length+pdu->proxy.length<=0xff){
                    memcpy(gatt->recv_cache->pdu + gatt->recv_cache->length+1, data+2, length-2);//
                    gatt->recv_cache->length+=pdu->proxy.length-1;
                }
                else{//incomplete continue segment pdu or too long, just delete
                    jmesh_pdu_free(gatt->recv_cache);
                    gatt->recv_cache=NULL;
                }
            }
            return;
        case(JMESH_PROXY_SAR_LAST_SEGMENT):
            if(gatt->recv_cache!=NULL){
                if(gatt->recv_cache->proxy.type==pdu->proxy.type && gatt->recv_cache->length+pdu->proxy.length<=0xff){
                    memcpy(gatt->recv_cache->pdu + gatt->recv_cache->length+1, data+2, length-2);//
                    gatt->recv_cache->length+=pdu->proxy.length-1;
                    break;
                }
                else{
                    jmesh_pdu_free(gatt->recv_cache);
                    gatt->recv_cache=NULL;
                }
            }
            return;
        default:
            return;
    }
		int retlen = 0;
		jmesh_pdu_t* buff=jmesh_pdu_new(100);		
    switch(gatt->recv_cache->proxy.type){
        case JMESH_PROXY_TYPE_NETWORK:
			gatt->recv_cache->length--;
            jmesh_interface_recv(jmesh_gatt_get_interface(gatt),gatt->recv_cache);
            break;
        case JMESH_PROXY_TYPE_BEACON:
            jmesh_beacon_handler(NULL,0,(jmesh_beacon_t*)gatt->recv_cache->proxy.para);
            jmesh_pdu_free(gatt->recv_cache);
            break;
        case JMESH_PROXY_TYPE_CONFIG:
            //jmesh_proxy_config_process(connect,connect->recv_cache);
            break;
        case JMESH_PROXY_TYPE_PROVISION:
            retlen= gatt_provisioning_server_handlers(gatt->recv_cache->proxy.para, buff->proxy.para);
						if(retlen>0){
								buff->length=retlen;
								buff->proxy.type=JMESH_PROXY_TYPE_PROVISION;
								jmesh_proxy_send(jmesh_gatt_get_interface(gatt),JMESH_PROXY_TYPE_PROVISION,buff);						
						}

				    jmesh_pdu_free(gatt->recv_cache);
            break;
    }
    gatt->recv_cache=NULL;
}
