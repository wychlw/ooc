#include "my_string.h"
#include "object.h"
#include <assert.h>
#include <malloc.h>
#include <memory.h>
#include <stddef.h>
#include <string.h>

static void copy_backward(void *_dst, const void *_src, size_t size)
{
    char *dst = _dst;
    const char *src = _src;
    for (int i = size - 1; i >= 0; i--)
    {
        *(dst + i) = *(src + i);
    }
}

void string_iterator_inc(void *_this)
{
    string_iterator_base *this = _this;
    this->offset++;
}

void string_iterator_dec(void *_this)
{
    string_iterator_base *this = _this;
    this->offset--;
}

bool string_iterator_eq(void *_this, va_list *ap_p)
{
    string_iterator_base *this = _this;

    string_iterator_base *that = va_arg(*ap_p, string_iterator_base *);

    return (this->offset == that->offset);
}

void *string_iterator_data(void *_this)
{
    string_iterator_base *this = _this;
    string_base *this2 = this->which_string;
    return this2->m_data + this->offset;
}

void string_iterator_constructor(void *_this, va_list *ap_p)
{
    string_iterator_base *this = _this;

    constructor(iterator, this, ap_p);
    this->inhert.data = string_iterator_data;
}

void string_iterator_destructor(void *_this)
{
    destructor(iterator, _this);
}

void string_iterator_deep_copy(const void *UNUSED(_this), void *UNUSED(_that))
{
}

// The capacity is add by one to fit the '\0'

class string_iterator_c = {.type_size = sizeof(string_iterator_base),
                           .constructor = string_iterator_constructor,
                           .destructor = string_iterator_destructor,
                           .deep_copy = string_iterator_deep_copy,
                           .operator_eq = string_iterator_eq,
                           .operator_inc = string_iterator_inc,
                           .operator_dec = string_iterator_dec,
                           .operator_add = iterator_operator_add,
                           .operator_iadd = iterator_operator_iadd,
                           .operator_min = iterator_operator_min,
                           .operator_imin = iterator_operator_imin};

class *string_iterator = &string_iterator_c;

void *string_begin(void *_this)
{
    string_base *this = _this;
    string_iterator_base *res = new (string_iterator);
    res->offset = 0;
    res->which_string = this;
    return res;
}

void *string_end(void *_this)
{
    string_base *this = _this;

    string_iterator_base *res = new (string_iterator);

    res->offset = this->m_size;
    res->which_string = this;
    return res;
}

size_t string_size(void *_this)
{
    string_base *this = _this;
    return this->m_size;
}

size_t string_length(void *_this)
{
    string_base *this = _this;
    return this->m_size;
}

size_t string_capacity(void *_this)
{
    string_base *this = _this;
    return this->m_capacity;
}

bool string_empty(void *_this)
{
    string_base *this = _this;
    return this->m_size == 0;
}

void string_resize(void *_this, size_t new_capacity)
{
    string_base *this = _this;

    void *new_data = malloc((new_capacity + 1) * sizeof(char));
    if (new_data == NULL)
    {
        return;
    }

    copy_backward(new_data, this->m_data, (this->m_size + 1) * sizeof(char));
    free(this->m_data);
    this->m_data = new_data;
    this->m_capacity = new_capacity;
}

void *string_data(void *_this)
{
    string_base *this = _this;

    return this->m_data;
}

char *string_get(void *_this, size_t n)
{
    string_base *this = _this;

    if (n > this->m_size)
    {
        return NULL;
    }

    return this->m_data + n;
}

char *string_at(void *_this, size_t n)
{
    return string_get(_this, n);
}

char *string_front(void *_this)
{
    string_base *this = _this;
    if (this->m_size == 0)
    {
        return NULL;
    }
    return this->m_data;
}

char *string_back(void *_this)
{
    string_base *this = _this;
    if (this->m_size == 0)
    {
        return NULL;
    }
    return this->m_data + (this->m_size - 1);
}

void string_clear(void *_this)
{
    string_base *this = _this;

    this->m_size = 0;
    (this->m_data)[0]='\n';
}

void string_push_back(void *_this, void *data_ptr)
{
    string_base *this = _this;

    if (this->m_size >= this->m_capacity)
    {
        string_resize(this, this->m_capacity * 1.5);
    }

    memcpy(this->m_data + this->m_size, data_ptr, sizeof(char));
    (this->m_data)[++this->m_size] = '\0';
}

void string_push_back_const(void *_this, ...)
{
    string_base *this = _this;

    if (this->m_size >= this->m_capacity)
    {
        string_resize(this, this->m_capacity * 1.5);
    }

    va_list ap;
    va_start(ap, _this);

    memcpy(this->m_data + this->m_size, ap, sizeof(char));
    (this->m_data)[++this->m_size] = '\0';

    va_end(ap);
}

void string_pop_back(void *_this)
{
    string_base *this = _this;

    (this->m_data)[--this->m_size] = '\0';
}

void string_insert(void *_this, string_iterator_base *position, void *data_ptr)
{
    string_base *this = _this;

    assert(position->which_string == this);

    if (this->m_size >= this->m_capacity)
    {
        string_resize(this, this->m_capacity * 1.5);
    }

    copy_backward(this->m_data + position->offset + 1, this->m_data + position->offset,
                  (this->m_data + this->m_size) - (this->m_data + position->offset));

    memcpy(this->m_data + position->offset, data_ptr, sizeof(char));

    position->offset++;
    (this->m_data)[++this->m_size] = '\0';
}

void string_insert_const(void *_this, string_iterator_base *position, ...)
{
    string_base *this = _this;

    assert(position->which_string == this);

    if (this->m_size >= this->m_capacity)
    {
        string_resize(this, this->m_capacity * 1.5);
    }

    copy_backward(this->m_data + position->offset + 1, this->m_data + position->offset,
                  (this->m_data + this->m_size) - (this->m_data + position->offset));

    va_list ap;
    va_start(ap, position);

    memcpy(this->m_data + position->offset, ap, sizeof(char));

    position->offset++;
    (this->m_data)[++this->m_size] = '\0';
}

void string_insert_range(void *_this, string_iterator_base *position, size_t n, void *data_ptr)
{
    string_base *this = _this;

    assert(position->which_string == this);

    if (this->m_size >= this->m_capacity)
    {
        string_resize(this, this->m_capacity * 1.5);
    }

    copy_backward(this->m_data + position->offset + n, this->m_data + position->offset,
                  (this->m_data + this->m_size) - (this->m_data + position->offset));

    for (size_t i = 0; i < n; i++)
    {
        memcpy(this->m_data + position->offset, data_ptr, sizeof(char));

        position->offset++;
    }

    this->m_size += n;
    (this->m_data)[this->m_size] = '\0';
}

void string_insert_range_const(void *_this, string_iterator_base *position, size_t n, ...)
{
    string_base *this = _this;

    assert(position->which_string == this);

    if (this->m_size >= this->m_capacity)
    {
        string_resize(this, this->m_capacity * 1.5);
    }

    copy_backward(this->m_data + position->offset + n, this->m_data + position->offset,
                  (this->m_data + this->m_size) - (this->m_data + position->offset));

    va_list ap;
    va_start(ap, n);

    for (size_t i = 0; i < n; i++)
    {
        memcpy(this->m_data + position->offset, ap, sizeof(char));

        position->offset++;
    }

    this->m_size += n;
    (this->m_data)[this->m_size] = '\0';
}

void string_insert_iterator(void *_this, string_iterator_base *position, void *_begin, void *_end)
{
    iterator_base *begin = _begin, *end = _end;

    iterator_base *it = copy(begin);

    for (; !eq(it, end); inc(it))
    {
        string_insert(_this, position, it_data(it));
    }

    delete (it);
}

void string_erase(void *_this, string_iterator_base *position)
{
    string_base *this = _this;

    assert(position->which_string == this);

    if (this->m_size == 0)
    {
        return;
    }

    memcpy(this->m_data + position->offset, (this->m_data + position->offset) + 1,
           (this->m_data + this->m_size) - (this->m_data + position->offset + 1));

    this->m_size--;
    (this->m_data)[--this->m_size] = '\0';
}

void string_erase_range(void *_this, string_iterator_base *begin, string_iterator_base *end)
{
    string_base *this = _this;

    assert(begin->which_string == this && end->which_string == this);

    if (this->m_size == 0)
    {
        return;
    }

    memcpy(this->m_data + begin->offset, this->m_data + end->offset,
           (this->m_data + this->m_size) - (this->m_data + end->offset));

    this->m_size -= (end->offset - begin->offset);
    (this->m_data)[this->m_size] = '\0';
}

char *string_c_str(void *_this)
{
    string_base *this = _this;
    return this->m_data;
}

void string_fgetc(void *_this, FILE *file)
{
    string_base *this = _this;
    char ch = fgetc(file);

    string_clear(this);
    if (ch != EOF)
    {
        string_push_back_const(this, ch);
    }
}

void string_fscan(void *_this, FILE *file)
{
    string_base *this = _this;

    char ch;
    this->m_size = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == ' ' || ch == '\n')
        {
            break;
        }
        string_push_back_const(this, ch);
    }
}

void string_fgets(void *_this, FILE *file)
{
    string_base *this = _this;

    char ch;
    this->m_size = 0;
    while ((ch = fgetc(file)) != EOF)
    {
        if (ch == '\n')
        {
            break;
        }
        string_push_back_const(this, ch);
    }
}

void string_getchar(void *_this)
{
    string_fgetc(_this, stdin);
}

void string_scan(void *_this)
{
    string_fscan(_this, stdin);
}

void string_getline(void *_this)
{
    string_fgets(_this, stdin);
}

void string_gets(void *_this)
{
    string_getline(_this);
}

static const string_base string_template = {.begin = string_begin,
                                            .end = string_end,
                                            .size = string_size,
                                            .length = string_length,
                                            .capacity = string_capacity,
                                            .empty = string_empty,
                                            .resize = string_resize,
                                            .data = string_data,
                                            .get = string_get,
                                            .at = string_at,
                                            .front = string_front,
                                            .back = string_back,
                                            .c_str = string_c_str,
                                            .clear = string_clear,
                                            .push_back = string_push_back,
                                            .push_back_const = string_push_back_const,
                                            .pop_back = string_pop_back,
                                            .insert = string_insert,
                                            .insert_const = string_insert_const,
                                            .insert_range = string_insert_range,
                                            .insert_range_const = string_insert_range_const,
                                            .insert_iterator = string_insert_iterator,
                                            .erase = string_erase,
                                            .erase_range = string_erase_range,
                                            .fgetc = string_fgetc,
                                            .fscan = string_fscan,
                                            .fgets = string_fgets,
                                            .getchar = string_getchar,
                                            .scan = string_scan,
                                            .getline = string_getline,
                                            .gets = string_gets};

void string_constructor(void *_this, va_list *UNUSED(ap_p))
{
    string_base *this = _this;

    *this = string_template;

    this->m_capacity = 50;
    this->m_size = 0;
    this->m_data = malloc((this->m_capacity + 1) * sizeof(char));
}

void string_destructor(void *_this)
{
    string_base *this = _this;
    this->clear(this);
    free(this->m_data);
}

void string_deep_copy(const void *_this, void *_that)
{
    const string_base *this = _this;
    string_base *that = _that;

    that->m_data = malloc((that->m_capacity + 1) * sizeof(char));

    memcpy(that->m_data, this->m_data, (that->m_capacity + 1) * sizeof(char));
}

class string_c = {.type_size = sizeof(string_base),
                  .constructor = string_constructor,
                  .destructor = string_destructor,
                  .deep_copy = string_deep_copy,
                  .iter = &string_iterator_c};

class *string = &string_c;