#ifndef JMESH_SAVE_H
#define JMESH_SAVE_H

int jmesh_save_write(unsigned short tag,unsigned short length,unsigned char* data);
int jmesh_save_read(unsigned short tag,unsigned short length,unsigned char* data);
int jmesh_save_clear(unsigned short tag);
int jmesh_save_delete(unsigned short tag,unsigned short length,unsigned char* data);

#endif // JMESH_SAVE_H
