/*
 * mesh_gatt_error.h
 *
 *  Created on: 2018Äê8ÔÂ7ÈÕ
 *      Author: huichen
 */

#ifndef FREERTOS_APP_MESH_GATT_MESH_GATT_ERROR_H_
#define FREERTOS_APP_MESH_GATT_MESH_GATT_ERROR_H_

/**
 ****************************************************************************************
 * @addtogroup MESH_GATT_ERRORS_API
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
  @defgroup MESH_GATT_ERRORS Mesh Gatt Global Error Codes
  @{

  @brief Global Error definitions
*/

/** @defgroup MESH_GATT_ERRORS_BASE Error Codes Base number definitions
 * @{ */
#define MESH_GATT_ERROR_BASE_NUM      MESH_GATT_ERROR_ALLOC       ///< Global GATT error base
/** @} */

#define MESH_GATT_SUCCESS                           (MESH_GATT_ERROR_BASE_NUM + 0)  ///< Successful command
#define MESH_GATT_ERROR_INTERNAL                    (MESH_GATT_ERROR_BASE_NUM + 1)  ///< Internal Error
#define MESH_GATT_ERROR_NO_MEM                      (MESH_GATT_ERROR_BASE_NUM + 2)  ///< No Memory for operation
#define MESH_GATT_ERROR_NOT_FOUND                   (MESH_GATT_ERROR_BASE_NUM + 3)  ///< Not found
#define MESH_GATT_ERROR_NOT_SUPPORTED               (MESH_GATT_ERROR_BASE_NUM + 4)  ///< Not supported
#define MESH_GATT_ERROR_INVALID_PARAM               (MESH_GATT_ERROR_BASE_NUM + 5)  ///< Invalid Parameter
#define MESH_GATT_ERROR_INVALID_STATE               (MESH_GATT_ERROR_BASE_NUM + 6)  ///< Invalid state, operation disallowed in this state
#define MESH_GATT_ERROR_INVALID_LENGTH              (MESH_GATT_ERROR_BASE_NUM + 7)  ///< Invalid Length
#define MESH_GATT_ERROR_INVALID_FLAGS               (MESH_GATT_ERROR_BASE_NUM + 8) ///< Invalid Flags
#define MESH_GATT_ERROR_INVALID_DATA                (MESH_GATT_ERROR_BASE_NUM + 9) ///< Invalid Data
#define MESH_GATT_ERROR_DATA_SIZE                   (MESH_GATT_ERROR_BASE_NUM + 10) ///< Invalid Data size
#define MESH_GATT_ERROR_TIMEOUT                     (MESH_GATT_ERROR_BASE_NUM + 11) ///< Operation timed out
#define MESH_GATT_ERROR_NULL                        (MESH_GATT_ERROR_BASE_NUM + 12) ///< Null Pointer
#define MESH_GATT_ERROR_FORBIDDEN                   (MESH_GATT_ERROR_BASE_NUM + 13) ///< Forbidden Operation
#define MESH_GATT_ERROR_INVALID_ADDR                (MESH_GATT_ERROR_BASE_NUM + 14) ///< Bad Memory Address
#define MESH_GATT_ERROR_BUSY                        (MESH_GATT_ERROR_BASE_NUM + 15) ///< Busy
#define MESH_GATT_ERROR_CONN_COUNT                  (MESH_GATT_ERROR_BASE_NUM + 16) ///< Maximum connection count exceeded.
#define MESH_GATT_ERROR_RESOURCES                   (MESH_GATT_ERROR_BASE_NUM + 17) ///< Not enough resources for operation

/**
  @}
*/

#endif /* FREERTOS_APP_MESH_GATT_MESH_GATT_ERROR_H_ */
/// @} MESH_GATT_ERRORS_API
