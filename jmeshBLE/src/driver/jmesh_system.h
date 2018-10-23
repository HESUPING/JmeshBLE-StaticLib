#ifndef JMESH_SYSTEM_H
#define JMESH_SYSTEM_H


extern void jmesh_system_timer_start(unsigned short interval_ms,void(*handler)(void));
extern void jmesh_thread_start(void(*handler)(void));

extern void jmesh_random_init(int seed);
extern int jmesh_random_get(int min,int max);
void jmesh_mutex_lock(void);
void jmesh_mutex_unlock(void);



#endif // JMESH_SYSTEM_H
