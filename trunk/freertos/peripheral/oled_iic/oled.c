//******************************************************************************/
#include "oled.h"
#include "iic.h"
#include "reg_iic0.h"
#include "pshare.h"
#include "log.h"
#include "charcode.h"
#include <stdarg.h>
#include <stdio.h>
#include "clk_gate.h"

#define APP_MSG_OLED_QUEUE_SIZE 5
TaskHandle_t handler_oled_task;
//#define HUAMI_OLED

#ifdef HUAMI_OLED
#include "gpio.h"
#define SEG_OFFSET 28
#define MAX_HEIGHT 40
#define MAX_WIDTH 72

#endif

QueueHandle_t oled_queue;

struct oled_str_t
{
    uint8_t x;
    uint8_t y;
    char *str;
};

#ifdef HUAMI_OLED
void iic_delay()
{
	uint32_t i;
	for(i=0;i<200000;i++)
		__NOP();
}


void iic_delay_1s()
{
    uint32_t i,j;

    for(j=0;j<200;j++)
        for(i=0;i<200000;i++)
        __NOP();

}
#endif

/**********************************************
// IIC Write Command
**********************************************/

static void Write_IIC_Command(unsigned char IIC_Command)
{
   iic0_SendAddrCmd(0x00, 0);
   iic0_WriteData(&IIC_Command, 1);

}

/**********************************************
// IIC Write Data
**********************************************/

static void Write_IIC_Data(unsigned char IIC_Data)
{
   iic0_SendAddrCmd(0x40, 0);
   iic0_WriteData(&IIC_Data, 1);
}






static void oled_start_display()
{

#ifndef HUAMI_OLED
	Write_IIC_Command(0xAE);   //display off
	Write_IIC_Command(0x20);	//Set Memory Addressing Mode	
	Write_IIC_Command(0x10);	//00,Horizontal Addressing Mode;01,Vertical Addressing Mode;10,Page Addressing Mode (RESET);11,Invalid
	Write_IIC_Command(0xb0);	//Set Page Start Address for Page Addressing Mode,0-7
	Write_IIC_Command(0xc8);	//Set COM Output Scan Direction
	Write_IIC_Command(0x00);//---set low column address
	Write_IIC_Command(0x10);//---set high column address
	Write_IIC_Command(0x40);//--set start line address
	Write_IIC_Command(0x81);//--set contrast control register
	Write_IIC_Command(0xdf);
	Write_IIC_Command(0xa1);//--set segment re-map 0 to 127
	Write_IIC_Command(0xa6);//--set normal display
	Write_IIC_Command(0xa8);//--set multiplex ratio(1 to 64)
	Write_IIC_Command(0x3F);//
	Write_IIC_Command(0xa4);//0xa4,Output follows RAM content;0xa5,Output ignores RAM content
	Write_IIC_Command(0xd3);//-set display offset
	Write_IIC_Command(0x00);//-not offset
	Write_IIC_Command(0xd5);//--set display clock divide ratio/oscillator frequency
	Write_IIC_Command(0xf0);//--set divide ratio
	Write_IIC_Command(0xd9);//--set pre-charge period
	Write_IIC_Command(0x22); //
	Write_IIC_Command(0xda);//--set com pins hardware configuration
	Write_IIC_Command(0x12);
	Write_IIC_Command(0xdb);//--set vcomh
	Write_IIC_Command(0x20);//0x20,0.77xVcc
	Write_IIC_Command(0x8d);//--set DC-DC enable
	Write_IIC_Command(0x14);//
	Write_IIC_Command(0xaf);//--turn on oled panel 
#else

	Write_IIC_Command(0xAE); //Set display off

	Write_IIC_Command(0xD5); //Display divide ratio/osc. freq. mode
	Write_IIC_Command(0xF0); //Divide ratio 2 70 160 f0 200

	Write_IIC_Command(0xA8); //Multiplex ration mode:40
	Write_IIC_Command(0x27);

	Write_IIC_Command(0xD3); //Set Display Offset
	Write_IIC_Command(0x00); //Set vertical shift

	Write_IIC_Command(0x40); //Set Display Start Line

	Write_IIC_Command(0x8D); //Internal charge pump:
	Write_IIC_Command(0x95); // Enable Charge Pump/ 10h:Disable Charge Pump

	Write_IIC_Command(0x20); //Set page address mode
	Write_IIC_Command(0x02);

	Write_IIC_Command(0xA1); //Segment Remap

	Write_IIC_Command(0xC8); //Set com output scan direction

	Write_IIC_Command(0xDA); //Common pads hardware: alternative
	Write_IIC_Command(0x12);

	Write_IIC_Command(0xAD); //Internal IREF Setting
	Write_IIC_Command(0x30); //Selectting: 30uA

//	Write_IIC_Command(0x81); //Contrast control
//	Write_IIC_Command(0xFF);

	iic_delay();

	Write_IIC_Command(0xD9); //Set pre-charge period
	Write_IIC_Command(0x22);

	Write_IIC_Command(0xDB); //VCOM deselect level mode
	Write_IIC_Command(0x20); //VCOM:0.71*VCC

	Write_IIC_Command(0xA4); //Set Entire Display On/Off

	Write_IIC_Command(0xA6); //Set Normal Display

	iic_delay();

    Write_IIC_Command(0xAF); //Set Display On

    while(1)
    {
        oled_fill(0x00);

    	iic_delay_1s();
    
        oled_fill(0xff);

        iic_delay_1s();
    }
#endif

}

static void oled_setpos(unsigned char x, unsigned char y)
{ 
	Write_IIC_Command(0xb0+y);
	Write_IIC_Command(((x&0xf0)>>4)|0x10);
	Write_IIC_Command((x&0x0f)|0x01);
}


static void oled_showstr(unsigned char x, unsigned char y, char ch[])         //(x:0~127, y:0~8)
{
	unsigned char c = 0,i = 0,j = 0;
	while(ch[j] != '\0')
	{
		c = ch[j] - 32;
		if(x > 120)
		{
			x = 0;
			y++;
		}
		oled_setpos(x,y);
		for(i=0;i<8;i++)
			Write_IIC_Data(F8X16[c*16+i]);
		oled_setpos(x,y+1);
		for(i=0;i<8;i++)
			Write_IIC_Data(F8X16[c*16+i+8]);
		x += 8;
		j++;
	}
}

#ifdef HUAMI_OLED
static void oled_reset()
{
    struct gpioConfigStruct gpio22;

    gpio_InitN(gpio2_2);

	memset(&gpio22, 0, sizeof(gpio22));
	// cfg3_5: output/high
	gpio22.debounce = gpio_Deb;
	gpio22.dir = gpio_Output;
	gpio22.value = gpio_Low;

	gpio_SetConfig(gpio2_2, &gpio22);

    iic_delay();

	gpio_SetOutputValue(gpio2_2,gpio_High);

}
#endif

void oled_init()
{
#ifdef HUAMI_OLED
    oled_reset();
#endif

    pshare_funcio_set(FUNC_IO_16,IO_IIC0_SDA,ENABLE);        //gpio mux 2  -> iic0 sck
    pshare_funcio_set(FUNC_IO_17,IO_IIC0_SCL,ENABLE);        //gpio mux 3  -> iic0 sda
    clk_gate_per_g0(PER_CLKG0_SET_IIC0);

    iic0_Disable();
    iic0_RestartModeEnable();

    iic0_Set7_10Addressing_Master(iic_7_Addressing);

    iic0_SetSpeed(iic_StandardMode);
    iic0_SetMode(iic_Master);
    
    iic0_SetTarAddr((0x3c));
    iic0_UnmaskAllIrq();
    iic0_SetTxTl(0);

    iic0_Enable();

//    while(*( ( volatile uint32_t * )  0x0 ) != 0)
    	oled_start_display();

}



void oled_printf(unsigned char x, unsigned char y, char *fmt, ...)  // char size 16*8
{      
    char *pbuf = pvPortMalloc(17);    // 128bit/8bit = 16 Byte and use 1byte for '\0' 
    struct oled_str_t str_queue;
    va_list args;
    va_start(args, fmt);
    vsprintf(pbuf, fmt, args);
    va_end(args);
    
    pbuf[16] = '\0';
    
    str_queue.x = x;
    str_queue.y = y;
    str_queue.str = pbuf;
    xQueueSend(oled_queue,&str_queue,portMAX_DELAY);
}


void oled_fill(unsigned char fill_Data) 
{
	unsigned char m,n;
#ifndef HUAMI_OLED
	for(m=0;m<8;m++)
	{
		Write_IIC_Command(0xb0+m);		//page0-page1

		Write_IIC_Command(0x00);		//low column start address
		Write_IIC_Command(0x10);		//high column start address
		for(n=0;n<132;n++)
		{
			Write_IIC_Data(fill_Data);
		}

	}
#else
    for(m=0;m<5;m++)
	{
		Write_IIC_Command(0xb0+m);		//page0-page1
		Write_IIC_Command((0x00 + SEG_OFFSET) & 0x0F);		//low column start address
		Write_IIC_Command(0x10 | (SEG_OFFSET >> 4));		//high column start address
		for(n=0;n<10;n++)
		{
			Write_IIC_Data(fill_Data);
		}
        iic_delay();
        for(n=0;n<10;n++)
		{
			Write_IIC_Data(fill_Data);
		}
        iic_delay();
        for(n=0;n<10;n++)
		{
			Write_IIC_Data(fill_Data);
		}
        iic_delay();
        for(n=0;n<10;n++)
		{
			Write_IIC_Data(fill_Data);
		}
        iic_delay();
        for(n=0;n<10;n++)
		{
			Write_IIC_Data(fill_Data);
		}
        iic_delay();
        for(n=0;n<10;n++)
		{
			Write_IIC_Data(fill_Data);
		}
        iic_delay();
        for(n=0;n<10;n++)
		{
			Write_IIC_Data(fill_Data);
		}
        iic_delay();
        for(n=0;n<10;n++)
		{
			Write_IIC_Data(fill_Data);
		}
        iic_delay();
	}
#endif


}

void oled_cls(void) //clear screen
{
	oled_fill(0x00);
}


void oled_on(void)
{
	Write_IIC_Command(0X8D);
	Write_IIC_Command(0X14);
	Write_IIC_Command(0XAF);
}

void oled_off(void)
{
	Write_IIC_Command(0X8D);
	Write_IIC_Command(0X10);
	Write_IIC_Command(0XAE);
}

void oled_task(void *params)
{
    struct oled_str_t str_queue;
    oled_init();
    oled_cls();
    oled_queue = xQueueCreate(APP_MSG_OLED_QUEUE_SIZE,sizeof(struct oled_str_t));

    while(1)
    {
        if(xQueueReceive(oled_queue, &str_queue, portMAX_DELAY)==pdTRUE)
        {
            oled_showstr(str_queue.x,str_queue.y,str_queue.str);
            vPortFree(str_queue.str);
        }
    }

}

