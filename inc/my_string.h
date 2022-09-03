/**
 * @file my_string.h
 * @author lingwang (lingwang@wcysite.com)
 * @brief   The string object in C, just most the same as in C++ STL.
 * @version 0.1
 * @date 2022-05-20
 *
 * @copyright Copyright (c) 2022 under GPL-V3
 *
 * Most usage just like the usage of the string class in C++ STL.
 */

#ifndef _STRING_H
#define _STRING_H

#include "my_iterator.h"
#include "object.h"
#include <stdio.h>

/**
 * @brief class string_iterator (the prototype of the string_iterator)
 *
 */
extern class *string_iterator;

struct STRING_BASE_T;

/**
 * @brief the base struct of the string_iterator
 *
 * inhert iterator
 */
typedef struct STRING_ITERATOR_T
{
    iterator_base inhert;

    struct STRING_BASE_T *which_string;
    size_t offset;
} string_iterator_base;

/**
 * @brief class string (the prototype of the string)
 *
 * @constructor
 *  @para 1 type size
 */
extern class *string;

/**
 * @brief the base struct of the string
 *
 * inhert string
 */
typedef struct STRING_BASE_T
{
    class_base obj_base;

    char *m_data;
    size_t m_size;
    size_t m_capacity;

    // iterators

    /**
     * @brief return the begin iterator of a string
     * (remember to delete, or a memory leak will happen)
     *
     */
    void *(*begin)(void *_this);

    /**
     * @brief return the end iterator of a string
     * (remember to delete, or a memory leak will happen)
     *
     */
    void *(*end)(void *_this);

    // capacity

    /**
     * @brief return how many element in side the string
     * not include the '\0' at the end of the str, so the real size is size+1.
     *
     */
    size_t (*size)(void *_this);

    /**
     * @brief return the length of the string
     * not include the '\0' at the end of the str, so the real size is size+1.
     *
     */
    size_t (*length)(void *_this);

    /**
     * @brief return how many element can fit in the string
     *
     */
    size_t (*capacity)(void *_this);

    /**
     * @brief return is the string is empty
     *
     */
    bool (*empty)(void *_this);

    /**
     * @brief resize the string to a new size
     *
     */
    void (*resize)(void *_this, size_t new_capacity);

    // element assess

    /**
     * @brief return the memory holding these data
     *
     */
    void *(*data)(void *_this);

    /**
     * @brief return the pointer of the character at the given index
     * Here return a pointer instead of a char is to be the same with other container.
     *
     */
    char *(*get)(void *_this, size_t n);

    /**
     * @brief return the pointer of the character at the given index
     * Here return a pointer instead of a char is to be the same with other container.
     *
     */
    char *(*at)(void *_this, size_t n);

    /**
     * @brief return the pointer of the character at fthe ront of the string
     * Here return a pointer instead of a char is to be the same with other container.
     *
     */
    char *(*front)(void *_this);

    /**
     * @brief return the pointer of the character at the end of the string
     * Here return a pointer instead of a char is to be the same with other container.
     *
     */
    char *(*back)(void *_this);

    /**
     * @brief return the char array contain the string.
     *
     */
    char *(*c_str)(void *_this);

    // modifier

    /**
     * @brief erase all element in a string
     *
     */
    void (*clear)(void *_this);

    /**
     * @brief insert a left_value char in to the back of the string
     *
     */
    void (*push_back)(void *_this, void *data_ptr);

    /**
     * @brief insert a right_value char in to the back of the string
     *
     */
    void (*push_back_const)(void *_this, ...);

    /**
     * @brief insert the whole string in to the back of the string
     *
     */
    void (*push_back_str)(void *_this, void *str);

    /**
     * @brief pop a element from the back of a string
     *
     */
    void (*pop_back)(void *_this);

    /**
     * @brief insert a left_value char ahead of a givem position
     *
     */
    void (*insert)(void *_this, string_iterator_base *position, void *data_ptr);

    /**
     * @brief insert a right_value element ahead of a givem position
     *
     */
    void (*insert_const)(void *_this, string_iterator_base *position, ...);

    /**
     * @brief insert n left_value element ahead of a givem position
     *
     */
    void (*insert_range)(void *_this, string_iterator_base *position, size_t n, void *data_ptr);

    /**
     * @brief insert n right_value element ahead of a givem position
     *
     */
    void (*insert_range_const)(void *_this, string_iterator_base *position, size_t n, ...);

    /**
     * @brief insert elements between iterator [begin,end) ahead of a givem
     * position
     *
     */
    void (*insert_iterator)(void *_this, string_iterator_base *position, void *_begin, void *_end);

    /**
     * @brief erase elements in a given position
     *
     */
    void (*erase)(void *_this, string_iterator_base *position);

    /**
     * @brief erase elements between iterator [begin,end)
     *
     */
    void (*erase_range)(void *_this, string_iterator_base *begin, string_iterator_base *end);

    // input

    /**
     * @brief read a single character from a given file.
     *
     */
    void (*fgetc)(void *_this, FILE *file);

    /**
     * @brief the same as fscanf(file,"%s",str);
     * but will automatically increase the space.
     *
     */
    void (*fscan)(void *_this, FILE *file);

    /**
     * @brief read a whole line from a given file.
     * get rid of the '\n'
     *
     */
    void (*fgets)(void *_this, FILE *file);

    /**
     * @brief read a single character from stdin.
     *
     */
    void (*getchar)(void *_this);

    /**
     * @brief the same as scanf("%s",str);
     * but will automatically increase the space.
     *
     */
    void (*scan)(void *_this);

    /**
     * @brief read a whole line from stdin.
     * get rid of the '\n'
     *
     */
    void (*getline)(void *_this);

    /**
     * @brief read a whole line from stdin in a safe way.
     * get rid of the '\n'
     *
     */
    void (*gets)(void *_this);

} string_base;

#endif