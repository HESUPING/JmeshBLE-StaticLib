#ifndef JMESH_PDU_H
#define JMESH_PDU_H


#define JMESH_SHORT_PDU_SIZE 31
#define JMESH_LONG_PDU_SIZE 384
#include"jmesh_config.h"
#include"../bearer/beacon/jmesh_beacon.h"

typedef struct st_jmesh_adv_pdu{
    unsigned char length;
    unsigned char ad_type;
    union{
      unsigned char para[1];
      jmesh_beacon_t beacon;
    };
}jmesh_adv_pdu_t;
typedef struct st_jmesh_proxy_pdu{
    unsigned char length;
    union{
        unsigned char head;
        struct{
            unsigned char type:6;
            unsigned char SAR:2;
        };
    };
    unsigned char para[1];
}jmesh_proxy_pdu_t;


typedef struct st_jmesh_lower_segment_control_pdu{
    unsigned char head[3];
    unsigned char pdu[8];
}jmesh_lower_segment_control_pdu_t;

typedef struct st_jmesh_lower_segment_acknowledgment{
    unsigned char OBO_and_seqZero[2];//1bit OBO,13 bit seqZero, 2bit rfu
    unsigned char ack_block[4];
}jmesh_lower_segment_acknowledgment_t;

typedef struct st_jmesh_lower_control_pdu{
    unsigned char OPCODE:7;
    unsigned char SEG:1;
    union{
        jmesh_lower_segment_acknowledgment_t ack;
        jmesh_lower_segment_control_pdu_t segment;
        unsigned char pdu[11];
    };
}jmesh_lower_control_pdu_t;

typedef struct st_jmesh_lower_segment_access_pdu{
    unsigned char head[3];
    unsigned char pdu[12];
}jmesh_lower_segment_access_pdu_t;

typedef struct st_jmesh_lower_access_pdu{
    unsigned char AID:6;
    unsigned char AKF:1;
    unsigned char SEG:1;
    union{
        jmesh_lower_segment_access_pdu_t segment;
        unsigned char pdu[15];
    };
}jmesh_lower_access_pdu_t;

typedef struct st_jmesh_network_pdu{
    unsigned char length;
    unsigned char itf;

    unsigned char NID:7;
    unsigned char IVI:1;
    unsigned char TTL:7;
    unsigned char CTL:1;
    unsigned char SEQ[3];
    unsigned char SRC[2];
    unsigned char DST[2];
    union{
        jmesh_lower_control_pdu_t control;
        jmesh_lower_access_pdu_t access;
        unsigned char pdu[1];//1+15m+4mac
    };
}jmesh_network_pdu_t;
typedef struct st_jmesh_provisioning_pdu{
    unsigned char length;
    unsigned char pdu[1];
}jmesh_provisioning_pdu_t;

#include"../foundation/state/jmesh_appkey.h"
typedef struct st_jmesh_access_pdu{
    union{
        struct{
            unsigned short src;
            unsigned short dst;
            unsigned short length;
            union{
                unsigned short netkey_index;
                jmesh_appkey_t* appkey;
            };
        }head;
        struct{
            unsigned char rfu[12];
            unsigned char data[1];
        }unsegment;
        struct{
            unsigned char rfu[15];
            unsigned char data[20];
        }segment;
    };
}jmesh_access_pdu_t;
typedef struct st_jmesh_ble_pdu{
  unsigned char length;
  union{
    struct{
      unsigned char id;
      unsigned char is_server;
			unsigned char reason;
      unsigned char mac[1];
    }connect;
  };
}jmesh_ble_pdu_t;

typedef struct st_jmesh_pdu jmesh_pdu_t;
struct st_jmesh_pdu{
    union{
        unsigned char length;
        unsigned char pdu[1];
        jmesh_adv_pdu_t adv;
        jmesh_proxy_pdu_t proxy;
        jmesh_network_pdu_t network;
        jmesh_provisioning_pdu_t provisioning;
        jmesh_access_pdu_t access;
        jmesh_ble_pdu_t ble;
    };
};

void jmesh_pdu_init(void);
jmesh_pdu_t* jmesh_pdu_new(int length);
void jmesh_pdu_free(jmesh_pdu_t* pdu);

#define JMESH_PDU_NEW_SHORT() jmesh_pdu_new(JMESH_SHORT_PDU_SIZE)
#define JMESH_PDU_NEW_LONG() jmesh_pdu_new(JMESH_LONG_PDU_SIZE)


#endif // JMESH_PDU_H
