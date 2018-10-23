#ifndef PROTOCOL_645_H
#define PROTOCOL_645_H
#include"stdint.h"
typedef uint8_t protocol_64597_di_t[2];
typedef uint8_t protocol_64507_di_t[4];


unsigned char check_sum(uint16_t len,const uint8_t* data);

int protocol_64507_pick(uint16_t len,const uint8_t* data,uint16_t* offset);
int protocol_64507_is_prm(const uint8_t* frame);
int protocol_64507_is_matched(const uint8_t* sframe,const uint8_t* rframe);
int protocol_64507_pack(const uint8_t* addr,const protocol_64507_di_t di,uint8_t c,uint8_t len,const uint8_t* data,uint8_t buffer_size,uint8_t* buffer);
int protocol_64507_get_data(uint8_t len,const uint8_t* frame,uint16_t buffer_size,uint8_t* buffer);
int protocol_64507_get_di(uint8_t len,const uint8_t* frame,protocol_64507_di_t di);

int protocol_64597_pick(uint16_t len,const uint8_t* data,uint16_t* offset);
int protocol_64597_is_prm(const uint8_t* frame);
int protocol_64597_is_matched(const uint8_t* sframe,const uint8_t* rframe);
int protocol_64597_pack(const uint8_t* addr,const protocol_64597_di_t di,uint8_t c,uint8_t len,const uint8_t* data,uint8_t buffer_size,uint8_t* buffer);
int protocol_64597_get_data(uint8_t len,const uint8_t* frame,uint16_t buffer_size,uint8_t* buffer);
int protocol_64597_get_di(uint8_t len,const uint8_t* frame,protocol_64597_di_t di);

typedef struct protocol_64507_t{
    unsigned char start_68;
    unsigned char addr[6];
    unsigned char fixed_68;
    union{
        unsigned char c;
        struct{
            unsigned char type:5;
            unsigned char seg:1;
            unsigned char err:1;
            unsigned char dir:1;
        };
    };
    unsigned char len;
    unsigned char di[4];
    unsigned char data[2];
}protocol_64507_t;

typedef struct protocol_64597_t{
    unsigned char start_68;
    unsigned char addr[6];
    unsigned char fixed_68;
    union{
        unsigned char c;
        struct{
            unsigned char type:5;
            unsigned char seg:1;
            unsigned char err:1;
            unsigned char dir:1;
        };
    };
    unsigned char len;
    unsigned char di[2];
    unsigned char data[2];
}protocol_64597_t;




#endif // PROTOCOL_645_H
