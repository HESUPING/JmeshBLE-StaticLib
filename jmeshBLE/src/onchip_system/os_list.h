#ifndef OS_LIST_H
#define OS_LIST_H

#ifndef NULL
#define NULL 0
#endif
typedef void **os_list_t;

void   os_list_init(os_list_t list);
void * os_list_head(os_list_t list);
void * os_list_tail(os_list_t list);
void * os_list_pop (os_list_t list);
void   os_list_push(os_list_t list, void *item);
void * os_list_chop(os_list_t list);
void   os_list_add(os_list_t list, void *item);
void   os_list_remove(os_list_t list, void *item);
int    os_list_length(os_list_t list);
void   os_list_insert(os_list_t list, void *previtem, void *newitem);
void * os_list_item_next(void *item);
int    os_list_is_in(os_list_t list,void*item);

#endif // _OS_LIST_H
