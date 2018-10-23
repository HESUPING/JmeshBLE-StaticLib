#include"jmesh_secure_beacon.h"
#include"../../jmesh/jmesh_pdu.h"
#include"../../onchip_system/os_timer_event.h"
#include"jmesh_beacon.h"
#include"../adv/jmesh_adv.h"
//#include "log.h"
static os_timer_event_t secure_beacon_timer;
static unsigned short secure_beacon_time_cache[BEACON_TIME_CACHE_SIZE]={0};//60*20/10=120s,
static unsigned char secure_beacon_time_index=0;

static void send_secure_beacon(void)
{
    int i,j;
    jmesh_pdu_t* pdu;
    jmesh_beacon_t* beacon;
    jmesh_netkey_t *net_key;
    jmesh_key_t cmac;
    unsigned long iv_index;

    for(i=1;i<BEACON_TIME_CACHE_SIZE;i++){
        j=(secure_beacon_time_index+BEACON_TIME_CACHE_SIZE-i)%BEACON_TIME_CACHE_SIZE;
        if(secure_beacon_time_cache[secure_beacon_time_index]-secure_beacon_time_cache[j]>BEACON_OBSERVATION_PERIOD_S
           ||secure_beacon_time_cache[j]==0){//now-history>observation_period
            break;
        }
    }
    os_timer_event_set(&secure_beacon_timer,(BEACON_OBSERVATION_PERIOD_S*i/BEACON_EXPECTED_NUMBER)*1000,(os_timer_event_caller_t)send_secure_beacon,NULL);

    net_key=jmesh_netkey_get_by_index(0);
    if(NULL==net_key)
    {
        return;
    }
    //else if(JMESH_STATUS_SUCCESS!=jmesh_netkey_state_get(0,net_key)){
    //    return;
    //}

     if(NULL==(pdu=jmesh_pdu_new(sizeof(jmesh_secure_beacon_t)+JMESH_BEACON_HEAD_SIZE))){
        return;
    }

    beacon=(jmesh_beacon_t*)pdu->adv.para;
    beacon->type=JMESH_BEACON_TYPE_SECURE;
    beacon->secure_beacon.key_refresh_flag=(2==jmesh_netkey_get_phase(net_key))? 1 : 0;
    beacon->secure_beacon.iv_update_flag=jmesh_netkey_get_iv_update_flag(0);
    iv_index=jmesh_netkey_get_iv_index(0);
    beacon->secure_beacon.iv_index[0]=(unsigned char)(iv_index>>24);
    beacon->secure_beacon.iv_index[1]=(unsigned char)(iv_index>>16);
    beacon->secure_beacon.iv_index[2]=(unsigned char)(iv_index>>8);
    beacon->secure_beacon.iv_index[3]=(unsigned char)(iv_index);

    memcpy(beacon->secure_beacon.network_id,JMESH_NETKEY_GET_NETID(net_key),JMESH_NETID_SIZE);

    security_AES_CMAC((uint8_t *)JMESH_NETKEY_GET_BEACON_KEY(net_key),13,(uint8_t *)&beacon->secure_beacon,(uint8_t *)cmac);
    memcpy(beacon->secure_beacon.authentication_value,cmac,8);

    pdu->adv.length=1+sizeof(jmesh_secure_beacon_t);

    jmesh_adv_send_beacon(pdu);
}

void jmesh_secure_beacon_start(int adv_time)
{
    int i;
    for(i=0;i<BEACON_TIME_CACHE_SIZE;i++){
        secure_beacon_time_cache[i]=0;
    }
    send_secure_beacon();
}
void jmesh_secure_beacon_stop(void){
    os_timer_event_remove(&secure_beacon_timer);
}
void jmesh_secure_beacon_handler(jmesh_secure_beacon_t* beacon){
    jmesh_key_t auth;
    static unsigned char cache_auth[8]={0};

    jmesh_netkey_t *net_key;
    unsigned long secure_iv_index,iv_index;

    net_key=jmesh_netkey_get_by_index(0);
    if(NULL==net_key)
    {
        //LOG(LOG_LVL_INFO,"\nprocess secure beacon error:3!!\n");
        return;
    }
    //else if(JMESH_STATUS_SUCCESS!=jmesh_netkey_state_get(0,net_key)){
    //    return;
    //}

    if(0==memcmp(beacon->network_id,JMESH_NETKEY_GET_NETID(net_key),JMESH_NETID_SIZE)
       &&0!=memcmp(cache_auth,beacon->authentication_value,8)){
        security_AES_CMAC((uint8_t *)JMESH_NETKEY_GET_BEACON_KEY(net_key),13,(uint8_t *)beacon,(uint8_t *)auth);
        if(0==memcmp(auth,beacon->authentication_value,8)){
            //LOG(LOG_LVL_INFO,"\nprocess secure beacon\n");

            secure_iv_index=beacon->iv_index[0];
            secure_iv_index<<=8;
            secure_iv_index|=beacon->iv_index[1];
            secure_iv_index<<=8;
            secure_iv_index|=beacon->iv_index[2];
            secure_iv_index<<=8;
            secure_iv_index|=beacon->iv_index[3];

            iv_index=jmesh_netkey_get_iv_index(0);

            if(secure_iv_index==1+iv_index){
                if(beacon->iv_update_flag==1){
                    jmesh_netkey_start_update_iv_index(0);//start update iv index
                }
                else{
                    jmesh_netkey_recover_iv_index(0,secure_iv_index);//recover iv index
                }
            }
            if(secure_iv_index>iv_index+1 && secure_iv_index<iv_index+48){
                jmesh_netkey_recover_iv_index(0,secure_iv_index);
            }
            if(beacon->iv_update_flag==0&&secure_iv_index==iv_index){//stop update iv_index
                jmesh_netkey_stop_update_iv_index(0);
            }

            if(secure_iv_index+48<iv_index){//ignore
                return;
            }

            memcpy(cache_auth,auth,8);
            secure_beacon_time_cache[secure_beacon_time_index]=os_time_get_seconds();
            secure_beacon_time_index=(secure_beacon_time_index+1)%BEACON_TIME_CACHE_SIZE;
        }
        else
        {
            //LOG(LOG_LVL_INFO,"\nprocess secure beacon error:1!!\n");

        }
    }
    else
    {
        //LOG(LOG_LVL_INFO,"\nprocess secure beacon error:2!!\n");
    }
}
