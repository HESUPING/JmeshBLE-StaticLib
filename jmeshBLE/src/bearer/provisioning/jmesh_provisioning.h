#ifndef JMESH_PROVISIONING_H
#define JMESH_PROVISIONING_H

#include"stdint.h"

#define LINK_HOLD_DURATION                  30000
#define confirmationInputsLength            1+11+5+64+64

//Attention Duration                 --------   Invite
#define Invite_Attention_Duration                  60

//Algorithm field values             --------   capabilities
#define Capabilities_Algorithm_FIPS_P256_EC              0x0
#define Capabilities_Algorithm_RFU                       0x1 /*0x1-0xff*/
//Public Key field values
#define Capbilities_PublicKey_NoOOB         0x0
#define Capbilities_PublicKey_OOB           0x1
#define Capbilities_PublicKey_Prohibit      0x2 /*0x2-0xff*/

//Authentication Method field values --------    start
#define Start_Authentication_NoOOB          0x0
#define Start_Authentication_StaticOOb      0x1
#define Start_Authentication_OutputOOB      0x2
#define Start_Authentication_InputOOB       0x3
#define Start_Authentication_Prohibit       0x4 /*0x4-0xff*/
//Public key type feild values
#define Start_PublicKey_OOB_Info            ((1)<<0)    /*bit0*/
#define Start_PublicKey_Prohibit            0xfe        /*bit1-bit7*/
//Authentication Action
//1. input
#define InputOOBAct_Push                0x00
#define InputOOBAct_Twist               0x01
#define InputOOBAct_InputNumeric        0x02
#define InputOOBAct_InputAlphaNumeric   0x03
#define InputOOBAct_RFU                 0x04    /*0x04-0xff*/
//2. output
#define OutputOOBAct_Blink              0x00
#define OutputOOBAct_Beep               0x01
#define OutputOOBAct_Vibrate            0x02
#define OutputOOBAct_OutputNumeric      0x03
#define OutputOOBAct_OutputAlphaNumeric 0x04
#define OutputOOBAct_RFU                0x05    /*0x05-0xff*/
//Authentication Size
#define Authentication_Size             0x06

//Failed
//provision fail error code                      Failed
#define Prohibited                      0x00
#define InvalidPDU                      0x01
#define InvalidFormat                   0x02
#define UnexpectedPDU                   0x03
#define ConfirmationFailed              0x04
#define OutofResources                  0x05
#define DecryptionFailed                0x06
#define UnexpectedError                 0x07
#define CannotAssignAddresses           0x08
#define PROV_FAILED_RFU                 0x09    /*0x09-0xff*/
#define PROV_ERROR_CANNOT_CONNECT      0x0a
#define PROV_ERROR_TIME_FLOW           0x0b

#define PROV_COMPLETED                    0xff


typedef enum{
    Prov_Invite         = 0,
    Prov_Capabilities   = 1,
    Prov_Start          = 2,
    Prov_Public_Key     = 3,
    Prov_Input_Complete = 4,
    Prov_Confirmation   = 5,
    Prov_Random         = 6,
    Prov_Data           = 7,
    Prov_Complete       = 8,
    Prov_Failed         = 9,
    Prov_Idle,
}prov_pdu_type_t;

/// 1. invite
typedef struct{
    uint8_t Attention_Duration;
}provision_invite_format_t;

/// 2. capabilities
typedef struct{
    uint8_t Num_of_Elements;
    uint8_t Algorithms[2];
    uint8_t Pulibc_Key_Type;
    uint8_t Static_OOB_Type;
    uint8_t Output_OOB_Size;
    uint8_t Output_OOB_Action[2];
    uint8_t Input_OOB_Size;
    uint8_t Input_OOB_Action[2];
}provision_capabilities_format_t;

/// 3. start
typedef struct{
    uint8_t Algorithm;
    uint8_t PublicKey;
    uint8_t AuthenticationMethod;
    uint8_t AuthenticationAction;
    uint8_t AuthenticationSize;
}provision_start_format_t;

/// 4. Public key
typedef struct{
    uint8_t public_key_x[32];
    uint8_t public_key_y[32];
}provision_public_key_format_t;

/// 5. input complete
typedef struct {
    uint8_t _empty[1];
}provision_input_complete_format_t;

/// 6. confirmation
typedef struct {
    uint8_t Confirmation[16];
}provision_confirmation_format_t;

/// 7. random
typedef struct {
    uint8_t Random[16];
}provision_random_format_t;

/// 8. Data
//WARN: Do not modify the structure of the struct provision_data_format_t
typedef struct {
    uint8_t network_key[16];
    uint8_t key_index[2];
    uint8_t flags;
    uint8_t iv_index[4];
    uint8_t unicast_addr[2];
    uint8_t mic[8];
}provision_data_format_t;



///9. Complete
typedef struct {
    uint8_t _empty[1];
    //empty
}provision_complete_format_t;

///10. failed
typedef struct {
    uint8_t error_code;
}provision_failed_format_t;

extern uint8_t LEN_PROVISION_PARAMETERS[10];
typedef int (*oob_output_action_t)(void* param);

/*----------------------------------capabilities--------------------------------------*/
//algorithms
typedef enum {
    ECDH = 0X0001,
    RFU
}Algorithms;

typedef enum {
    None = 0x0,
    PublicKeyOOB = 0x01,
}PublicKeyType;

typedef enum {
    StaticOOB   = 0x01,
}StaticOOBType;

#define OutputOOBSize(x) x
typedef enum {
    Blink       = 0x0001,
    Beep        = 0x0002,
    Vibrate     = 0x0004,
    OutputNum   = 0x0008,
    OutputAlph  = 0x0010
}OutputOOBAction;

#define InputOOBSize(x) x
typedef enum {
    Push        = 0x0001,
    Twist       = 0x0002,
    InputNum    = 0x0004,
    InputAlph   = 0x0008
}InputOOBAction;

/*------------------------------------------start---------------------------*/
typedef enum {
    NoOOBAuth     = 0x0,
    StaticOOBAuth = 0x01,
    OutputOOBAuth = 0x02,
    InputOOBAuth  = 0x03,
}AuthenticationMethod;

#define BX_DEV_ADDR {1,2,3,4,5,6}
#define Device_OOB_Init(profile_name,\
                        ElementSUM, \
                        Algorithms, \
                        PublicKey, \
                        OOBStatic, \
                        OOBOutputSize, \
                        OOBOutputAction, \
                        OOBInputSize, \
                        OOBInputAction) \
                        provision_capabilities_format_t profile_name = \
                        {ElementSUM, {(ECDH>>8)&0xff, ECDH&0xff}, PublicKey,OOBStatic,\
                        OutputOOBSize(OOBOutputSize),\
                        {((OOBOutputAction)>>8)&0xff, (OOBOutputAction)&0xff},\
                        InputOOBSize(OOBInputSize),\
                        {((OOBInputAction)>>8)&0xff, (OOBInputAction)&0xff}};

void do_authentication_action(uint8_t duration, provision_start_format_t* start_dat, uint8_t* authentication_value);
void verify_authentication_action(provision_start_format_t* start_dat, uint8_t* authentication_value);
void calculate_confirmation(provision_invite_format_t*       invite_dat,
                            provision_capabilities_format_t* capabilities_dat,
                            provision_start_format_t*        start_dat,
                            provision_public_key_format_t*   provisioner_publickey,
                            provision_public_key_format_t*   unporv_device_publickey,
                            uint8_t secret_key[32],
                            uint8_t authentication_value[16],
                            provision_random_format_t* random_output,
                            provision_confirmation_format_t* confirmation_output,
                            uint8_t*                         confirmation_salt,
                            uint8_t*                         confirmation_key);
int  check_confirmation(provision_random_format_t* peer_random,
                        uint8_t* authentication_value,
                        uint8_t* confirmation_key,
                        provision_confirmation_format_t* peer_confirmation);
void calculate_provision_key(uint8_t* confirmation_salt,
                            provision_random_format_t* random_prov,
                            provision_random_format_t* random_dev,
                            uint8_t* secret_key,
                            uint8_t* session_key,
                            uint8_t* session_nonce,
                            uint8_t* device_key);
void encrypt_provision_data(uint8_t* session_key,
                            uint8_t* session_nonce,
                            provision_data_format_t* plaintext);
int  decrypt_provision_data(uint8_t* session_key,
                            uint8_t* session_nonce,
                            provision_data_format_t* ciphertext);









#endif // JMESH_PROVISIONING_H
