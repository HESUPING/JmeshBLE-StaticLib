#include "reg_sysc_cpu.h"
#include "pin_share.h"
void pshare_funcio_set(uint8_t io_num, uint8_t idx, uint8_t en)
{
	uint32_t enable_map;

	enable_map = sysc_cpu_func_io_en_getf();
	if(en == DISABLE)
	{
		enable_map &= (~(1 << io_num));
		sysc_cpu_func_io_en_setf(enable_map);
		return;
	}
	switch(io_num)
	{
		case FUNC_IO_0:
			sysc_cpu_func_io00_sel_setf(idx);
			break;
		case FUNC_IO_1:
			sysc_cpu_func_io01_sel_setf(idx);
			break;
		case FUNC_IO_2:
			sysc_cpu_func_io02_sel_setf(idx);
			break;
		case FUNC_IO_3:
			sysc_cpu_func_io03_sel_setf(idx);
			break;
		case FUNC_IO_4:
			sysc_cpu_func_io04_sel_setf(idx);
			break;
		case FUNC_IO_5:
			sysc_cpu_func_io05_sel_setf(idx);
			break;
		case FUNC_IO_6:
			sysc_cpu_func_io06_sel_setf(idx);
			break;
		case FUNC_IO_7:
			sysc_cpu_func_io07_sel_setf(idx);
			break;
		case FUNC_IO_8:
			sysc_cpu_func_io08_sel_setf(idx);
			break;
		case FUNC_IO_9:
			sysc_cpu_func_io09_sel_setf(idx);
			break;
		case FUNC_IO_10:
			sysc_cpu_func_io10_sel_setf(idx);
			break;
		case FUNC_IO_11:
			sysc_cpu_func_io11_sel_setf(idx);
			break;
		case FUNC_IO_12:
			sysc_cpu_func_io12_sel_setf(idx);
			break;
		case FUNC_IO_13:
			sysc_cpu_func_io13_sel_setf(idx);
			break;
		case FUNC_IO_14:
			sysc_cpu_func_io14_sel_setf(idx);
			break;
		case FUNC_IO_15:
			sysc_cpu_func_io15_sel_setf(idx);
			break;
		case FUNC_IO_16:
			sysc_cpu_func_io16_sel_setf(idx);
			break;
		case FUNC_IO_17:
			sysc_cpu_func_io17_sel_setf(idx);
			break;
		case FUNC_IO_18:
			sysc_cpu_func_io18_sel_setf(idx);
			break;
		case FUNC_IO_19:
			sysc_cpu_func_io19_sel_setf(idx);
			break;
		case FUNC_IO_20:
			sysc_cpu_func_io20_sel_setf(idx);
			break;
		case FUNC_IO_21:
			sysc_cpu_func_io21_sel_setf(idx);
			break;
		default:
			break;

	}
	enable_map |= (1 << io_num);
	sysc_cpu_func_io_en_setf(enable_map);
}
