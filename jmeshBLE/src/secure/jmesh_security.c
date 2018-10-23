#include"jmesh_security.h"



void jmesh_generate_nonce(unsigned char* nonce,unsigned char type,unsigned char opcode,unsigned long seq,unsigned short src,unsigned short dst,unsigned long iv_index)
{
    nonce[0]=type;
    nonce[1]=opcode;
    nonce[2]=seq>>16;
    nonce[3]=seq>>8;
    nonce[4]=seq;
    nonce[5]=src>>8;
    nonce[6]=src;
    nonce[7]=dst>>8;
    nonce[8]=dst;
    nonce[9]=iv_index>>24;
    nonce[10]=iv_index>>16;
    nonce[11]=iv_index>>8;
    nonce[12]=iv_index;
}

int jmesh_security_decrypt(unsigned short length,unsigned char* data,unsigned char* nonce,jmesh_key_t key,unsigned char mic_length)
{
		/* when config opcode is 2 and access length is 0, the security length is 6*/
    if(length<6||length>(32*12)){//384
        return -1;
    }
    if(0!=security_aes_ccm_decrypt2(key,nonce,data, length,0,(MIC_MODE)mic_length)){
        return -1;
    }
    return length-mic_length;
}
int jmesh_security_encrypt(unsigned short length,unsigned char* data,unsigned char* nonce,jmesh_key_t key,unsigned char mic_length)
{
    if(length==0||length>(32*12-4)){//380
        return -1;
    }
    security_aes_ccm_encrypt2(key, nonce, data, length, 0, (MIC_MODE)mic_length);
    return length+mic_length;
}

jmesh_addr_t jmesh_security_cal_virtual_addr(unsigned char* uuid)
{
    unsigned char mac[16];
    unsigned short virtual_address;
    jmesh_key_t salt={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//s1("vtad");
    security_AES_CMAC(salt,16,uuid,mac);
    virtual_address=mac[1]&0x3f;
    virtual_address<<=8;
    virtual_address|=mac[0];
    virtual_address|=0x8000;
    return virtual_address;
}
unsigned char jmesh_security_cal_aid(jmesh_key_t key)
{
    k4_result_t k4_value;
    security_k4_derivation(key,&k4_value);
    return k4_value;
}
unsigned char jmesh_security_cal_master_encryption_and_privacy_keys(jmesh_key_t netkey,jmesh_key_t encryption_key,jmesh_key_t privacy_key)
{
     k2_result_t  k2_result;
     unsigned char p[1]={0};
     security_k2_derivation(netkey, p,1, &k2_result);
     memcpy(encryption_key,k2_result.encryption_key,JMESH_KEY_SIZE);
     memcpy(privacy_key,k2_result.privacy_key,JMESH_KEY_SIZE);
     return k2_result.nid;
}
unsigned char jmesh_security_cal_friendship_encryption_and_privacy_keys(jmesh_key_t netkey,unsigned char* p,jmesh_key_t encryption_key,jmesh_key_t privacy_key)
{
    k2_result_t  k2_result;
    security_k2_derivation(netkey, p,9,&k2_result);
     memcpy(encryption_key,k2_result.encryption_key,JMESH_KEY_SIZE);
     memcpy(privacy_key,k2_result.privacy_key,JMESH_KEY_SIZE);
     return k2_result.nid;
}
void jmesh_security_cal_netid(jmesh_key_t netkey,jmesh_netid_t netid)
{
    k3_result_t  result;
    security_k3_derivation(netkey,&result);
    memcpy(netid,result.network_id,JMESH_NETID_SIZE);
}
/*
salt = s1(��nkik��)
P = ��id128�� || 0x01
IdentityKey = k1 (NetKey, salt, P)
*/
void jmesh_security_cal_identity_key(jmesh_key_t netkey,jmesh_key_t identity_key)
{
    k1_result_t k1_result;
    jmesh_key_t identity_key_salt={0xf8,0x79,0x5a,0x1a,0xab,0xf1,0x82,0xe4,0xf1,0x63,0xd8,0x6e,0x24,0x5e,0x19,0xf4};
    unsigned char p[6]={'i','d','1','2','8',0x01};

    security_k1_derivation(netkey,16,p,6,identity_key_salt, &k1_result);

    memcpy(identity_key,k1_result.k1,JMESH_KEY_SIZE);
}
/*
salt = s1(��nkbk��)
P = ��id128�� || 0x01
IdentityKey = k1 (NetKey, salt, P)
*/
void jmesh_security_cal_beacon_key(jmesh_key_t netkey,jmesh_key_t beacon_key)
{
    k1_result_t k1_result;
    jmesh_key_t identity_key_salt={0x2c,0x24,0x61,0x9a,0xb7,0x93,0xc1,0x23,0x3f,0x6e,0x22,0x67,0x38,0x39,0x3d,0xec};
    unsigned char p[6]={'i','d','1','2','8',0x01};
    security_k1_derivation(netkey,16,p,6,identity_key_salt, &k1_result);
    memcpy(beacon_key,k1_result.k1,JMESH_KEY_SIZE);
}


#ifdef JMESH_TEST
#ifdef JMESH_TEST_SECURITY

void salt_test(void)
{
    int i;
    jmesh_key_t key;
    unsigned char salt[5]="test";
    printf("------------------salt test---------------------\n");
    printf("salt(test) expected output is :\n\tb73cefbd641ef2ea598c2b6efb62f79c\n the output is:\n\t");
    security_s1_salt_generation(salt,strlen("test"),key);
    for(i=0;i<16;i++){
        printf("%x",key[i]);
    }
    printf("\n");
}
void k1_test(void)
{
    int i;

    printf("------------------k1 test---------------------\n");
    printf("k1 input N is: \n\t3216d1509884b533248541792b877f98\nP is: \n\t5a09d60797eeb4478aada59db3352a0d\nsalt is:\n\t2ba14ffa0df84a2831938d57d276cab4\nexpected k1 is:f6ed15a8934afbe7d83e8dcb57fcf5d7\nthe output is:\n\t");

    jmesh_key_t k1_n={0x32,0x16,0xd1,0x50,0x98,0x84,0xb5,0x33,0x24,0x85,0x41,0x79,0x2b,0x87,0x7f,0x98};
    jmesh_key_t k1_p={0x5a,0x09,0xd6,0x07,0x97,0xee,0xb4,0x47,0x8a,0xad,0xa5,0x9d,0xb3,0x35,0x2a,0x0d};
    jmesh_key_t k1_salt={0x2b,0xa1,0x4f,0xfa,0x0d,0xf8,0x4a,0x28,0x31,0x93,0x8d,0x57,0xd2,0x76,0xca,0xb4};
    k1_result_t k1_result;
    security_k1_derivation(k1_n,16,k1_p,16,k1_salt,&k1_result);
    for(i=0;i<16;i++){
        printf("%x",k1_result.k1[i]);
    }
    printf("\n");
}
void k2_test(void)
{
    int i;
    unsigned char k2_n[16]={0xf7,0xa2,0xa4,0x4f,0x8e,0x8a,0x80,0x29,0x06,0x4f,0x17,0x3d,0xdc,0x1e,0x2b,0x00};
    unsigned char k2_p[9]={0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09};
    k2_result_t  k2_result;
    security_k2_derivation(k2_n, k2_p,9,&k2_result);

    printf("------------------k2 test---------------------\n");
    printf("\nk2 input Nis:\n\tf7a2a44f8e8a8029064f173ddc1e2b00\nP is:\n\t010203040506070809\nexpected output NID:\n\t73\nexpected encryption key:\n\t11efec0642774992510fb5929646df49\nexpected privacykey:\n\td4d7cc0dfa772d836a8df9df5510d7a7\nthe output nid is:\n\t");
    printf("%x\nthe output encryption key is:\n\t",k2_result.nid);
    for(i=0;i<16;i++){
        printf("%x",k2_result.encryption_key[i]);
    }
    printf("\nthe output privacy key is:\n\t");
    for(i=0;i<16;i++){
        printf("%x",k2_result.privacy_key[i]);
    }
    printf("\n");
}
void k3_test(void)
{

    printf("------------------k3 test---------------------\n");
}
void aid_test(void)
{
    jmesh_key_t key={0x63,0x96,0x47,0x71,0x73,0x4f,0xbd,0x76,0xe3,0xb4,0x05,0x19,0xd1,0xd9,0x4a,0x48};

    printf("------------------aid test---------------------\n");
    printf("cal the appkey:63964771734fbd76e3b40519d1d94a48,expected aid:\n\t26\nthe result is:\n\t%x\n",jmesh_security_cal_aid(key));
}
void nid_test(void)
{
    int i;
    jmesh_key_t netkey={0x7d,0xd7,0x36,0x4c,0xd8,0x42,0xad,0x18,0xc1,0x7c,0x2b,0x82,0x0c,0x84,0xc3,0xd6};
    jmesh_key_t encryption_key;
    jmesh_key_t privacy_key;

    printf("------------------nid test---------------------\n");
    printf("cal nid the netkey is:\n\t7dd7364cd842ad18c17c2b820c84c3d6\nthe expected nid is:\n\t68\nthe expected encryption_key is:\n\t0953fa93e7caac9638f58820220a398e\nthe expected privacy_key is:\n\t8b84eedec100067d670971dd2aa700cf\n");
    printf("the result nid is:\n\t%x\n",jmesh_security_cal_master_encryption_and_privacy_keys(netkey,encryption_key,privacy_key));
    printf("the result encryption_key is:\n\t");
    for(i=0;i<16;i++)
        printf("%02x",encryption_key[i]);
    printf("\nthe result privacy_key is:\n\t");
    for(i=0;i<16;i++)
        printf("%02x",privacy_key[i]);
    printf("\n");
}
void netid_test(void)
{

    int i;
    jmesh_key_t netkey={0x7d,0xd7,0x36,0x4c,0xd8,0x42,0xad,0x18,0xc1,0x7c,0x2b,0x82,0x0c,0x84,0xc3,0xd6};
    jmesh_netid_t netid;

    printf("------------------netid test---------------------\n");
    jmesh_security_cal_netid(netkey,netid);
    printf("the netkey is\n\t7dd7364cd842ad18c17c2b820c84c3d6\nthe expected netid is:\n\t3ecaff672f673370\nthe result is:\n\t");
    for(i=0;i<8;i++){
        printf("%02x",netid[i]);
    }
    printf("\n");
}
void identity_key_test(void)
{
     int i;
    jmesh_key_t netkey={0x7d,0xd7,0x36,0x4c,0xd8,0x42,0xad,0x18,0xc1,0x7c,0x2b,0x82,0x0c,0x84,0xc3,0xd6};
    jmesh_key_t identity_key;

    printf("------------------identity key test---------------------\n");
    jmesh_security_cal_identity_key(netkey,identity_key);
    printf("the netkey is\n\t7dd7364cd842ad18c17c2b820c84c3d6\nthe expected identity_key is:\n\t84396c435ac48560b5965385253e210c\nthe result is:\n\t");
    for(i=0;i<16;i++){
        printf("%02x",identity_key[i]);
    }
    printf("\n");
}
void beacon_key_test(void)
{
     int i;
    jmesh_key_t netkey={0x7d,0xd7,0x36,0x4c,0xd8,0x42,0xad,0x18,0xc1,0x7c,0x2b,0x82,0x0c,0x84,0xc3,0xd6};
    jmesh_key_t beacon_key;

    printf("------------------beacon key test---------------------\n");
    jmesh_security_cal_beacon_key(netkey,beacon_key);
    printf("the beacon_key is\n\t7dd7364cd842ad18c17c2b820c84c3d6\nthe expected identity_key is:\n\t5423d967da639a99cb02231a83f7d254\nthe result is:\n\t");
    for(i=0;i<16;i++){
        printf("%02x",beacon_key[i]);
    }
    printf("\n");
}
void security_mic4_test(void)
{
    int i;

    jmesh_key_t key={0x09,0x53,0xfa,0x93,0xe7,0xca,0xac,0x96,0x38,0xf5,0x88,0x20,0x22,0x0a,0x39,0x8e};
    jmesh_nonce_t nonce={0x00,0x04,0x31,0x29,0xab,0x00,0x03,0x00,0x00,0x12,0x34,0x56,0x78};
    unsigned char pdu[32]={0x12,0x01,0x80,0x26,0xac,0x01,0xee,0x9d,0xdd,0xfd,0x21,0x69,0x32,0x6d,0x23,0xf3,0xaf,0xdf};

    printf("------------------security mic4 test---------------------\n");
    jmesh_security_encrypt(18,pdu,nonce,key,4);
    printf("expected output is:\n\t0afba8c63d4e686364979deaf4fd40961145939cda0e\nthe output is:\n\t");
    for(i=0;i<22;i++)
        printf("%02x",pdu[i]);
    printf("\n");
    printf("expected output is:\n\t12018026ac01ee9dddfd2169326d23f3afdf\nthe output ret=%d is:\n\t",jmesh_security_decrypt(22,pdu,nonce,key,4));
    for(i=0;i<18;i++)
        printf("%02x",pdu[i]);
    printf("\n");
}
void security_mic8_test(void)
{
    int i;

    jmesh_key_t key={0x09,0x53,0xfa,0x93,0xe7,0xca,0xac,0x96,0x38,0xf5,0x88,0x20,0x22,0x0a,0x39,0x8e};
    jmesh_nonce_t nonce={0x00,0x04,0x31,0x29,0xab,0x00,0x03,0x00,0x00,0x12,0x34,0x56,0x78};
    unsigned char pdu[32]={0x12,0x01,0x80,0x26,0xac,0x01,0xee,0x9d,0xdd,0xfd,0x21,0x69,0x32,0x6d,0x23,0xf3,0xaf,0xdf};

    printf("------------------security mic8 test---------------------\n");
    jmesh_security_encrypt(18,pdu,nonce,key,8);
    printf("expected output is:\n\t12018026ac01ee9dddfd2169326d23f3afdf\nthe output ret=%d is:\n\t",jmesh_security_decrypt(26,pdu,nonce,key,8));
    for(i=0;i<18;i++)
        printf("%02x",pdu[i]);
    printf("\n");
}
void jmesh_security_test(void)
{
    printf("--------------------jmesh security_test start--------------------------\n");
    salt_test();
    k1_test();
    k2_test();
    k3_test();
    aid_test();
    nid_test();
    netid_test();
    identity_key_test();
    beacon_key_test();
    security_mic4_test();
    security_mic8_test();

    printf("--------------------jmesh security_test stop --------------------------\n");
}
#endif // JMESH_TEST_SECURITY
#endif // JMESH_TEST
