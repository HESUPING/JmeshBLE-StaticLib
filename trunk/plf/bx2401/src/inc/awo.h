#ifndef AWO_MAIN_H_
#define AWO_MAIN_H_
#include "bx_config.h"
#if HW_BX_VERSION == 2400
	#include "awo_2400.h"
#elif HW_BX_VERSION == 2401
	#include "awo_2401.h"
#else
	#error ERROR: ERROR to define HW_BX_VERSION
#endif

#endif
