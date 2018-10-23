#ifndef JMESH_DRIVER_CONFIG_H
#define JMESH_DRIVER_CONFIG_H

#define JMESH_DRIVER_X86 0
#define JMESH_DRIVER_BX2400 1
#define JMESH_DRIVER_ANDROID 0

#if(JMESH_DRIVER_BX2400 == 1)
#include"../../../../trunk/plf/bx_debug/bx_dbg.h"
#define JMESH_ASSERT(e)  BX_ASSERT(e)
#else
#define JMESH_ASSERT(e)
#endif

#if(JMESH_DRIVER_X86+JMESH_DRIVER_BX2400+JMESH_DRIVER_ANDROID!=1)
    #error "must choose and only choose one driver platform!"
#endif

#endif // JMESH_DRIVER_CONFIG_H
