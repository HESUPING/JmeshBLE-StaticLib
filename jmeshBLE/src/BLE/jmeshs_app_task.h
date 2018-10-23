#ifndef JMESHS_APP_TASK_H
#define JMESHS_APP_TASK_H
#include "jmeshs_app.h"
#include"jmeshs_prov_task.h"

enum jmeshs_app_msg_id
{
    JMESHS_APP_TRANS_REQ_IND = TASK_FIRST_MSG(TASK_ID_JMESHS_PROV),
    JMESHS_APP_TRANS_CFM,

    JMESHS_APP_TRANS_REQ,
    JMESHS_APP_TRANS_RSP,
};

#endif // JMESHS_PROV_TASK_H
