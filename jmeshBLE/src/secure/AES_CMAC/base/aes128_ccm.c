/*
 * aes128_ccm.c
 *
 *  Created on: 2017ï¿½ï¿½10ï¿½ï¿½10ï¿½ï¿½
 *      Author: wz
 */

#include "aes128_ccm.h"


static  unsigned short Counter = 0;
static uint8_t AES_BUFF[AES_BUFF_SIZE];

//cipher_t block_padding(cipher_t origin)
//{
//    cipher_t ret;
//    ret.len_data = origin.len_data;
//    memset(ret.data, 0, 16);
//    memcpy(ret.data, origin.data, origin.len_data);
//    return ret;
//    /*
//    if (origin.len_data == 0){
//        ret.len_data = 16;
//        memset(ret.data, 0, 32);
//    }
//    else if (origin.len_data %16 != 0){
//        uint8_t blocks = origin.len_data / 16 + 1;
//        ret.len_data = blocks * 16;
//        memset(ret.data, 0, ret.len_data);
//        memcpy(ret.data, origin.data, origin.len_data);
//    }
//    else if (origin.len_data % 16 == 0){
//        ret.len_data = origin.len_data;
//        memcpy(ret.data, origin.data, origin.len_data);
//    }
//    return ret;
//    */
//}

uint16_t block_padding2(uint8_t* original, uint16_t ori_len, uint8_t** block)
{
    memset(AES_BUFF, 0, AES_BUFF_SIZE);
    memcpy(AES_BUFF, original, ori_len);
    *block = AES_BUFF;
    return (ori_len/16+1)*16;
}


mac_t aes_cbc_mac(uint8_t* key, uint8_t dat[], uint8_t len_dat)
{
    uint8_t tail_block[16] = {0};
    //2 encrypt and xor operation circularly
    mac_t mac_val = {
        .len = 4
    };
    uint8_t xor_data[16] = {0};
    uint8_t temp_out[16] = {0};
    uint8_t loop = (len_dat/16) + 1 ;
    uint8_t index;
    if (len_dat % 16 != 0){
        memcpy(tail_block, dat + (loop-1)*16, len_dat - (loop-1)*16);
    }
    for (index = 0; index < loop-1; ++index){
        ArrayXor(16, &dat[index*16], xor_data, temp_out);
        aes128_encryption(key, temp_out, mac_val.mac);
        memcpy(xor_data, mac_val.mac, 16);
    }
    //the last block
    ArrayXor(16, tail_block, xor_data, temp_out);
    aes128_encryption(key, temp_out, mac_val.mac);
    memcpy(xor_data, mac_val.mac, 16);
    return mac_val;
}

uint16_t generate_blocks2(uint8_t addition_data, uint8_t* Nonce, uint8_t* payload, uint16_t payload_len, uint8_t** blocks)
{
    if (payload_len > 0xff){
        return 0;
    }
    //------------------b0 ï¿½ï¿½Ê¼ï¿½ï¿½-------------------------------------
    struct _B0_T b0;
    memset(&b0, 0, sizeof(b0));
    //b0.Flags = (AData << 6) | (((M-2)/2) << 3) | (L- 1);
    b0.Flags = 0X49;
    //user input the nonce
    memcpy(b0.Nonce, Nonce, 13);
    /*
    b0.Nonce[0] = packageCounter[0];
    //memcpy(b0.Nonce, packageCounter, 16 - 1 - L);
    //TODO: check the MSB or LSB
    memcpy(b0.Nonce, packageCounter, 5);
    b0.Nonce[4] = Master ? (b0.Nonce[4]>>1) | 0x80 : (b0.Nonce[4]>1) & 0x7f;
    //TODO: check the MSB or LSB
    memcpy(b0.Nonce + 5, IV, 8);
    */
    b0.Len_Payload_h = 0x00;
    b0.Len_Payload_l = payload_len;
    //------------------b1 (Additional data )ï¿½ï¿½Ê¼ï¿½ï¿½-------------------------------------
    struct _B1_T b1;
    memset(&b1, 0, sizeof(b1));
    b1.Len_ADD_h = 0x00;
    b1.Len_ADD_l = 0x01;
    b1.ADD = addition_data;    //1 byte

    uint16_t block_len = block_padding2(payload, payload_len, blocks);
    block_len += 16+16; //Flags + AddData + block_pad[payload]

    memcpy(*blocks + 0, (uint8_t*)&b0, 16);
    memcpy(*blocks + 16, (uint8_t*)&b1, 16);
    memcpy(*blocks + 32, payload, payload_len);

    return block_len;
}

void CTR_encrypt(uint8_t* key,  uint8_t* Nonce, mac_t mic, uint8_t* dat, uint8_t len_dat, MIC_MODE mic_mode)
{
    Counter = 0;
    uint8_t s0[16];
    uint8_t enc_out[16] = {0};
    struct _Ax_t ax = {
        .Flags = 0x01,
        .Counter_h = (Counter >> 8) & 0x00ff,
        .Counter_l = Counter & 0x00ff
    };
    memcpy(ax.Nonce, Nonce, 13);

    //encrypt a0 -> s0
    aes128_encryption(key, (uint8_t*)&ax, enc_out);
    memcpy(s0, enc_out, 16);

    uint8_t loop = (len_dat/16) + 1;
    uint16_t index;
    for (index = 0; index < loop-1 ; ++index){
        Counter++;
        ax.Counter_h = (Counter >> 8) & 0x00ff;
        ax.Counter_l = Counter & 0x00ff;
        aes128_encryption(key, (uint8_t*)&ax, enc_out);
        ArrayXor(16, enc_out, &dat[index*16], &dat[index*16]);
    }
    Counter++;
    ax.Counter_h = (Counter >> 8) & 0x00ff;
    ax.Counter_l = Counter & 0x00ff;
    aes128_encryption(key, (uint8_t*)&ax, enc_out);
    ArrayXor(len_dat-(loop-1)*16, enc_out, &dat[(loop-1)*16], &dat[(loop-1)*16]);
}


void CTR_decrypt(uint8_t* key,  uint8_t* Nonce,  uint8_t* dat, uint8_t len_dat, MIC_MODE mic_mode)
{
    Counter = 0;
    struct _Ax_t ax = {
        .Flags = 0x01,
        .Counter_h = (Counter >> 8) & 0x00ff,
        .Counter_l = Counter & 0x00ff
    };

    memcpy(ax.Nonce, Nonce, 13);
    uint8_t enc_out[16] = {0};

    uint8_t loop = (len_dat/16) + 1;
    uint16_t index;
    for (index = 0; index < loop - 1; ++index){
        //ï¿½ï¿½ï¿½ï¿½ï¿½Ðµï¿½S0Ã»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ü£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ð»ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ò»ï¿½ï¿½MAC,ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ä³ï¿½ï¿½È±ï¿½ï¿½ï¿½ï¿½Ä¶ï¿½16 + M(MAC ï¿½ï¿½ï¿½ï¿½)
        Counter++;
        ax.Counter_h = (Counter >> 8) & 0xff;
        ax.Counter_l = Counter & 0xff;

        aes128_encryption(key, (uint8_t*)&ax, enc_out);
        ArrayXor(16, enc_out, &dat[index*16], &dat[index*16]);
    }
    Counter++;
    ax.Counter_h = (Counter >> 8) & 0xff;
    ax.Counter_l = Counter & 0xff;
    aes128_encryption(key, (uint8_t*)&ax, enc_out);
    ArrayXor(len_dat-(loop-1)*16, enc_out, &dat[(loop-1)*16], &dat[(loop-1)*16]);
}

void security_aes_ccm_encrypt2(uint8_t* key, uint8_t* Nonce, uint8_t* dat, uint16_t dat_len, uint8_t a_data, MIC_MODE mic_mode)
{
    //Bx
    uint8_t* blocks;
    uint16_t block_len = generate_blocks2(a_data, Nonce, dat, dat_len, &blocks);
    mac_t mac  = aes_cbc_mac(key, blocks, block_len);
    mac.len = mic_mode;
    memset(mac.mac + mic_mode, 0, 16 - mic_mode);
    //1.
    CTR_encrypt(key, Nonce, mac, dat, dat_len, mic_mode);
    //BUG: ³¤¶È²»¹»
    memcpy(dat+dat_len, mac.mac, mac.len);
}

uint8_t security_aes_ccm_decrypt2(uint8_t* key, uint8_t* Nonce, uint8_t* dat, uint16_t dat_len, uint8_t a_data, MIC_MODE mic_mode)
{
    mac_t mac_recv;
    mac_recv.len = mic_mode;
    memcpy(mac_recv.mac, dat+dat_len-mic_mode, mic_mode);
    CTR_decrypt(key, Nonce, dat, dat_len-mic_mode, mic_mode);

    dat_len-=mic_mode;

    uint8_t* blocks;
    uint16_t block_len = generate_blocks2(a_data, Nonce, dat, dat_len, &blocks);
    mac_t mac  = aes_cbc_mac(key, blocks, block_len);
    mac.len = mic_mode;
    memset(mac.mac + mic_mode, 0, 16 - mic_mode);
    return memcmp(mac.mac, mac_recv.mac, mic_mode);
}


