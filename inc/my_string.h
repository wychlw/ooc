#ifndef _STRING_H
#define _STRING_H

#include "my_iterator.h"
#include "object.h"
#include <stdio.h>

extern class *string_iterator;

typedef struct STRING_ITERATOR_T
{
    iterator_base inhert;

    void *which_string;
    size_t offset;
} string_iterator_base;

extern class *string;

typedef struct STRING_BASE_T
{
    class_base obj_base;

    char *m_data;
    size_t m_size;
    size_t m_capacity;

    // iterators
    void *(*begin)(void *_this);
    void *(*end)(void *_this);

    // capacity
    size_t (*size)(void *_this);
    size_t (*length)(void *_this);
    size_t (*capacity)(void *_this);
    bool (*empty)(void *_this);
    void (*resize)(void *_this, size_t new_capacity);

    // element assess
    void *(*data)(void *_this);
    char *(*get)(void *_this, size_t n);
    char *(*at)(void *_this, size_t n);
    char *(*front)(void *_this);
    char *(*back)(void *_this);
    char *(*c_str)(void *_this);

    // modifier
    void (*clear)(void *_this);
    void (*push_back)(void *_this, void *data_ptr);
    void (*push_back_const)(void *_this, ...);
    void (*pop_back)(void *_this);

    void (*insert)(void *_this, string_iterator_base *position, void *data_ptr);
    void (*insert_const)(void *_this, string_iterator_base *position, ...);
    void (*insert_range)(void *_this, string_iterator_base *position, size_t n, void *data_ptr);
    void (*insert_range_const)(void *_this, string_iterator_base *position, size_t n, ...);
    void (*insert_iterator)(void *_this, string_iterator_base *position, void *_begin, void *_end);
    void (*erase)(void *_this, string_iterator_base *position);
    void (*erase_range)(void *_this, string_iterator_base *begin, string_iterator_base *end);

    // input
    void (*fgetc)(void *_this,FILE *file);
    void (*fscan)(void *_this,FILE *file);
    void (*fgets)(void *_this,FILE *file);
    void (*getchar)(void *_this);
    void (*scan)(void *_this);
    void (*getline)(void *_this);
    void (*gets)(void *_this);

} string_base;

#endif