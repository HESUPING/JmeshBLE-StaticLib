#include"os_callback.h"
#include"../../driver/jmesh_driver_config.h"
#if (JMESH_DRIVER_BX2400)
#include"FreeRTOS.h"
#include"task.h"
#elif (JMESH_DRIVER_X86)
#include"windows.h"
#endif


void os_start_callback(void){
    jmesh_uart_init(JMESH_UART_0, JMESH_UART_BAUD_9600, JMESH_UART_PARITY_EVEN,JMESH_UART_STOP_BITS_1);
    jmesh_gpio_init(JMESH_LED1,JMESH_GPIO_MODE_OUTPUT);
	jmesh_random_init(os_time_ticks());
	jmesh_mac_init();
    jmesh_pdu_init();
    jmesh_addr_init();
    jmesh_TTL_init();
    jmesh_features_init();
    jmesh_network_init();
    jmesh_segment_init();
    jmesh_netkey_init();
    jmesh_access_init();
    jmesh_appkey_init();
	jmesh_device_init();
    jmesh_interface_init();
    jmesh_neighbor_init();
    jmesh_gatt_init();
    jmesh_route_init();
	jmesh_seq_list_init();
    jmesh_gpio_set(JMESH_LED1, GPIO_VALUE_HIGH);
    jmesh_gpio_init(POWER_LIGHT,JMESH_GPIO_MODE_OUTPUT);
		
    jmesh_gpio_set(POWER_LIGHT, GPIO_VALUE_LOW);
	jmesh_set_relay_feature(JMESH_FEATURE_RELAY);//JMESH_FEATURE_RELAY);	JMESH_FEATURE_DISABLE
	jmesh_TTL_set_default(5);		
//		network_light_indicate_init();
    //jmesh_ble_reset();

}
extern void gatt_connect_test(void);
void os_inited_callback(void){
    jmesh_adv_start();
    jmesh_device_beacon_start(20);

    unsigned char key[16]={0,0,0,0,0x11,0x11,0x11,0x11,0x22,0x22,0x22,0x22,0x33,0x33,0x33,0x33};
//    jmesh_netkey_state_set(0,key);
//		jmesh_set_primary_addr(7);
	jmesh_appkey_set(0,200,key);
//		jmesh_device_new(7,2,key,key);
//		config_appkey_add(7,0,1,key);		
//		config_model_app_bind(7,7,0,1,jmesh_appkey_get_by_key_index(0,1));
    jmesh_model_bind_app(&test_client,jmesh_appkey_get_by_key_index(0,200));
    jmesh_model_bind_app(&test_server,jmesh_appkey_get_by_key_index(0,200));
    jmesh_model_bind_app(&light_client,jmesh_appkey_get_by_key_index(0,200));
    jmesh_model_bind_app(&light_server,jmesh_appkey_get_by_key_index(0,200));
    jmesh_model_bind_app(&light_config,jmesh_appkey_get_by_key_index(0,200));
    jmesh_model_bind_app(&realcomm_client,jmesh_appkey_get_by_key_index(0,200));
    jmesh_model_bind_app(&realcomm_server,jmesh_appkey_get_by_key_index(0,200));
    jmesh_model_bind_app(&realcomm_config,jmesh_appkey_get_by_key_index(0,200));
//    jmesh_device_new(7,2,key,key);
    unsigned char key1[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};		
//		config_netkey_add(7,0,key);
//    config_appkey_add(7,0,100,key);
//    light_config_client_button_bind_scene(6,0,1,6,1,1,1);
    static os_timer_event_t timer;
//		config_appkey_delete(7,0,100);
//    jmesh_routing_beacon_start(0);

}
void os_cycle_callback(void){
    #if (JMESH_DRIVER_BX2400)
//    vTaskDelay(1);
    #elif (JMESH_DRIVER_X86)
    Sleep(1);

    #endif
}
