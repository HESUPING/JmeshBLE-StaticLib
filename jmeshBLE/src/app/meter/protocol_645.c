#include"protocol_645.h"
#include"string.h"

/*
    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16
    68 aa aa aa aa aa aa 68 13 05 33 33 33 33 34 cs 16
    68 aa aa aa aa aa aa 68 13 01 00 e0 16
*/

unsigned char check_sum(unsigned short len,const unsigned char* data){
    unsigned char cs;

    for(cs=0;len>0;){
        cs+=data[--len];
    }
    return cs;
}

int protocol_64507_pick(unsigned short len,const unsigned char* data,unsigned short* offset)
{
    unsigned short i;

    for(i=0;i+11<len;i++){
        if(data[i]==0x68&&data[i+7]==0x68
            &&len>=(i+data[i+9]+12)
            &&data[i+data[i+9]+11]==0x16
            &&data[i+data[i+9]+10]==check_sum(data[i+9]+10,data+i)){
            *offset=i;
            return data[i+9]+12;
        }
    }
    return 0;
}
int protocol_64507_is_prm(const unsigned char* frame)
{
    return !((protocol_64507_t*)frame)->dir;
}
int protocol_64507_is_matched(const unsigned char* sframe,const unsigned char* rframe)
{
    int i;
    if((protocol_64507_is_prm(sframe)!=1)||(protocol_64507_is_prm(rframe)!=0)){//prm check
        return 0;
    }
    for(i=1;i<7;i++){
        if(sframe[i]!=0xaa)
            break;
    }
    if(i==7){
        return 1;
    }
    for(i=1;i<7;i++){   //addr check
        if(sframe[i]!=rframe[i]){
            return 0;
        }
    }
    for(i=10;i<14;i++){   //di check
        if(sframe[i]!=rframe[i]){
            return 0;
        }
    }
    return 1;
}


int protocol_64507_pack(const unsigned char* addr,const protocol_64597_di_t di,unsigned char c,unsigned char len,const unsigned char* data,unsigned char buffer_size,unsigned char* buffer)
{
    int i;
    protocol_64507_t* pdu=(protocol_64507_t*)buffer;
    if(buffer_size<len+16){
        return -1;
    }
    pdu->start_68=0x68;
    pdu->fixed_68=0x68;
    memcpy(pdu->addr,addr,6);
    pdu->c=c;
    pdu->len=len+4;
    for(i=0;i<4;i++){
        pdu->di[i]=di[i]+0x33;
    }
    for(i=0;i<len;i++){
        pdu->data[i]=data[i]+0x33;
    }
    buffer[len+10+4]=check_sum(len+10+4,buffer);
    buffer[len+11+4]=0x16;
    return len+12+4;
}
int protocol_64507_get_data(unsigned char len,const unsigned char* frame,unsigned short buffer_size,unsigned char* buffer)
{
    int i;
    protocol_64507_t* pdu=(protocol_64507_t*)frame;

    if(pdu->len<=4){
        return 0;
    }
    for(i=0;i<pdu->len-4&&i<buffer_size;i++){
        buffer[i]=pdu->data[i]-0x33;
    }
    return i;
}
int protocol_64507_get_di(unsigned char len,const unsigned char* frame,protocol_64507_di_t di)
{
    protocol_64507_t* pdu=(protocol_64507_t*)frame;
    int i;
    if(pdu->len<4){
        return 0;
    }
    for(i=0;i<4;i++){
        di[i]=pdu->di[i]-0x33;
    }
    return 4;
}

int protocol_64597_pick(unsigned short len,const unsigned char* data,unsigned short* offset)
{
    return protocol_64507_pick(len,data,offset);
}
int protocol_64597_is_prm(const unsigned char* frame)
{
    return protocol_64507_is_prm(frame);
}
int protocol_64597_is_matched(const unsigned char* sframe,const unsigned char* rframe)
{
    int i;
    if((protocol_64507_is_prm(sframe)!=1)||(protocol_64507_is_prm(rframe)!=0)){//prm check
        return 0;
    }
    for(i=1;i<7;i++){
        if(sframe[i]!=0xaa){
            break;
        }
    }
    if(i==7){
        return 1;
    }
    for(i=1;i<7;i++){   //addr check
        if(sframe[i]!=rframe[i]){
            return 0;
        }
    }
    for(i=0;i<2;i++){   //di check
        if(sframe[i+10]!=rframe[i+10]){
            return 0;
        }
    }
    return 1;
}
int protocol_64597_pack(const unsigned char* addr,const protocol_64597_di_t di,unsigned char c,unsigned char len,const unsigned char* data,unsigned char buffer_size,unsigned char* buffer)
{
    int i;
    protocol_64597_t* pdu=(protocol_64597_t*)buffer;
    if(buffer_size<len+16){
        return -1;
    }
    pdu->start_68=0x68;
    pdu->fixed_68=0x68;

    memcpy(pdu->addr,addr,6);

    pdu->c=c;

    pdu->len=len+2;

    pdu->di[0]=di[0]+0x33;
    pdu->di[1]=di[1]+0x33;

    for(i=0;i<len;i++){
        pdu->data[i]=data[i]+0x33;
    }
    buffer[len+10+2]=check_sum(len+10+2,buffer);
    buffer[len+11+2]=0x16;
    return len+12+2;
}
int protocol_64597_get_data(unsigned char len,const unsigned char* frame,unsigned short buffer_size,unsigned char* buffer)
{
    int i;
    protocol_64597_t* pdu=(protocol_64597_t*)frame;

    if(pdu->len<=4){
        return 0;
    }
    for(i=0;i<pdu->len-4&&i<buffer_size;i++){
        buffer[i]=pdu->data[i]-0x33;
    }
    return i;
}
int protocol_64597_get_di(unsigned char len,const unsigned char* frame,protocol_64507_di_t di)
{
    protocol_64597_t* pdu=(protocol_64597_t*)frame;
    if(pdu->len<2){
        return 0;
    }
    di[0]=pdu->di[0]-0x33;
    di[1]=pdu->di[1]-0x33;
    return 2;
}

