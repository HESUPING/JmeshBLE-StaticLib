#ifndef MESH_DEFINITIONS_H_
#define MESH_DEFINITIONS_H_

#define MESH_PROVISIONING_AD_TYPE 0x29
#define MESH_MESSAGE_AD_TYPE 0x2A
#define MESH_BEACON_AD_TYPE 0x2B

#define MESH_DEVICE_UUID_LENGTH 16

#define MESH_KEY_LENGTH 16
#define MESH_NETWORK_KEY_LENGTH MESH_KEY_LENGTH
#define NETWORK_ID_LENGTH 8
#define LABEL_UUID_SIZE 16

#define PROXY_PDU_LENGTH_MAX 66
#define ALL_NODES_GROUP_ADDR 0xffff
enum Beacon_Type{
    Unprovisioned_Device_Beacon = 0,
    Secure_Network_Beacon = 1,
};
enum Nonce_Type{
    Network_Nonce = 0,
    Application_Nonce,
    Device_Nonce,
    Proxy_Nonce,
};


typedef enum
{
    /** Key refresh phase 0. Indicates normal device operation. */
    MESH_KEY_REFRESH_PHASE_0,
    /** Key refresh phase 1. Old keys are used for packet transmission, but new keys can be used to receive messages. */
    MESH_KEY_REFRESH_PHASE_1,
    /** Key refresh phase 2. New keys are used for packet transmission, but old keys can be used to receive messages. */
    MESH_KEY_REFRESH_PHASE_2,
    /** Key refresh phase 3. Used to complete a key refresh procedure and transition back to phase 0. */
    MESH_KEY_REFRESH_PHASE_3,
    MESH_KEY_REFRESH_PHASE_INVALID,
} mesh_key_refresh_phase_t;


#endif

