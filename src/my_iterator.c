#include "my_iterator.h"
#include "object.h"

void iterator_constructor(void *UNUSED(_this), va_list *UNUSED(ap_p))
{
}
void iterator_destructor(void *UNUSED(_this))
{
}

void iterator_operator_iadd(void *_this, va_list *ap_p)
{
    iterator_base *this = _this;
    int inc_num = va_arg(*ap_p, int);
    for (int i = 0; i < inc_num; i++)
    {
        this->obj_base.self_class->operator_inc(this);
    }
}

void *iterator_operator_add(void *_this, va_list *ap_p)
{
    iterator_base *this = _this;

    iterator_base *res = copy(this);
    res->obj_base.self_class->operator_iadd(res, ap_p);
    return res;
}

void iterator_operator_imin(void *_this, va_list *ap_p)
{
    iterator_base *this = _this;
    int min_num = va_arg(*ap_p, int);
    for (int i = 0; i < min_num; i++)
    {
        this->obj_base.self_class->operator_dec(this);
    }
}

void *iterator_operator_min(void *_this, va_list *ap_p)
{
    iterator_base *this = _this;

    iterator_base *res = copy(this);
    res->obj_base.self_class->operator_imin(res, ap_p);
    return res;
}

class iterator_c = {
    .type_size = sizeof(iterator_base),
    .constructor = iterator_constructor,
    .destructor = iterator_destructor,
    .operator_add = iterator_operator_add,
    .operator_iadd = iterator_operator_iadd,
    .operator_min = iterator_operator_min,
    .operator_imin = iterator_operator_imin};

class *iterator = &iterator_c;

void *it_data(void *_this)
{
    iterator_base *this = _this;
    return this->data(this);
}