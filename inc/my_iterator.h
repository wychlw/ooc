/**
 * @file my_iterator.h
 * @author lingwang (lingwang@wcysite.com)
 * @brief The base file of the iterator object in ooc.
 * @version 0.1
 * @date 2022-05-20
 * 
 * @copyright Copyright (c) 2022 under GPL-V3
 * 
 * see https://blog.wcysite.com/2022/在C中面向对象-0x2-让我们来实现一个迭代器！ for more infomation
 */

#ifndef _ITERATOR_H
#define _ITERATOR_H

#include "object.h"

/**
 * @brief class iterator (the prototype of the iterator)
 * 
 */
extern class * iterator;

/**
 * @brief the base struct of the iterator
 * 
 * inhert class_base
 * need to finish data function when inhert
 * need to finish inc function when inhert
 * need to finish dec function when inhert
 */
typedef struct ITERATOR_BASE_T
{
    class_base obj_base;

    /**
     * @brief return the pointer of a data where the iterator points at.
     * 
     */
    void *(*data)(void *this);

} iterator_base;

/**
 * @brief get the pointer of a data where the iterator is point at.
 * 
 * @param _this 
 * @return void* 
 */
void *it_data(void *_this);

/**
 * @brief you shall NEVER USE THEM unless you are writting an iterator class and wants to use these prototype,
 * or, you know what you are doing.

 * see https://blog.wcysite.com/2022/在C中面向对象-0x2-让我们来实现一个迭代器！/#暴露的接口函数 for more infomation
 */
void iterator_constructor(void *UNUSED(_this), va_list *UNUSED(ap_p));
void iterator_destructor(void *UNUSED(_this));
void iterator_operator_iadd(void *_this, va_list *ap_p);
void *iterator_operator_add(void *_this, va_list *ap_p);
void iterator_operator_imin(void *_this, va_list *ap_p);
void *iterator_operator_min(void *_this, va_list *ap_p);

#endif