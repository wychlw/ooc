#include "my_list.h"
#include <malloc.h>
#include <memory.h>
#include <stdlib.h>

// list_node class

bool list_node_eq(void *_this, va_list *ap_p) {
  list_node_base *this = _this;
  list_node_base *that = va_arg(*ap_p, list_node_base *);

  return (this->data_ptr == that->data_ptr) &&
         (this->data_size == that->data_size);
}

void list_node_constructor(void *_this, va_list *ap_p) {
  list_node_base *this = _this;

  size_t data_size = va_arg(*ap_p, size_t);

  this->data_size = data_size;
  this->data_ptr = malloc(data_size);
}

void list_node_destructor(void *_this) {
  list_node_base *this = _this;

  free(this->data_ptr);
}

void list_node_deep_copy(const void *UNUSED(_this), void *UNUSED(_that)) {}

class list_node_c = {.type_size = sizeof(list_node_base),
                     .constructor = list_node_constructor,
                     .destructor = list_node_destructor,
                     .deep_copy = list_node_deep_copy,
                     .operator_eq = list_node_eq};

class *list_node = &list_node_c;

// list_iterator class
void list_iterator_inc(void *_this) {
  list_iterator_base *this = _this;
  this->m_node = this->m_node->nxt;
}

void list_iterator_dec(void *_this) {
  list_iterator_base *this = _this;
  this->m_node = this->m_node->prv;
}

bool list_iterator_eq(void *_this, va_list *ap_p) {
  list_iterator_base *this = _this;

  list_iterator_base *that = va_arg(*ap_p, list_iterator_base *);

  return this->m_node == that->m_node;
}

void *list_iterator_data(void *_this) {
  list_iterator_base *this = _this;
  return this->m_node->data_ptr;
}

void list_iterator_constructor(void *_this, va_list *ap_p) {
  list_iterator_base *this = _this;

  constructor(iterator, this, ap_p);
  this->inhert.data = list_iterator_data;
}

void list_iterator_destructor(void *_this) { destructor(iterator, _this); }

void list_iterator_deep_copy(const void *UNUSED(_this), void *UNUSED(_that)) {}

class list_iterator_c = {.type_size = sizeof(list_iterator_base),
                         .constructor = list_iterator_constructor,
                         .destructor = list_iterator_destructor,
                         .deep_copy = list_iterator_deep_copy,
                         .operator_eq = list_iterator_eq,
                         .operator_inc = list_iterator_inc,
                         .operator_dec = list_iterator_dec,
                         .operator_add = iterator_operator_add,
                         .operator_iadd = iterator_operator_iadd,
                         .operator_min = iterator_operator_min,
                         .operator_imin = iterator_operator_imin};

class *list_iterator = &list_iterator_c;

void *list_begin(const void *_this) {
  const list_base *this = _this;
  list_iterator_base *res = new (list_iterator);
  res->m_node = this->m_base->nxt;
  return res;
}

void *list_end(const void *_this) {
  const list_base *this = _this;

  list_iterator_base *res = new (list_iterator);

  res->m_node = this->m_base;

  return res;
}

size_t list_size(void *_this) {
  list_base *this = _this;
  return this->m_size;
}

bool list_empty(void *_this) {
  list_base *this = _this;
  return this->m_size == 0;
}

void *list_front(void *_this) {
  list_base *this = _this;
  if (this->m_size == 0) {
    return NULL;
  }
  return this->m_base->nxt->data_ptr;
}

void *list_back(void *_this) {
  list_base *this = _this;
  if (this->m_size == 0) {
    return NULL;
  }
  return this->m_base->prv->data_ptr;
}

void list_insert(void *_this, list_iterator_base *position, void *data_ptr) {
  list_base *this = _this;

  list_node_base *new_node = new (list_node, this->data_size);

  memcpy(new_node->data_ptr, data_ptr, this->data_size);

  new_node->prv = position->m_node->prv;
  new_node->nxt = position->m_node;
  position->m_node->prv = new_node;
  new_node->prv->nxt = new_node;

  this->m_size++;
}

void list_insert_const(void *_this, list_iterator_base *position, ...) {
  list_base *this = _this;

  va_list ap;
  va_start(ap, position);

  list_insert(this, position, ap);

  va_end(ap);
}

void list_insert_range(void *_this, list_iterator_base *position, size_t n,
                       void *data_ptr) {
  list_base *this = _this;

  for (size_t i = 0; i < n; i++) {
    this->insert(this, position, data_ptr);
  }
}

void list_insert_range_const(void *_this, list_iterator_base *position,
                             size_t n, ...) {
  list_base *this = _this;

  va_list ap;
  va_start(ap, n);

  void *data_ptr = ap;

  for (size_t i = 0; i < n; i++) {
    this->insert(this, position, data_ptr);
  }

  va_end(ap);
}

void list_insert_iterator(void *_this, list_iterator_base *position,
                          void *_begin, void *_end) {
  list_base *this = _this;

  iterator_base *begin = _begin, *end = _end;

  iterator_base *it = copy(begin);

  for (; !eq(it, end); inc(it)) {
    this->insert(this, position, it_data(it));
  }

  delete (it);
}

void list_erase(void *_this, list_iterator_base *position) {
  list_base *this = _this;

  if (this->m_size == 0) {
    return;
  }

  position->m_node->prv->nxt = position->m_node->nxt;
  position->m_node->nxt->prv = position->m_node->prv;

  list_node_base *rem = position->m_node;
  inc(position);
  delete (rem);

  this->m_size--;
}

void list_erase_range(void *_this, list_iterator_base *begin,
                      list_iterator_base *end) {
  list_base *this = _this;

  if (this->m_size == 0) {
    return;
  }

  list_iterator_base *it = copy(begin);

  for (; !eq(it, end);) {
    this->erase(this, it);
  }

  delete (it);
}

void list_push_front(void *_this, void *data_ptr) {
  list_base *this = _this;

  list_iterator_base *begin = this->begin(this);

  this->insert(this, begin, data_ptr);

  delete (begin);
}

void list_push_front_const(void *_this, ...) {
  list_base *this = _this;

  list_iterator_base *begin = this->begin(this);

  va_list ap;
  va_start(ap, _this);

  void *data_ptr = ap;

  this->insert(this, begin, data_ptr);

  delete (begin);

  va_end(ap);
}

void list_pop_front(void *_this) {
  list_base *this = _this;

  list_iterator_base *begin = this->begin(this);

  this->erase(this, begin);

  delete (begin);
}

void list_push_back(void *_this, void *data_ptr) {
  list_base *this = _this;

  list_iterator_base *end = this->end(this);

  this->insert(this, end, data_ptr);

  delete (end);
}

void list_push_back_const(void *_this, ...) {
  list_base *this = _this;

  list_iterator_base *end = this->end(this);

  va_list ap;
  va_start(ap, _this);

  void *data_ptr = ap;

  this->insert(this, end, data_ptr);

  delete (end);

  va_end(ap);
}

void list_pop_back(void *_this) {
  list_base *this = _this;

  list_iterator_base *end = this->end(this);

  this->erase(this, end);

  delete (end);
}

void list_clear(void *_this) {
  list_base *this = _this;
  list_iterator_base *begin = this->begin(this);
  list_iterator_base *end = this->end(this);

  this->erase_range(this, begin, end);

  delete (begin);
  delete (end);
}

static const list_base list_template = {
    .begin = list_begin,
    .end = list_end,
    .size = list_size,
    .empty = list_empty,
    .front = list_front,
    .back = list_back,
    .clear = list_clear,
    .push_front = list_push_front,
    .push_front_const = list_push_front_const,
    .pop_front = list_pop_front,
    .push_back = list_push_back,
    .push_back_const = list_push_back_const,
    .pop_back = list_pop_back,
    .insert = list_insert,
    .insert_const = list_insert_const,
    .insert_range = list_insert_range,
    .insert_range_const = list_insert_range_const,
    .insert_iterator = list_insert_iterator,
    .erase = list_erase,
    .erase_range = list_erase_range};

void list_constructor(void *_this, va_list *ap_p) {
  list_base *this = _this;

  *this = list_template;

  this->m_size = 0;
  this->data_size = va_arg(*ap_p, size_t);

  this->m_base = new (list_node, this->data_size);

  this->m_base->nxt = this->m_base;
  this->m_base->prv = this->m_base;
}

void list_destructor(void *_this) {
  list_base *this = _this;
  this->clear(this);
  delete (this->m_base);
}

void list_deep_copy(const void *_this, void *_that) {
  const list_base *this = _this;
  list_base *that = _that;

  that->m_size = 0;

  that->m_base = new (list_node, this->data_size);

  that->m_base->nxt = that->m_base;
  that->m_base->prv = that->m_base;

  list_iterator_base *begin = this->begin(this);
  list_iterator_base *end = this->end(this);

  list_iterator_base *that_begin = that->begin(that);

  that->insert_iterator(that, that_begin, begin, end);

  delete (that_begin);
  delete (begin);
  delete (end);
}

class list_c = {.type_size = sizeof(list_base),
                .constructor = list_constructor,
                .destructor = list_destructor,
                .deep_copy = list_deep_copy,
                .iter = &list_iterator_c};

class *list = &list_c;