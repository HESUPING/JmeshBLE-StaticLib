#ifndef JMESH_PRINT_H
#define JMESH_PRINT_H



#include"stdint.h"
#include <stdarg.h>
#include"jmesh_config.h"
int _print(const char* fmt, ...);
int _print_buffer(int len,char* data,const char* fmt, ...);
int _print_cmd(const char* fmt, ...);
int _print_buffer_cmd(int len,char* data,const char* fmt, ...);
#if(JMESH_CMD_PRINTABLE==1)
    #define print_cmd(fmt, ...) _print_cmd(fmt, ##__VA_ARGS__)
    #define print_buffer_cmd(len,buffer,fmt,...) _print_buffer_cmd(len,(char*)buffer,fmt, ##__VA_ARGS__)
#else
    #define print_cmd(fmt, ...)
    #define print_buffer_cmd(len,buffer,fmt,...)
#endif

#if(JMESH_INFO_PRINTABLE==1)
    #define print_info(fmt, ...) _print(fmt, ##__VA_ARGS__)
    #define print_buffer_info(len,buffer,fmt,...) _print_buffer(len,(char*)buffer,fmt, ##__VA_ARGS__)
#else
    #define print_info(fmt, ...)
    #define print_buffer_info(len,buffer,fmt,...)
#endif

#if(JMESH_NOTE_PRINTABLE==1)
    #define print_note(fmt, ...)  _print("(note)"fmt"", ##__VA_ARGS__)
    #define print_buffer_note(len,buffer,fmt,...) _print_buffer(len,(char*)buffer,"(note)"fmt"", ##__VA_ARGS__)
#else
    #define print_note(fmt, ...)
    #define print_buffer_note(len,buffer,fmt,...)
#endif

#if(JMESH_WARNING_PRINTABLE==1)
    #define print_warning(fmt, ...)  _print("<warning>"fmt"", ##__VA_ARGS__)
    #define print_buffer_warning(len,buffer,fmt,...) _print_buffer(len,(char*)buffer,"<warning>"fmt"", ##__VA_ARGS__)
#else
    #define print_warning(fmt, ...)
    #define print_buffer_warning(len,buffer,fmt,...)
#endif

#if(JMESH_ERROR_PRINTABLE==1)
    #define print_error(fmt, ...)  _print("[error]file:"__FILE__",line:%d,"fmt"", __LINE__,##__VA_ARGS__)
    #define print_buffer_error(len,buffer,fmt,...) _print_buffer(len,(char*)buffer,"[error]file:"__FILE__",line:%d,"fmt"", __LINE__, ##__VA_ARGS__)
#else
    #define print_error(fmt, ...)
    #define print_buffer_error(len,buffer,fmt,...)
#endif


#endif // JMESH_PRINT_H
