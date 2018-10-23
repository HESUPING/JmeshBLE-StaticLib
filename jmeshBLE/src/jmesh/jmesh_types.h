#ifndef JMESH_TYPES_H
#define JMESH_TYPES_H
#include"stdio.h"
#include"string.h"

#ifndef NULL
#define NULL 0
#endif

#define JMESH_MIC64_SIZE 8
#define JMESH_MIC32_SIZE 4

#define JMESH_KEY_SIZE 16
#define JMESH_NONCE_SIZE 13
#define JMESH_NETID_SIZE 8
#define JMESH_MAC_SIZE 6

#define JMESH_FEATURE_DISABLE     0
#define JMESH_FEATURE_ENABLE      1
#define JMESH_FEATURE_UNSUPPORTED 2


typedef unsigned char jmesh_key_t[JMESH_KEY_SIZE];
typedef unsigned char jmesh_nonce_t[JMESH_NONCE_SIZE];
typedef unsigned char jmesh_netid_t[JMESH_NETID_SIZE];
typedef unsigned char jmesh_mac_t[JMESH_MAC_SIZE];

typedef unsigned short jmesh_addr_t;


#define JMESH_INIT_IV_INDEX         0x12345678
#define JMESH_INVALID_IV_INDEX      0 /**< do not change this */
#define JMESH_DEFAULT_NODE_IDENTITY 0







/* two 12-bit key indexes into three octets,
 * -------------------------
 * |  key ID1  |  key ID2  |
 * b012345670123456701234567
 * |octet0 |octet1 |octet2 |
 * -------------------------
 */
#define JMESH_KEY_INDEX_PACK2(key1,key2,index)      \
do{                                                 \
    (index)[0]=(unsigned char)key1;                   \
    (index)[1]=(unsigned char)((key1>>8)|(key2<<4));  \
    (index)[2]=(unsigned char)(key2>>4);              \
}while(0)

#define JMESH_KEY_INDEX_PICK2(key1,key2,index)              \
do{                                                         \
    key1=(index)[0]|(((unsigned short)((index)[1]&0x0f))<<8);   \
    key2=((index)[1]>>4)|(((unsigned short)(index)[2])<<4);     \
}while(0)

#define JMESH_KEY_INDEX_PACK1(key1,index)   \
do{                                         \
    (index)[0]=(unsigned char)key1;           \
    (index)[1]=(unsigned char)(key1>>8);      \
}while(0)

#define JMESH_KEY_INDEX_PICK1(key1,index)                   \
do{                                                         \
    key1=(index)[0]|(((unsigned short)((index)[1]&0x0f))<<8);   \
}while(0)

#define JMESH_BIG_ENDIAN_FILL2(value,buffer)    do{(buffer)[0]=(unsigned char)(value>>8);(buffer)[1]=(unsigned char)value;}while(0)
#define JMESH_BIG_ENDIAN_PICK2(value,buffer)    do{value=(((unsigned short)(buffer)[0])<<8)|(buffer)[1];}while(0)
#define JMESH_LITTLE_ENDIAN_FILL2(value,buffer) do{(buffer)[1]=(unsigned char)(value>>8);(buffer)[0]=(unsigned char)value;}while(0)
#define JMESH_LITTLE_ENDIAN_PICK2(value,buffer) do{value=(((unsigned short)(buffer)[1])<<8)|(buffer)[0];}while(0)

#define JMESH_BIG_ENDIAN_FILL3(value,buffer)    do{(buffer)[0]=(unsigned char)(value>>16);(buffer)[1]=(unsigned char)(value>>8);(buffer)[2]=(unsigned char)value;}while(0)
#define JMESH_BIG_ENDIAN_PICK3(value,buffer)    do{value=(((unsigned long)(buffer)[0])<<16)|(((unsigned long)(buffer)[1])<<8)|(buffer)[2];}while(0)
#define JMESH_LITTLE_ENDIAN_FILL3(value,buffer) do{(buffer)[2]=(unsigned char)(value>>16);(buffer)[1]=(unsigned char)(value>>8);(buffer)[0]=(unsigned char)value;}while(0)
#define JMESH_LITTLE_ENDIAN_PICK3(value,buffer) do{(((unsigned long)(buffer)[2])<<16)|(((unsigned long)(buffer)[1])<<8)|(buffer)[0];}while(0)

#define JMESH_BIG_ENDIAN_FILL4(value,buffer)    do{(buffer)[0]=(unsigned char)(value>>24);(buffer)[1]=(unsigned char)(value>>16);(buffer)[2]=(unsigned char)(value>>8);(buffer)[3]=(unsigned char)value;}while(0)
#define JMESH_BIG_ENDIAN_PICK4(value,buffer)    do{value=(((unsigned long)(buffer)[0])<<24)|(((unsigned long)(buffer)[1])<<16)|(((unsigned long)(buffer)[2])<<8)|(buffer)[3];}while(0)
#define JMESH_LITTLE_ENDIAN_FILL4(value,buffer) do{(buffer)[3]=(unsigned char)(value>>24);(buffer)[2]=(unsigned char)(value>>16);(buffer)[1]=(unsigned char)(value>>8);(buffer)[0]=(unsigned char)value;}while(0)
#define JMESH_LITTLE_ENDIAN_PICK4(value,buffer) do{value=(((unsigned long)(buffer)[3])<<24)|(((unsigned long)(buffer)[2])<<16)|(((unsigned long)(buffer)[1])<<8)|(buffer)[0];}while(0)


enum{
    JMESH_FAULT_NO_FAULT=0x00,
    JMESH_FAULT_BATTERY_LOW_WARNING=0x01,
    JMESH_FAULT_BATTERY_LOW_ERROR=0x02,
    JMESH_FAULT_SUPPLY_VOLTAGE_TOO_LOW_WARNING=0x03,
    JMESH_FAULT_SUPPLY_VOLTAGE_TOO_LOW_ERROR=0x04,
    JMESH_FAULT_SUPPLY_VOLTAGHE_TOO_HIGH_WARNING=0x05,
    JMESH_FAULT_SUPPLY_VOLTAGHE_TOO_HIGH_ERROR=0x06,
    JMESH_FAULT_POWER_SUPPLY_INTERRUPTED_WARNING=0x07,
    JMESH_FAULT_POWER_SUPPLY_INTERRUPTED_ERROR=0x08,
    JMESH_FAULT_NO_LOAD_WARNING=0x09,
    JMESH_FAULT_NO_LOAD_ERROR=0x0a,
    JMESH_FAULT_OVERLOAD_WARNING=0x0b,
    JMESH_FAULT_OVERLOAD_ERROR=0x0c,
    JMESH_FAULT_OVERHEAT_WARNING=0x0d,
    JMESH_FAULT_OVERHEAT_ERROR=0x0e,
    JMESH_FAULT_CONDENSATION_WARNING=0x0f,
    JMESH_FAULT_CONDENSATION_ERROR=0x10,
    JMESH_FAULT_VIBRATION_WARNING=0x11,
    JMESH_FAULT_VIBRATION_ERROR=0x12,
    JMESH_FAULT_CONFIGURATION_WARNING=0x13,
    JMESH_FAULT_CONFIGURATION_ERROR=0x14,
    JMESH_FAULT_ELEMENT_NOT_CALIBRATED_WARNING=0x15,
    JMESH_FAULT_ELEMENT_NOT_CALIBRATED_ERROR=0x16,
    JMESH_FAULT_MEMORY_WARNING=0x17,
    JMESH_FAULT_MEMORY_ERROR=0x18,
    JMESH_FAULT_SELF_TEST_WARNING=0x19,
    JMESH_FAULT_SELF_TEST_ERROR=0x1a,
    JMESH_FAULT_INPUT_TOO_LOW_WARNING=0x1b,
    JMESH_FAULT_INPUT_TOO_LOW_ERROR=0x1c,
    JMESH_FAULT_INPUT_TOO_HIGH_WARNING=0x1d,
    JMESH_FAULT_INPUT_TOO_HIGH_ERROR=0x1e,
    JMESH_FAULT_INPUT_NO_CHANGE_WARNING=0x1f,
    JMESH_FAULT_INPUT_NO_CHANGE_ERROR=0x20,
    JMESH_FAULT_ACTUATOR_BLOCKED_WARNING=0x21,
    JMESH_FAULT_ACTUATOR_BLOCKED_ERROR=0x22,
    JMESH_FAULT_HOUSING_OPENEd_WARNING=0x23,
    JMESH_FAULT_HOUSING_OPENED_ERROR=0x24,
    JMESH_FAULT_TAMPER_WARNING=0x25,
    JMESH_FAULT_TAMPER_ERROR=0x26,
    JMESH_FAULT_DEVICE_MOVED_WARNING=0x27,
    JMESH_FAULT_DEVICE_MOVED_ERROR=0x28,
    JMESH_FAULT_DEVICE_DROPPED_WARNING=0x29,
    JMESH_FAULT_DEVICE_DROPPED_ERROR=0x2a,
    JMESH_FAULT_OVERFLOW_WARNING=0x2b,
    JMESH_FAULT_OVERFLOW_ERROR=0x2c,
    JMESH_FAULT_EMPTY_WARNING=0x2d,
    JMESH_FAULT_EMPTY_ERROR=0x2e,
    JMESH_FAULT_INTERNAL_BUS_WARNING=0x2f,
    JMESH_FAULT_INTERNAL_BUS_ERROR=0x30,
    JMESH_FAULT_MECHANISM_JAMMED_WARNING=0x2,
    JMESH_FAULT_MECHANISM_JAMMED_ERROR=0x2,

    JMESH_FAULT_VENDOR_SPECIFIC_WARNING=0x80,
    JMESH_FAULT_VENDOR_SPECIFIC_ERROR=0x81,
};
typedef enum{
    JMESH_STATUS_SUCCESS=0x00,
    JMESH_STATUS_INVALID_ADDRESS=0x01,
    JMESH_STATUS_INVALID_MODEL=0x02,
    JMESH_STATUS_INVALID_APPKEY_INDEX=0x03,
    JMESH_STATUS_INVALID_NETKEY_INDEX=0x04,
    JMESH_STATUS_INSUFFCIENT_RESOURCES=0x05,
    JMESH_STATUS_KEY_INDEX_ALREADY_STORED=0x06,
    JMESH_STATUS_INVALID_PUBLISH_PARAMETERS=0x07,
    JMESH_STATUS_NOT_A_SUBSCRIBE_MODEL=0x08,
    JMESH_STATUS_STORAGE_FAILURE=0x09,
    JMESH_STATUS_FEATURE_NOT_SUPPORTED=0x0a,
    JMESH_STATUS_CANNOT_UPDATE=0x0b,
    JMESH_STATUS_CANNOT_REMOVE=0x0c,
    JMESH_STATUS_CANNOT_BIND=0x0d,
    JMESH_STATUS_TEMPORARILY_UNABLE_TO_CHANGE_STATE=0x0e,
    JMESH_STATUS_CANNOT_SET=0x0f,
    JMESH_STATUS_UNSPECIFIED_ERROR=0x10,
    JMESH_STATUS_INVALID_BINDING=0x11,
}JMESH_STATUS_CODE_T;





#endif // JMESH_TYPES_H
