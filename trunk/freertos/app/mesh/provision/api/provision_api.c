/**
 ****************************************************************************************
 *
 * @file   provision_api.c
 *
 * @brief  .
 *
 * @author  jiachuang
 * @date    2018-09-14 17:15
 * @version <0.0.0.1>
 *
 * @license 
 *              Copyright (C) BlueX Microelectronics 2018
 *                         ALL Right Reserved.
 *
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "osapp_config.h"
#ifdef OSAPP_MESH

#include "provision_api.h"

#include "provisioner.h"
#include "unprov_device.h"
/*
 * MACROS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */




/*
 * GLOBAL VARIABLE DEFINITIONS
 ****************************************************************************************
 */
/**/

/*
 * LOCAL FUNCTIONS DEFINITIONS
 ****************************************************************************************
 */



/**
 ****************************************************************************************
 * @brief   Init provision role and callback handle register.
 *
 * @param[in] role     provision role.
 * @param[in] handle   callback handle pointer.
 *
 ****************************************************************************************
 */
void provision_init(mesh_provsion_role_t role , mesh_prov_evt_cb_t handle)
{
    if (MESH_ROLE_PROVISIONER == role )
    {

    }
    else
    {
        unprov_device_init(handle);
    }
}

/**
 ****************************************************************************************
 * @brief   Send action to mesh stack.
 *
 * @param[in] type     The type of the action message.
 * @param[in] param    The parameter of the action message.
 *
 ****************************************************************************************
 */
void provision_action_send (mesh_prov_action_type_t type , mesh_prov_evt_param_t param)
{
    switch(type)
    {
        /*******PROVISIONER*******/
        //PROV_EVT_AUTH_INPUT_NUMBER
        case  PROV_ACTION_AUTH_INPUT_NUMBER_DONE : //input random number done
        //PROV_EVT_READ_PEER_PUBLIC_KEY_OOB
        case  PROV_ACTION_READ_PEER_PUBLIC_KEY_OOB_DONE :
        //PROV_EVT_BEACON
        case  PROV_ACTION_SET_LINK_OPEN :
        //PROV_EVT_CAPABILITIES
        case  PROV_ACTION_SEND_START_PDU :

        /*******UNPROV DEVICE*******/
        //UNPROV_EVT_AUTH_INPUT_NUMBER
        case  UNPROV_ACTION_AUTH_INPUT_NUMBER_DONE : //input random number done
        {

        }
        break;
        default:break;
    }
}

/**
 ****************************************************************************************
 * @brief   Configure parameter to mesh stack.
 *
 * @param[in] type     The opcode of the configure parameter message.
 * @param[in] param    The parameter of the configuration message.
 *
 ****************************************************************************************
 */
void provision_config (mesh_prov_config_type_t opcode , mesh_prov_evt_param_t param)
{
    switch(opcode)
    {
        /*******PROVISIONER*******/
        case  PROV_SET_PRIVATE_KEY :
        {

        }
        break;
        case  PROV_SET_AUTH_STATIC :
        {

        }
        break;
        case  PROV_SET_DISTRIBUTION_DATA :
        {

        }
        break;
        case  PROV_SET_INVITE_DURATION :
        {

        }
        break;
        case  PROV_RESET :
        {

        }
        break;
        case  PROV_CLEAR_CACHE :
        {

        }
        break;

        /*******UNPROV DEVICE*******/
        case  UNPROV_SET_PROVISION_METHOD :
        case  UNPROV_SET_BEACON :
        case  UNPROV_SET_PRIVATE_KEY :
        case  UNPROV_SET_OOB_CAPS :
        case  UNPROV_SET_AUTH_STATIC :
        case  UNPROV_RESET :
        {
           unprov_device_config(opcode,param);
        }
        break;
        default:break;
    }
}

#endif /* OSAPP_MESH */
