/**
 * @file object.h
 * @author LingWang (lingwang@wcysite.com)
 * @brief The base file for object-orinted class in C
 * @version 0.1
 * @date 2022-05-20
 * @respository https://github.com/wychlw/ooc
 * 
 * @copyright Copyright (c) 2022 under GPL-V3
 * 
 * see https://blog.wcysite.com/2022/在C中面向对象-0x1-来-注册-一个对象吧 for more infomation
 */

#ifndef _OBJECT_H
#define _OBJECT_H

#include <stddef.h>
#include <stdarg.h>
#include <stdbool.h>

/**
 * @brief define UNUSED micro for unused para
 * 
 */
#ifdef UNUSED
#elif defined(__GNUC__) || defined(MSVC) || defined(__clang__)
#define UNUSED(x) UNUSED_##x __attribute__((unused))
#elif defined(__LCLINT__)
#define UNUSED(x) (void *)(x)
#else
#define UNUSED(x)(void *)(x)
#endif

/**
 * @brief define pointer to data micro for easy to use
 * 
 */
#ifndef p2d
#define p2d ptr2data
#endif
#ifndef ptr2data
#define ptr2data(type, x) (*((type *)x))
#endif

/**
 * @brief class prototype defination, use to register a class prototype
 * 
 * see https://blog.wcysite.com/2022/在C中面向对象-0x1-来-注册-一个对象吧 for more infomation
 * 
 */
typedef struct CLASS_T
{

    const size_t type_size; // the size to store an object

    void (*constructor)(void *_this, va_list *ap_p); // the constructor of an object
    void (*destructor)(void *_this);                 // the distructoe of an object
    void (*deep_copy)(const void *_this, void *_that);    // deep copy an object

    void *(*operator_add)(void *_this, va_list *ap_p);
    void (*operator_iadd)(void *_this, va_list *ap_p);
    void (*operator_inc)(void *_this);
    void *(*operator_min)(void *_this, va_list *ap_p);
    void (*operator_imin)(void *_this, va_list *ap_p);
    void *(*operator_mul)(void *_this, va_list *ap_p);
    void (*operator_dec)(void *_this);
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
 * @brief the base of an object.
 * **PUT IT AT THE TOP OF YOUR STRUCTOR, SO CAN KNOW EXACTLY WHERE IT IS!**
 * 
 */
typedef struct CLASS_BASE_T
{
    const class *self_class;

} class_base;

/**
 * @brief call the constructor to generate an object (remember to delete!)
 * 
 * @param _class the name of the class
 * @param ... the para for the class constructor, see the class for more info!
 * @return void* the pointer of the object
 */
void *new (const class *_class, ...);

/**
 * @brief call the destructor to delete an object
 * 
 * @param this the pointer of the obj you want to delete
 */
void delete (void *this);

/**
 * @brief call the deep copy constructor to copy an object
 * 
 * @param this the pointer of the obj you want to copy
 * @return void* the new obj
 */
void *copy(const void *this);

/**
 * @brief call the constructor of the father class
 * This function should only be used in a constructor unless you know what you are doing!
 * 
 * @param _class the class of the constructor class want to call
 * @param _this this of a child obj
 * @param ap_p the pointer of the arg_list
 */
void constructor(const class *_class, void *_this, va_list *ap_p);

/**
 * @brief call the destructor of the father class
 * This function should only be used in a constructor unless you know what you are doing!
 * 
 * @param _class the class of the destructor want to call
 * @param _this this of a child obj
 */
void destructor(class *_class, void *_this);

/**
 * @brief operator+, add two obj and return a new obj
 * (remember to delete, or a memory leak will happen)
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void *add(void *_this, ...);

/**
 * @brief operator+=. add the second obj to the first obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void iadd(void *_this, ...);

/**
 * @brief operator++, add one to the obj
 * 
 * @param _this first obj, support left_value
 * @return void* 
 */
void inc(void *_this);

/**
 * @brief operator-, minus two obj and return a new obj
 * (remember to delete, or a memory leak will happen)
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void *min(void *_this, ...);

/**
 * @brief operator-=. minus the second obj to the first obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void imin(void *_this, ...);

/**
 * @brief operator--, minus one to the obj
 * 
 * @param _this first obj, support left_value
 * @return void* 
 */
void dec(void *_this);

/**
 * @brief operator*, multiply two obj and return a new obj
 * (remember to delete, or a memory leak will happen)
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void *mul(void *_this, ...);

/**
 * @brief operator*=. multiply the second obj to the first obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void imul(void *_this, ...);

/**
 * @brief operator/, divide the first obj by the second and return a new obj(due to the name issue, with a _ in front)
 * (remember to delete, or a memory leak will happen)
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void *_div(void *_this, ...);

/**
 * @brief operator//=. diide the second obj to the first obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void idiv(void *_this, ...);

/**
 * 
 @brief operator<<, lshift the first obj by the second and return a new obj
 * (remember to delete, or a memory leak will happen)
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void *lshift(void *_this, ...);

/**
 * @brief operator<<=, lshift the first obj by the second
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void ilshift(void *_this, ...);

/**
 * @brief operator>>, rshift the first obj by the second and return a new obj
 * (remember to delete, or a memory leak will happen)
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void *rshift(void *_this, ...);

/**
 * @brief operator>>=, rshift the first obj by the second
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void irshift(void *_this, ...);

/**
 * @brief operator&, and two obj and return a new obj
 * (remember to delete, or a memory leak will happen)
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void * and (void *_this, ...);

/**
 * @brief operator&=, and the second obj to the first obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void iand(void *_this, ...);

/**
 * @brief operator|, or two obj and return a new obj
 * (remember to delete, or a memory leak will happen)
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void * or (void *_this, ...);

/**
 * @brief operator|=, or the second obj to the first obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void ior(void *_this, ...);

/**
 * @brief operator^, or two obj and return a new obj
 * (remember to delete, or a memory leak will happen)
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void * xor (void *_this, ...);

/**
 * @brief operator^=, or the second obj to the first obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return void* 
 */
void ixor(void *_this, ...);

/**
 * @brief operator<, is the first obj less than the second obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return true 
 * @return false 
 */
bool lt(void *_this, ...);
#define is_less_than lt

/**
 * @brief operator<=, is the first obj less or equal than the second obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return true 
 * @return false 
 */
bool le(void *_this, ...);
#define is_less_equal le

/**
 * @brief operator=, is the first obj equal to the second obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return true 
 * @return false 
 */
bool eq(void *_this, ...);
#define is_equal eq

/**
 * @brief operator!=, is the first obj not equal to the second obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return true 
 * @return false 
 */
bool ne(void *_this, ...);
#define is_not_equal ne

/**
 * @brief operator>, is the first obj greater than the second obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return true 
 * @return false 
 */
bool gt(void *_this, ...);
#define is_greater_than gt

/**
 * @brief operator>=, is the first obj greater or equal than the second obj
 * 
 * @param _this first obj, support left_value
 * @param ... second obj, support both left_value and right_value
 * @return true 
 * @return false 
 */
bool ge(void *_this, ...);
#define is_greater_equal ge

/**
 * @brief get the iterator of a gien class
 * 
 * @param _class the name of a given class
 */
class *iter(class _class);

#endif