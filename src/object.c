#include "object.h"
#include <malloc.h>
#include <string.h>

void *new (const class *_class, ...) {

  class_base *res = malloc(_class->type_size);

  if (_class->constructor) {
    va_list ap;

    va_start(ap, _class);
    _class->constructor(res, &ap);
    va_end(ap);
  }

  res->self_class = _class;

  return res;
}

void delete (void *_this) {
  class_base *this = _this;

  if (this->self_class->destructor) {
    this->self_class->destructor(this);
  }

  free(this);
}

void *copy(const void *_this) {
  const class_base *this = _this;

  class_base *res = malloc(this->self_class->type_size);

  memcpy(res, this, this->self_class->type_size);

  this->self_class->deep_copy(this, res);

  return res;
}

void constructor(const class *_class, void *_this, va_list *ap_p) {
  class_base *this = _this;

  _class->constructor(this, ap_p);
}

void destructor(class *_class, void *_this) {
  class_base *this = _this;

  _class->destructor(this);
}

void *add(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_add) {
    return this->self_class->operator_add(_this, &ap);
  }

  va_end(ap);

  return NULL;
}

void iadd(void *_this, ...) {

  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_iadd) {
    this->self_class->operator_iadd(_this, &ap);
  }

  va_end(ap);
}

void inc(void *_this) {
  const class_base *this = _this;

  if (this->self_class->operator_inc) {
    this->self_class->operator_inc(_this);
  }
}

void *min(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_min) {
    return this->self_class->operator_min(_this, &ap);
  }

  va_end(ap);

  return NULL;
}

void imin(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_imin) {
    this->self_class->operator_imin(_this, &ap);
  }

  va_end(ap);
}

void dec(void *_this) {
  const class_base *this = _this;

  if (this->self_class->operator_dec) {
    this->self_class->operator_dec(_this);
  }
}

void *mul(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_mul) {
    return this->self_class->operator_mul(_this, &ap);
  }

  va_end(ap);

  return NULL;
}

void imul(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_imul) {
    this->self_class->operator_imul(_this, &ap);
  }

  va_end(ap);
}

void *_div(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_div) {
    return this->self_class->operator_div(_this, &ap);
  }

  va_end(ap);

  return NULL;
}

void idiv(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_idiv) {
    this->self_class->operator_idiv(_this, &ap);
  }

  va_end(ap);
}

void *lshift(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_lshift) {
    return this->self_class->operator_lshift(_this, &ap);
  }

  va_end(ap);

  return NULL;
}

void ilshift(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_ilshift) {
    this->self_class->operator_ilshift(_this, &ap);
  }

  va_end(ap);
}

void *rshift(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_rshift) {
    return this->self_class->operator_rshift(_this, &ap);
  }

  va_end(ap);

  return NULL;
}

void irshift(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_irshift) {
    this->self_class->operator_irshift(_this, &ap);
  }

  va_end(ap);
}

void * and (void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_and) {
    return this->self_class->operator_and(_this, &ap);
  }

  va_end(ap);

  return NULL;
}

void iand(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_iand) {
    this->self_class->operator_iand(_this, &ap);
  }

  va_end(ap);
}

void * or (void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_or) {
    return this->self_class->operator_or(_this, &ap);
  }

  va_end(ap);

  return NULL;
}

void ior(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_ior) {
    this->self_class->operator_ior(_this, &ap);
  }

  va_end(ap);
}

void * xor
    (void *_this, ...) {
      const class_base *this = _this;
      va_list ap;
      va_start(ap, _this);

      if (this->self_class->operator_xor) {
        return this->self_class->operator_xor(_this, &ap);
      }

      va_end(ap);

      return NULL;
    }

    void ixor(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_ixor) {
    this->self_class->operator_ixor(_this, &ap);
  }

  va_end(ap);
}

bool gt(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_gt) {
    return this->self_class->operator_gt(_this, &ap);
  }

  va_end(ap);

  return false;
}

bool eq(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_eq) {
    return this->self_class->operator_eq(_this, &ap);
  }

  va_end(ap);

  return false;
}

bool ne(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_eq) {
    return !(this->self_class->operator_eq(_this, &ap));
  }

  va_end(ap);

  return true;
}

bool ge(void *_this, ...) {

  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_gt || this->self_class->operator_eq) {
    bool gt = false, eq = false;
    if (this->self_class->operator_gt) {
      gt = this->self_class->operator_gt(_this, &ap);
    }
    if (this->self_class->operator_eq) {
      eq = this->self_class->operator_eq(_this, &ap);
    }
    return gt || eq;
  }

  va_end(ap);

  return false;
}

bool lt(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_gt || this->self_class->operator_eq) {
    bool gt = false, eq = false;
    if (this->self_class->operator_gt) {
      gt = this->self_class->operator_gt(_this, &ap);
    }
    if (this->self_class->operator_eq) {
      eq = this->self_class->operator_eq(_this, &ap);
    }
    return !(gt || eq);
  }

  va_end(ap);

  return false;
}

bool le(void *_this, ...) {
  const class_base *this = _this;
  va_list ap;
  va_start(ap, _this);

  if (this->self_class->operator_gt) {
    return !(this->self_class->operator_gt(_this, &ap));
  }

  va_end(ap);

  return false;
}

class *iter(class _class) {
  return _class.iter;
}