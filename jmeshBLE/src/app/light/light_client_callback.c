#include"light_client.h"
#include"light_server.h"
#include"light_config.h"
#include"light_client_callback.h"
#include"../../access/jmesh_access.h"

#include"../../jmesh/jmesh_print.h"
#include"../../jmesh/jmesh_save.h"
#include"../../driver/jmesh_system.h"

void light_client_status_callback(unsigned char pwm_nums,unsigned char* pwm_values){
    print_info("light client status pwm nums %d,values:%d %d %d\n",pwm_nums,pwm_values[0],pwm_values[1],pwm_values[2]);
}

static light_config_client_button_t client_button[LIGHT_CLIENT_BUTTON_SIZE*2];

void light_client_button_init(void)
{
    memset(client_button,0,sizeof(client_button));
    //save_read
}

void light_client_config_button_callback(unsigned short src,unsigned short nid,unsigned short aid,light_config_client_button_t* button)
{
    print_info("light client config button %d callback\n",button->button_id);
    if(button->button_id>=LIGHT_CLIENT_BUTTON_SIZE){
        return;
    }
    client_button[button->button_id*(1+button->value)]=*button;
    //SAVE WRITE
    if(button->type==0){
        jmesh_access_send(src,nid,aid,&light_client,message_light_config_client_button_status,button->pwm.nums+5,(unsigned char*)button);
    }
    else{
        jmesh_access_send(src,nid,aid,&light_client,message_light_config_client_button_status,5,(unsigned char*)button);
    }
}
void light_client_get_button_callback(unsigned short src,unsigned short nid,unsigned short aid,unsigned char button_id,unsigned char value)
{
    int i;
    for(i=0;i<LIGHT_CLIENT_BUTTON_SIZE*2;i++){
        if(client_button[i].dst!=0 && button_id==client_button[i].button_id && value==client_button[i].value){
             if(client_button[i].type==0){
                jmesh_access_send(src,nid,aid,&light_client,message_light_config_client_button_status,client_button[i].pwm.nums+5,(unsigned char*)&client_button[i]);
            }
            else{
                jmesh_access_send(src,nid,aid,&light_client,message_light_config_client_button_status,5,(unsigned char*)&client_button[i]);
            }
            return;
        }
    }
}

void light_client_button_callback(unsigned char button_id,unsigned char value)
{
    int index;
    print_info("light client button %d press callback\n",button_id);
    if(button_id>=LIGHT_CLIENT_BUTTON_SIZE||value>1){
        return;
    }
    index=button_id*(1+value);
    if(client_button[index].dst==0){
        return;
    }
    jmesh_mutex_lock();
    if(client_button[index].type==0){
        jmesh_access_send(client_button[index].dst,0,client_button[index].aid,&light_client,message_light_server_control,client_button[index].pwm.nums+1,&client_button[index].pwm.nums);
    }
    else{
        jmesh_access_send(client_button[index].dst,0,client_button[index].aid,&light_client,message_light_server_scene,1,&client_button[index].scene.id);
    }
    jmesh_mutex_unlock();
    return;

}
