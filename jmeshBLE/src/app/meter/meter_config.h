#ifndef METER_CONFIG_H
#define METER_CONFIG_H
#include"../../access/jmesh_model.h"


#define MESSAGE_METER_CONFIG_REPORT_STATUS              {0xc0,0x09,0x01}/**< data:id+di,interval*/
#define MESSAGE_METER_CONFIG_LINE_STATUS                {0xc0,0x09,0x02}/**< data:id+di+interval*/
JMESH_MESSAGE_CREATE(MESSAGE_METER_CONFIG_REPORT_STATUS,message_meter_config_report_status);
JMESH_MESSAGE_CREATE(MESSAGE_METER_CONFIG_LINE_STATUS,  message_meter_config_line_status);


JMESH_MODEL_NAME(meter_config);

#define METER_CONFIG_COMPANY_ID JMESH_MODEL_COMPANY_ID
#define METER_CONFIG_MODEL_ID   0x0009

#endif
