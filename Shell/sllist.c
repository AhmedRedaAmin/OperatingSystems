//
// All rights reserved to the original author of the list
// StackExchange user 2679083 "oddlogic"
//

#include <stdlib.h>
#include "sllist.h"

struct sllist* sllist_create(void)
{
    struct sllist *sllist;
    sllist = (struct sllist *) malloc(sizeof(struct sllist));
    if (sllist != NULL) {
        sllist->head = NULL;
        sllist->tail = NULL;
        sllist->current = NULL;
        sllist->size = 0;
    }
    return sllist;
}

void sllist_destroy(struct sllist *sllist)
{
    struct lnode *save_next;
    sllist->current = sllist->head;
    while(sllist->current != NULL) {
        save_next = sllist->current->next;
        free(sllist->current->data);
        free(sllist->current);
        sllist->current = save_next;
    }
    free(sllist);
}

int sllist_push_front(struct sllist *sllist, char *key,void *data)
{
    struct lnode *lnode;
    lnode = (struct lnode *) malloc(sizeof(struct lnode));
    if (lnode == NULL)
        return -1;
    lnode->data = data;
    lnode->key = key;
    lnode->next = sllist->head;
    sllist->head = lnode;
    if (sllist->size == 0)
        sllist->tail = lnode;
    sllist->size++;
    return 0;

}

int sllist_push_back(struct sllist *sllist, char *key,void *data)
{
    struct lnode *lnode;
    lnode = (struct lnode *) malloc(sizeof(struct lnode));
    if (lnode ==NULL)
        return -1;
    lnode->data = data;
    lnode->key = key;
    lnode->next = NULL;
    if (sllist->size == 0) {
        sllist->head = lnode;
        sllist->tail = lnode;
    } else {
        sllist->tail->next = lnode;
        sllist->tail = lnode;
    }
    sllist->size++;
    return 0;
}

void* sllist_pop_front(struct sllist *sllist)
{
    if (sllist->size == 0)
        return NULL;
    void* data = sllist->head->data;
    struct lnode *save_head = sllist->head;
    if (sllist->size == 1) {
        sllist->head = NULL;
        sllist->tail = NULL;
        //Clear current since it shouldn't be used.
        sllist->current = NULL;
    } else {
        sllist->head = sllist->head->next;
    }
    free(save_head);
    sllist->size--;
    return data;
}

void* sllist_pop_back(struct sllist *sllist)
{
    if (sllist->size == 0)
        return NULL;
    void *data = sllist->tail->data;
    struct lnode *save_tail = sllist->tail;
    if (sllist->size == 1) {
        sllist->head = NULL;
        sllist->tail = NULL;
        //Clear current since it shouldn't be used.
        sllist->current = NULL;
    } else {
        struct lnode *new_tail = sllist->head;
        while(new_tail->next->next != NULL)
            new_tail = new_tail->next;
        sllist->tail = new_tail;
        sllist->tail->next = NULL;
    }
    free(save_tail);
    sllist->size--;
    return data;
}

int sllist_step(struct sllist *sllist)
{
    if (sllist->current == NULL)
        return 1;
    else {
        sllist->current = sllist->current->next;
        return 0;
    }
}

void* sllist_read_index(struct sllist *sllist, int index)
{
    if ( ((sllist->size - index - 1) < 0 ) || (index < 0) )
        return NULL;
    struct lnode *target;
    target = sllist->head;
    for(int i = 0; i < index; i++)
        target = target->next;
    return (target->data);
}

int sllist_insert_after(struct sllist *sllist, int index, char *key,void *data)
{
    if ( ((sllist->size - index - 1) < 0 ) || (index < 0) )
        return 1;
    struct lnode *target;
    target = sllist->head;
    for(int i = 0; i < index; i++)
        target = target->next;
    struct lnode *lnode;
    lnode = (struct lnode *) malloc(sizeof(struct lnode));
    if (lnode == NULL)
        return -1;
    lnode->data = data;
    lnode->key = data;
    lnode->next = target->next;
    target->next = lnode;
    if (index == sllist->size - 1) //if inserting after tail
        sllist->tail = lnode;
    sllist->size++;
    return 0;

}

void* sllist_extract_after(struct sllist *sllist, int index)
{
    if ( ((sllist->size - index - 2) < 0 ) || (index < 0) )
        return NULL;
    struct lnode *target;
    target = sllist->head;
    for(int i = 0; i < index; i++)
        target = target->next;
    if (index == sllist->size - 1) //if extracting tail
        sllist->tail = target;
    void *data = target->next->data;
    struct lnode *save_obsolete = target->next;
    target->next = target->next->next;
    free(save_obsolete);
    sllist->size--;
    return data;
}
