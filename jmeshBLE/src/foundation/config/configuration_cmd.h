#ifndef CONFIGURATION_CMD_H
#define CONFIGURATION_CMD_H
#include"string.h"
#include"stdlib.h"
#include "../../jmesh/jmesh_save_define.h"
#include "../../jmesh/jmesh_config.h"
#include "../../jmesh/jmesh_save.h"
typedef struct {
		unsigned long baudrate;
}cmd_state_t;

extern cmd_state_t cmd_state;
void configuration_cmd_process(unsigned char length,unsigned char* data);

#endif // CONFIGURATION_CMD_H
