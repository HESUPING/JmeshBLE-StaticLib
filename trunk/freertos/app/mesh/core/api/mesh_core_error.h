/*
 * mesh_core_error.h
 *
 *  Created on: 2018Äê9ÔÂ11ÈÕ
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_CORE_API_MESH_CORE_ERROR_H_
#define FREERTOS_APP_MESH_CORE_API_MESH_CORE_ERROR_H_

/**
 ****************************************************************************************
 * @addtogroup MESH_CORE_ERRORS_API
 * @ingroup  MESH_ERRORS_API
 * @brief defines for BLE MESH ERRORS API
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "sdk_mesh_config_pro.h"


 /**
  @defgroup MESH_CORE_ERRORS Mesh CORE Global Error Codes
  @{

  @brief Global Error definitions
*/

/** @defgroup MESH_CORE_ERRORS_BASE Error Codes Base number definitions
 * @{ */
#define MESH_CORE_ERROR_BASE_NUM      MESH_CORE_ERROR_ALLOC       ///< Global CORE error base
/** @} */

#define MESH_CORE_SUCCESS                           (MESH_CORE_ERROR_BASE_NUM + 0)  ///< Successful command
#define MESH_CORE_ERROR_INTERNAL                    (MESH_CORE_ERROR_BASE_NUM + 1)  ///< Internal Error
#define MESH_CORE_ERROR_NO_MEM                      (MESH_CORE_ERROR_BASE_NUM + 2)  ///< No Memory for operation
#define MESH_CORE_ERROR_NOT_FOUND                   (MESH_CORE_ERROR_BASE_NUM + 3)  ///< Not found
#define MESH_CORE_ERROR_NOT_SUPPORTED               (MESH_CORE_ERROR_BASE_NUM + 4)  ///< Not supported
#define MESH_CORE_ERROR_INVALID_PARAM               (MESH_CORE_ERROR_BASE_NUM + 5)  ///< Invalid Parameter
#define MESH_CORE_ERROR_INVALID_STATE               (MESH_CORE_ERROR_BASE_NUM + 6)  ///< Invalid state, operation disallowed in this state
#define MESH_CORE_ERROR_INVALID_LENGTH              (MESH_CORE_ERROR_BASE_NUM + 7)  ///< Invalid Length
#define MESH_CORE_ERROR_INVALID_FLAGS               (MESH_CORE_ERROR_BASE_NUM + 8) ///< Invalid Flags
#define MESH_CORE_ERROR_INVALID_DATA                (MESH_CORE_ERROR_BASE_NUM + 9) ///< Invalid Data
#define MESH_CORE_ERROR_DATA_SIZE                   (MESH_CORE_ERROR_BASE_NUM + 10) ///< Invalid Data size
#define MESH_CORE_ERROR_TIMEOUT                     (MESH_CORE_ERROR_BASE_NUM + 11) ///< Operation timed out
#define MESH_CORE_ERROR_NULL                        (MESH_CORE_ERROR_BASE_NUM + 12) ///< Null Pointer
#define MESH_CORE_ERROR_FORBIDDEN                   (MESH_CORE_ERROR_BASE_NUM + 13) ///< Forbidden Operation
#define MESH_CORE_ERROR_INVALID_ADDR                (MESH_CORE_ERROR_BASE_NUM + 14) ///< Bad Memory Address
#define MESH_CORE_ERROR_BUSY                        (MESH_CORE_ERROR_BASE_NUM + 15) ///< Busy
#define MESH_CORE_ERROR_CONN_COUNT                  (MESH_CORE_ERROR_BASE_NUM + 16) ///< Maximum connection count exceeded.
#define MESH_CORE_ERROR_RESOURCES                   (MESH_CORE_ERROR_BASE_NUM + 17) ///< Not enough resources for operation
#define MESH_CORE_ERROR_KEYREFRESH_IN_PROCESSING    (MESH_CORE_ERROR_BASE_NUM + 18) ///< key refresh is processing, can not start other refresh process

/**
  @}
*/

#endif /* FREERTOS_APP_MESH_CORE_API_MESH_CORE_ERROR_H_ */
/// @} MESH_CORE_ERRORS_API
