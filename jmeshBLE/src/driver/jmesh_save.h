#ifndef JMESH_SAVE_H
#define JMESH_SAVE_H



extern int jmesh_save_write(signed short name, unsigned short length, unsigned char *data);
extern int jmesh_save_read(signed short name, unsigned short length, unsigned char *data);
extern void jmesh_save_delete(signed short name);

#endif // JMESH_SAVE_H
