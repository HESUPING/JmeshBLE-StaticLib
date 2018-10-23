#include"os_list.h"
struct st_list {
    struct st_list *next;
};

void os_list_init(os_list_t list)
{
    *list = NULL;
}
void *os_list_head(os_list_t list)
{
    return *list;
}

void *os_list_tail(os_list_t list)
{
    struct st_list *l;

    if(*list == NULL) {
        return NULL;
    }

    for(l = *list; l->next != NULL; l = l->next);

    return l;
}

void os_list_add(os_list_t list, void *item)
{
    struct st_list *l;

    /* Make sure not to add the same element twice */
    os_list_remove(list, item);

    ((struct st_list *)item)->next = NULL;

    l = os_list_tail(list);

    if(l == NULL) {
        *list = item;
    }
    else {
        l->next = item;
    }
}

void os_list_push(os_list_t list, void *item)
{
    os_list_remove(list, item);

    ((struct st_list *)item)->next = *list;
    *list = item;
}
void *os_list_chop(os_list_t list)
{
    struct st_list *l, *r;

    if(*list == NULL) {
        return NULL;
    }
    if(((struct st_list *)*list)->next == NULL) {
        l = *list;
        *list = NULL;
        return l;
    }

    for(l = *list; l->next->next != NULL; l = l->next);

    r = l->next;
    l->next = NULL;

    return r;
}

void *os_list_pop(os_list_t list)
{
    struct st_list *l;
    l = *list;
    if(*list != NULL) {
        *list = ((struct st_list *)*list)->next;
    }

    return l;
}

void os_list_remove(os_list_t list, void *item)
{
    struct st_list *l, *r;

    if(*list == NULL) {
        return;
    }

    r = NULL;
    for(l = *list; l != NULL; l = l->next) {
        if(l == item) {
            if(r == NULL) {
                /* First on list */
                *list = l->next;
            }
            else {
                /* Not first on list */
                r->next = l->next;
            }
            l->next = NULL;
            return;
        }
        r = l;
    }
}

int os_list_length(os_list_t list)
{
    struct st_list *l;
    int n = 0;

    for(l = *list; l != NULL; l = l->next) {
        ++n;
    }

    return n;
}

void os_list_insert(os_list_t list, void *previtem, void *newitem)
{
    if(previtem == NULL) {
        os_list_push(list, newitem);
    }
    else {
        ((struct st_list *)newitem)->next = ((struct st_list *)previtem)->next;
        ((struct st_list *)previtem)->next = newitem;
    }
}
void *os_list_item_next(void *item)
{
    return item == NULL? NULL: ((struct st_list *)item)->next;
}

int    os_list_is_in(os_list_t list,void*item)
{
    struct st_list* l;
    for(l=*list;l!=NULL;l=l->next){
        if(l==item){
            return 1;
        }
    }
    return 0;
}
