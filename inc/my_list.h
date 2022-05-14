#ifndef _LIST_H
#define _LIST_H

#include "object.h"
#include "my_iterator.h"

extern class *list_node;

typedef struct LIST_NODE_BASE_T {
    struct LIST_NODE_T *prev,*next;
    void *data_ptr;
    size_t data_size;
} list_node_base;




#endif