#include "my_vector.h"
#include <malloc.h>
#include <memory.h>
#include <stddef.h>

// iterator class

void vector_iterator_inc(void *_this)
{
    vector_iterator_base *this = _this;
    this->m_data += this->data_size;
}

void vector_iterator_dec(void *_this)
{
    vector_iterator_base *this = _this;
    this->m_data -= this->data_size;
}

bool vector_iterator_eq(void *_this, va_list *ap_p)
{
    vector_iterator_base *this = _this;

    vector_iterator_base *that = va_arg(*ap_p, vector_iterator_base *);

    return (this->m_data == that->m_data) && (this->data_size == that->data_size);
}

void *vector_iterator_data(void *_this)
{
    vector_iterator_base *this = _this;
    return this->m_data;
}

void vector_iterator_constructor(void *_this, va_list *ap_p)
{
    vector_iterator_base *this = _this;

    constructor(iterator, this, ap_p);
    this->inhert.data = vector_iterator_data;
}

void vector_iterator_destructor(void *_this)
{
    destructor(iterator, _this);
}
class vector_iterator_c = {
    .type_size = sizeof(vector_iterator_base),
    .constructor = vector_iterator_constructor,
    .destructor = vector_iterator_destructor,
    .operator_eq = vector_iterator_eq,
    .operator_inc = vector_iterator_inc,
    .operator_dec = vector_iterator_dec,
    .operator_add = iterator_operator_add,
    .operator_iadd = iterator_operator_iadd,
    .operator_min = iterator_operator_min,
    .operator_imin = iterator_operator_imin};

class *vector_iterator = &vector_iterator_c;

void *vector_begin(void *_this)
{
    vector_base *this = _this;
    vector_iterator_base *res = new (vector_iterator);
    res->data_size = this->data_size;
    res->m_data = this->m_data;
    return res;
}

void *vector_end(void *_this)
{
    vector_base *this = _this;

    vector_iterator_base *res = new (vector_iterator);

    res->m_data = this->m_data + (this->m_size * this->data_size);
    res->data_size = this->data_size;
    return res;
}

size_t vector_size(void *_this)
{
    vector_base *this = _this;
    return this->m_size;
}

size_t vector_capacity(void *_this)
{
    vector_base *this = _this;
    return this->m_capacity;
}

bool vector_empty(void *_this)
{
    vector_base *this = _this;
    return this->m_size == 0;
}

void vector_resize(void *_this, size_t new_capacity)
{
    vector_base *this = _this;

    void *new_data = malloc(new_capacity * this->data_size);
    if (new_data == NULL)
    {
        return;
    }

    memcpy(new_data, this->m_data, this->m_size * this->data_size);
    free(this->m_data);
    this->m_data = new_data;
    this->m_capacity = new_capacity;
}

void *vector_data(void *_this)
{
    vector_base *this = _this;

    return this->m_data;
}

void *vector_get_data(void *_this, size_t n)
{
    vector_base *this = _this;

    if (n > this->m_size)
    {
        return NULL;
    }

    return this->m_data + (n * this->data_size);
}

void *vector_at(void *_this, size_t n)
{
    return vector_get_data(_this, n);
}

void *vector_front(void *_this)
{
    vector_base *this = _this;
    if (this->m_size == 0)
    {
        return NULL;
    }
    return this->m_data;
}

void *vector_back(void *_this)
{
    vector_base *this = _this;
    if (this->m_size == 0)
    {
        return NULL;
    }
    return this->m_data + ((this->m_size - 1) * this->data_size);
}

void vector_clear(void *_this)
{
    vector_base *this = _this;

    this->m_size = 0;
}

void vector_push_back(void *_this, void *data_ptr)
{
    vector_base *this = _this;

    if (this->m_size >= this->m_capacity)
    {
        vector_resize(this, this->m_capacity * 1.5);
    }

    memcpy(this->m_data + this->m_size * this->data_size, data_ptr, this->data_size);
    this->m_size++;
}

void vector_push_back_const(void *_this, ...)
{
    vector_base *this = _this;

    if (this->m_size >= this->m_capacity)
    {
        vector_resize(this, this->m_capacity * 1.5);
    }

    va_list ap;
    va_start(ap, _this);

    memcpy(this->m_data + this->m_size * this->data_size, ap, this->data_size);
    this->m_size++;

    va_end(ap);
}

void vector_pop_back(void *_this)
{
    vector_base *this = _this;

    this->m_size--;
}

void vector_insert(void *_this, vector_iterator_base *position, void *data_ptr)
{
    vector_base *this = _this;

    if (this->m_size >= this->m_capacity)
    {
        vector_resize(this, this->m_capacity * 1.5);
    }

    memcpy(position->m_data + (this->data_size * 1), position->m_data, (this->m_data + this->m_size * this->data_size) - (position->m_data));

    memcpy(position->m_data, data_ptr, this->data_size);

    position->m_data += position->data_size;
    this->m_size++;
}

void vector_insert_const(void *_this, vector_iterator_base *position, ...)
{
    vector_base *this = _this;

    if (this->m_size >= this->m_capacity)
    {
        vector_resize(this, this->m_capacity * 1.5);
    }

    memcpy(position->m_data + (this->data_size * 1), position->m_data, (this->m_data + this->m_size * this->data_size) - (position->m_data));

    va_list ap;
    va_start(ap, position);

    memcpy(position->m_data, ap, this->data_size);

    position->m_data += position->data_size;

    va_end(ap);
    this->m_size++;
}

void vector_insert_range(void *_this, vector_iterator_base *position, size_t n, void *data_ptr)
{
    vector_base *this = _this;

    if (this->m_size >= this->m_capacity)
    {
        vector_resize(this, this->m_capacity * 1.5);
    }

    memcpy(position->m_data + (this->data_size * n), position->m_data, (this->m_data + this->m_size * this->data_size) - (position->m_data));

    for (size_t i = 0; i < n; i++)
    {
        memcpy(position->m_data, data_ptr, this->data_size);

        position->m_data += position->data_size;
    }

    this->m_size += n;
}

void vector_insert_range_const(void *_this, vector_iterator_base *position, size_t n, ...)
{
    vector_base *this = _this;

    if (this->m_size >= this->m_capacity)
    {
        vector_resize(this, this->m_capacity * 1.5);
    }

    memcpy(position->m_data + (this->data_size * n), position->m_data, (this->m_data + this->m_size * this->data_size) - (position->m_data));

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++)
    {
        memcpy(position->m_data, ap, this->data_size);

        position->m_data += position->data_size;
    }
    va_end(ap);
    this->m_size += n;
}

void vector_insert_iterator(void *_this, vector_iterator_base *position, void *_begin, void *_end)
{
    iterator_base *begin = _begin, *end = _end;

    iterator_base *it = copy(begin);

    for (; !eq(it, end); inc(it))
    {
        vector_insert(_this, position, it_data(it));
    }

    delete (it);
}

void vector_erase(void *_this, vector_iterator_base *position)
{
    vector_base *this = _this;

    if (this->m_size == 0)
    {
        return;
    }

    memcpy(position->m_data, position->m_data + this->data_size, (this->m_data + (this->data_size * this->m_size)) - (position->m_data + this->data_size));

    this->m_size--;
}

void vector_erase_range(void *_this, vector_iterator_base *begin, vector_iterator_base *end)
{
    vector_base *this = _this;

    if (this->m_size == 0)
    {
        return;
    }

    memcpy(begin->m_data, end->m_data, (this->m_data + (this->data_size * this->m_size)) - (end->m_data));

    this->m_size -= (end->m_data - begin->m_data) / this->data_size;
}

static const vector_base vector_template = {
    .begin = vector_begin,
    .end = vector_end,
    .size = vector_size,
    .capacity = vector_capacity,
    .empty = vector_empty,
    .resize = vector_resize,
    .data = vector_data,
    .get_data = vector_get_data,
    .at = vector_at,
    .front = vector_front,
    .back = vector_back,
    .clear = vector_clear,
    .push_back = vector_push_back,
    .push_back_const = vector_push_back_const,
    .pop_back = vector_pop_back,
    .insert = vector_insert,
    .insert_const = vector_insert_const,
    .insert_range = vector_insert_range,
    .insert_range_const = vector_insert_range_const,
    .insert_iterator = vector_insert_iterator,
    .erase = vector_erase,
    .erase_range = vector_erase_range};

void vector_constructor(void *_this, va_list *ap_p)
{
    vector_base *this = _this;

    *this = vector_template;

    this->m_capacity = 50;
    this->m_size = 0;
    this->data_size = va_arg(*ap_p, size_t);
    this->m_data = malloc(this->m_capacity * this->data_size);
}

void vector_destructor(void *_this)
{
    vector_base *this = _this;
    this->clear(this);
    free(this->m_data);
}

void vector_deep_copy(const void *_this, void *_that)
{
    const vector_base *this = _this;
    vector_base *that = _that;

    that->m_data = malloc(that->m_capacity * that->data_size);

    memcpy(that->m_data, this->m_data, that->m_capacity * that->data_size);
}

class vector_c = {
    .type_size = sizeof(vector_base),
    .constructor = vector_constructor,
    .destructor = vector_destructor,
    .deep_copy = vector_deep_copy,
    .iter = &vector_iterator_c};

class *vector = &vector_c;
