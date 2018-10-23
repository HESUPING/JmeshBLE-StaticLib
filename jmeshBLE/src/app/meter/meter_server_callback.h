#ifndef METER_SERVER_CALLBACK_H
#define METER_SERVER_CALLBACK_H
#include"stdint.h"

int meter_server_addr_get_callback(uint8_t* data,uint8_t len);
int meter_server_energy_get_callback(uint8_t* data,uint8_t len);
int meter_server_voltage_get_callback(uint8_t* data,uint8_t len);
int meter_server_pdu_get_callback(uint8_t* data,uint8_t len);

#endif // LIGHT_SERVER_CALLBACK_H
