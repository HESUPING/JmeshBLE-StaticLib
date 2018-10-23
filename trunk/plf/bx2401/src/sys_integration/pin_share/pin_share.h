#ifndef PIN_SHARE_H_
#define PIN_SHARE_H_
#include <stdint.h>
#define FUNC_IO_0					0
#define FUNC_IO_1					1
#define FUNC_IO_2					2
#define FUNC_IO_3					3
#define FUNC_IO_4					4
#define FUNC_IO_5					5
#define FUNC_IO_6					6
#define FUNC_IO_7					7
#define FUNC_IO_8					8
#define FUNC_IO_9					9
#define FUNC_IO_10					10
#define FUNC_IO_11					11
#define FUNC_IO_12					12
#define FUNC_IO_13					13
#define FUNC_IO_14					14
#define FUNC_IO_15					15
#define FUNC_IO_16					16
#define FUNC_IO_17					17
#define FUNC_IO_18					18
#define FUNC_IO_19					19
#define FUNC_IO_20					20
#define FUNC_IO_21					21

#define IO_UART0_TXD				0				
#define IO_UART0_RXD				1
#define IO_UART0_CTS				2
#define IO_UART0_RTS				3
#define IO_UART1_TXD				4
#define IO_UART1_RXD				5
#define IO_IIC0_SCL					6
#define IO_IIC0_SDA					7
#define IO_IIC1_SCL					8
#define IO_IIC1_SDA					9
#define IO_PWM_0					10
#define IO_PWM_1					11
#define IO_PWM_2					12
#define IO_PWM_3					13
#define IO_PWM_4					14

#define ENABLE						1
#define DISABLE						0
void pshare_funcio_set(uint8_t io_num, uint8_t idx, uint8_t en);


#endif