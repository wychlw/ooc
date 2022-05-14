#ifndef _ITERATOR_H
#define _ITERATOR_H

#include "object.h"

extern class * iterator;

typedef struct ITERATOR_BASE_T
{
    class_base obj_base;
    void *(*data)(void *this);

} iterator_base;

void *it_data(void *_this);

void iterator_constructor(void *UNUSED(_this), va_list *UNUSED(ap_p));
void iterator_destructor(void *UNUSED(_this));
void iterator_operator_iadd(void *_this, va_list *ap_p);
void *iterator_operator_add(void *_this, va_list *ap_p);
void iterator_operator_imin(void *_this, va_list *ap_p);
void *iterator_operator_min(void *_this, va_list *ap_p);

#endif