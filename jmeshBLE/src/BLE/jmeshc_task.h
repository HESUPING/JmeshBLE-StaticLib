#ifndef _JMESHC_TASK_H
#define _JMESHC_TASK_H

#include "rwip_task.h" // Task definitions
#include "prf_types.h"

enum
{
    JMESHC_DISCOVER_REQ = TASK_FIRST_MSG(TASK_ID_DISC),
    JMESHC_DISCOVER_RSP,

    JMESHC_TRANS_REQ,
    JMESHC_TRANS_RSP,
};

struct jmeshc_discover_req
{
    uint8_t device_index;
};

struct jmeshc_discover_rsp
{
    uint8_t status;
};

struct jmeshc_trans_req
{
    unsigned short len;
    unsigned char data[5];
};

struct jmeshc_trans_rsp
{
    uint8_t status;
};



#endif // _JMESHC_ASK_H
