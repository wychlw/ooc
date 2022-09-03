/**
 * @file my_vector.h
 * @author lingwang (lingwang@wcysite.com)
 * @brief   The vector object in C, just most the same as in C++ STL.
 * @version 0.1
 * @date 2022-05-20
 *
 * @copyright Copyright (c) 2022 under GPL-V3
 *
 * Most usage just like the usage of the vector class in C++ STL.
 */

#ifndef _VECTOR_H
#define _VECTOR_H

#include "my_iterator.h"
#include "object.h"

/**
 * @brief class vector_iterator (the prototype of the vector_iterator)
 *
 */
extern class *vector_iterator;

struct VECTOR_BASE_T;

/**
 * @brief the base struct of the vector_iterator
 *
 * inhert iterator
 */
typedef struct VECTOR_ITERATOR_T
{
    iterator_base inhert;

    struct VECTOR_BASE_T *which_vector;
    size_t offset;
    size_t data_size;
} vector_iterator_base;

/**
 * @brief class vector (the prototype of the vector)
 *
 * @constructor
 *  @para 1 type size
 */
extern class *vector;

/**
 * @brief the base struct of the vector
 *
 * inhert vector
 */
typedef struct VECTOR_BASE_T
{
    class_base obj_base;

    void *m_data;
    size_t m_size;
    size_t m_capacity;
    size_t data_size;

    // iterators

    /**
     * @brief return the begin iterator of a vector
     * (remember to delete, or a memory leak will happen)
     *
     */
    void *(*begin)(void *_this);

    /**
     * @brief return the end iterator of a vector
     * (remember to delete, or a memory leak will happen)
     *
     */
    void *(*end)(void *_this);

    // capacity

    /**
     * @brief return how many element in side the vector
     *
     */
    size_t (*size)(void *_this);

    /**
     * @brief return how many element can fit in the vector
     *
     */
    size_t (*capacity)(void *_this);

    /**
     * @brief return is the vector is empty
     *
     */
    bool (*empty)(void *_this);

    /**
     * @brief resize the vector to a new size
     *
     */
    void (*resize)(void *_this, size_t new_capacity);

    // element access
    
    /**
     * @brief return the memory holding these data
     *
     */
    void *(*data)(void *_this);

    /**
     * @brief return the pointer of the data at the given index
     *
     */
    void *(*get_data)(void *_this, size_t n);

    /**
     * @brief return the pointer of the data at the given index
     *
     */
    void *(*at)(void *_this, size_t n);

    /**
     * @brief return the pointer of the fist element in a vector
     *
     */
    void *(*front)(void *_this);

    /**
     * @brief return the pointer of the last element in a vector
     *
     */
    void *(*back)(void *_this);

    // modifier

    /**
     * @brief erase all element in a vector
     *
     */
    void (*clear)(void *_this);

    /**
     * @brief insert a left_value element in to the back of the vector
     *
     */
    void (*push_back)(void *_this, void *data_ptr);

    /**
     * @brief insert a right_value element in to the back of the vector
     *
     */
    void (*push_back_const)(void *_this, ...);

    /**
     * @brief pop a element from the back of a vector
     *
     */
    void (*pop_back)(void *_this);

    /**
     * @brief insert a left_value element ahead of a givem position
     *
     */
    void (*insert)(void *_this, vector_iterator_base *position, void *data_ptr);

    /**
     * @brief insert a right_value element ahead of a givem position
     *
     */
    void (*insert_const)(void *_this, vector_iterator_base *position, ...);

    /**
     * @brief insert n left_value element ahead of a givem position
     *
     */
    void (*insert_range)(void *_this, vector_iterator_base *position, size_t n, void *data_ptr);

    /**
     * @brief insert n right_value element ahead of a givem position
     *
     */
    void (*insert_range_const)(void *_this, vector_iterator_base *position, size_t n, ...);

    /**
     * @brief insert elements between iterator [begin,end) ahead of a givem
     * position
     *
     */
    void (*insert_iterator)(void *_this, vector_iterator_base *position, void *_begin, void *_end);

    /**
     * @brief erase elements in a given position
     *
     */
    void (*erase)(void *_this, vector_iterator_base *position);

    /**
     * @brief erase elements between iterator [begin,end)
     *
     */
    void (*erase_range)(void *_this, vector_iterator_base *begin, vector_iterator_base *end);
} vector_base;

#endif