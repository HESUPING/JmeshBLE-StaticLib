#ifndef JMESH_MESSAGE_H
#define JMESH_MESSAGE_H

typedef void(*jmesh_message_handler_t)(unsigned short src,unsigned short dst,unsigned short nid,unsigned short aid,unsigned short len,unsigned char* data);

typedef unsigned char jmesh_message_t[3];

unsigned char jmesh_message_fill_opcode(unsigned char* message,unsigned char length,unsigned char* buffer);

#define JMESH_MESSAGE_OPCODE_SIZE(opcode0) ((opcode0&0x80)?(opcode0>>6):1)

#ifdef JMESH_MESSAGE_DEFINE
#define JMESH_MESSAGE_CREATE(message,name)  const unsigned char name[3]=message;
#else
#define JMESH_MESSAGE_CREATE(message,name) extern const unsigned char name[3]
#endif

#endif // JMESH_MESSAGE_H
