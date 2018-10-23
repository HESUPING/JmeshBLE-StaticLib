/**
 *  low power node                                  friend node
    request            ---------------------->
                       <----------------------           offer
    subscription add   ---------------------->
                       <----------------------      subscription confirm
    poll               ---------------------->
                       <----------------------      update MD=0
                       <----------------------      clear(previous addr!=local)
    sleep
    poll               ---------------------->
                       <----------------------      pdu
    poll               ---------------------->
                       <----------------------      update MD=0
    sleep
    ...
 *
 */

#ifndef JMESH_FRIEND_H
#define JMESH_FRIEND_H
#include"../../jmesh/jmesh_config.h"
#include"../../jmesh/jmesh_types.h"
#include"../../jmesh/jmesh_pdu.h"
#include"../../onchip_system/os_timer_event.h"


typedef struct st_jmesh_friend_poll{
    unsigned char FSN:1;
    unsigned char padding:7;
}jmesh_friend_poll_t;

typedef struct st_jmesh_friend_update{
    unsigned char key_refresh_flag:1;
    unsigned char IV_update_flag:1;
    unsigned char reserved:6;
    unsigned char iv_index[4];
    unsigned char MD;
}jmesh_friend_update_t;

typedef struct st_jmesh_friend_request{
    unsigned char RFU:1;
    unsigned char RSSI_factor:2;
    unsigned char receive_window_factor:2;
    unsigned char min_queue_size_log:3;

    unsigned char receive_delay;
    unsigned char poll_timeout[3];
    unsigned char previous_address[2];
    unsigned char element_num;
    unsigned char LPN_counter[2];
}jmesh_friend_request_t;

typedef struct st_jmesh_friend_offer{
    unsigned char receive_window;
    unsigned char queue_size;
    unsigned char subscription_list_size;
    unsigned char rssi;
    unsigned char friend_counter[2];
}jmesh_friend_offer_t;

typedef struct st_jmesh_friend_clear{
    unsigned char LPN_addr[2];
    unsigned char LPN_counter[2];
}jmesh_friend_clear_t;

typedef struct st_jmesh_friend_clear_confirm{
    unsigned char LPN_addr[2];
    unsigned char LPN_counter[2];
}jmesh_friend_clear_confirm_t;

typedef struct st_jmesh_friend_subscription_list_add{
    unsigned char transaction_number;
    unsigned char address_list[1];
}jmesh_friend_subscription_list_add_t;

typedef struct st_jmesh_friend_subscription_list_remove{
    unsigned char transaction_number;
    unsigned char address_list[1];
}jmesh_friend_subscription_list_remove_t;

typedef struct st_jmesh_friend_subscription_list_confirm{
    unsigned char transaction_number;
}jmesh_friend_subscription_list_confirm_t;


typedef struct st_jmesh_friendpdu{
    union{
        jmesh_friend_poll_t                         poll;
        jmesh_friend_update_t                       update;
        jmesh_friend_request_t                      request;
        jmesh_friend_offer_t                        offer;
        jmesh_friend_clear_t                        clear;
        jmesh_friend_clear_confirm_t                clear_confirm;
        jmesh_friend_subscription_list_add_t        subscription_list_add;
        jmesh_friend_subscription_list_remove_t     subscription_list_remove;
        jmesh_friend_subscription_list_confirm_t    subscription_list_confirm;
    };
}jmesh_friend_pdu_t;





int jmesh_friend_recv(unsigned short netkey_index,unsigned short length,jmesh_pdu_t* pdu);
int jmesh_friend_send(jmesh_pdu_t* pdu);

#endif // JMESH_FRIEND_H
