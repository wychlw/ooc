#pragma once

#ifndef _OBJECT_H
#define _OBJECT_H

#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

#ifdef UNUSED
#elif defined(__GNUC__) || defined(MSVC)
#define UNUSED(x) UNUSED_##x __attribute__((unused))
#elif defined(__LCLINT__)
#define UNUSED(x) (void *)(x)
#else
#deifne UNUSED(x)(void *)(x)
#endif

#ifndef p2d
#define p2d ptr2data
#endif
#ifndef ptr2data
#define ptr2data(type, x) (*((type *)x))
#endif


typedef struct CLASS_T
{

    const size_t type_size; // the size to store an object

    void (*constructor)(void *_this, va_list *ap_p); // the constructor of an object
    void (*destructor)(void *_this);                 // the distructoe of an object
    void (*deep_copy)(const void *_this, void *_that);    // deep copy an object

    void *(*operator_add)(void *_this, va_list *ap_p);
    void (*operator_iadd)(void *_this, va_list *ap_p);
    void *(*operator_min)(void *_this, va_list *ap_p);
    void (*operator_imin)(void *_this, va_list *ap_p);
    void *(*operator_mul)(void *_this, va_list *ap_p);
    void (*operator_imul)(void *_this, va_list *ap_p);
    void *(*operator_div)(void *_this, va_list *ap_p);
    void (*operator_idiv)(void *_this, va_list *ap_p);
    void *(*operator_lshift)(void *_this, va_list *ap_p);
    void *(*operator_ilshift)(void *_this, va_list *ap_p);
    void *(*operator_rshift)(void *_this, va_list *ap_p);
    void *(*operator_irshift)(void *_this, va_list *ap_p);
    void *(*operator_and)(void *_this, va_list *ap_p);
    void *(*operator_iand)(void *_this, va_list *ap_p);
    void *(*operator_or)(void *_this, va_list *ap_p);
    void *(*operator_ior)(void *_this, va_list *ap_p);
    void *(*operator_xor)(void *_this, va_list *ap_p);
    void *(*operator_ixor)(void *_this, va_list *ap_p);

    bool (*operator_gt)(void *_this, va_list *ap_p);
    bool (*operator_eq)(void *_this, va_list *ap_p);

    struct CLASS_T *iter;
} class;

/**
 * the base of an object.
 * **PUT IT AT THE TOP OF YOUR STRUCTOR, SO WE CAN KNOW EXACTLY WHERE IT IS!**
 */

typedef struct CLASS_BASE_T
{
    const class *self_class;

} class_base;

void *new (const class *_class, ...);
void delete (void *this);
void *copy(const void *this);
void constructor(const class *_class, void *_this, va_list *ap_p);
void destructor(class *_class, void *_this);

void *add(void *_this, ...);
void iadd(void *_this, ...);
void *min(void *_this, ...);
void imin(void *_this, ...);
void *mul(void *_this, ...);
void imul(void *_this, ...);
void *_div(void *_this, ...);
void idiv(void *_this, ...);
void *lshift(void *_this, ...);
void ilshift(void *_this, ...);
void *rshift(void *_this, ...);
void irshift(void *_this, ...);
void * and (void *_this, ...);
void iand(void *_this, ...);
void * or (void *_this, ...);
void ior(void *_this, ...);
void * xor (void *_this, ...);
void ixor(void *_this, ...);

bool lt(void *_this, ...);
#define is_lower_than lt
bool le(void *_this, ...);
#define is_lower_equal le
bool eq(void *_this, ...);
#define is_equal eq
bool ne(void *_this, ...);
#define is_not_equal ne
bool gt(void *_this, ...);
#define is_greater_than gt
bool ge(void *_this, ...);
#define is_greater_equal ge

class *iter(class _class);

#endif