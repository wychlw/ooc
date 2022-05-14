#ifndef _VECTOR_H
#define _VECTOR_H

#include "object.h"
#include "my_iterator.h"

extern class *vector_iterator;

typedef struct VECTOR_ITERATOR_T
{
    iterator_base inhert;

    void *m_data;
    size_t data_size;
} vector_iterator_base;

extern class *vector;

typedef struct VECTOR_BASE_T
{
    class_base obj_base;

    void *m_data;
    size_t m_size;
    size_t m_capacity;
    size_t data_size;

    // iterators
    void *(*begin)(void *_this);
    void *(*end)(void *_this);

    // capacity
    size_t (*size)(void *_this);
    size_t (*capacity)(void *_this);
    bool (*empty)(void *_this);
    void (*resize)(void *_this, size_t new_capacity);

    // element access
    void *(*data)(void *_this);
    void *(*get_data)(void *_this, size_t n);
    void *(*at)(void *_this, size_t n);
    void *(*front)(void *_this);
    void *(*back)(void *_this);

    // modifier
    void (*clear)(void *_this);
    void (*push_back)(void *_this, void *data_ptr);
    void (*push_back_const)(void *_this, ...);
    void (*pop_back)(void *_this);
    void (*insert)(void *_this, vector_iterator_base *position, void *data_ptr);
    void (*insert_const)(void *_this, vector_iterator_base *position, ...);
    void (*insert_range)(void *_this, vector_iterator_base *position, size_t n, void *data_ptr);
    void (*insert_range_const)(void *_this, vector_iterator_base *position, size_t n, ...);
    void (*insert_iterator)(void *_this, vector_iterator_base *position, void *_begin, void *_end);
    void (*erase)(void *_this, vector_iterator_base *position);
    void (*erase_range)(void *_this, vector_iterator_base *begin, vector_iterator_base *end);
} vector_base;

#endif