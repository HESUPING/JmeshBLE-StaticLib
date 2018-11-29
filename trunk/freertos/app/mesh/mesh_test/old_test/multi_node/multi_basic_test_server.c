/*
 * multi_basic_test_server.c
 *
 *  Created on: 2018Äê5ÔÂ17ÈÕ
 *      Author: jiachuang
 */


#include "osapp_config.h"
#ifdef OSAPP_MESH
#include "mesh_test_config.h"
#ifdef MESH_TEST_BASIC_MULTI_NODE
#include "multi_basic_test_common.h"






void generate_device_key_by_ecdh_and_salt_done()
{
    LOG(3,"unprov_dev_net_key_all_keys_generate_done\n");
    //FOR DEBUG
    #ifdef TEST_APP_DEBUG
        provisioner_init_mesh_provision_data();
    #endif
    //set iv index
    //iv_index = provision_data.current_iv_index;
    mesh_beacon_iv_index_set(provision_data.current_iv_index);
    //init self
    uint8_t add_key_statue = 0;
    init_elmt_addr(provision_data.unicast_addr);
    init_elmt_addr(provision_data.unicast_addr + 1);
    
    //config_server_add_netkey will generate all keys
    config_server_add_netkey(provision_data.network_key , provision_data.key_index , &add_key_statue);
    
    //ELEMENT 0/1
    server_elmts[0].uni_addr = provision_data.unicast_addr;
    server_elmts[1].uni_addr = provision_data.unicast_addr + 1;

}
void unprov_dev_complete_callback(uint8_t success , uint8_t reason)
{
    if(success == 1)
    {
        //generate device key
        generate_device_key_by_ecdh_and_salt(generate_device_key_by_ecdh_and_salt_done);
    }
}


#endif
#endif




