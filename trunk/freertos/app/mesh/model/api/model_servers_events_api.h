#ifndef FREERTOS_APP_MESH_MODEL_MODEL_EVENTS_API_H_
#define FREERTOS_APP_MESH_MODEL_MODEL_EVENTS_API_H_
/**
 ****************************************************************************************
 * @addtogroup MESH_MODEL_MODEL_SERVER_EVENTS
 * @ingroup  MESH_MODEL_API
 * @brief defines for BLE MESH MODEL API
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

/*
 * ENUMERATIONS
 ****************************************************************************************
 */
/**Enum of mesh onoff state define */
typedef enum
{
    MESH_ONOFF_SERVER_OFF = 0,
    MESH_ONOFF_SERVER_ON  = 1,
}mesh_onoff_state_t;

/**Mesh model event type. */
typedef enum
{
    ONOFF_MODEL_EVT_SET,
    ONOFF_MODEL_EVT_GET,
}mesh_model_evt_type_t;


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
/** Mesh model event onoff set structure. */
typedef struct
{
    /** Target state. */
    mesh_onoff_state_t target_state;
} mesh_onoff_model_evt_set_t;

/** Mesh model event onoff get structure. */
typedef struct
{
  uint8_t index;
} mesh_onoff_model_evt_get_t;


/** Mesh models event structure. */
typedef struct
{
    /** Type of event. */
    mesh_model_evt_type_t type;
    /** Union of event parameters. */
    union
    {
        mesh_onoff_model_evt_set_t onoff_set;
        mesh_onoff_model_evt_get_t onoff_get;
    } params;
} mesh_model_evt_t;


/**
 * Mesh model event callback type.
 * @param[in] p_evt Event pointer from the configuration server.
 */
typedef void (*mesh_model_evt_cb_t)(const mesh_model_evt_t * p_evt);



/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */


/// @} MESH_MODEL_MODEL_SERVER_EVENTS
#endif /* FREERTOS_APP_MESH_MODEL_MODEL_EVENTS_API_H_ */
