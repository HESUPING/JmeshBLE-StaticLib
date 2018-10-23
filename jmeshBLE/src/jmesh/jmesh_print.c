#include"jmesh_print.h"
#include"../driver/jmesh_uart.h"
#include"../driver/jmesh_uart_callback.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char sprint_buf[256] = {0};

int _print(const char* fmt, ...)
{
	va_list args;
	int n;
	if(JMESH_UART_DEBUG != JMESH_RTT_LOG) wait_uart_send_over();
	va_start(args, fmt);
	n = vsprintf(sprint_buf, fmt,args);
	va_end(args);

  JMESH_DEBUG_SEND(strlen(sprint_buf),(unsigned char*)sprint_buf);

	return n;
}
void StrToHex(unsigned char *pbDest, char *pszSrc, int nLen)
{
    char h1, h2;
    int i;
    unsigned char s1, s2;
    for (i = 0; i < nLen; i++)
    {
        h1 = pszSrc[2 * i];
        h2 = pszSrc[2 * i + 1];

        s1 = toupper(h1) - 0x30;
        if (s1 > 9)
            s1 -= 7;

        s2 = toupper(h2) - 0x30;
        if (s2 > 9)
            s2 -= 7;

        pbDest[i] = s1 * 16 + s2;
    }
}
void HexToStr(char *pszDest, unsigned char *pbSrc, int nLen)
{
    char    ddl, ddh;
    int i;
    for (i = 0; i < nLen; i++)
    {
        ddh = 48 + pbSrc[i] / 16;
        ddl = 48 + pbSrc[i] % 16;
        if (ddh > 57) ddh = ddh + 7;
        if (ddl > 57) ddl = ddl + 7;
        pszDest[i * 2] = ddh;
        pszDest[i * 2 + 1] = ddl;
    }

    //pszDest[nLen * 2] = '\0';
}

int _print_buffer(int len,char* data,const char* fmt, ...)
{
    int str_len;
    va_list args;
	int n;
	if(JMESH_UART_DEBUG != JMESH_RTT_LOG) wait_uart_send_over();
	va_start(args, fmt);
	n = vsprintf(sprint_buf, fmt,args);
	va_end(args);
	str_len=strlen(sprint_buf);
	if(sprint_buf[str_len-1]=='\n'){
        str_len--;
	}
	if(str_len+len*2>254){
        len=(254-str_len)/2;
	}
    HexToStr(sprint_buf+str_len,(unsigned char*)data,len);
    sprint_buf[str_len+len*2]='\n';
    sprint_buf[str_len+len*2+1]='\0';
    JMESH_DEBUG_SEND(len*2+str_len+1,(unsigned char*)sprint_buf);

	return n;
}
