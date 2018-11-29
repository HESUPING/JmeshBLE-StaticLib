/*
 * mesh_test_config.h
 *
 *  Created on: 2018-3-15
 *      Author: jiachuang
 */
#ifndef FREERTOS_APP_MESH_MESH_TEST_MESH_TEST_CONFIG_H_
#define FREERTOS_APP_MESH_MESH_TEST_MESH_TEST_CONFIG_H_

//#define MESH_CCM_CMAC_QUEUE_TEST            /*   */
//#define MESH_TEST_AES_CCM                  /*   */
//#define MESH_TEST_AES_CMAC                  /*   */
//#define MESH_TEST_PROVISION                 /*   */
//#define MESH_TEST_NETWORK_LAYER             /*   */
//#define MESH_TEST_LOWER_TRANSPORT_LAYER     /*   */
//#define MESH_TEST_BASIC_APP                 /*need open MESH_TEST_PROVISION*/
//#define MESH_TEST_BASIC_MULTI_NODE

//#define MESH_TEST_UART_CTRL  /** <Bx2400 MESH UART TEST TOOL.  when you use this, should define OSAPP_MESH ! */

#ifdef MESH_TEST_BASIC_APP
    #define MESH_TEST_PROVISION
#endif

#ifdef MESH_TEST_BASIC_MULTI_NODE
    #define MESH_TEST_PROVISION
#endif




#endif /* FREERTOS_APP_MESH_MESH_TEST_MESH_TEST_CONFIG_H_ */
