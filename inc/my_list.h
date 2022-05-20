/**
 * @file my_list.h
 * @author lingwang (lingwang@wcysite.com)
 * @brief   The list object in C, just most the same as in C++ STL.
 * @version 0.1
 * @date 2022-05-20
 *
 * @copyright Copyright (c) 2022 under GPL-V3
 *
 * Most usage just like the usage of the List class in C++ STL.
 */

#ifndef _LIST_H
#define _LIST_H

#include "my_iterator.h"
#include "object.h"

/**
 * @brief class list_node (the prototype of the list_node)
 *
 */
extern class *list_node;

/**
 * @brief the base struct of the list_node
 *
 * inhert class_base
 */
typedef struct LIST_NODE_BASE_T {
  class_base obj_base;
  struct LIST_NODE_BASE_T *prv, *nxt;
  void *data_ptr;
  size_t data_size;
} list_node_base;

/**
 * @brief class list_iterator (the prototype of the list_iterator)
 *
 */
extern class *list_iterator;

/**
 * @brief the base struct of the list_iterator
 *
 * inhert iterator
 */
typedef struct LIST_ITERATOR_BASE_T {
  iterator_base inhert;

  list_node_base *m_node;
} list_iterator_base;

/**
 * @brief class list (the prototype of the list)
 *
 */
extern class *list;

/**
 * @brief the base struct of the list
 *
 * inhert list
 */
typedef struct LIST_BASE_T {
  class_base obj_base;

  list_node_base *m_base;
  size_t m_size;
  size_t data_size;

  // iterators

  /**
   * @brief return the begin iterator of a list
   * (remember to delete, or a memory leak will happen)
   *
   */
  void *(*begin)(const void *_this);

  /**
   * @brief return the end iterator of a list
   * (remember to delete, or a memory leak will happen)
   *
   */
  void *(*end)(const void *_this);

  // capacity

  /**
   * @brief return how many element in side the list
   *
   */
  size_t (*size)(void *_this);

  /**
   * @brief return is the list is empty
   *
   */
  bool (*empty)(void *_this);

  // element access

  /**
   * @brief return the pointer of the fist element in a list
   *
   */
  void *(*front)(void *_this);

  /**
   * @brief return the pointer of the last element in a list
   *
   */
  void *(*back)(void *_this);

  // modifier

  /**
   * @brief erase all element in a list
   *
   */
  void (*clear)(void *_this);

  /**
   * @brief insert a left_value element ahead of a givem position
   *
   */
  void (*insert)(void *_this, list_iterator_base *position, void *data_ptr);

  /**
   * @brief insert a right_value element ahead of a givem position
   *
   */
  void (*insert_const)(void *_this, list_iterator_base *position, ...);

  /**
   * @brief insert n left_value element ahead of a givem position
   *
   */
  void (*insert_range)(void *_this, list_iterator_base *position, size_t n,
                       void *data_ptr);

  /**
   * @brief insert n right_value element ahead of a givem position
   *
   */
  void (*insert_range_const)(void *_this, list_iterator_base *position,
                             size_t n, ...);

  /**
   * @brief insert elements between iterator [begin,end) ahead of a givem
   * position
   *
   */
  void (*insert_iterator)(void *_this, list_iterator_base *position,
                          void *_begin, void *_end);

  /**
   * @brief erase elements in a given position
   *
   */
  void (*erase)(void *_this, list_iterator_base *position);

  /**
   * @brief erase elements between iterator [begin,end)
   *
   */
  void (*erase_range)(void *_this, list_iterator_base *begin,
                      list_iterator_base *end);

  /**
   * @brief push a left_value element in the front of a list
   *
   */
  void (*push_front)(void *_this, void *data_ptr);

  /**
   * @brief push a right_value element in the front of a list
   *
   */
  void (*push_front_const)(void *_this, ...);

  /**
   * @brief pop a element in the front of a list
   *
   */
  void (*pop_front)(void *_this);

  /**
   * @brief push a left_value element in the end of a list
   *
   */
  void (*push_back)(void *_this, void *data_ptr);

  /**
   * @brief push a right_value element in the end of a list
   *
   */
  void (*push_back_const)(void *_this, ...);

  /**
   * @brief pop a element in the back of a list
   *
   */
  void (*pop_back)(void *_this);
} list_base;

#endif